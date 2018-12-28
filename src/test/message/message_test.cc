#include <gtest/gtest.h>
#include <project/message/message.cc>
#include <string>
#include <sstream>

TEST(MessageTest, FormatTest)
{
    auto pattern = "Test %; % % %%";
    std::stringstream test_str;
    message(test_str, pattern, "example", 1, 3.14);

    EXPECT_TRUE(std::string("Test example; 1 3.14 %") == test_str.str());
}

TEST(MessageTest, ToMuchArgsTest)
{
    auto pattern = "Test %; % % %%";
    std::stringstream test_str;
    message(test_str, pattern, "example", 1, 3.14, 13, 14);

    EXPECT_TRUE(std::string("Test example; 1 3.14 %") == test_str.str());
}

TEST(MessageTest, NotEnoughArgsTest)
{
    auto pattern = "Test %; % % %%";
    std::stringstream test_str;

    EXPECT_THROW(message(test_str, pattern, "example"), std::invalid_argument);
}