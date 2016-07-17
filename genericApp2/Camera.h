//
//  Camera.h
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/16.
//  Copyright (c) 2016 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Camera__
#define __genericApp2__Camera__

#include "TestSled.h"

class Camera
{
public:
    static Camera *getCamera();

    void resetCamera();

    float getPositionX() const;
    void setPositionX(float x);
    void increasePositionX(float deltaX);

    float getPositionY() const;
    void setPositionY(float y);
    void increasePositionY(float deltaY);

    float getPositionZ() const;
    void setPositionZ(float z);
    void increasePositionZ(float deltaZ);

    float getYaw() const;
    void setYaw(float yaw);
    void increaseYaw(float deltaYaw);

    float getPitch() const;
    void setPitch(float pitch);
    void increasePitch(float deltaPitch);

    float getRoll() const;
    void setRoll(float roll);
    void increaseRoll(float deltaRoll);

private:
    Camera();

    static Camera *s_camera;

    float pos[3];
    float rot[3];
};

class CameraTestSled : public TestSled
{
public:
    void test();

};

#endif /* defined(__genericApp2__Camera__) */
