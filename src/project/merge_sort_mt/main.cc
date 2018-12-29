#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <project/merge_sort_mt/merge_sort_mt.cc>

int main(int argc, char const *argv[])
{
    std::cout << "Run merge sort mt benchmark..." << std::endl;

    auto file = std::ofstream("./sort_comp.csv");
    for (uint power = 0; power < 7; power++)
    {
        uint64_t size = (uint64_t)pow(10, power);
        file << size << ", ";
        std::cout << size << ", ";

        std::vector<void (*)(std::vector<int>::iterator, std::vector<int>::iterator)> test_funcs = {merge_sort, merge_sort_mt};

        for (auto &func : test_funcs)
        {
            std::vector<int> numbers(size);
            std::generate(numbers.begin(), numbers.end(), std::rand);
            auto start_time = std::chrono::system_clock::now();
            func(numbers.begin(), numbers.end());
            auto end_time = std::chrono::system_clock::now();
            file << (end_time - start_time).count() << ", ";
            std::cout << (end_time - start_time).count() << ", ";
        }
        file << std::endl;
        std::cout << std::endl;
    }
    file.close();

    std::cout << "Done." << std::endl;
    return 0;
}
