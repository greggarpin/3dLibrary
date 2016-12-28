//
//  Cube.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "Cube.h"
#include "RenderContext.h"

Cube::Cube() : vertices(24)
{
    size = 0.5;
    int v = 0;

    // Back face
    vertices[v].setPosition(-size,  size, -size); vertices[v].setNormal(0, 0, -1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size, -size, -size); vertices[v].setNormal(0, 0, -1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size, -size); vertices[v].setNormal(0, 0, -1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size,  size, -size); vertices[v].setNormal(0, 0, -1); vertices[v].setTextureCoord(0, 0); v++;

    // Front face
    vertices[v].setPosition( size,  size,  size); vertices[v].setNormal(0, 0, 1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size,  size); vertices[v].setNormal(0, 0, 1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size, -size,  size); vertices[v].setNormal(0, 0, 1); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size,  size,  size); vertices[v].setNormal(0, 0, 1); vertices[v].setTextureCoord(0, 0); v++;

    // Left face
    vertices[v].setPosition(-size,  size,  size); vertices[v].setNormal(-1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size, -size,  size); vertices[v].setNormal(-1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size, -size, -size); vertices[v].setNormal(-1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size,  size, -size); vertices[v].setNormal(-1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;

    // Right face
    vertices[v].setPosition( size,  size, -size); vertices[v].setNormal(1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size, -size); vertices[v].setNormal(1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size,  size); vertices[v].setNormal(1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size,  size,  size); vertices[v].setNormal(1, 0, 0); vertices[v].setTextureCoord(0, 0); v++;

    // Bottom face
    vertices[v].setPosition(-size, -size, -size); vertices[v].setNormal(0, -1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size, -size,  size); vertices[v].setNormal(0, -1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size,  size); vertices[v].setNormal(0, -1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size, -size, -size); vertices[v].setNormal(0, -1, 0); vertices[v].setTextureCoord(0, 0); v++;

    // Top face
    vertices[v].setPosition( size,  size, -size); vertices[v].setNormal(0, 1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition( size,  size,  size); vertices[v].setNormal(0, 1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size,  size,  size); vertices[v].setNormal(0, 1, 0); vertices[v].setTextureCoord(0, 0); v++;
    vertices[v].setPosition(-size,  size, -size); vertices[v].setNormal(0, 1, 0); vertices[v].setTextureCoord(0, 0); v++;

    setColor(0, 0, 1);
/* // Color back face
    vertices[0].setColor(1, 0, 0);
    vertices[1].setColor(1, 0, 0);
    vertices[2].setColor(1, 0, 0);
    vertices[3].setColor(1, 0, 0);
    vertices[10].setColor(1, 0, 0);
    vertices[11].setColor(1, 0, 0);
    vertices[12].setColor(1, 0, 0);
    vertices[13].setColor(1, 0, 0);
    vertices[16].setColor(1, 0, 0);
    vertices[19].setColor(1, 0, 0);
    vertices[20].setColor(1, 0, 0);
    vertices[23].setColor(1, 0, 0);
 */
}

Cube::~Cube()
{
}

void Cube::render(RenderMode mode) const
{
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getPositionPointer());

    glVertexAttribPointer(RenderContext::getContext()->getNormalHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getNormalPointer());
    if (mode == wireframe || mode == solidWireframe)
    {
        static const GLfloat blackColor [] = {0,0,0,1};
        glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, 0, blackColor);

        RenderContext::getContext()->disableLighting();

        static GLushort wireframeIndices [] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 7, 1, 6, 3, 4, 2, 5};

        glDrawElements(GL_LINE_STRIP, sizeof(wireframeIndices)/sizeof(GLushort), GL_UNSIGNED_SHORT, wireframeIndices);
    }

    if (mode != wireframe)
    {
        static GLushort solidIndices [] = {
                                            // Back face
                                            2, 1, 0,
                                            3, 2, 0,

                                            // Front face
                                            6, 5, 4,
                                            7, 6, 4,

                                            // Left face
                                            10, 9, 8,
                                            11, 10, 8,

                                            // Right face
                                            14, 13, 12,
                                            15, 14, 12,

                                            // Bottom face
                                            18, 17, 16,
                                            19, 18, 16,

                                            // Top face
                                            22, 21, 20,
                                            23, 22, 20
                                            };

        RenderContext::getContext()->enableLighting();
        RenderContext::getContext()->enableTexturing();

        glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getColorPointer());
        glVertexAttribPointer(RenderContext::getContext()->getNormalHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getNormalPointer());
        glVertexAttribPointer(RenderContext::getContext()->getTextureCoordHandle(), 2, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getTextureCoordPointer());
        glDrawElements(GL_TRIANGLES, sizeof(solidIndices)/sizeof(GLushort), GL_UNSIGNED_SHORT, solidIndices);

        RenderContext::getContext()->disableTexturing();
    }
    renderNormals();
}

void Cube::setColor(float r, float g, float b)
{
    for (int i = 0; i < vertices.getNumVertices(); i++)
    {
        vertices[i].setColor(r, g, b);
    }
}

void Cube::renderNormals() const
{
    VertexList normalVertices(12);
    const float normalLength = 1;

    unsigned int v = 0;

    normalVertices[v++].setPosition(0, 0, size);
    normalVertices[v++].setPosition(0, 0, size + normalLength);

    normalVertices[v++].setPosition(0, 0, -size);
    normalVertices[v++].setPosition(0, 0, -size - normalLength);

    normalVertices[v++].setPosition(0, size, 0);
    normalVertices[v++].setPosition(0, size + normalLength, 0);

    normalVertices[v++].setPosition(0, -size, 0);
    normalVertices[v++].setPosition(0, -size - normalLength, 0);

    normalVertices[v++].setPosition(size, 0, 0);
    normalVertices[v++].setPosition(size + normalLength, 0, 0);

    normalVertices[v++].setPosition(-size, 0, 0);
    normalVertices[v++].setPosition(-size - normalLength, 0, 0);

    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, normalVertices.getStride(), normalVertices.getPositionPointer());

    glVertexAttribPointer(RenderContext::getContext()->getNormalHandle(), 3, GL_FLOAT, GL_FALSE, normalVertices.getStride(), normalVertices.getNormalPointer());

    static const GLfloat blackColor [] = {0,0,0,1};
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, 0, blackColor);

    RenderContext::getContext()->disableLighting();

    static GLushort indices [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    glDrawElements(GL_LINES, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, indices);
}