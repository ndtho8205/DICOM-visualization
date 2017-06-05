#ifndef UTILS_PLANE3_H
#define UTILS_PLANE3_H

/*
 *  Plane3
 *  Version: 1.2
 */

#include "Vector3.h"


template <typename T> class Plane3;


typedef Plane3<double> Plane3d;
typedef Plane3<float>  Plane3f;
typedef Plane3<int>    Plane3i;


template <typename T> class Plane3
{
public:
    T a;
    T b;
    T c;
    T d;

    //
    // -----------------------------------------------------------------------
    //
    Plane3();
    Plane3(const Plane3<T> &P);
    Plane3(T _a, T _b, T _c, T _d);
    Plane3(const Vector3<T> &normalizedNormal, T _d);

    //
    // -----------------------------------------------------------------------
    //

    static Plane3<T> fromPointNormal(const Point3<T> &point, const Vector3<T> &normal);
    static Plane3<T> fromPointVectors(const Point3<T> & point,
                                      const Vector3<T> &vector1,
                                      const Vector3<T> &vector2);
    static Plane3<T> fromPoints(const Point3<T> &point1,
                                const Point3<T> &point2,
                                const Point3<T> &point3);

    //
    // -----------------------------------------------------------------------
    //
    Point3<T> intersectLine(const Point3<T> &p1, const Point3<T> &p2, bool &hit) const;
    double intersectLineRatio(const Point3<T> &p1, const Point3<T> &p2, bool &hit) const;
    Point3<T> intersectRay(const Point3<T> &orig, const Vector3<T> &dir, bool &hit) const;
    double intersectRayRatio(const Point3<T> &orig, const Vector3<T> &dir, bool &hit) const;

    static double dotCoord(const Plane3<T> &p, const Vector3<T> &v);
    static double dotNormal(const Plane3<T> &p, const Vector3<T> &v);

    //
    // -----------------------------------------------------------------------
    //

    Vector3<T> normal() const;
    Plane3<T>  flip();
    void       normalize();
    Plane3<T>  normalized();
};


// ===========================================================================
// --- Plane3 implementation ---
// ===========================================================================

//
// ---------------------------------------------------------------------------
//

template <typename T> Plane3<T>::Plane3()
{
}

template <typename T> Plane3<T>::Plane3(const Plane3<T> &P)
{
    a = P.a;
    b = P.b;
    c = P.c;
    d = P.d;
}

template <typename T> Plane3<T>::Plane3(T _a, T _b, T _c, T _d)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}

template <typename T> Plane3<T>::Plane3(const Vector3<T> &normalizedNormal, T _d)
{
    a = normalizedNormal.x;
    b = normalizedNormal.y;
    c = normalizedNormal.z;
    d = _d;
}

//
// ---------------------------------------------------------------------------
//

template <typename T>
Plane3<T> Plane3<T>::fromPointNormal(const Point3<T> &point, const Vector3<T> &normal)
{
    Plane3<T>  plane;
    Vector3<T> normalizedNormal = normal.normalized();
    plane.a                     = normalizedNormal.x;
    plane.b                     = normalizedNormal.y;
    plane.c                     = normalizedNormal.z;
    plane.d                     = -Vec3d::dot(point, normalizedNormal);
    return plane;
}

template <typename T>
Plane3<T> Plane3<T>::fromPointVectors(const Point3<T> & point,
                                      const Vector3<T> &vector1,
                                      const Vector3<T> &vector2)
{
    Plane3<T>  plane;
    Vector3<T> normal = vector1 ^ vector2;
    return fromPointNormal(point, normal);
}

template <typename T>
Plane3<T> Plane3<T>::fromPoints(const Point3<T> &point0,
                                const Point3<T> &point1,
                                const Point3<T> &point2)
{
    Vector3<T> normal = (Vector3<T>(point1 - point0) ^ (point2 - point0)).normalized();
    return fromPointNormal(point0, normal);
}

//
// ---------------------------------------------------------------------------
//

template <typename T>
Point3<T> Plane3<T>::intersectLine(const Point3<T> &p1, const Point3<T> &p2, bool &hit) const
{
    return intersectRay(p1, p2 - p1, hit);
}

template <typename T>
double Plane3<T>::intersectLineRatio(const Point3<T> &p1, const Point3<T> &p2, bool &hit) const
{
    return intersectRayRatio(p1, p2 - p1, hit);
}

template <typename T>
Point3<T> Plane3<T>::intersectRay(const Point3<T> &orig, const Vector3<T> &dir, bool &hit) const
{
    hit                = true;
    double denominator = a * dir.x + b * dir.y + c * dir.z;
    if (fabs(denominator) <= EPSILON) {
        hit = false;
        return orig;
    }
    double t = -(a * orig.x + b * orig.y + c * orig.z + d) / denominator;

    return orig + t * dir;
}

template <typename T>
double Plane3<T>::intersectRayRatio(const Point3<T> &orig, const Vector3<T> &dir, bool &hit) const
{
    hit                = true;
    double denominator = a * dir.x + b * dir.y + c * dir.z;
    if (fabs(denominator) <= EPSILON) {
        hit = false;
        return 0;
    }
    return -(a * orig.x + b * orig.y + c * orig.z + d) / denominator;
}

template <typename T> double Plane3<T>::dotCoord(const Plane3<T> &p, const Vector3<T> &v)
{
    return p.a * v.x + p.b * v.y + p.c * v.z + p.d;
}

template <typename T> double Plane3<T>::dotNormal(const Plane3<T> &p, const Vector3<T> &v)
{
    return p.a * v.x + p.b * v.y + p.c * v.z;
}

//
// ---------------------------------------------------------------------------
//

template <typename T> Vector3<T> Plane3<T>::normal() const
{
    return Vector3<T>(a, b, c);
}

template <typename T> Plane3<T> Plane3<T>::flip()
{
    return Plane3(-a, -b, -c, -d);
}

template <typename T> void Plane3<T>::normalize()
{
    T distance = std::sqrt(a * a + b * b + c * c);
    a /= distance;
    b /= distance;
    c /= distance;
    d /= distance;
}

template <typename T> Plane3<T> Plane3<T>::normalized()
{
    T distance = std::sqrt(a * a + b * b + c * c);
    return Plane3<T>(a / distance, b / distance, c / distance, d / distance);
}

#endif  // UTILS_PLANE3_H
