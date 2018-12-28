#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <unordered_set>

struct User
{
  const unsigned int id;
  std::string firstname;
  std::string lastname;

  User(const unsigned int id, std::string firstname, std::string lastname) : id(id), firstname(firstname), lastname(lastname) {}
  bool operator==(const User &user) const;
};

namespace std
{

template <>
class hash<User>
{
public:
  size_t operator()(const User &user) const;
};

template <>
class equal_to<User>
{
public:
  bool operator()(const User &lhs, const User &rhs) const;
};
} // namespace std

struct UserGroup
{
  const unsigned int id;
  std::string name;
  std::unordered_set<User> users;

  UserGroup(const unsigned int id, std::string name) : id(id), name(name) {}
  UserGroup(const unsigned int id, std::string name, std::unordered_set<User> users) : id(id), name(name), users(users) {}
};

namespace std
{

template <>
class hash<UserGroup>
{
public:
  size_t operator()(const UserGroup &group) const;
};

} // namespace std

template <class T>
struct binary_size_traits;

template <>
class binary_size_traits<User>
{
public:
  static size_t size(const User &user);
};

template <>
class binary_size_traits<UserGroup>
{
public:
  static size_t size(const UserGroup &group);
};

#endif