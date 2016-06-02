//
//  Cube.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "Cube.h"
#include "RenderContext.h"

Cube::Cube() : vertices(8)
{
    float sz = 0.5;
    vertices[0].setPosition(-sz, -sz, -sz);
    vertices[1].setPosition( sz, -sz, -sz);
    vertices[2].setPosition(-sz,  sz, -sz);
    vertices[3].setPosition( sz,  sz, -sz);
    vertices[4].setPosition(-sz, -sz,  sz);
    vertices[5].setPosition( sz, -sz,  sz);
    vertices[6].setPosition(-sz,  sz,  sz);
    vertices[7].setPosition( sz,  sz,  sz);
/*
    vertices[0].setColor(1, 0, 0);
    vertices[1].setColor(1, .5, 0);
    vertices[2].setColor(1, 1, 0);
    vertices[3].setColor(0, 1, 0);
    vertices[4].setColor(0, 0, 1);
    vertices[5].setColor(1, 0, 1);
    vertices[6].setColor(1, 0.5, .5);
    vertices[7].setColor(1, .33, .67);
 /*/
    setColor(0, 0, 1);
//*/
}

Cube::~Cube()
{
}

void Cube::render(RenderMode mode) const
{
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getPositionPointer());

    if (mode == wireframe || mode == solidWireframe)
    {
        static GLfloat blackColor [] = {0,0,0,1};
        glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, 0, blackColor);

        static GLushort wireframeIndices [] = {0, 1, 3, 2, 0, 4, 5, 7, 6, 4, 0, 2, 6, 7, 3, 1, 5};

        glDrawElements(GL_LINE_STRIP, 17, GL_UNSIGNED_SHORT, wireframeIndices);
    }

    if (mode != wireframe)
    {
        static GLushort solidIndices [] = {
                                            7, 5, 4,
                                            6, 7, 4,
                                            2, 0, 1,
                                            2, 1, 3,
                                            3, 1, 5,
                                            3, 5, 7,
                                            6, 4, 0,
                                            6, 0, 2,
                                            7, 6, 2,
                                            7, 2, 3,
                                            4, 5, 1,
                                            4, 1, 0
                                            };
        glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getColorPointer());
        glDrawElements(GL_TRIANGLES, sizeof(solidIndices)/sizeof(GLushort), GL_UNSIGNED_SHORT, solidIndices);
    }
}

void Cube::setColor(float r, float g, float b)
{
    color.set(r, g, b);
    for (int i = 0; i < 8; i++)
    {
        vertices[i].setColor(r, g, b);
    }
}
