#include <project/echo_service/client/client.hh>

Client::Client(uint host, uint port)
{
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd == -1)
        handle_error("Couldn't create socket");

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(host);
    server_addr.sin_port = htons(port);

    sockaddr_in client_addr{};
    if (bind(this->fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
        handle_error("Couldn't bind socket");

    if (connect(this->fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        handle_error("Couldn't connect to server");
}
Client::~Client()
{
    this->disconnect();
}

void Client::disconnect()
{
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
    std::cout << "Disconnected." << std::endl;
}

bool Client::send_message(const char *buffer, ssize_t buffer_size)
{
    ssize_t nwritten = 0;
    while (nwritten != buffer_size)
    {
        ssize_t nbytes = write(this->fd, buffer + nwritten, buffer_size - nwritten);
        if (nbytes == -1)
        {
            perror("Couldn't write message");
            return false;
        }
        nwritten += nbytes;
    }
    return true;
}

bool Client::read_message(char *buffer, ssize_t buffer_size)
{
    bzero(buffer, buffer_size);
    int n = read(this->fd, buffer, buffer_size);
    if (n == -1)
    {
        perror("Couldn't read message");
        return false;
    }
    return true;
}