//
//  GLView.h
//  genericApp
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <CoreLocation/CoreLocation.h>
#import "AccelerometerFilter.h"

struct IRenderingEngine;

@interface GLView : UIView <CLLocationManagerDelegate, UIAccelerometerDelegate> {
@private
    EAGLContext *m_context;
    struct IRenderingEngine *m_renderingEngine;
    float m_timestamp;
    CLLocationManager *m_locationManager;
    AccelerometerFilter *m_accelFilter;
}

- (void) drawView : (CADisplayLink*) displayLink;
- (void) didRotate : (NSNotification*) notification;

@end
