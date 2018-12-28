#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <vector>
#include "project/ostream_iterator/custom_ostream_iterator.cc"

struct ostream_iter_param
{
    size_t n;
    std::vector<int> input;
    std::string expexted;
};

class ostream_iter_test : public ::testing::TestWithParam<ostream_iter_param>
{
};

TEST_P(ostream_iter_test, _)
{
    const ostream_iter_param &param = GetParam();

    std::stringstream string_stream;
    auto test_iterator = ostream_iterator<int>(string_stream, param.n);
    std::copy(param.input.begin(), param.input.end(), test_iterator);
    EXPECT_EQ(param.expexted, string_stream.str());
}

INSTANTIATE_TEST_CASE_P(
    _,
    ostream_iter_test,
    ::testing::Values(
        ostream_iter_param{
            1,
            {1, 2, 3, 4, 5, 6, 7},
            "1234567"},
        ostream_iter_param{
            1,
            {},
            ""},
        ostream_iter_param{
            2,
            {1, 2, 3, 4, 5, 6, 7},
            "246"},
        ostream_iter_param{
            3,
            {1, 2, 3},
            "3"},
        ostream_iter_param{
            3,
            {1, 2},
            ""}));