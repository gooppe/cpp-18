#include <project/user_manager/user_manager.hh>
#include <project/message/message.cc>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Run user manager sample..." << std::endl;

    auto user = User(0, "Ivan", "Ivanov");
    auto group = UserGroup(0, "Students", std::unordered_set<User>({user}));
    auto usersize = binary_size_traits<User>::size(user);
    auto groupsize = binary_size_traits<UserGroup>::size(group);
    message(std::cout, "Created user \'% %\' in group \'%\'.\nUser data size: % byte. Group data size: % byte.\n",
            user.firstname, user.lastname, group.name, usersize, groupsize);

    std::cout << "Done." << std::endl;
    return 0;
}
