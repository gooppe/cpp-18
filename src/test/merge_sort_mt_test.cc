#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <functional>
#include "project/merge_sort_mt.hh"

struct merge_sort_param
{
    std::vector<int> input;
};

class merge_sort_test : public ::testing::TestWithParam<merge_sort_param>
{
};

TEST_P(merge_sort_test, _)
{
    const merge_sort_param &param = GetParam();
    auto comp = std::less<int>();
    std::vector<int> test_vector = param.input;
    std::vector<int> golden_vector = param.input;
    merge_sort_mt(test_vector.begin(), test_vector.end(), comp);
    std::sort(golden_vector.begin(), golden_vector.end(), comp);
    EXPECT_EQ(golden_vector, test_vector);
}

INSTANTIATE_TEST_CASE_P(
    _,
    merge_sort_test,
    ::testing::Values(
        merge_sort_param{
            {},
        },
        merge_sort_param{
            {1},
        },
        merge_sort_param{
            {1, 2},
        },
        merge_sort_param{
            {2, 1},
        },
        merge_sort_param{
            {2, 2},
        },
        merge_sort_param{
            {2, 2, -1000, 3},
        },
        merge_sort_param{
            {1, 2, 3, 4, 5, 6, 7},
        },
        merge_sort_param{
            {7, 6, 5, 4, 3, 2, 1},
        },
        merge_sort_param{
            {1, 4, 5, 2, 7, 3, 6},
        },
        merge_sort_param{
            {42, 3, 3, 2, 2, 1, 1},
        }));