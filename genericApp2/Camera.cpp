//
//  Camera.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/16.
//  Copyright (c) 2016 Arpin, Gregg. All rights reserved.
//

#include "Util.h"
#include "Camera.h"

Camera *Camera::s_camera = NULL;

Camera::Camera()
{
    resetCamera();
}

Camera *Camera::getCamera()
{
    if(s_camera == NULL)
    {
        s_camera = new Camera();
    }

    return s_camera;
}

void Camera::resetCamera()
{
    pos[0] = 0;
    pos[1] = 5;
    pos[2] = 0;
    rot[0] = rot[1] = rot[2] = 0;
}

float Camera::getPositionX() const
{
    return pos[0];
}

void Camera::setPositionX(float x)
{
    pos[0] = x;
}

void Camera::increasePositionX(float deltaX)
{
    pos[0] += deltaX;
}

float Camera::getPositionY() const
{
    return pos[1];
}

void Camera::setPositionY(float y)
{
    pos[1] = y;
}

void Camera::increasePositionY(float deltaY)
{
    pos[1] += deltaY;
}

float Camera::getPositionZ() const
{
    return pos[2];
}
void Camera::setPositionZ(float z)
{
    pos[2] = z;
}

void Camera::increasePositionZ(float deltaZ)
{
    pos[2] += deltaZ;
}

float Camera::getYaw() const
{
    return rot[0];
}

void Camera::setYaw(float yaw)
{
    rot[0] = yaw;
}

void Camera::increaseYaw(float deltaYaw)
{
    rot[0] += deltaYaw;
}

float Camera::getPitch() const
{
    return rot[1];
}
void Camera::setPitch(float pitch)
{
    rot[1] = pitch;
}

void Camera::increasePitch(float deltaPitch)
{
    rot[1] += deltaPitch;
}

float Camera::getRoll() const
{
    return rot[2];
}
void Camera::setRoll(float roll)
{
    rot[2] = roll;
}

void Camera::increaseRoll(float deltaRoll)
{
    rot[2] += deltaRoll;
}

void CameraTestSled::test()
{
    Camera *cam = Camera::getCamera();

    test_fail_if(cam != Camera::getCamera(), "Singleton not working");

    const float testX = 0.7;
    const float testY = 0.8;
    const float testZ = 0.9;
    const float testYaw = 0.4;
    const float testPitch = 0.5;
    const float testRoll = 0.6;
    const float testInc = 0.1;

    float x = cam->getPositionX();
    float y = cam->getPositionY();
    float z = cam->getPositionZ();

    float yaw = cam->getYaw();
    float pitch = cam->getPitch();
    float roll = cam->getRoll();

    cam->setPositionX(testX);
    cam->setPositionY(testY);
    cam->setPositionZ(testZ);

    cam->setYaw(testYaw);
    cam->setPitch(testPitch);
    cam->setRoll(testRoll);

    test_fail_if(cam->getPositionX() != testX, "Incorrect x after set");
    test_fail_if(cam->getPositionY() != testY, "Incorrect y after set");
    test_fail_if(cam->getPositionZ() != testZ, "Incorrect z after set");

    test_fail_if(cam->getYaw() != testYaw, "Incorrect yaw after set");
    test_fail_if(cam->getPitch() != testPitch, "Incorrect pitch after set");
    test_fail_if(cam->getRoll() != testRoll, "Incorrect roll after set");

    cam->increasePositionX(testInc);
    cam->increasePositionY(testInc);
    cam->increasePositionZ(testInc);

    cam->increaseYaw(testInc);
    cam->increasePitch(testInc);
    cam->increaseRoll(testInc);

    test_fail_if(cam->getPositionX() != testInc + testX, "Incorrect x after increase");
    test_fail_if(cam->getPositionY() != testInc + testY, "Incorrect y after increase");
    test_fail_if(cam->getPositionZ() != testInc + testZ, "Incorrect z after increase");

    test_fail_if(cam->getYaw() != testInc + testYaw, "Incorrect yaw after increase");
    test_fail_if(cam->getPitch() != testInc + testPitch, "Incorrect pitch after increase");
    test_fail_if(cam->getRoll() != testInc + testRoll, "Incorrect roll after increase");

    cam->resetCamera();

    test_fail_if(x != cam->getPositionX(), "Incorrect x after reset");
    test_fail_if(y != cam->getPositionY(), "Incorrect y after reset");
    test_fail_if(z != cam->getPositionZ(), "Incorrect z after reset");

    test_fail_if(yaw != cam->getYaw(), "Incorrect yaw after reset");
    test_fail_if(pitch != cam->getPitch(), "Incorrect pitch after reset");
    test_fail_if(roll != cam->getRoll(), "Incorrect roll after reset");

    test_pass;
}