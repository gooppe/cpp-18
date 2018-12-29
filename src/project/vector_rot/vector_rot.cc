#include <project/vector_rot/vector_rot.hh>

Vector2d::Vector2d(float x, float y) : x(x), y(y) {}

void Vector2d::rotate_multiple_90(uint mult)
{
    switch (mult % 4)
    {
    case 1:
        std::swap(x, y);
        x = -x;
        break;
    case 2:
        x = -x;
        y = -y;
        break;
    case 3:
        std::swap(x, y);
        y = -y;
        break;
    default:
        break;
    }
}

std::ostream &operator<<(std::ostream &out, const Vector2d &v)
{
    out << '(' << v.x << ',' << v.y << ')';
    return out;
}

bool operator==(const Vector2d &v1, const Vector2d &v2)
{
    return (v1.x == v2.x) && (v2.y == v2.y);
}