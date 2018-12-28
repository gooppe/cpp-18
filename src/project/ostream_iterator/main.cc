#include <project/ostream_iterator/custom_ostream_iterator.cc>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::cout << "Run custom iterator sample..." << std::endl;

    auto out_iter = ostream_iterator<int>(std::cout, ", ", 2);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    std::copy(values.begin(), values.end(), out_iter);
    std::cout << std::endl;

    std::cout << "Done." << std::endl;
    return 0;
}
