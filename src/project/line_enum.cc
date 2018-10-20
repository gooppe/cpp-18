#include <iostream>
#include "line_number_buffer.hh"

int main(int argc, char const *argv[])
{
    StreamBuffGuard guard(std::cout);

    LineNumberBuffer buff(std::cout.rdbuf());
    std::cout.rdbuf(&buff);

    // std::cout << std::string(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

    std::cout << std::cin.rdbuf();

    return 0;
}
