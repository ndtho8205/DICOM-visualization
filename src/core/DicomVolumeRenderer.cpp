#include "DicomVolumeRenderer.h"

#include <GL/glu.h>
#include <QDebug>

#include <DicomReader.h>


DicomVolumeRenderer::DicomVolumeRenderer()
{
    m_isLoaded = false;
}

void DicomVolumeRenderer::setDicomData(const QString &dicomDir)
{
    if (!m_dicomSet)
        delete m_dicomSet;

    m_dicomSet = DicomReader::readSet(dicomDir);

    m_dicomTexture.load(*m_dicomSet);

    m_isLoaded = true;
}

uint64_t *DicomVolumeRenderer::getHistogramData()
{
    return m_dicomSet->histogram;
}

bool DicomVolumeRenderer::isLoaded()
{
    return m_isLoaded;
}

void DicomVolumeRenderer::changeTextureAlphaRange(int lower, int upper)
{
    if (m_isLoaded)
        m_dicomTexture.load(*m_dicomSet, std::uint8_t(lower), std::uint8_t(upper));
}

//
// ---------------------------------------------------------------------------
//



//
// ---------------------------------------------------------------------------
//

void DicomVolumeRenderer::drawCube()
{
    glDisable(GL_TEXTURE_3D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3d(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    }
    glEnd();
}

//
// ---------------------------------------------------------------------------
//

void DicomVolumeRenderer::renderTextureFixed()
{
    if (!m_isLoaded)
        return;

    glEnable(GL_TEXTURE_3D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_dicomTexture.bind(3);


    for (std::uint32_t i = 0; i < m_dicomSet->depth; ++i) {
        float z = i * 2.0f / (m_dicomSet->depth - 1) - 1.0f;
        glBegin(GL_QUADS);
        {
            glTexCoord3f(0.0f, 0.0f, (z + 1.0f) / 2.0f);
            glVertex3f(-1, -1, z);
            glTexCoord3f(1.0f, 0.0f, (z + 1.0f) / 2.0f);
            glVertex3f(1, -1, z);
            glTexCoord3f(1.0f, 1.0f, (z + 1.0f) / 2.0f);
            glVertex3f(1, 1, z);
            glTexCoord3f(0.0f, 1.0f, (z + 1.0f) / 2.0f);
            glVertex3f(-1, 1, z);
        }
        glEnd();
    }
    glBindTexture(GL_TEXTURE_3D, 0);
}

//
// ---------------------------------------------------------------------------
//

void DicomVolumeRenderer::renderTextureDynamic(const Point3d &orig, const Vec3d &dest)
{
    if (!m_isLoaded)
        return;

    std::uint32_t count = m_dicomSet->depth;

    // -----------------------------------------------------------------------

    std::vector<double>         closestPointsRatio;
    const std::vector<Point3d> &vertices = m_dicomVolume.getVertices();
    Vec3d                       dir      = dest - orig;
    for (Point3d p : vertices) {
        closestPointsRatio.push_back(Vec3d::dot(p - orig, dir) / Vec3d::dot(dir, dir));
    }

    std::sort(closestPointsRatio.begin(), closestPointsRatio.end());
    closestPointsRatio.erase(std::unique(closestPointsRatio.begin(), closestPointsRatio.end()),
                             closestPointsRatio.end());

    std::sort(closestPointsRatio.begin(), closestPointsRatio.end());
    // -----------------------------------------------------------------------

    Plane3d              plane;
    std::vector<Point3d> points;
    Point3d              lineOrig = orig + (closestPointsRatio[0] + 0.02) * dir;
    Point3d lineDest = orig + (closestPointsRatio[closestPointsRatio.size() - 1] - 0.02) * dir;

    // -----------------------------------------------------------------------

    Vec3d  intersectSegmentDir = lineDest - lineOrig;
    double padding             = 0;

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glEnable(GL_TEXTURE_3D);
    glPolygonMode(GL_FRONT, GL_FILL);
    m_dicomTexture.bind(3);


    for (std::uint32_t i = 0; i < count; ++i) {
        Point3d point = lineOrig + padding * intersectSegmentDir;
        padding += 1.0 / (count - 1);
        plane = Plane3d::fromPointNormal(point, intersectSegmentDir);
        points.clear();
        points = m_dicomVolume.intersectPlane(plane);

        if (points.size() < 3) {
            qDebug().noquote() << "Intersect < 3";
            continue;
        }
        setTexture(points);
    }

    glBindTexture(GL_TEXTURE_3D, 0);
}

//
// ---------------------------------------------------------------------------
//

/*
 * Cach 1: tia nhin cat cac mat cua volume
 *
 */
// void DicomVolumeRenderer::renderPolyDynamic(const Point3d &point, const Vec3d &dir)
//{
//    std::uint32_t        count      = 206;
//    std::vector<Point3d> pointsLine = m_dicomVolume.intersectRay(point, dir);

//    Point3d orig = pointsLine[0];
//    Point3d dest = pointsLine[1];
//    if (Point3d::distance(point, orig) >= Point3d::distance(point, dest)) {
//        orig = pointsLine[1];
//        dest = pointsLine[0];
//    }

//    double t = 0;

//    for (std::uint32_t i = 0; i < count; ++i) {
//        Point3d point = orig + t * (dest - orig);
//        t += 1.0 / count;
//        Plane3d              plane  = Plane3d::fromPointNormal(point, dest - orig);
//        std::vector<Point3d> points = m_dicomVolume.intersectPlane(plane);

//        glColor3f(1.f, 0.5f, 1.0f);
//        glBegin(GL_LINE_LOOP);
//        {
//            for (Point3d p : points)
//                glVertex3d(p.x, p.y, p.z);
//        }
//        glEnd();
//    }
//}

//    std::sort(closestPoints.begin(),
//              closestPoints.end(),
//              [&](const Point3d &p1, const Point3d &p2) -> bool {
//                  return Point3d::distance(p1, orig) < Point3d::distance(p2, orig);
//              });

//    for (unsigned long i = 0; i < closestPoints.size(); ++i) {
//        qDebug().noquote() << "Point: " << closestPoints[i];
//        qDebug().noquote() << "\tDistance: " << Vec3d::distance(orig, closestPoints[i]);
//        Plane3d              plane  = Plane3d::fromPointNormal(closestPoints[i], dest - orig);
//        std::vector<Point3d> points = m_dicomVolume.intersectPlane(plane);
//        qDebug().noquote() << "\tIntersect: " << points.size();
//        if (points.size() >= 3) {
//            if (!lineOrig) {
//                lineOrig = &closestPoints[i];
//            } else {
//                lineDest = &closestPoints[i];
//            }
//        }
//    }

void DicomVolumeRenderer::renderPolyDynamic(const Point3d &orig, const Point3d &dest)
{
    std::uint32_t count = 20;

    // -----------------------------------------------------------------------

    std::vector<double>         closestPointsRatio;
    const std::vector<Point3d> &vertices = m_dicomVolume.getVertices();
    Vec3d                       dir      = dest - orig;
    Vec3d                       ap;
    for (Point3d p : vertices) {
        ap = p - orig;
        closestPointsRatio.push_back(Vec3d::dot(ap, dir) / Vec3d::dot(dir, dir));
    }

    std::sort(closestPointsRatio.begin(), closestPointsRatio.end());
    closestPointsRatio.erase(std::unique(closestPointsRatio.begin(), closestPointsRatio.end()),
                             closestPointsRatio.end());

    std::sort(closestPointsRatio.begin(), closestPointsRatio.end());

    // -----------------------------------------------------------------------

    Plane3d              plane;
    std::vector<Point3d> points;
    Point3d              lineOrig = orig + (closestPointsRatio[0] + 0.02) * dir;
    plane                         = Plane3d::fromPointNormal(lineOrig, dest - orig);
    points                        = m_dicomVolume.intersectPlane(plane);
    qDebug().noquote() << "\tIntersect: " << points.size();

    Point3d lineDest = orig + (closestPointsRatio[closestPointsRatio.size() - 1] - 0.02) * dir;
    plane            = Plane3d::fromPointNormal(lineDest, dest - orig);
    points           = m_dicomVolume.intersectPlane(plane);
    qDebug().noquote() << "\tIntersect: " << points.size();
    qDebug().noquote() << "\n\n";

    // -----------------------------------------------------------------------

    double t = 0;

    for (std::uint32_t i = 0; i < count; ++i) {
        Point3d point = lineOrig + t * (lineDest - lineOrig);
        t += 1.0 / (count - 1);
        Plane3d              plane  = Plane3d::fromPointNormal(point, lineDest - lineOrig);
        std::vector<Point3d> points = m_dicomVolume.intersectPlane(plane);

        if (points.size() < 3)
            continue;

        glColor3f(1.f, 0.5f, 1.0f);
        glBegin(GL_LINE_LOOP);
        {
            for (Point3d p : points)
                glVertex3d(p.x, p.y, p.z);
        }
        glEnd();
    }
}

//
// ---------------------------------------------------------------------------
//

void DicomVolumeRenderer::setTextureCoordinates(const Point3d &vertex)
{
    glTexCoord3d((vertex.x + 1.0) / 2.0, (vertex.y + 1.0) / 2.0, (vertex.z + 1.0) / 2.0);
    glVertex3d(vertex.x, vertex.y, vertex.z);
}

void DicomVolumeRenderer::setTexture(std::vector<Point3d> &vertices)
{
    //    glBegin(GL_POLYGON);
    //    {
    //        for (Point3d point : vertices) {
    //            glTexCoord3d((point.x + 1.0) / 2.0, (point.y + 1.0) / 2.0, (point.z + 1.0) / 2.0);
    //            glVertex3d(point.x, point.y, point.z);
    //        }
    //    }
    //    glEnd();

    Point3d G;
    for (Point3d vertex : vertices) {
        G += vertex;
    }
    G /= vertices.size();

    glBegin(GL_TRIANGLE_FAN);
    {
        setTextureCoordinates(G);
        for (Point3d vertex : vertices) {
            setTextureCoordinates(vertex);
        }
        setTextureCoordinates(vertices.at(0));
    }
    glEnd();
}

//
// ---------------------------------------------------------------------------
//
