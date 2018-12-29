#ifndef VECTOR_ROT_HH
#define VECTOR_ROT_HH

#include <iostream>

struct Vector2d
{
    float x, y;

    Vector2d(float x, float y);
    void rotate_multiple_90(uint mult);
    friend std::ostream &operator<<(std::ostream &out, const Vector2d &v);
    friend bool operator==(const Vector2d &v1, const Vector2d &v2);
};

#endif