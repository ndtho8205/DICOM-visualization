#include "DicomVolume.h"

#include <algorithm>
#include <QDebug>

//
//                     e3
//          v5 o----------------o v4
//            /|               /|
//           / |              / |
//      e10 /  |          e9 /  |e7
//         /   |   e1       /   |
//     v3 o----------------o v2 |
//        |    |           |    |
//        |    |e6         |    |
//        |e5  |           |e4  |
//        |    |    e2     |    |
//        |    o-----------|----o v7
//        |   /  v6        |   /
//        |  /             |  /
//        | /e11           | /e8
//        |/               |/
//   y    o----------------o
//   | z  v0      e0       v1
//   |/
//   +---x


DicomVolume::DicomVolume()
{
    m_vertex.push_back(Point3d(-1, -1, 1));   // v0
    m_vertex.push_back(Point3d(1, -1, 1));    // v1
    m_vertex.push_back(Point3d(1, 1, 1));     // v2
    m_vertex.push_back(Point3d(-1, 1, 1));    // v3
    m_vertex.push_back(Point3d(1, 1, -1));    // v4
    m_vertex.push_back(Point3d(-1, 1, -1));   // v5
    m_vertex.push_back(Point3d(-1, -1, -1));  // v6
    m_vertex.push_back(Point3d(1, -1, -1));   // v7

    Vec3d dir = m_vertex.at(1) - m_vertex.at(0);
    m_edge.push_back(Edge(m_vertex.at(0), dir));
    m_edge.push_back(Edge(m_vertex.at(3), dir));
    m_edge.push_back(Edge(m_vertex.at(5), dir));
    m_edge.push_back(Edge(m_vertex.at(6), dir));
    dir = m_vertex.at(3) - m_vertex.at(0);
    m_edge.push_back(Edge(m_vertex.at(0), dir));
    m_edge.push_back(Edge(m_vertex.at(6), dir));
    m_edge.push_back(Edge(m_vertex.at(7), dir));
    m_edge.push_back(Edge(m_vertex.at(1), dir));
    dir = m_vertex.at(0) - m_vertex.at(6);
    m_edge.push_back(Edge(m_vertex.at(7), dir));
    m_edge.push_back(Edge(m_vertex.at(6), dir));
    m_edge.push_back(Edge(m_vertex.at(5), dir));
    m_edge.push_back(Edge(m_vertex.at(4), dir));

    m_face.push_back(Plane3d::fromPoints(m_vertex.at(1), m_vertex.at(2), m_vertex.at(3)));
    m_face.push_back(Plane3d::fromPoints(m_vertex.at(6), m_vertex.at(5), m_vertex.at(4)));
    m_face.push_back(Plane3d::fromPoints(m_vertex.at(0), m_vertex.at(3), m_vertex.at(5)));
    m_face.push_back(Plane3d::fromPoints(m_vertex.at(4), m_vertex.at(2), m_vertex.at(1)));
    m_face.push_back(Plane3d::fromPoints(m_vertex.at(2), m_vertex.at(4), m_vertex.at(5)));
    m_face.push_back(Plane3d::fromPoints(m_vertex.at(0), m_vertex.at(6), m_vertex.at(7)));
}

//
// ---------------------------------------------------------------------------
//

std::vector<Point3d> DicomVolume::intersectPlane(const Plane3d &plane)
{
    bool                 hit;
    std::vector<Point3d> points;

    for (Edge edge : m_edge) {
        hit      = true;
        double t = plane.intersectRayRatio(edge.orig, edge.dir, hit);
        if (hit && 0. <= t && t <= 1.)
            points.push_back(edge.orig + t * edge.dir);
    }

    if (!points.size())
        return points;


    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    const Vec3d planeNormal = plane.normal();
    const Vec3d origin      = points[0];
    std::sort(points.begin(), points.end(), [&](const Point3d &p1, const Point3d &p2) -> bool {
        Vec3d v;
        v = (p1 - origin) ^ (p2 - origin);
        return Vec3d::dot(v, planeNormal) < 0;
    });

    return points;
}

std::vector<Point3d> DicomVolume::intersectLine(const Point3d &p1, const Point3d &p2)
{
    return intersectRay(p1, p2 - p1);
}

std::vector<Point3d> DicomVolume::intersectRay(const Point3d &orig, const Vec3d &dir)
{
    std::vector<Point3d> points;
    for (Plane3d plane : m_face) {
        bool    hit   = true;
        Point3d point = plane.intersectRayRatio(orig, dir, hit);
        if (hit && (-1. - EPSILON <= point.x && point.x <= 1. + EPSILON) &&
            (-1. - EPSILON <= point.y && point.y <= 1. + EPSILON) &&
            (-1. - EPSILON <= point.z && point.z <= 1. + EPSILON)) {
            points.push_back(point);
        }
    }

    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());

    std::sort(points.begin(), points.end(), [&](const Point3d &p1, const Point3d &p2) -> bool {
        return Point3d::distance(p1, orig) < Point3d::distance(p2, orig);
    });

    return points;
}


//        const Vec3d planeNormal = dest - orig;
//        const Vec3d origin      = points[0];
//        for (int i = 0; i < points.size() - 1; ++i)
//            for (int j = 0; j < points.size(); ++j) {
//                Vec3d v;
//                v = (points.at(i) - origin) ^ (points.at(j) - origin);
//                if (!(Vec3d::dot(v, planeNormal) < 0)) {
//                    Point3d tmp = points[i];
//                    points[i]   = points[j];
//                    points[j]   = tmp;
//                }
//            }


//        std::sort(points.begin(), points.end(), [&](const Point3d &a, const Point3d &b) ->
//        bool {
//            if (a.x - point.x >= 0 && b.x - point.x < 0)
//                return true;
//            if (a.x - point.x < 0 && b.x - point.x >= 0)
//                return false;
//            if (a.x - point.x == 0 && b.x - point.x == 0) {
//                if (a.y - point.y >= 0 || b.y - point.y >= 0)
//                    return a.y > b.y;
//                return b.y > a.y;
//            }
//
//            // compute the cross product of vectors (point -> a) x (point -> b)
//            double det = (a.x - point.x) * (b.y - point.y) - (b.x - point.x) * (a.y -
//            point.y);
//            if (det < 0)
//                return true;
//            if (det > 0)
//                return false;
//
//            // points a and b are on the same line from the point
//            // check which point is closer to the point
//            double d1 = (a.x - point.x) * (a.x - point.x) + (a.y - point.y) * (a.y -
//            point.y);
//            double d2 = (b.x - point.x) * (b.x - point.x) + (b.y - point.y) * (b.y -
//            point.y);
//            return d1 > d2;
//        });
