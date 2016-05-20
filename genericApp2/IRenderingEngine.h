//
//  IRenderingEngine.h
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef genericApp2_IRenderingEngine_h
#define genericApp2_IRenderingEngine_h

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
    virtual ~IRenderingEngine() {}
};
#endif
