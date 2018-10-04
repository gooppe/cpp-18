#include <gtest/gtest.h>
#include <project/array2d.cc>

struct simple3x3_array_test : public ::testing::Test
{
    Array2d<int> test_array;
    Array2d<int> op_array;

    simple3x3_array_test() : test_array(3, 3, 42), op_array(3, 3, 2) {}
};

struct masked3x3_array_test : public ::testing::Test
{
    Array2d<int> test_array;
    Array2d<int> op_array;

    masked3x3_array_test() : test_array(3, 3), op_array(3, 3, 42) {}

    void SetUp()
    {
        test_array = Array2d<int>(3, 3, {1, 2, 3, 3, 2, 1, 42, 42, 42});
    }
};

struct array2d_param
{
    Array2d<int> test;
    Array2d<int> expected;
};

struct array2d_comp_param
{
    Array2d<bool> test;
    Array2d<bool> expected;
};

class array2d_init_test : public ::testing::TestWithParam<array2d_param>
{
};

class array2d_comp_test : public ::testing::TestWithParam<array2d_comp_param>
{
};

INSTANTIATE_TEST_CASE_P(
    _,
    array2d_init_test,
    ::testing::Values(
        array2d_param{
            Array2d<int>(1, 1, 1),
            Array2d<int>(1, 1, {1})},

        array2d_param{
            Array2d<int>(3, 3, 7),
            Array2d<int>(3, 3, {7, 7, 7, 7, 7, 7, 7, 7, 7})},

        array2d_param{
            Array2d<int>(Array2d<int>(1, 1, 7)),
            Array2d<int>(1, 1, {7})},

        array2d_param{
            Array2d<int>(2, 2, 7) + Array2d<int>(2, 2, 7),
            Array2d<int>(2, 2, 14)},

        array2d_param{
            Array2d<int>(2, 2, 7) - Array2d<int>(2, 2, 7),
            Array2d<int>(2, 2, 0)},

        array2d_param{
            Array2d<int>(2, 2, 7) * Array2d<int>(2, 2, 7),
            Array2d<int>(2, 2, 49)},

        array2d_param{
            Array2d<int>(2, 2, 7) / Array2d<int>(2, 2, 7),
            Array2d<int>(2, 2, 1)}));

INSTANTIATE_TEST_CASE_P(
    _,
    array2d_comp_test,
    ::testing::Values(
        array2d_comp_param{
            (Array2d<int>(2, 2, 7) == Array2d<int>(2, 2, 42)),
            Array2d<bool>(2, 2, false)},

        array2d_comp_param{
            Array2d<int>(2, 2, 7) != Array2d<int>(2, 2, 42),
            Array2d<bool>(2, 2, true)},

        array2d_comp_param{
            Array2d<int>(2, 2, 7) <= Array2d<int>(2, 2, 42),
            Array2d<bool>(2, 2, true)},

        array2d_comp_param{
            Array2d<int>(2, 2, 7) >= Array2d<int>(2, 2, 42),
            Array2d<bool>(2, 2, false)}));

TEST_P(array2d_init_test, _)
{
    const array2d_param &param = GetParam();
    EXPECT_TRUE(Array2d<int>::equal(param.expected, param.test));
}

TEST_P(array2d_comp_test, _)
{
    const array2d_comp_param &param = GetParam();
    EXPECT_TRUE(Array2d<bool>::equal(param.expected, param.test));
}

TEST_F(simple3x3_array_test, UnsafeGettingTest)
{
    EXPECT_EQ(42, test_array(0, 0));
    EXPECT_EQ(42, test_array(2, 2));
    EXPECT_NO_THROW(test_array(3, 4));
}

TEST_F(simple3x3_array_test, UnsafeSettingTest)
{
    test_array(1, 1) = 7;
    EXPECT_EQ(7, test_array(1, 1));
    test_array(1, 1) = 42;
    EXPECT_EQ(42, test_array(1, 1));
}

TEST_F(simple3x3_array_test, SafeGettingTest)
{
    EXPECT_EQ(42, test_array.at(0, 0));
    EXPECT_EQ(42, test_array.at(2, 2));
    EXPECT_THROW(test_array.at(3, 4), std::out_of_range);
}

TEST_F(simple3x3_array_test, SafeSettingTest)
{
    test_array.at(1, 1) = 7;
    EXPECT_EQ(7, test_array.at(1, 1));
    test_array.at(1, 1) = 42;
    EXPECT_EQ(42, test_array.at(1, 1));
    EXPECT_THROW(test_array.at(3, 4), std::out_of_range);
}

TEST_F(simple3x3_array_test, CopyTest)
{
    auto copy_array = Array2d<int>(test_array);
    EXPECT_EQ(42, copy_array(0, 0));
    EXPECT_EQ(42, copy_array(2, 2));
}

TEST_F(simple3x3_array_test, EquateCopyTest)
{
    auto copy_array = Array2d<int>(3, 3, 7);
    copy_array = test_array;
    EXPECT_THROW(copy_array = Array2d<int>(1, 1), std::length_error);
    EXPECT_EQ(42, copy_array(0, 0));
    EXPECT_EQ(42, copy_array(2, 2));
}

TEST_F(masked3x3_array_test, BuildMaskTest)
{
    auto mask = test_array == op_array;
    auto masked_array = test_array(mask);
    auto filled_array = masked_array = 7;

    EXPECT_TRUE(filled_array.equal(Array2d<int>(3, 3, {1, 2, 3, 3, 2, 1, 7, 7, 7})));
}