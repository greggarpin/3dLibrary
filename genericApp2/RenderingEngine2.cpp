//
//  RenderingEngine1.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.h"

#define STRINGIFY(A) #A
#include "shaders/Simple.vert"
#include "shaders/Simple.frag"

struct Vertex{
    float Position[3];
    float Color[4];
};

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep) {}
    void OnRotate(DeviceOrientation orientation) {}

private:
    GLuint BuildShader(const char *source, GLenum shaderType) const;
    GLuint BuildProgram(const char *vertShader, const char *fragShader) const;
    void ApplyOrtho(float maxX, float maxY) const;
    void ApplyPerspective(float near, float far, float left, float right, float top, float bottom);
    void ApplyRotation(float degrees) const;
    void RenderVertices(const Vertex *vertexArray, unsigned int numVertices, GLuint positionHandle, GLuint colorHandle) const;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    GLuint m_simpleProgram;
};


IRenderingEngine* CreateRenderer2()
{
    return new RenderingEngine2();
}

const Vertex Vertices[] = {
    {{-0.5, -0.866, 0}, {1,1,0.5,1}},
    {{0.5, -0.866, 0}, {1,1,0.5,1}},
    {{0, 1, 0}, {1,1,0.5,1}},
    {{-0.5, -0.866, 0}, {0.5,0.5,0.5,1}},
    {{0.5, -0.866, 0}, {0.5,0.5,0.5,1}},
    {{0, -0.4, 0}, {0.5,0.5,0.5,1}}
};

const Vertex Vertices_prime[] = {
    {{0, -0.866, 0}, {1,0.5,0.5,1}},
    {{1, -0.866, 0}, {1,0.5,0.5,1}},
    {{0.5, 1, 0},    {1,0.5,0.5,1}},
    {{0, -0.866, 0}, {1,0.5,0.5,1}},
    {{1, -0.866, 0}, {1,0.5,0.5,1}},
    {{0.5, -0.4, 0}, {1,0.5,0.5,1}}
};

const float s = 0.5;
const Vertex Vertices2[] = {
    {{-s, -s,  s}, {1, 1, 1, 1}},
    {{-s,  s,  s}, {1, 1, 1, 1}},
    {{ s, -s,  s}, {1, 1, 1, 1}},
    {{ s,  s,  s}, {1, 1, 1, 1}},

    {{ s,  s, -s}, {1, 0, 0, 1}},
    {{-s,  s, -s}, {1, 0, 0, 1}},
    {{ s, -s, -s}, {1, 0, 0, 1}},
    {{-s, -s, -s}, {1, 0, 0, 1}}
};

RenderingEngine2::RenderingEngine2()
{
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

void RenderingEngine2::Initialize(int width, int height)
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);

    glViewport(0, 0, width, height);

    m_simpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);

    glUseProgram(m_simpleProgram);

    ApplyRotation(0);
//    ApplyOrtho(2, 3);
    ApplyPerspective(-1, 1, -2, 2, -3, 3);
}

void RenderingEngine2::RenderVertices(const Vertex *vertexArray, unsigned int numVertices, GLuint positionHandle, GLuint colorHandle) const
{
    const GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &vertexArray[0].Position[0];
    const GLvoid *pColors = &vertexArray[0].Color[0];

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorHandle, 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void RenderingEngine2::Render() const
{
    glClearColor(.6,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");

    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);

    RenderVertices(Vertices, sizeof(Vertices)/sizeof(Vertex), positionSlot, colorSlot);
    RenderVertices(Vertices_prime, sizeof(Vertices_prime)/sizeof(Vertex), positionSlot, colorSlot);

    glDisableVertexAttribArray(colorSlot);
    glDisableVertexAttribArray(positionSlot);
}

GLuint RenderingEngine2::BuildProgram(const char *vertexShaderSource, const char *fragmentShaderSource) const
{
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLuint programHandle = glCreateProgram();

    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);

    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);

    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }

    return programHandle;
}

GLuint RenderingEngine2::BuildShader(const char *source, GLenum shaderType) const
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);

    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }

    return shaderHandle;
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
{
    float a = 1.0/maxX;
    float b = 1.0/maxY;

    float ortho[16] = {a, 0, 0, 0,
                        0, b, 0, 0,
                        0, 0, -1, 0,
                        0, 0, 0, 1};

    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void RenderingEngine2::ApplyPerspective(float near, float far, float left, float right, float top, float bottom)
{
    float a = 2*near/(right - left);
    float b = 2*near/(top - bottom);
    float c = (right+left)/(right - left);
    float d = (top+bottom)/(top - bottom);
    float e = (far+ near)/(far - near);
    float f = -2*far*near/(far - near);

    float proj[16] = {
        a,  0,  0,  0,
        0,  b,  0,  0,
        c,  d,  e,  -1,
        0,  0,  f,  1
    };

    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &proj[0]);
}

void RenderingEngine2::ApplyRotation(float degrees) const
{
    float radians = degrees * 3.14159/180.0;
    float s = std::sin(radians);
    float c = std::cos(radians);

    float zRotation[16] = {
        c, s, 0, 0,
        -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    glUniformMatrix4fv(modelviewUniform, 1, 0, &zRotation[0]);
}