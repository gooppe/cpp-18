#include <project/echo_service/server/server.hh>

EchoServer::~EchoServer()
{
    close(this->conn_fd);
}

void EchoServer::run(uint host, uint port)
{
    this->conn_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->conn_fd == -1)
        handle_error("Couldn't create socket");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(host);
    addr.sin_port = htons(port);

    if (bind(this->conn_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        handle_error("Couldn't bind socket");

    if (listen(this->conn_fd, SOMAXCONN) == -1)
        handle_error("Couldn't listen clients");

    std::cout << "Start listening clients" << std::endl;

    while (true)
    {
        sockaddr_in cl_addr{};
        socklen_t cl_addr_size = sizeof(struct sockaddr_in);

        int client_fd = accept(conn_fd, (struct sockaddr *)&cl_addr, &cl_addr_size);
        if (client_fd == -1)
            handle_error("Client accepting error");

        std::cout << "Client " << inet_ntoa(cl_addr.sin_addr) << " connected" << std::endl;
        pid_t pid = fork();
        if (pid == 0)
        {
            while (echo(client_fd))
                ;
            shutdown(client_fd, SHUT_RDWR);
            close(client_fd);
            std::cout << "Client " << inet_ntoa(cl_addr.sin_addr) << " disconnected" << std::endl;
            exit(0);
        }
    }
}

bool echo(int client_fd)
{
    char buffer[256];
    if (receive(client_fd, buffer, 256))
    {
        send(client_fd, buffer, 256);
        std::cout << "Send echo: " << buffer << std::endl;
        return true;
    }
    return false;
}

bool send(int trg_fd, const char *buffer, ssize_t buffer_size)
{
    ssize_t nwritten = 0;
    while (nwritten != buffer_size)
    {
        ssize_t nbytes = write(trg_fd, buffer + nwritten, buffer_size - nwritten);
        if (nbytes == -1)
        {
            perror("Couldn't write message");
            return false;
        }
        nwritten += nbytes;
    }
    return true;
}

bool receive(int trg_fd, char *buffer, ssize_t buffer_size)
{
    bzero(buffer, buffer_size);
    int n = read(trg_fd, buffer, buffer_size - 1);
    if (n == -1)
    {
        perror("Couldn't read message");
        return false;
    }
    return n;
}

NonBlockingEchoServer::~NonBlockingEchoServer()
{
    close(this->conn_fd);
}

void NonBlockingEchoServer::run(uint host, uint port)
{
    this->conn_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (this->conn_fd == -1)
        handle_error("Couldn't create socket");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(host);
    addr.sin_port = htons(port);

    if (bind(this->conn_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        handle_error("Couldn't bind socket");

    if (listen(this->conn_fd, SOMAXCONN) == -1)
        handle_error("Couldn't listen clients");

    std::cout << "Start listening clients" << std::endl;

    struct epoll_event ev, events[MAX_EVENTS];
    int nfds;
    int epollfd = epoll_create1(0);
    if (epollfd == -1)
        handle_error("epollc_reate1");

    ev.events = EPOLLIN;
    ev.data.fd = this->conn_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, this->conn_fd, &ev) == -1)
        handle_error("epoll_ctl: listen_sock");

    while (true)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
            handle_error("epoll_wait");

        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == this->conn_fd)
            {
                sockaddr_in cl_addr{};
                socklen_t cl_addr_size = sizeof(struct sockaddr_in);

                int client_fd = accept4(this->conn_fd, (struct sockaddr *)&cl_addr, &cl_addr_size, SOCK_NONBLOCK);
                if (client_fd == -1)
                    handle_error("Client accepting error");

                std::cout << "Client " << inet_ntoa(cl_addr.sin_addr) << " connected" << std::endl;

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = client_fd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_fd, &ev) == -1)
                    handle_error("epoll_ctl: client_fd");
            }
            else
            {
                if (!echo(events[n].data.fd))
                {
                    shutdown(events[n].data.fd, SHUT_RDWR);
                    close(events[n].data.fd);
                    std::cout << "Client disconnected" << std::endl;
                }
            }
        }
    }
}
