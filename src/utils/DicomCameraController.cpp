#include "DicomCameraController.h"

#include <GL/glu.h>
#include <QDebug>


DicomCameraController::DicomCameraController(Vec3d  position,
                                             Vec3d  viewPoint,
                                             Vec3d  up,
                                             double yaw,
                                             double pitch)
{
    m_position  = position;
    m_viewPoint = viewPoint;
    m_upVector  = up;

    m_worldUpVector = up;
    m_viewDirVector = m_viewPoint - m_position;

    m_yaw   = yaw;
    m_pitch = pitch;

    //    updateCameraVectors();
}

void DicomCameraController::lookAt()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(m_position.x,
              m_position.y,
              m_position.z,
              m_viewPoint.x,
              m_viewPoint.y,
              m_viewPoint.z,
              m_upVector.x,
              m_upVector.y,
              m_upVector.z);
}

Point3d DicomCameraController::getCameraPosition()
{
    return m_position;
}

Point3d DicomCameraController::getCameraViewPoint()
{
    return m_viewPoint;
}

Vec3d DicomCameraController::getCameraViewDirVector()
{
    return m_viewPoint - m_position;
}

// void DicomCameraController::move(DicomCameraController::CameraMovement direction, double
// deltaTime)
//{
//    double velocity = m_movementSpeed * deltaTime;

//    switch (direction) {
//        case FORWARD:
//            m_position += m_viewDirVector * velocity;
//            break;
//        case BACKWARD:
//            m_position -= m_viewDirVector * velocity;
//            break;
//        case LEFT:
//            m_position -= m_rightVector * velocity;
//            break;
//        case RIGHT:
//            m_position += m_rightVector * velocity;
//            break;
//        case UP:
//            m_position += m_upVector * velocity;
//            break;
//        case DOWN:
//            m_position -= m_upVector * velocity;
//            break;
//        case ROTATE_X:
//            m_pitch += 1;
//            updateCameraVectors();
//            break;
//        case ROTATE_Y:
//            m_yaw += 1;
//            updateCameraVectors();
//            break;
//        case ROTATE_Z:
//            break;
//    }
//}

void DicomCameraController::processMouseMovement(const Vec2d &offset)
{
    m_yaw += offset.x * 0.002;
    m_pitch += offset.y * 0.002;

    double radius = 2;

    m_position.x = radius * cos(m_pitch) * sin(m_yaw);
    m_position.y = radius * sin(m_pitch) * sin(m_yaw);
    m_position.z = radius * cos(m_yaw);
    //    m_position.x = radius * sin(m_yaw);    // * sin(m_yaw);
    //    m_position.y = radius * cos(m_pitch);  // * sin(m_yaw);
    //    m_position.z = radius * cos(m_yaw);

    //    m_yaw += offset.x * 0.15;
    //    m_pitch += offset.y * 0.15;

    //    if (m_pitch > 89.0)
    //        m_pitch = 89.0;
    //    if (m_pitch < -89.0)
    //        m_pitch = -89.0;
    //    updateCameraVectors();
}

void DicomCameraController::updateCameraVectors()
{
    const double DEG2RAD = M_PI / 180.0;
    m_viewDirVector.x    = cos(DEG2RAD * m_yaw) * cos(DEG2RAD * m_pitch);
    m_viewDirVector.y    = sin(DEG2RAD * m_pitch);
    m_viewDirVector.z    = sin(DEG2RAD * m_yaw) * cos(DEG2RAD * m_pitch);
    m_viewDirVector.normalize();

    m_rightVector = (m_viewDirVector ^ m_worldUpVector).normalized();
    m_upVector    = (m_rightVector ^ m_viewDirVector).normalized();
}
