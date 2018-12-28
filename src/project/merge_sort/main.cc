#include <project/merge_sort/merge_sort.cc>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Run merge sort sample..." << std::endl;

    auto x = std::vector<int>({42, 3, 3, 2, 2, 1, 1});
    merge_sort(x.begin(), x.end());

    for (auto v : x)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Done." << std::endl;
    return 0;
}
