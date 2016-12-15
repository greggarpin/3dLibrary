//
//  GLView.m
//  genericApp
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h>
#import "IRenderingEngine.h"
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@implementation GLView

- (id) initWithFrame:(CGRect)frame
{
    bool compassSupported = false;
    bool accelerometerSupported = false;
    bool forceES1 = false;

    if (self = [super initWithFrame:frame]) {
        self.multipleTouchEnabled = true;

        CAEAGLLayer *eaglLayer = (CAEAGLLayer*)super.layer;
        eaglLayer.opaque = YES;

        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;

       m_context = [[EAGLContext alloc] initWithAPI:api];

        if (!m_context || forceES1) {
            api = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:api];
        }

        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }

        if (api == kEAGLRenderingAPIOpenGLES1) {
            m_renderingEngine = CreateRenderer1();
        } else {
            m_renderingEngine = CreateRenderer2();
        }

        [m_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));

        [self drawView: nil];

        m_timestamp = CACurrentMediaTime();

        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];

        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];

        m_locationManager = [[CLLocationManager alloc] init];

#if TARGET_IPHONE_SIMULATOR
        compassSupported = false;
        accelerometerSupported = false;
#else
        compassSupported = true;
        accelerometerSupported = true;
#endif // TARGET_IPHONE_SIMULATOR

        if (compassSupported) {
            m_locationManager.headingFilter = kCLHeadingFilterNone;
            m_locationManager.delegate = self;
            [m_locationManager startUpdatingHeading];
        } else {
            NSLog(@"Compass not supported");
        }

        if (accelerometerSupported) {
            float updateFreq = 60;
            m_accelFilter = [[LowpassFilter alloc] initWithSampleRate:updateFreq cutoffFrequency:5];
            m_accelFilter.adaptive = true;

            [[UIAccelerometer sharedAccelerometer] setUpdateInterval:1.0/updateFreq];
            [[UIAccelerometer sharedAccelerometer] setDelegate:self];
        }
    }
    NSLog(@"Initialized");
    return self;
}

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (void) drawView : (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        float elapsedSec = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAnimation(elapsedSec);
    }

    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) didRotate : (NSNotification*) notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_renderingEngine->OnRotate((DeviceOrientation) orientation);
    [self drawView: nil];
}

- (void) dealloc
{
    if ([EAGLContext currentContext] == m_context) {
        [EAGLContext setCurrentContext:nil];
    }

    [m_context release];
    [super dealloc];
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    TouchPoint *tp = new TouchPoint[touches.count];
    for (int i = 0; i < touches.count; i++)
    {
        UITouch* touch = [[touches allObjects] objectAtIndex:i];
        CGPoint loc = [touch locationInView:self];
        tp[i].set(loc.x, loc.y);
    }

    TouchEvent te(tp, touches.count);
    m_renderingEngine->onTouchStart(te);
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    TouchPoint *tp = new TouchPoint[touches.count];
    for (int i = 0; i < touches.count; i++)
    {
        UITouch* touch = [[touches allObjects] objectAtIndex:i];
        CGPoint loc = [touch locationInView:self];
        tp[i].set(loc.x, loc.y);
    }

    TouchEvent te(tp, touches.count);
    m_renderingEngine->onTouchMoved(te);
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    TouchPoint *tp = new TouchPoint[touches.count];
    for (int i = 0; i < touches.count; i++)
    {
        UITouch* touch = [[touches allObjects] objectAtIndex:i];
        CGPoint loc = [touch locationInView:self];
        tp[i].set(loc.x, loc.y);
    }

    TouchEvent te(tp, touches.count);
    m_renderingEngine->onTouchEnd(te);
}

- (void) locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    float degrees = (float)newHeading.magneticHeading;
//    NSLog(@"Compass degrees: %f", degrees);
////    m_renderingEngine->SetRotationY(degrees*3.14159/180.0);
    m_renderingEngine->SetYaw(degrees*3.14159/180.0);
}

- (void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    [m_accelFilter addAcceleration:acceleration];
    float x = m_accelFilter.x;
    float y = m_accelFilter.y;
    float z = m_accelFilter.z;
    float angle = atan2f(z, -y);
//    NSLog(@"Received accelerometer: %f", angle);
//    NSLog(@"Received accelerometer: \nX: %f  Y: %f  Z: %f", x, y, z);
/////    m_renderingEngine->SetRotationX(-angle);
    m_renderingEngine->SetPitch(angle);
}
@end
