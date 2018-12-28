#include <project/ostream_guard/ostream_guard.hh>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Run guard sample..." << std::endl;

    ostream_guard g(std::cout);
    std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cout.width(10);
    std::cout.fill('$');
    std::cout << 100 << std::endl;

    std::cout << "Done." << std::endl;

    return 0;
}
