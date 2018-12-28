#include <project/vector/vector.cc>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Run vector sample..." << std::endl;

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

    std::cout << "Done." << std::endl;

    return 0;
}
