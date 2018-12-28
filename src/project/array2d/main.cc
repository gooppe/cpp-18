#include <project/array2d/array2d.cc>

int main(int argc, char const *argv[])
{
    std::cout << "Run array2d sample..." << std::endl;

    auto x = Array2d<int>(1, 3, {1, 2, 3});
    std::cout << x;
    auto y = Array2d<int>(7, 4, 42);
    std::cout << y;
    auto z = Array2d<int>(5, 5, 7);
    std::cout << z;

    std::cout << "Done." << std::endl;

    return 0;
}
