#include "Vector2.h"
#include <cmath>
#include <cassert>

namespace GraphicsEngine
{
    const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
    const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
    const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
    const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& Vector2::operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2& Vector2::operator/=(float scale)
    {
        // 나눌 값이 0이 아닌지 확인.
        assert(scale != 0.0f);

        x /= scale;
        y /= scale;
        return *this;
    }

    bool Vector2::operator==(const Vector2& other)
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other)
    {
        return x != other.x || y != other.y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scale) const
    {
        return Vector2(x * scale, y * scale);
    }

    Vector2 operator*(float scale, const Vector2& vector)
    {
        //return Vector2(vector.x * scale, vector.y * scale);
        //return vector * scale;
        return vector.operator*(scale);
    }

    Vector2 Vector2::operator/(float scale) const
    {
        assert(scale != 0);
        return Vector2(x / scale, y / scale);
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    std::wstring Vector2::ToString()
    {
        wchar_t buffer[256];
        swprintf_s(buffer, 256, L"(%f,%f)", x, y);
        return buffer;
    }

    float Vector2::Length()
    {
        return sqrt(x * x + y * y);
    }

    float Vector2::LengthSquared()
    {
        return x * x + y * y;
    }

    float Vector2::Dot(const Vector2& left, const Vector2& right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }

    Vector2 Vector2::Normalized()
    {
        float length = Length();
        return Vector2(x / length, y / length);
    }

    bool Vector2::Equals(const Vector2& other)
    {
        return x == other.x && y == other.y;
    }

    Vector2 Vector2::Lerp(const Vector2& from, const Vector2& to, float t)
    {
        // t 가두기.
        t = t < 0.0f ? 0.0f : t > 1.0f ? 1.0f : t;
        //if (t < 0.0f)
        //{
        //    t = 0.0f;
        //}
        //if (t > 1.0f)
        //{
        //    t = 1.0f;
        //}

        return (1.0f - t) * from + t * to;
    }
}
