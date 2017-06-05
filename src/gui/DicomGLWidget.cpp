#include "DicomGLWidget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>


DicomGLWidget::DicomGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_volumeRenderer(new DicomVolumeRenderer)
{
    setFocusPolicy(Qt::StrongFocus);

    //    QSurfaceFormat fmt = format();
    //    fmt.setSamples(32);
    //    setFormat(fmt);
}

DicomGLWidget::~DicomGLWidget()
{
}

//
// ---------------------------------------------------------------------------
//


void DicomGLWidget::loadDicomData(const QString &dicomDir)
{
    m_volumeRenderer->setDicomData(dicomDir);
    if (m_volumeRenderer->isLoaded()) {
        update();
        emit dataLoaded(m_volumeRenderer->getHistogramData());
    }
}

//
// ---------------------------------------------------------------------------
//

void DicomGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);

    //    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.01f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void DicomGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1000, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DicomGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -----------------------------------------------------------------------

    m_cameraController.lookAt();

    drawAxis();

    m_volumeRenderer->drawCube();

    // -----------------------------------------------------------------------

    if (m_volumeRenderer->isLoaded())
        m_volumeRenderer->renderTextureDynamic(m_cameraController.getCameraPosition(),
                                               m_cameraController.getCameraViewPoint());
    else
        m_volumeRenderer->renderPolyDynamic(m_cameraController.getCameraPosition(),
                                            m_cameraController.getCameraViewPoint());

    //            m_volumeRenderer->renderTextureFixed();
}


//
// ---------------------------------------------------------------------------
//

void DicomGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    Vec2d currentMousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());
    Vec2d offset(currentMousePressPosition.x - m_mousePressPosition.x,
                 m_mousePressPosition.y - currentMousePressPosition.y);
    m_mousePressPosition = currentMousePressPosition;

    m_cameraController.processMouseMovement(offset);

    update();
}

void DicomGLWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());
}

void DicomGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_mousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());
}

void DicomGLWidget::keyPressEvent(QKeyEvent *e)
{
    Q_UNUSED(e)
    update();
}

//
// ---------------------------------------------------------------------------
//

void DicomGLWidget::changeTextureAlphaRange(int lower, int upper)
{
    m_volumeRenderer->changeTextureAlphaRange(lower, upper);
    update();
}

//
// ---------------------------------------------------------------------------
//

void DicomGLWidget::drawAxis()
{
    const double AXIS_LENGTH = 10;
    Vec3d        origin      = Vec3d();
    Vec3d        xAxis       = Vec3d(AXIS_LENGTH, 0, 0);
    Vec3d        yAxis       = Vec3d(0, AXIS_LENGTH, 0);
    Vec3d        zAxis       = Vec3d(0, 0, AXIS_LENGTH);

    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3d(origin.x, origin.y, origin.z);
        glVertex3d(xAxis.x, xAxis.y, xAxis.z);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3d(origin.x, origin.y, origin.z);
        glVertex3d(yAxis.x, yAxis.y, yAxis.z);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3d(origin.x, origin.y, origin.z);
        glVertex3d(zAxis.x, zAxis.y, zAxis.z);
    }
    glEnd();
}
