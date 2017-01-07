#include "Overlay.h"
#include "RenderContext.h"


Overlay::Overlay(float leftP, float topP, float widthP, float heightP, const char *imgPath) : vertices(4)
{
    left = leftP;
    top = topP;
    right = left + widthP;
    bottom = top - heightP;

    unsigned int v = 0;
    vertices[v].setPosition(left, top, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(left, bottom, 0); vertices[v].setTextureCoord(1, 0); v++;
    vertices[v].setPosition(right, bottom, 0); vertices[v].setTextureCoord(1, 1); v++;
    vertices[v].setPosition(right, top, 0); vertices[v].setTextureCoord(0, 1); v++;

    setBackgroundColor(0, 0, 100);
}

Overlay::~Overlay()
{
}

void Overlay::PreRender(RenderMode mode) const
{
    IRenderable::PreRender(mode);
    RenderContext::getContext()->disableLighting();
    RenderContext::getContext()->disableNormalHandle();
    RenderContext::getContext()->disableTransformations();
}

void Overlay::PostRender(RenderMode mode) const
{
    RenderContext::getContext()->enableTransformations();
    IRenderable::PostRender(mode);
}

void Overlay::render(RenderMode mode) const
{
    static GLushort indices [] = {0, 1, 2, 3 };

    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getColorPointer());
    glVertexAttribPointer(RenderContext::getContext()->getTextureCoordHandle(), 2, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getTextureCoordPointer());
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getPositionPointer());

    glDrawElements(GL_TRIANGLE_FAN, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, indices);

    static const GLfloat blackColor [] = {0,0,0,0};
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 1, GL_FLOAT, GL_FALSE, 1, blackColor);
    glDrawElements(GL_LINE_LOOP, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, indices);
}

void Overlay::setBackgroundColor(float r, float g, float b)
{
    for (unsigned int i = 0; i < vertices.getNumVertices(); i++)
    {
        vertices[i].setColor(r, g, b);
    }
}