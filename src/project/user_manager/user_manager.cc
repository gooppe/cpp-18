#include <project/user_manager/user_manager.hh>

bool User::operator==(const User &user) const
{
    return this->id == user.id;
}

size_t std::hash<User>::operator()(const User &user) const
{
    return hash<unsigned int>()(user.id);
}

bool std::equal_to<User>::operator()(const User &lhs, const User &rhs) const
{
    return lhs == rhs;
}

size_t std::hash<UserGroup>::operator()(const UserGroup &group) const
{
    return hash<unsigned int>()(group.id);
}

size_t binary_size_traits<User>::size(const User &user)
{
    return sizeof(user.id) + user.firstname.size() + user.lastname.size();
}

size_t binary_size_traits<UserGroup>::size(const UserGroup &group)
{
    size_t users_size = 0;
    for (auto user : group.users)
        users_size += binary_size_traits<User>::size(user);
    return sizeof(group.id) + group.name.size() + users_size;
}