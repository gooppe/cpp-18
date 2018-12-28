#include <gtest/gtest.h>
#include <project/line_number_buffer/line_number_buffer.hh>
#include <string>
#include <sstream>

struct line_number_buffer_param
{
    std::string text;
    std::string formated_text;
};

class line_number_buffer_test : public ::testing::TestWithParam<line_number_buffer_param>
{
};

TEST_P(line_number_buffer_test, _)
{
    const line_number_buffer_param &param = GetParam();
    std::stringstream test_str;
    std::ostream test_stream(test_str.rdbuf());
    LineNumberBuffer test_buffer(test_stream.rdbuf());
    test_stream.rdbuf(&test_buffer);
    test_stream << param.text;
    EXPECT_EQ(param.formated_text, test_str.str());
}

INSTANTIATE_TEST_CASE_P(
    _,
    line_number_buffer_test,
    ::testing::Values(
        line_number_buffer_param{"abc", "1 abc\n"},
        line_number_buffer_param{"\n\n\n", "1 \n2 \n3 \n"},
        line_number_buffer_param{"", ""}));