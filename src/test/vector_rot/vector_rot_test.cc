#include <gtest/gtest.h>
#include <project/vector_rot/vector_rot.hh>
#include <vector>
#include <string>

struct vector_rot_param
{
    Vector2d vector;
    Vector2d true_vector;
    uint angle_multiple;
};

class vector_rot_test : public ::testing::TestWithParam<vector_rot_param>
{
};

TEST_P(vector_rot_test, _)
{
    const vector_rot_param &param = GetParam();
    auto vector = param.vector;
    auto true_vector = param.true_vector;
    auto angle_multiple = param.angle_multiple;

    vector.rotate_multiple_90(angle_multiple);

    EXPECT_EQ(true_vector, vector);
}

INSTANTIATE_TEST_CASE_P(
    _,
    vector_rot_test,
    ::testing::Values(
        vector_rot_param{
            Vector2d(1, 0),
            Vector2d(0, 1),
            1,
        },
        vector_rot_param{
            Vector2d(1, 0),
            Vector2d(-1, 0),
            2,
        },
        vector_rot_param{
            Vector2d(1, 0),
            Vector2d(0, -1),
            3,
        },
        vector_rot_param{
            Vector2d(0, 1),
            Vector2d(0, 1),
            4,
        },
        vector_rot_param{
            Vector2d(1, 1),
            Vector2d(-1, 1),
            5,
        },
        vector_rot_param{
            Vector2d(1, 1),
            Vector2d(-1, -1),
            6,
        },
        vector_rot_param{
            Vector2d(1, 1),
            Vector2d(1, -1),
            7,
        },
        vector_rot_param{
            Vector2d(1, 1),
            Vector2d(1, 1),
            8,
        }));

TEST(vector_rot_test, ostream_test)
{
    auto vector = Vector2d(1, 1);
    auto out_str = std::stringstream();
    out_str << vector;

    EXPECT_EQ("(1,1)", out_str.str());
}
