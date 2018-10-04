#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include "message.cc"
#include "vector.cc"
#include "ostream_guard.cc"
#include "array2d.cc"

void vector_sample();
void ostream_flag_sample();
void array2d_sample();

int main()
{
    std::cout << "Hello, world!" << std::endl;
    std::cout << "There are tasks solutions for cpp course." << std::endl;
    std::cout << std::string(42, '=') << std::endl;

    std::cout << "[1] Run vector sample..." << std::endl;
    vector_sample();
    std::cout << "[2] Run message sample..." << std::endl;
    message(std::cout, "This is formatting %. pi=%; year=%; Use '%%' character to encode pattern.\n", "example", 3.14, 2018);
    std::cout << "[3] Run guard sample..." << std::endl;
    ostream_flag_sample();
    std::cout << "[4] Run array2d sample..." << std::endl;
    array2d_sample();

    std::cout << std::string(42, '=') << std::endl;
    std::cout << "Running all examples completed." << std::endl;
    std::cout << "Sometimes some experiments available in tests." << std::endl;

    return 0;
}

void vector_sample()
{
    Vector<std::ofstream> v = Vector<std::ofstream>();

    mkdir("data", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    v.push_back(std::ofstream("./data/a.txt"));
    v.push_back(std::ofstream("./data/b.txt"));
    v.push_back(std::ofstream("./data/c.txt"));

    std::shuffle(v.begin(), v.end(), std::random_device());

    int idx = 0;
    for (auto &f : v)
    {
        f << idx++;
        f.close();
    }
}

void ostream_flag_sample()
{
    ostream_guard g(std::cout);
    std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cout.width(10);
    std::cout.fill('$');
    std::cout << 100 << std::endl;
}

void array2d_sample()
{
    auto x = Array2d<int>(1, 3, {1, 2, 3});
    std::cout << x;
    auto y = Array2d<int>(7, 4, 42);
    std::cout << y;
    auto z = Array2d<int>(5, 5, 7);
    std::cout << z;
}