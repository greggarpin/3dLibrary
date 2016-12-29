//
//  IRenderingEngine.h
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef genericApp2_IRenderingEngine_h
#define genericApp2_IRenderingEngine_h

#include "TouchEvent.h"

enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown
};

struct IRenderingEngine* CreateRenderer1();
struct IRenderingEngine* CreateRenderer2();

struct IRenderingEngine {
    virtual void Initialize(int width, int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAnimation(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual void Rotate(float deltaXRad, float deltaYRad, float deltaZRad) = 0;
    virtual void SetRotation(float xRad, float yRad, float zRad) = 0;
    virtual void SetRotationX(float rad) = 0;
    virtual void SetRotationY(float rad) = 0;
    virtual void SetRotationZ(float rad) = 0;
    virtual void SetRoll(float rad) = 0;
    virtual void SetPitch(float rad) = 0;
    virtual void SetYaw(float rad) = 0;

    virtual void onTouchStart(int x, int y) = 0;
    virtual void onTouchMoved(int x, int y) = 0;
    virtual void onTouchEnd(int x, int y) = 0;

    virtual void onTouchStart(const TouchEvent &event) = 0;
    virtual void onTouchMoved(const TouchEvent &event) = 0;
    virtual void onTouchEnd(const TouchEvent &event) = 0;

    virtual void addTextureImage(const void* imageBytesRGBA, unsigned int width, unsigned int height) = 0;

    virtual ~IRenderingEngine() {}
};
#endif
