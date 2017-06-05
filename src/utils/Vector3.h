#ifndef UTILS_VECTOR3_H
#define UTILS_VECTOR3_H

/*
 *  Vector3
 *  Version: 2.3
 */

#ifndef QT_CORE_LIB


#include <iostream>


#else
#include <QDataStream>
#endif


#include <cmath>


#ifndef UTILS
#define UTILS
#define EPSILON .000001
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


template <class T> class Vector3;


typedef Vector3<double> Vec3d;
typedef Vector3<float>  Vec3f;
typedef Vector3<int>    Vec3i;


template <class T> using Point3 = Vector3<T>;


typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
typedef Point3<int>    Point3i;


template <class T> class Vector3
{
public:
    T x;
    T y;
    T z;

    //
    // -----------------------------------------------------------------------
    //

    Vector3();

    Vector3(T _v);

    Vector3(T _x, T _y, T _z);

    Vector3(const Vector3<T> &_other);

    //
    // -----------------------------------------------------------------------
    //

    Vector3 &operator=(const Vector3<T> &_other);

    //
    // -----------------------------------------------------------------------
    //

    bool operator<(const Vector3<T> &_other) const;

    bool operator==(const Vector3<T> &_other) const;

    bool operator!=(const Vector3<T> &_other) const;

    //
    // -----------------------------------------------------------------------
    //

    const Vector3 &operator+() const;

    Vector3 operator-() const;

    Vector3 operator+(const Vector3<T> &_other) const;

    Vector3 operator-(const Vector3<T> &_other) const;

    Vector3 operator*(const Vector3<T> &_other) const;

    Vector3 operator*(T _s) const;

    Vector3 operator/(T _s) const;

    //
    // -----------------------------------------------------------------------
    //

    Vector3 &operator+=(const Vector3<T> &_other);

    Vector3 &operator-=(const Vector3<T> &_other);

    Vector3 &operator*=(const Vector3<T> &_other);

    Vector3 &operator*=(T _s);

    Vector3 &operator/=(T _s);

//
// -----------------------------------------------------------------------
//

#ifdef QT_CORE_LIB
    operator QString() const;
#endif

    T latitude() const;

    T longitude() const;

    T length() const;

    T lengthSquared() const;

    void normalize();

    Vector3 normalized() const;

    Vector3 operator^(const Vector3<T> &_other);

    //
    // -----------------------------------------------------------------------
    //

    static T dot(const Vector3<T> &vec1, const Vector3<T> &vec2);

    static T distance(const Vector3<T> &vec1, const Vector3<T> &vec2);

    static T angle(const Vector3<T> &vec1, const Vector3<T> &vec2);

    static T angleNormalized(const Vector3<T> &vec1, const Vector3<T> &vec2);
};

//
// ---------------------------------------------------------------------------
//

template <class T> Vector3<T> operator*(T _s, const Vector3<T> &_other)
{
    return _other * _s;
}

#ifdef QT_CORE_LIB

template <class T> QDataStream &operator<<(QDataStream &out, const Vector3<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ", " << _v.z << ")";
    return out;
}

template <class T> QDataStream &operator>>(QDataStream &in, Vector3<T> &_v)
{
    in >> _v.x >> _v.y >> _v.z;
    return in;
}

template <class T> Vector3<T>::operator QString() const
{
    return QString("(%1, %2, %3)").arg(x).arg(y).arg(z);
}

#else

template <class T> std::ostream &operator<<(std::ostream &out, const Vector3<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ", " << _v.z << ")";
    return out;
}

template <class T> std::istream &operator>>(std::istream &in, Vector3<T> &_v)
{
    in >> _v.x >> _v.y >> _v.z;
    return in;
}

#endif



// ===========================================================================
// --- Vector3 implementation ---
// ===========================================================================

//
// ---------------------------------------------------------------------------
//

template <class T> Vector3<T>::Vector3() : x(0), y(0), z(0)
{
}

template <class T> Vector3<T>::Vector3(T _v) : x(_v), y(_v), z(_v)
{
}

template <class T> Vector3<T>::Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
{
}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &_other) : x(_other.x), y(_other.y), z(_other.z)
{
}

//
// ---------------------------------------------------------------------------
//

template <class T> Vector3<T> &Vector3<T>::operator=(const Vector3<T> &_other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    return *this;
}

//
// ---------------------------------------------------------------------------
//

template <class T> bool Vector3<T>::operator<(const Vector3<T> &_other) const
{
    if (x < _other.x)
        return true;
    if (x > _other.x)
        return false;
    if (y < _other.y)
        return true;
    if (y > _other.y)
        return false;
    return z < _other.z;
}


template <class T> bool Vector3<T>::operator==(const Vector3<T> &_other) const
{
    return (fabs(x - _other.x) <= EPSILON && fabs(y - _other.y) <= EPSILON &&
            fabs(z - _other.z) <= EPSILON);
}

template <class T> bool Vector3<T>::operator!=(const Vector3<T> &_other) const
{
    return (fabs(x - _other.x) > EPSILON || fabs(y - _other.y) > EPSILON ||
            fabs(z - _other.z) > EPSILON);
}

//
// ---------------------------------------------------------------------------
//

template <class T> const Vector3<T> &Vector3<T>::operator+() const
{
    return *this;
}

template <class T> Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-x, -y, -z);
}

template <class T> Vector3<T> Vector3<T>::operator+(const Vector3<T> &_other) const
{
    return Vector3(x + _other.x, y + _other.y, z + _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator-(const Vector3<T> &_other) const
{
    return Vector3(x - _other.x, y - _other.y, z - _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator*(const Vector3<T> &_other) const
{
    return Vector3(x * _other.x, y * _other.y, z * _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator*(T _s) const
{
    return Vector3(x * _s, y * _s, z * _s);
}

template <class T> Vector3<T> Vector3<T>::operator/(T _s) const
{
    return Vector3(x / _s, y / _s, z / _s);
}

//
// ---------------------------------------------------------------------------
//

template <class T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &_other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &_other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &_other)
{
    x *= _other.x;
    y *= _other.y;
    z *= _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator*=(T _s)
{
    x *= _s;
    y *= _s;
    z *= _s;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator/=(T _s)
{
    x /= _s;
    y /= _s;
    z /= _s;
    return *this;
}

//
// ---------------------------------------------------------------------------
//

template <class T> T Vector3<T>::latitude() const
{
    return std::asin(z / length());
}

template <class T> T Vector3<T>::longitude() const
{
    return std::atan2(y, x);
}

template <class T> T Vector3<T>::length() const
{
    return (T)std::sqrt(x * x + y * y + z * z);
}

template <class T> T Vector3<T>::lengthSquared() const
{
    return (x * x + y * y + z * z);
}

template <class T> void Vector3<T>::normalize()
{
    T l = length();
    x /= l;
    y /= l;
    z /= l;
}

template <class T> Vector3<T> Vector3<T>::normalized() const
{
    T l = length();
    return Vector3<T>(x / l, y / l, z / l);
}

template <class T> Vector3<T> Vector3<T>::operator^(const Vector3<T> &_other)
{
    return Vector3<T>(
        y * _other.z - z * _other.y, z * _other.x - x * _other.z, x * _other.y - y * _other.x);
}

//
// -----------------------------------------------------------------------
//

template <class T> T Vector3<T>::dot(const Vector3<T> &vec1, const Vector3<T> &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

template <class T> T Vector3<T>::distance(const Vector3<T> &vec1, const Vector3<T> &vec2)
{
    Vector3<T> offset = vec2 - vec1;
    return sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
}

template <class T> T Vector3<T>::angle(const Vector3<T> &vec1, const Vector3<T> &vec2)
{
    const T cosAngle =
        Vector3<T>::dot(vec1, vec2) / std::sqrt(vec1.lengthSquared() * vec2.lengthSquared());
    return cosAngle >= 1 ? 0 : (cosAngle <= -1 ? M_PI : std::acos(cosAngle));
}

template <class T> T Vector3<T>::angleNormalized(const Vector3<T> &vec1, const Vector3<T> &vec2)
{
    const T cosAngle = Vector3<T>::dot(vec1, vec2);
    return cosAngle >= 1 ? 0 : (cosAngle <= -1 ? M_PI : std::acos(cosAngle));
}

#endif  // UTILS_VECTOR3_H
