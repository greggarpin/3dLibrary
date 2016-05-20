//
//  RenderingEngine1.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.h"

class RenderingEngine1 : public IRenderingEngine {
public:
    RenderingEngine1();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep) {}
    void OnRotate(DeviceOrientation orientation) {}
    void Rotate(float xRadDelta, float yRadDelta, float zRadDelta) {};

    void onTouchStart(int x, int y) {};
    void onTouchMoved(int x, int y) {};
    void onTouchEnd(int x, int y) {};
    void SetRotation(float xRad, float yRad, float zRad);
    void SetRotationX(float rad);
    void SetRotationY(float rad);
    void SetRotationZ(float rad);

    void SetRoll(float rad);
    void SetPitch(float rad);
    void SetYaw(float rad);

private:
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
};


IRenderingEngine* CreateRenderer1()
{
    return new RenderingEngine1();
}

struct Vertex{
    float Position[2];
    float Color[4];
};

const Vertex Vertices[] = {
    {{-0.5, -0.866}, {1,1,0.5,1}},
    {{0.5, -0.866}, {1,1,0.5,1}},
    {{0, 1}, {1,1,0.5,1}},
    {{-0.5, -0.866}, {0.5,0.5,0.5,1}},
    {{0.5, -0.866}, {0.5,0.5,0.5,1}},
    {{0, -0.4}, {0.5,0.5,0.5,1}}
};

RenderingEngine1::RenderingEngine1()
{
    glGenRenderbuffersOES(1, &m_renderbuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
}

void RenderingEngine1::Initialize(int width, int height)
{
    glGenFramebuffersOES(1, &m_framebuffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_renderbuffer);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    const float maxX = 2;
    const float maxY = 3;
    glOrthof(-maxX, maxX, -maxY, maxY, -1, 1);

    glMatrixMode(GL_MODELVIEW);
}

void RenderingEngine1::Render() const
{
    glClearColor(0.5,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);

    GLsizei vertexCount = sizeof(Vertices)/sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void RenderingEngine1::SetRotation(float xRad, float yRad, float zRad)
{

}

void RenderingEngine1::SetRotationX(float rad)
{

}
void RenderingEngine1::SetRotationY(float rad)
{

}
void RenderingEngine1::SetRotationZ(float rad)
{
    
}

void RenderingEngine1::SetRoll(float rad)
{

}
void RenderingEngine1::SetPitch(float rad)
{

}
void RenderingEngine1::SetYaw(float rad)
{

}

