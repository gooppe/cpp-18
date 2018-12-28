#include <project/message/message.cc>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Run message sample..." << std::endl;
    message(std::cout, "This is formatting %. pi=%; year=%; Use '%%' character to encode pattern.\n", "example", 3.14, 2018);

    std::cout << "Done." << std::endl;
    return 0;
}
