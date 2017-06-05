#ifndef VECTOR4_H
#define VECTOR4_H

#ifndef QT_CORE_LIB
#include <iostream>
#else
#include <QDataStream>
#endif

#include <cmath>



template <class T> class Vector4;

typedef Vector4<double> Vec4d;
typedef Vector4<float>  Vec4f;
typedef Vector4<int>    Vec4i;



template <class T> class Vector4
{
public:
    T v[4];

    //
    //  --- Constructors and Destructors ---
    //

    Vector4();

    Vector4(T _v);

    Vector4(T _x, T _y, T _z, T _a);

    Vector4(const Vector4<T> &_other);

    //
    // --- Assignment operator ---
    //

    Vector4 &operator=(const Vector4<T> &_other);

    //
    //  --- Indexing Operator ---
    //

    T &operator[](int ind);

    const T &operator[](int ind) const;

    operator T *();

    operator const T *() const;

    //
    // --- Relational operator ---
    //

    bool operator==(const Vector4<T> &_other) const;

    bool operator!=(const Vector4<T> &_other) const;

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    const Vector4 &operator+() const;

    Vector4 operator-() const;

    Vector4 operator+(const Vector4<T> &_other) const;

    Vector4 operator-(const Vector4<T> &_other) const;

    Vector4 operator*(const Vector4<T> &_other) const;

    Vector4 operator*(T _s) const;

    Vector4 operator/(T _s) const;

    //
    //  --- (modifying) Arithematic Operators ---
    //

    Vector4 &operator+=(const Vector4<T> &_other);

    Vector4 &operator-=(const Vector4<T> &_other);

    Vector4 &operator*=(const Vector4<T> &_other);

    Vector4 &operator*=(T _s);

    Vector4 &operator/=(T _s);

    //
    // --- Method ---
    //
    operator QString();

    T dot(const Vector4<T> &_other) const;

    T length() const;

    T lengthSquared() const;

    void normalize();
};

//
// --- Friend method ---
//

template <class T> Vector4<T> operator*(T _s, const Vector4<T> &_other)
{
    return _other * _s;
}

//
// --- Input & Output ---
//

#ifdef QT_CORE_LIB

template <class T> QDataStream &operator<<(QDataStream &out, const Vector4<T> &_v)
{
    out << "(" << _v[0] << ", " << _v[1] << ", " << _v[2] << ", " << _v[3] << ")";
    return out;
}

template <class T> QDataStream &operator>>(QDataStream &in, Vector4<T> &_v)
{
    in >> _v[0] >> _v[1] >> _v[2] >> _v[3];
    return in;
}

template <class T> Vector4<T>::operator QString()
{
    return QString("(%1, %2, %3, %4)").arg(v[0]).arg(v[1]).arg(v[2]).arg(v[3]);
}

#else

template <class T> std::ostream &operator<<(std::ostream &out, const Vector4<T> &_v)
{
    out << "(" << _v[0] << ", " << _v[1] << ", " << _v[2] << ", " << _v[3] << ")";
    return out;
}

template <class T> std::istream &operator>>(std::istream &in, Vector4<T> &_v)
{
    in >> _v[0] >> _v[1] >> _v[2] >> _v[3];
    return in;
}

#endif



// ===========================================================================
// --- Vector4 implementation ---
// ===========================================================================

//
//  --- Constructors and Destructors ---
//

template <class T> Vector4<T>::Vector4()
{
    v[0] = v[1] = v[2] = v[3] = 0;
}

template <class T> Vector4<T>::Vector4(T _v)
{
    v[0] = v[1] = v[2] = v[3] = _v;
}

template <class T> Vector4<T>::Vector4(T _x, T _y, T _z, T _a)
{
    v[0] = _x;
    v[1] = _y;
    v[2] = _z;
    v[3] = _a;
}

template <class T> Vector4<T>::Vector4(const Vector4<T> &_other)
{
    v[0] = _other[0];
    v[1] = _other[1];
    v[2] = _other[2];
    v[3] = _other[3];
}

//
// --- Assignment operator ---
//

template <class T> Vector4<T> &Vector4<T>::operator=(const Vector4<T> &_other)
{
    v[0] = _other[0];
    v[1] = _other[1];
    v[2] = _other[2];
    v[3] = _other[3];
    return *this;
}

//
//  --- Indexing Operator ---
//

template <class T> T &Vector4<T>::operator[](int ind)
{
    return v[ind];
}

template <class T> const T &Vector4<T>::operator[](int ind) const
{
    return v[ind];
}

template <class T> Vector4<T>::operator T *()
{
    return v;
}

template <class T> Vector4<T>::operator const T *() const
{
    return v;
}

//
// --- Relational operator ---
//

template <class T> bool Vector4<T>::operator==(const Vector4<T> &_other) const
{
    return (v[0] == _other[0] && v[1] == _other[1] && v[2] == _other[2] && v[3] == _other[3]);
}

template <class T> bool Vector4<T>::operator!=(const Vector4<T> &_other) const
{
    return (v[0] != _other[0] || v[1] != _other[1] || v[2] != _other[2] || v[3] != _other[3]);
}

//
//  --- (non-modifying) Arithematic Operators ---
//

template <class T> const Vector4<T> &Vector4<T>::operator+() const
{
    return *this;
}

template <class T> Vector4<T> Vector4<T>::operator-() const
{
    return Vector4<T>(-v[0], -v[1], -v[2], -v[3]);
}

template <class T> Vector4<T> Vector4<T>::operator+(const Vector4<T> &_other) const
{
    return Vector4(v[0] + _other[0], v[1] + _other[1], v[2] + _other[2], v[3] + _other[3]);
}

template <class T> Vector4<T> Vector4<T>::operator-(const Vector4<T> &_other) const
{
    return Vector4(v[0] - _other[0], v[1] - _other[1], v[2] - _other[2], v[3] - _other[3]);
}

template <class T> Vector4<T> Vector4<T>::operator*(const Vector4<T> &_other) const
{
    return Vector4(v[0] * _other[0], v[1] * _other[1], v[2] * _other[2], v[3] * _other[3]);
}

template <class T> Vector4<T> Vector4<T>::operator*(T _s) const
{
    return Vector4(v[0] * _s, v[1] * _s, v[2] * _s, v[3] * _s);
}

template <class T> Vector4<T> Vector4<T>::operator/(T _s) const
{
    return Vector4(v[0] / _s, v[1] / _s, v[2] / _s, v[3] / _s);
}

//
//  --- (modifying) Arithematic Operators ---
//

template <class T> Vector4<T> &Vector4<T>::operator+=(const Vector4<T> &_other)
{
    v[0] += _other[0];
    v[1] += _other[1];
    v[2] += _other[2];
    v[3] += _other[3];
    return *this;
}

template <class T> Vector4<T> &Vector4<T>::operator-=(const Vector4<T> &_other)
{
    v[0] -= _other[0];
    v[1] -= _other[1];
    v[2] -= _other[2];
    v[3] -= _other[3];
    return *this;
}

template <class T> Vector4<T> &Vector4<T>::operator*=(const Vector4<T> &_other)
{
    v[0] *= _other[0];
    v[1] *= _other[1];
    v[2] *= _other[2];
    v[3] *= _other[3];
    return *this;
}

template <class T> Vector4<T> &Vector4<T>::operator*=(T _s)
{
    v[0] *= _s;
    v[1] *= _s;
    v[2] *= _s;
    v[3] *= _s;
    return *this;
}

template <class T> Vector4<T> &Vector4<T>::operator/=(T _s)
{
    v[0] /= _s;
    v[1] /= _s;
    v[2] /= _s;
    v[3] /= _s;
    return *this;
}

//
// --- Method ---
//

template <class T> T Vector4<T>::dot(const Vector4<T> &_other) const
{
    return v[0] * _other[0] + v[1] * _other[1] + v[2] * _other[2] + v[3] * _other[3];
}

template <class T> T Vector4<T>::length() const
{
    return (T)std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

template <class T> T Vector4<T>::lengthSquared() const
{
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

template <class T> void Vector4<T>::normalize()
{
    T s = length();
    v[0] /= s;
    v[1] /= s;
    v[2] /= s;
    v[3] /= s;
}


#endif  // VECTOR4_H
