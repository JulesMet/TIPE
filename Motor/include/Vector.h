#pragma once

#include "Logger.h"

//////////////////////////////////////////////////
//////////////////   Vector 2   //////////////////
//////////////////////////////////////////////////

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2(T _x, T _y)
        : x(_x), y(_y)
    {
    }

    Vec2(const Vec2& vec)
        : x(vec.x), y(vec.y)
    {
    }

    /////////// add operators

    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }

    template<typename Ty>
    friend Vec2<Ty> operator+(const Vec2<Ty>& v1, const Vec2<Ty>& v2);

    void operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
    }



    /////////// substract operator

    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }

    template<typename Ty>
    friend Vec2<Ty> operator-(const Vec2<Ty>& v1, const Vec2<Ty>& v2);

    void operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
    }


};



//////////////////////////////////////////////////
//////////////////   Vector 3   //////////////////
//////////////////////////////////////////////////

template<typename T>
struct Vec3 {

    union
    {
        struct
        {
            T x, y, z;
        };

        struct
        {
            T r, g, b;
        };
    };

    Vec3(T _x, T _y, T _z)
        : x(_x), y(_y), z(_z)
    {
    }

    Vec3(const Vec3& vec)
        : x(vec.x), y(vec.y), z(vec.vec3)
    {
    }






    /////////// add operators

    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }

    template<typename Ty>
    friend Vec3<Ty> operator+(const Vec3<Ty>& v1, const Vec3<Ty>& v2);

    void operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }



    /////////// substract operator

    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y); }

    template<typename Ty>
    friend Vec3<Ty> operator-(const Vec3<Ty>& v1, const Vec3<Ty>& v2);

    void operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }


};








/////// Vector 2


template<typename Ty>
Vec2<Ty> operator+(const Vec2<Ty>& v1, const Vec2<Ty>& v2)
{
    return Vec2<Ty>(v1.x + v2.x, v1.y + v2.y);
}

template<typename Ty>
Vec2<Ty> operator-(const Vec2<Ty>& v1, const Vec2<Ty>& v2)
{
    return Vec2<Ty>(v1.x - v2.x, v1.y - v2.y);
}


// print operator Vec2
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec2<Ty>& obj) {
    os << "(" << obj.x << ", " << obj.y << ")";
    return os;
}





//////// Vector 3


template<typename Ty>
Vec3<Ty> operator+(const Vec3<Ty>& v1, const Vec3<Ty>& v2)
{
    return Vec3<Ty>(v1.x + v2.x, v1.y + v2.y);
}

template<typename Ty>
Vec3<Ty> operator-(const Vec3<Ty>& v1, const Vec3<Ty>& v2)
{
    return Vec3<Ty>(v1.x - v2.x, v1.y - v2.y);
}


// print operator Vec3
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec3<Ty>& obj) {
    os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
    return os;
}