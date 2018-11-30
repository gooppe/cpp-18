#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include <chrono>
#include "message.cc"
#include "vector.cc"
#include "ostream_guard.cc"
#include "array2d.cc"
#include "custom_ostream_iterator.cc"
#include "user_manager.cc"
#include "merge_sort_mt.cc"

void vector_sample();
void ostream_flag_sample();
void array2d_sample();
void iterator_sample();
void merge_sort_sample();
void user_manager_sample();
void merge_sort_mt_sample();
void sort_benchmark();

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
    std::cout << "[5] Run custom iterator sample..." << std::endl;
    iterator_sample();
    std::cout << "[6] Run merge sort sample..." << std::endl;
    merge_sort_sample();
    std::cout << "[7] Run user manager sample..." << std::endl;
    user_manager_sample();
    std::cout << "[8] Run merge sort benchmark..." << std::endl;
    sort_benchmark();

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

void iterator_sample()
{
    auto out_iter = ostream_iterator<int>(std::cout, ", ", 2);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    std::copy(values.begin(), values.end(), out_iter);
    std::cout << std::endl;
}

void merge_sort_sample()
{
    auto x = std::vector<int>({42, 3, 3, 2, 2, 1, 1});
    merge_sort(x.begin(), x.end());

    for (auto v : x)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

void user_manager_sample()
{
    auto user = User(0, "Ivan", "Ivanov");
    auto group = UserGroup(0, "Students", std::unordered_set<User>({user}));
    auto usersize = binary_size_traits<User>::size(user);
    auto groupsize = binary_size_traits<UserGroup>::size(group);
    message(std::cout, "Created user \'% %\' in group \'%\'.\nUser data size: % byte. Group data size: % byte.\n",
            user.firstname, user.lastname, group.name, usersize, groupsize);
}

void sort_benchmark()
{
    auto file = std::ofstream("./sort_comp.csv");
    for (uint power = 0; power < 7; power++)
    {
        uint64_t size = (uint64_t)pow10l(power);
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
}