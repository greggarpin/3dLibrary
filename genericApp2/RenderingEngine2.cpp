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
#include "Polygon.h"
#include "Cube.h"
#include "Landscape.h"
#include "RenderContext.h"
#include "Matrix.h"
#include "Stack.h"
#include "Vector.h"
#include "Util.h"
#include "TouchEvent.h"
#include "Camera.h"

#define STRINGIFY(A) #A
#include "shaders/Simple.vert"
#include "shaders/Simple.frag"

class ShaderProgram {
public:
    ShaderProgram()
    {
        vertShaderHandle = fragShaderHandle = progHandle = 0;
    };
    void Build(const char *vertexShaderSource, const char *fragmentShaderSource)
    {
        GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        progHandle = glCreateProgram();
        RenderContext::getMutableContext()->setProgramHandle(progHandle);

        glAttachShader(progHandle, vertexShader);
        glAttachShader(progHandle, fragmentShader);
        glLinkProgram(progHandle);

        GLint linkSuccess;
        glGetProgramiv(progHandle, GL_LINK_STATUS, &linkSuccess);

        if (linkSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetProgramInfoLog(progHandle, sizeof(messages), 0, &messages[0]);
            std::cout << messages;
            exit(1);
        }
    }
    static ShaderProgram *GetActiveProgram()
    {
        return activeProgram;
    }
    void Use()
    {
        glUseProgram(progHandle);
        RenderContext::getMutableContext()->setProgramHandle(progHandle);
        ShaderProgram::activeProgram = this;
    }
    inline GLuint GetAttribLocation(const char *handleName)
    {
        return glGetAttribLocation(progHandle, handleName);
    }
    inline GLuint GetUniformLocation(const char *handleName)
    {
        return glGetUniformLocation(progHandle, handleName);
    }
private:
    GLuint vertShaderHandle, fragShaderHandle, progHandle;
    static ShaderProgram *activeProgram;

    GLuint BuildShader(const char *source, GLenum shaderType) const
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

};

ShaderProgram *ShaderProgram::activeProgram = NULL;

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep) {}
    void OnRotate(DeviceOrientation orientation) {}
    void Rotate(float deltaXRad, float deltaYRad, float deltaZRad);
    void SetRotation(float xRad, float yRad, float zRad);
    void SetRotationX(float rad) { SetRotation(rad, yRot, zRot); };
    void SetRotationY(float rad) { SetRotation(xRot, rad, zRot); };
    void SetRotationZ(float rad) { SetRotation(xRot, yRot, rad); };
    void SetRoll(float rad);
    void SetPitch(float rad);
    void SetYaw(float rad);

    void onTouchStart(const TouchEvent &event);
    void onTouchMoved(const TouchEvent &event);
    void onTouchEnd(const TouchEvent &event);
    void onTouchStart(int x, int y);
    void onTouchMoved(int x, int y);
    void onTouchEnd(int x, int y);
    void onTap(int x, int y);

private:
    GLuint BuildShader(const char *source, GLenum shaderType) const;
    GLuint BuildProgram(const char *vertShader, const char *fragShader) const;
    void ApplyOrtho(float maxX, float maxY) const;
    void ApplyPerspective(float near, float far, float left, float right, float bottom, float top);
    void ApplyRotation() const;
    void InitializeCameraMatrix() const;
    Vertex GetViewDirection() const;
    void GetWorldCoordFromScreenCoord(int screenX, int screenY, float worldHeight) const;
    void RenderObject(const IRenderable &obj) const;
    void selectPositionalObject(PositionalObject *obj);
    void deselectPositionalObject();
    bool linesAreColinear(const Vector &l1p0, const Vector &l1p1, const Vector &l2p0, const Vector &l2p1);
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    GLuint m_depthbuffer;
    ShaderProgram normalProgram;
    float xRot, yRot, zRot;
    bool useRollPitchYaw;
    int numTouchMoves;
    bool touchStarted;

    Polygon testPolygon;
mutable    Cube testCube;
    Cube tc[10];
    IRenderable **renderableObjs;
    unsigned int numRenderableObjs;
    PositionalObject *selectedPositionalObject;

    TouchEventList touchList;
};

void dotests()
{
    IRenderableTestSled rts;
    rts.test();
    
    MatrixTestSled mts;
    mts.test();

    VectorTestSled vts;
    vts.test();

    StackTestSled sts;
    sts.test();

    TouchEventTestSled tets;
    tets.test();

    CameraTestSled cts;
    cts.test();

    RenderContextTestSled rcts;
    rcts.test();
}
IRenderingEngine* CreateRenderer2()
{
    // TODO:: Don't do these when going live!
    if (1)
        dotests();

    return new RenderingEngine2();
}

RenderingEngine2::RenderingEngine2() : numRenderableObjs(0), selectedPositionalObject(NULL)
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);

    xRot = yRot = zRot = 0;
    touchStarted = false;
    numTouchMoves = 0;
    useRollPitchYaw = true;

    renderableObjs = new IRenderable*[numRenderableObjs++];
    renderableObjs[0] = &testCube;
    int i = 0;
    tc[i++].SetPosition(-3, 0, -2);
    tc[i++].SetPosition( 3, 0, -2);
    tc[i++].SetPosition(0, -3, -2);
    tc[i++].SetPosition(0,  3, -2);
    tc[i++].SetPosition(0, 0, -3);
    tc[i++].SetPosition(0, 0,  3);
    for (unsigned int j = 0; j < i; j++)
    {
        renderableObjs[numRenderableObjs++] = &tc[j];
    }

    testCube.SetPosition(0, 0, -2);
    testCube.SetRotation(PI/2, 0, 0);
}

void RenderingEngine2::Initialize(int width, int height)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);

    // Create and enable depth buffer testing
    glGenRenderbuffers(1, &m_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    RenderContext::getMutableContext()->setWidth(width);
    RenderContext::getMutableContext()->setHeight(height);

    glViewport(0, 0, width, height);

    normalProgram.Build(SimpleVertexShader, SimpleFragmentShader);

    normalProgram.Use();

    ApplyRotation();
//    ApplyOrtho(2, 3);
    ApplyPerspective(1, 10, -2, 2, -3, 3);
}

RenderMode renderMode = solidWireframe;
bool testRotation = false;
void RenderingEngine2::RenderObject(const IRenderable &obj) const
{
    obj.PreRender(renderMode);
    obj.render(renderMode);
    obj.PostRender(renderMode);
}
void RenderingEngine2::Render() const
{
    RenderContext::getMutableContext()->applySelectionId(0);

    GLuint positionSlot;
    GLuint colorSlot;
    GLuint normalSlot;
    if (renderMode == selection)
    {
    }
    positionSlot = ShaderProgram::GetActiveProgram()->GetAttribLocation("Position");
    colorSlot = ShaderProgram::GetActiveProgram()->GetAttribLocation("SourceColor");
    normalSlot = ShaderProgram::GetActiveProgram()->GetAttribLocation("Normal");

    if (renderMode == selection)
    {
        glClearColor(0, 0, 0, 0);
    }
    else
    {
        glClearColor(0.2,0.8,0.8,1);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderContext::getMutableContext()->setPositionHandle(positionSlot);
    RenderContext::getMutableContext()->setColorHandle(colorSlot);
    RenderContext::getMutableContext()->setNormalHandle(normalSlot);

    RenderContext::getMutableContext()->enableLighting();
    RenderContext::getMutableContext()->applyLightColor(1, 1, 1);
    RenderContext::getMutableContext()->applyLightPosition(1, 1, 0, true);

    InitializeCameraMatrix();

    Landscape::getLandscape()->render(renderMode);

    for (unsigned int i = 0; i < numRenderableObjs; i++)
    {
        if (renderableObjs[i] != NULL)
            RenderObject(*renderableObjs[i]);
    }
    if (testRotation)
        testCube.RotateBy(0.01, 0.01, 0);
    RenderContext::getMutableContext()->setPositionHandle(VERTEX_HANDLE_NONE);
    RenderContext::getMutableContext()->setColorHandle(VERTEX_HANDLE_NONE);
    RenderContext::getMutableContext()->setNormalHandle(VERTEX_HANDLE_NONE);
}

void RenderingEngine2::InitializeCameraMatrix() const
{
    const Camera *cam = Camera::getCamera();

    RenderContext::getMutableContext()->modelviewMatrix.makeTranslationMatrix(-cam->getPositionX(), -cam->getPositionY(), -cam->getPositionZ());
    RenderContext::getMutableContext()->applyModelviewMatrix();
    ApplyRotation();
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
{
    float a = 1.0/maxX;
    float b = 1.0/maxY;

    RenderContext::getMutableContext()->projectionMatrix.set(
                    a, 0, 0, 0,
                    0, b, 0, 0,
                    0, 0, -1, 0,
                    0, 0, 0, 1);
    RenderContext::getMutableContext()->applyProjectionMatrix();
}

void RenderingEngine2::ApplyPerspective(float near, float far, float left, float right, float bottom, float top)
{
    assert(left == -right);
    assert(top == -bottom);
// Still a problem for point.z == 0 (and subsequent points that straddle the line)
    float a = near/right;
    float b = near/top;
    float c = -(far + near)/(far - near);
    float d = -2*far*near/(far - near);

    RenderContext::getMutableContext()->projectionMatrix.set(
        a,  0,  0,  0,
        0,  b,  0,  0,
        0,  0,  c,  d,
        0,  0,  -1,  0);

    RenderContext::getMutableContext()->applyProjectionMatrix();
}

void RenderingEngine2::Rotate(float deltaXRad, float deltaYRad, float deltaZRad)
{
    xRot += deltaXRad;
    CLAMP_RAD(xRot);
    
    yRot += deltaYRad;
    CLAMP_RAD(yRot);

    zRot += deltaZRad;
    CLAMP_RAD(zRot);
}

void RenderingEngine2::SetRotation(float xRad, float yRad, float zRad)
{
    xRot = xRad;
    yRot = yRad;
    zRot = zRad;
}

void RenderingEngine2::ApplyRotation() const
{
    Matrix m;
    Camera *cam = Camera::getCamera();

    static float xAxis []  = {1, 0, 0};
    static float yAxis []  = {0, 1, 0};
    static float zAxis []  = {0, 0, 1};

 //   RenderContext::getMutableContext()->modelviewMatrix.makeIdentityMatrix();

    if (!useRollPitchYaw)
    {
        m.makeRotationMatrix(xAxis, xRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(yAxis, yRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(zAxis, zRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    }
    else
    {
        m.makeRotationMatrix(yAxis, cam->getYaw());
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(xAxis, cam->getPitch());
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(zAxis, cam->getRoll());
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    }

    RenderContext::getMutableContext()->applyModelviewMatrix();
}

void RenderingEngine2::onTouchStart(const TouchEvent &event)
{
    touchList.clear();

    touchList.appendEvent(event);

    deselectPositionalObject();

    // Single touch, attempt to select something
    if (event.getNumPoints() == 1)
    {
        const TouchPoint &curPoint = event.getPoint(0);

        RenderMode prevMode = renderMode;
        renderMode = selection;
        Render();
        renderMode = prevMode;

        unsigned int selectedId =
            RenderContext::getContext()->getSelectionIdAt(
                curPoint.getX(),
                RenderContext::getContext()->getHeight() - curPoint.getY());

        if (selectedId != 0)
        {
            IRenderable *selectedObject = IRenderable::findObjectById(selectedId);
            selectPositionalObject(dynamic_cast<PositionalObject*>(selectedObject));
        }
    }

}

bool RenderingEngine2::linesAreColinear(const Vector &l1p0, const Vector &l1p1, const Vector &l2p0, const Vector &l2p1)
{
    // Uses definition of a line as  {p : p = p0 + lambda(p1 - p0)}

    const float nearlyZero = 0.1;

    Vector l1Dir(l1p1);
    l1Dir.subtract(l1p0);
    float l1DirLen = l1Dir.length();

    Vector l2Dir(l2p1);
    l2Dir.subtract(l2p0);
    float l2DirLen = l2Dir.length();

    // If the lines aren't parallel, they aren't colinear
    if (fabs(l1Dir.dot(l2Dir)) - (l1DirLen * l2DirLen) > nearlyZero)
        return false;

    // Knowing that the lines are parallel, we need only check that one point from the second line is part of the first line
    // We do this by substituting l1p0 for p, l1p0 for p0 and l1p1 for p1 in the equation above and solving for lambda:
    //     lambda  =    (p - p0)   =   (l2p0 - l1p0)
    //                  -------        -------------
    //                  (p1 - p0)      (l1p1 - l1p0)
    //
    // Using x values to calculate the above, we substitute back in to the original equation and check for a true
    // statement when using y values:
    // l2p0.y = l1p0.y + (l2p0.x - l1p0.x) * (l1p1.y - l1p0.y)
    //                   -----------------
    //                   (l1p1.x - l1p0.x)
    //
    // Rearranging we get:
    // (l2p0.y - l1p0.y)(l1p1.x - l1p0.x) = (l2p0.x - l1p0.x) * (l1p1.y - l1p0.y)
    //
    // Or
    // (l2p0.y - l1p0.y)(l1p1.x - l1p0.x) - (l2p0.x - l1p0.x) * (l1p1.y - l1p0.y) = 0
    //
    // Of course, we have already calculated l1p1 - l1p0 above, so:
    // (l2p0.y - l1p0.y) * l1Dir.x - (l2p0.x - l1p0.x) * l1Dir.y = 0
    float leftHandSide = (l2p0.getY() - l1p0.getY()) * l1Dir.getX() - (l2p0.getX() - l1p0.getX()) * l1Dir.getY();

    return (fabs(leftHandSide) < nearlyZero);
}

void RenderingEngine2::onTouchMoved(const TouchEvent &event)
{
    // If we haven't done a touchStart first
    if (touchList.getNumItems() < 1)
        return;

    // If the number of touch points has changed, start over
    if (event.getNumPoints() != touchList.getFirst()->getNumPoints())
    {
        touchList.clear();
        onTouchStart(event);
        return;
    }

    touchList.appendEvent(event);

    // If we haven't moved enough to be counted
    const unsigned int tap_move_threshold = 2;
    if (touchList.getNumItems() < tap_move_threshold)
        return;

    Camera *cam = Camera::getCamera();

    // Moving a selected object
    if (event.getNumPoints() == 1)
    {
        if (selectedPositionalObject != NULL)
        {
            const TouchPoint &prevPoint = touchList.getPrevious()->getPoint(0);
            const TouchPoint &curPoint = event.getPoint(0);
// TODO:: Need to project movement onto appropriate plane
            selectedPositionalObject->MoveBy(
                ((float)(curPoint.getX() - prevPoint.getX()))/100.0,
                ((float)(prevPoint.getY() - curPoint.getY()))/100.0,
                0);
        }
    }
    else if (event.getNumPoints() == 2)
    {
        const TouchPoint &prevPoint0 = touchList.getPrevious()->getPoint(0);
        const TouchPoint &prevPoint1 = touchList.getPrevious()->getPoint(1);
        const TouchPoint &curPoint0 = event.getPoint(0);
        const TouchPoint &curPoint1 = event.getPoint(1);

        Vector delta0(curPoint0.getX() - prevPoint0.getX(), prevPoint0.getY() - curPoint0.getY(), 0);
        Vector delta1(curPoint1.getX() - prevPoint1.getX(), prevPoint1.getY() - curPoint1.getY(), 0);

        float dotProduct = delta0.dot(delta1);
        float d0Len = delta0.length();
        float d1Len = delta1.length();
        float lenDotProduct = d0Len*d1Len;
        float normalizedDot = dotProduct/lenDotProduct;

        // If both touches move in parallel, move along x and y axes
        if (fabs(normalizedDot - 1) < 0.1)
        {
            cam->increasePositionX(-delta0.getX()/100.0);
            cam->increasePositionY(-delta0.getY()/100.0);
        }
        else
        {
            const TouchPoint &firstPoint0 = touchList.getFirst()->getPoint(0);
            const TouchPoint &firstPoint1 = touchList.getFirst()->getPoint(1);
            Vector midpoint(firstPoint0.getX(), firstPoint0.getY(), 0);
            midpoint.add(firstPoint1.getX(), firstPoint1.getY(), 0);
            midpoint.multiply(0.5);

            Vector prevPoint0Vec(prevPoint0.getX(), prevPoint0.getY(), 0);
            Vector prevPoint1Vec(prevPoint1.getX(), prevPoint1.getY(), 0);
            Vector curPoint0Vec(curPoint0.getX(), curPoint0.getY(), 0);
            Vector curPoint1Vec(curPoint1.getX(), curPoint1.getY(), 0);

            Vector point0Dir(curPoint0Vec.getX() - prevPoint0Vec.getX(),
                             prevPoint0Vec.getY() - curPoint0Vec.getY(),
                             0);
            float point0DirLen = point0Dir.length();

            Vector point0Radius(curPoint0Vec.getX() - midpoint.getX(),
                                midpoint.getY() - curPoint0Vec.getY(),
                                0);
            float point0RadiusLen = point0Radius.length();

            // If we're moving towards or away from the midpoint, we have a pinch, move along z axis
            if (fabs(point0Dir.dot(point0Radius)) > 0.9 * point0DirLen * point0RadiusLen)
            {
                float curDist = curPoint0Vec.distance(curPoint1Vec);
                float prevDist = prevPoint0Vec.distance(prevPoint1Vec);
                float factor = 50.0;

                if (curDist > prevDist)
                    cam->increasePositionZ(-d0Len/factor);
                else
                    cam->increasePositionZ(d0Len/factor);

            }
            // Otherwise touches are moving in a circular pattern, rotate around y axis
            else
            {
                cam->increaseYaw(delta0.getX()/10.0);
            }
        }
    }
}

void RenderingEngine2::onTouchEnd(const TouchEvent &event)
{
    touchList.appendEvent(event);

    deselectPositionalObject();

    if (touchList.getNumItems() == 2)
        onTap(event.getPoint(0).getX(), event.getPoint(0).getY());

    touchList.clear();
}

void RenderingEngine2::onTouchStart(int x, int y)
{
}

void RenderingEngine2::onTouchMoved(int x, int y)
{
}

void RenderingEngine2::onTouchEnd(int x, int y)
{
}

void RenderingEngine2::selectPositionalObject(PositionalObject *obj)
{
    selectedPositionalObject = obj;
    Cube *c = dynamic_cast<Cube*>(obj);
    if (c != NULL)
        c->setColor(1, 0, 0);
}

void RenderingEngine2::deselectPositionalObject()
{
    Cube *c = dynamic_cast<Cube*>(selectedPositionalObject);
    if (c != NULL)
        c->setColor(0, 0, 1);
    
    selectedPositionalObject = NULL;
}

void RenderingEngine2::onTap(int x, int y)
{
    Camera::getCamera()->resetCamera();
}

void RenderingEngine2::SetRoll(float rad)
{
    useRollPitchYaw = true;
    Camera::getCamera()->setRoll(rad);
}
void RenderingEngine2::SetPitch(float rad)
{
    useRollPitchYaw = true;
    Camera::getCamera()->setPitch(rad);
}
void RenderingEngine2::SetYaw(float rad)
{
    useRollPitchYaw = true;
    Camera::getCamera()->setYaw(rad);
}

Vertex RenderingEngine2::GetViewDirection() const
{
    Camera *cam = Camera::getCamera();

    Vertex retValue;
    Vector4 transVect;
    Matrix rotMatrix;
    static float xAxis []  = {1, 0, 0};
    static float yAxis []  = {0, 1, 0};
    static float zAxis []  = {0, 0, 1};

    transVect.set(0, 0, 1, 1);

    rotMatrix.makeRotationMatrix(yAxis, cam->getYaw());
    transVect.multiplyByMatrix(rotMatrix);

    rotMatrix.makeRotationMatrix(xAxis, cam->getPitch());
    transVect.multiplyByMatrix(rotMatrix);

    rotMatrix.makeRotationMatrix(zAxis, cam->getRoll());
    transVect.multiplyByMatrix(rotMatrix);

    retValue.setPosition(transVect.getX(), transVect.getY(), transVect.getZ());

    return retValue;
}

void RenderingEngine2::GetWorldCoordFromScreenCoord(int screenX, int screenY, float worldHeight) const
{
    const Vertex floorNormal(0, 1, 0);
    Vertex view = GetViewDirection();

    // If view direction is close to (less than 5 degrees from) perpendicular to (0,1,0), don't try to find floor intersection
    if (false && fabs(view.dot(floorNormal)) < 5.0 * PI/180.0)
    {
        //    Return tapPos + viewDirection*10
    }
    else
    {
        Vertex near, far;
        // Return tapPos + viewDirection intersect with P(0,1,0,worldHeight)
        near = RenderContext::getContext()->UnProject(screenX, RenderContext::getContext()->getHeight() - screenY, 0);
        far = RenderContext::getContext()->UnProject(screenX,  RenderContext::getContext()->getHeight() - screenY, 1);

        float lambda = near.getX() - near.getY()*(far.getX() - near.getX())/(near.getY() - far.getY());

        Vertex delta(far);
        delta.subtract(near);
        delta.multiply(lambda);
        Vertex point(near);
        point.add(delta);
        LOG(point.getX() << ", " << point.getY() << ", " << point.getZ());
    }
}

