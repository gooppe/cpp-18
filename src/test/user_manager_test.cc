#include <gtest/gtest.h>
#include "project/user_manager.hh"
#include <string>
#include <sstream>

TEST(UserManagerTest, UserHashTest)
{
    auto testUser = User(1, "FirstName", "LastName");
    EXPECT_EQ(1, std::hash<User>()(testUser));
}

TEST(UserManagerTest, UserEqualTest)
{
    auto firstUser = User(1, "FirstName", "LastName");
    auto secondUser = User(firstUser);

    EXPECT_TRUE(std::equal_to<User>()(firstUser, secondUser));
}

TEST(UserManagerTest, GroupHashTest)
{
    auto testUser = User(1, "FirstName", "LastName");
    auto testGroup = UserGroup(1, "Students", std::unordered_set<User>({testUser}));
    EXPECT_EQ(1, std::hash<UserGroup>()(testGroup));
}

TEST(UserManagerTest, UserSizeTest)
{
    auto testUser = User(1, "F", "L");
    EXPECT_EQ(6, binary_size_traits<User>::size(testUser));
}

TEST(UserManagerTest, GroupSizeTest)
{
    auto testUser = User(1, "FirstName", "LastName");
    auto testGroup = UserGroup(1, "Students", std::unordered_set<User>({testUser}));
    EXPECT_EQ(33, binary_size_traits<UserGroup>::size(testGroup));
}