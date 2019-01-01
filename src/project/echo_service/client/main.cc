#include <project/echo_service/client/client.hh>

int main(int argc, char const *argv[])
{
    Client client;
    std::string message;
    char response[256];

    while (true)
    {
        std::cout << "Enter message: ";
        std::cin >> message;

        client.send_message(message.c_str(), message.length());
        if (client.read_message(response, 256))
            std::cout << "Echo server: " << response << std::endl;
        else
            break;
    }

    return 0;
}
