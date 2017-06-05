#ifndef DICOMVOLUME_H
#define DICOMVOLUME_H

#include <vector>

#include <Plane3.h>


class DicomVolume
{
public:
    DicomVolume();

    const std::vector<Point3d> &getVertices() const
    {
        return m_vertex;
    }

    std::vector<Point3d> intersectPlane(const Plane3d &plane);
    std::vector<Point3d> intersectLine(const Point3d &p1, const Point3d &p2);
    std::vector<Point3d> intersectRay(const Point3d &orig, const Vec3d &dir);

private:
    std::vector<Point3d> m_vertex;
    std::vector<Plane3d> m_face;


    struct Edge
    {
        Point3d orig;
        Vec3d   dir;

        Edge(Point3d _orig, Vec3d _dir) : orig(_orig), dir(_dir)
        {
        }
    };

    std::vector<Edge> m_edge;
};

#endif  // DICOMVOLUME_H
