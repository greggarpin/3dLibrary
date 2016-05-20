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
    bool forceES1 = false;
    if (self = [super initWithFrame:frame]) {
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

        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        [m_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];

        [self drawView: nil];

        m_timestamp = CACurrentMediaTime();

        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];

        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];
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
@end
