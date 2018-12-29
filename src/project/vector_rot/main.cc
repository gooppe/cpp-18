#include <iostream>
#include <project/vector_rot/vector_rot.hh>

int main(int argc, char const *argv[])
{
    std::cout << "Run vector rotate sample..." << std::endl;
    Vector2d v = Vector2d(1, 0);
    std::cout << v << std::endl;
    v.rotate_multiple_90(1);
    std::cout << v << std::endl;
    std::cout << "Done." << std::endl;
    return 0;
}
