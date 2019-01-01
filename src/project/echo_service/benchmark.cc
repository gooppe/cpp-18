#include <project/echo_service/client/client.hh>
#include <project/echo_service/server/server.hh>
#include <chrono>
#include <fstream>
#include <math.h>
#include <thread>

void echo_test(uint port, uint client_number)
{
    std::string msg = "Hello, Server!";
    char response[256];
    for (uint cl = 0; cl < client_number; cl++)
    {
        Client client(INADDR_LOOPBACK, port);
        client.send_message(msg.c_str(), msg.length());
        client.read_message(response, 256);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<uint> ports = {42421, 42422};

    std::cout << "Run echo server benchmark..." << std::endl;

    auto file = std::ofstream("./server_comp.csv");
    for (uint clients : {100, 200, 300})
    {
        file << clients << ", ";
        for (uint port : ports)
        {
            std::cout << clients << ", ";

            auto start_time = std::chrono::system_clock::now();
            echo_test(port, clients);
            auto end_time = std::chrono::system_clock::now();

            std::chrono::duration<double> diff = end_time - start_time;
            file << (int)(clients / diff.count()) << ", ";
            std::cout << (int)(clients / diff.count()) << ", ";
        }

        file << std::endl;
        std::cout << std::endl;
    }
    file.close();

    // std::terminate();

    std::cout << "Done." << std::endl;
    return 0;
}
