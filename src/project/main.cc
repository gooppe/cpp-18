#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include "message.cc"
#include "vector.cc"

void vector_sample();

int main()
{
    std::cout << "Hello, world!" << std::endl;
    std::cout << "There are tasks solutions for cpp course." << std::endl;
    std::cout << std::string(42, '=') << std::endl;

    std::cout << "[1] Run vector sample..." << std::endl;
    vector_sample();
    std::cout << "[1] Run message sample..." << std::endl;
    message(std::cout, "% % % %", 1, 2, 3, 4);

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