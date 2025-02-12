#pragma once

#include <string>
#include "../Core/Type.h"

namespace GraphicsEngine
{
    // 3차원 벡터 클래스.
    class Vector3
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // 기본 값.
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Right;
        static const Vector3 Up;
        static const Vector3 Forward;

    public:
        inline Vector3()
            : x(0.0f), y(0.0f), z(0.0f)
        {
        }

        inline Vector3(float value)
            : x(value), y(value), z(value)
        {
        }

        inline Vector3(float x, float y, float z)
            : x(x), y(y), z(z)
        {
        }

        inline static constexpr uint32 Stride() { return sizeof(Vector3); }
        
        // 연산자 오버로딩.
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(float scale);
        Vector3& operator/=(float scale);

        bool operator==(const Vector3& other);
        bool operator!=(const Vector3& other);

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;

        Vector3 operator*(float scale) const;
        friend Vector3 operator*(float scale, const Vector3& vector);

        Vector3 operator/(float scale) const;

        Vector3 operator-() const;

        // (x, y, z) 문자열 생성 함수.
        std::wstring ToString();

        // 길이 구하기.
        float Length();
        float LengthSquared();
        
        // 내적(Dot Product/Inner Product).
        static float Dot(const Vector3& left, const Vector3& right);
        
        // 외적(Cross Product/Outer Product).
        static Vector3 Cross(const Vector3& left, const Vector3& right);

        Vector3 Normalized();
        bool Equals(const Vector3& other);

        // 선형 보간(Lerp - Linear Interpolation).
        // (1 - t)*from + t*to;
        // from + t*(to-from);
        static Vector3 Lerp(const Vector3& from, const Vector3& to, float t);
    };
}