#include <gtest/gtest.h>
#include <project/vector/vector.cc>
#include <vector>
#include <fstream>
#include <algorithm>

TEST(VectorTest, SizeTest)
{
    auto test_vector = Vector<int>({1, 2, 3, 4, 5, 6, 7});
    auto empty_vector = Vector<int>();

    EXPECT_EQ(0, empty_vector.size());
    EXPECT_EQ(7, test_vector.size());
    EXPECT_GE(test_vector.capacity(), test_vector.size());
}

TEST(VectorTest, PushCopyTest)
{
    auto test_vector = Vector<int>();
    int x = 42;
    test_vector.push_back(x);
    EXPECT_EQ(x, test_vector[0]);
    EXPECT_EQ(42, x);
    EXPECT_EQ(1, test_vector.size());
}

TEST(VectorTest, PushMoveTest)
{
    auto test_vector = Vector<int>();
    test_vector.push_back(42);
    EXPECT_EQ(42, test_vector[0]);
    EXPECT_EQ(1, test_vector.size());
}

TEST(VectorTest, PopTest)
{
    auto test_vector = Vector<int>();
    test_vector.push_back(42);
    test_vector.pop_back();
    EXPECT_EQ(0, test_vector.size());
}

TEST(VectorTest, AtTest)
{
    auto test_vector = Vector<int>({1, 2, 3});
    EXPECT_EQ(1, test_vector.at(0));
    EXPECT_EQ(2, test_vector.at(1));
    EXPECT_EQ(3, test_vector.at(2));
    EXPECT_THROW(test_vector.at(3), std::out_of_range);
}

TEST(VectorTest, EraseTest)
{
    auto test_vector = Vector<int>({1, 2, 3, 4, 5});
    test_vector.erase(test_vector.begin() + 1);
    EXPECT_EQ(4, test_vector.size());
    test_vector.erase(test_vector.begin() + 1, test_vector.begin() + 3);
    EXPECT_EQ(2, test_vector.size());
    EXPECT_EQ(1, test_vector.at(0));
    EXPECT_EQ(5, test_vector.at(1));
}

TEST(VectorTest, ShuffleTest)
{
    unsigned seed = 42;

    auto test_vector = Vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    auto trusted_vector = std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    std::shuffle(test_vector.begin(), test_vector.end(), std::default_random_engine(seed));
    std::shuffle(trusted_vector.begin(), trusted_vector.end(), std::default_random_engine(seed));

    for (size_t i = 0; i < test_vector.size(); i++)
    {
        EXPECT_EQ(trusted_vector[i], test_vector[i]);
    }
}

TEST(VectorTest, CopyTest)
{
    auto test_vector = Vector<int>({1, 2, 3, 4, 5});
    auto test_vector_copy = Vector<int>(test_vector);

    EXPECT_EQ(test_vector.size(), test_vector_copy.size());

    test_vector.pop_back();
    test_vector[1] = 42;

    EXPECT_EQ(4, test_vector.size());
    EXPECT_EQ(5, test_vector_copy.size());
    EXPECT_NE(test_vector.at(1), test_vector_copy.at(1));
}

TEST(VectorTest, MoveTest)
{
    auto test_vector = Vector<int>({1, 2, 3, 4, 5});
    auto test_vector_move = Vector<int>(std::move(test_vector));

    EXPECT_EQ(5, test_vector_move.size());
}

TEST(VectorTest, EquateCopyTest)
{
    auto test_vector_1 = Vector<int>({1, 2, 3, 4, 5});
    auto test_vector_2 = Vector<int>({1, 2, 3});

    test_vector_1 = test_vector_2;

    EXPECT_EQ(test_vector_1.size(), test_vector_2.size());

    test_vector_1.pop_back();
    test_vector_1[1] = 42;

    EXPECT_EQ(2, test_vector_1.size());
    EXPECT_EQ(3, test_vector_2.size());
    EXPECT_NE(test_vector_1.at(1), test_vector_2.at(1));
}

TEST(VectorTest, EquateMoveTest)
{
    auto test_vector_1 = Vector<int>({1, 2, 3, 4, 5});
    auto test_vector_2 = Vector<int>({1, 2, 3});

    test_vector_1 = std::move(test_vector_2);

    EXPECT_EQ(3, test_vector_1.size());
}