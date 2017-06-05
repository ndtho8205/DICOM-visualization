#ifndef DICOMCAMERACONTROLLER_H
#define DICOMCAMERACONTROLLER_H

#include <Vector2.h>
#include <Vector3.h>


class DicomCameraController
{
public:
    //    enum CameraMovement
    //    {
    //        FORWARD,
    //        BACKWARD,
    //        LEFT,
    //        RIGHT,
    //        UP,
    //        DOWN,
    //        ROTATE_X,
    //        ROTATE_Y,
    //        ROTATE_Z
    //    };

    DicomCameraController(Vec3d  position  = Vec3d(0, 0, 2),
                          Vec3d  viewPoint = Vec3d(0., 0., 0),
                          Vec3d  up        = Vec3d(0., 1., 0.),
                          double yaw       = 0.,
                          double pitch     = 0.);

    void    lookAt();
    Point3d getCameraPosition();
    Point3d getCameraViewPoint();
    Vec3d   getCameraViewDirVector();

    //    void move(CameraMovement direction, double deltaTime);
    void processMouseMovement(const Vec2d &offset);


private:
    void updateCameraVectors();

    Vec3d m_position;

    Vec3d m_viewPoint;
    Vec3d m_viewDirVector;
    Vec3d m_upVector;
    Vec3d m_rightVector;
    Vec3d m_worldUpVector;

    double m_pitch;
    double m_yaw;
    double m_roll;

    double m_movementSpeed = 2.0;
    double m_mouseSensitivity;
};

#endif  // DICOMCAMERACONTROLLER_H
