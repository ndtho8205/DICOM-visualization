#ifndef VECTOR2_H
#define VECTOR2_H

#ifndef QT_CORE_LIB
#include <iostream>
#else
#include <QDataStream>
#endif

#include <cmath>



template <class T> class Vector2;

typedef Vector2<double> Vec2d;
typedef Vector2<float>  Vec2f;
typedef Vector2<int>    Vec2i;



template <class T> class Vector2
{
public:
    T x;
    T y;

    //
    //  --- Constructors and Destructors ---
    //

    Vector2();

    Vector2(T _v);

    Vector2(T _x, T _y);

    Vector2(const Vector2<T> &_other);

    //
    // --- Assignment operator ---
    //

    Vector2 &operator=(const Vector2<T> &_other);

    //
    // --- Relational operator ---
    //

    bool operator==(const Vector2<T> &_other) const;

    bool operator!=(const Vector2<T> &_other) const;

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    const Vector2 &operator+() const;

    Vector2 operator-() const;

    Vector2 operator+(const Vector2<T> &_other) const;

    Vector2 operator-(const Vector2<T> &_other) const;

    Vector2 operator*(const Vector2<T> &_other) const;

    Vector2 operator*(T _s) const;

    Vector2 operator/(T _s) const;

    //
    //  --- (modifying) Arithematic Operators ---
    //

    Vector2 &operator+=(const Vector2<T> &_other);

    Vector2 &operator-=(const Vector2<T> &_other);

    Vector2 &operator*=(const Vector2<T> &_other);

    Vector2 &operator*=(T _s);

    Vector2 &operator/=(T _s);

//
// --- Method ---
//

#ifdef QT_CORE_LIB
    operator QString();
#endif

    T dot(const Vector2<T> &_other) const;

    T length() const;

    T lengthSquared() const;

    void normalize();
};

//
// --- Friend method ---
//

template <class T> Vector2<T> operator*(T _s, const Vector2<T> &_other)
{
    return _other * _s;
}

//
// --- Input & Output ---
//

#ifdef QT_CORE_LIB

template <class T> QDataStream &operator<<(QDataStream &out, const Vector2<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ")";
    return out;
}

template <class T> QDataStream &operator>>(QDataStream &in, Vector2<T> &_v)
{
    in >> _v.x >> _v.y;
    return in;
}

template <class T> Vector2<T>::operator QString()
{
    return QString("(%1, %2)").arg(x).arg(y);
}

#else

template <class T> std::ostream &operator<<(std::ostream &out, const Vector2<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ")";
    return out;
}

template <class T> std::istream &operator>>(std::istream &in, Vector2<T> &_v)
{
    in >> _v.x >> _v.y;
    return in;
}

#endif



// ===========================================================================
// --- Vector2 implementation ---
// ===========================================================================

//
//  --- Constructors and Destructors ---
//

template <class T> Vector2<T>::Vector2() : x(0), y(0)
{
}

template <class T> Vector2<T>::Vector2(T _v) : x(_v), y(_v)
{
}

template <class T> Vector2<T>::Vector2(T _x, T _y) : x(_x), y(_y)
{
}

template <class T> Vector2<T>::Vector2(const Vector2<T> &_other) : x(_other.x), y(_other.y)
{
}

//
// --- Assignment operator ---
//

template <class T> Vector2<T> &Vector2<T>::operator=(const Vector2<T> &_other)
{
    x = _other.x;
    y = _other.y;
    return *this;
}

//
// --- Relational operator ---
//

template <class T> bool Vector2<T>::operator==(const Vector2<T> &_other) const
{
    return (x == _other.x && y == _other.y);
}

template <class T> bool Vector2<T>::operator!=(const Vector2<T> &_other) const
{
    return (x != _other.x || y != _other.y);
}

//
//  --- (non-modifying) Arithematic Operators ---
//

template <class T> const Vector2<T> &Vector2<T>::operator+() const
{
    return *this;
}

template <class T> Vector2<T> Vector2<T>::operator-() const
{
    return Vector2<T>(-x, -y);
}

template <class T> Vector2<T> Vector2<T>::operator+(const Vector2<T> &_other) const
{
    return Vector2(x + _other.x, y + _other.y);
}

template <class T> Vector2<T> Vector2<T>::operator-(const Vector2<T> &_other) const
{
    return Vector2(x - _other.x, y - _other.y);
}

template <class T> Vector2<T> Vector2<T>::operator*(const Vector2<T> &_other) const
{
    return Vector2(x * _other.x, y * _other.y);
}

template <class T> Vector2<T> Vector2<T>::operator*(T _s) const
{
    return Vector2(x * _s, y * _s);
}

template <class T> Vector2<T> Vector2<T>::operator/(T _s) const
{
    return Vector2(x / _s, y / _s);
}

//
//  --- (modifying) Arithematic Operators ---
//

template <class T> Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &_other)
{
    x += _other.x;
    y += _other.y;
    return *this;
}

template <class T> Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &_other)
{
    x -= _other.x;
    y -= _other.y;
    return *this;
}

template <class T> Vector2<T> &Vector2<T>::operator*=(const Vector2<T> &_other)
{
    x *= _other.x;
    y *= _other.y;
    return *this;
}

template <class T> Vector2<T> &Vector2<T>::operator*=(T _s)
{
    x *= _s;
    y *= _s;
    return *this;
}

template <class T> Vector2<T> &Vector2<T>::operator/=(T _s)
{
    x /= _s;
    y /= _s;
    return *this;
}

//
// --- Method ---
//

template <class T> T Vector2<T>::dot(const Vector2<T> &_other) const
{
    return x * _other.x + y * _other.y;
}

template <class T> T Vector2<T>::length() const
{
    return (T)std::sqrt(x * x + y * y);
}

template <class T> T Vector2<T>::lengthSquared() const
{
    return (x * x + y * y);
}

template <class T> void Vector2<T>::normalize()
{
    T s = this->length();
    x /= s;
    y /= s;
}

#endif  // VECTOR2_H
