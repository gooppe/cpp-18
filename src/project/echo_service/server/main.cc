#include <project/echo_service/server/server.hh>

int main(int argc, char const *argv[])
{
    if (argc == 3)
        NonBlockingEchoServer().run(INADDR_LOOPBACK, atoi(argv[1]));
    else if (argc == 2)
        EchoServer().run(INADDR_LOOPBACK, atoi(argv[1]));
    else
        std::cout << "Enter port" << std::endl;
    return 0;
}
