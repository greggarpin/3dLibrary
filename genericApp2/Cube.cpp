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
    vertices[0].setPosition(-0.5, -0.5, -2.5);
    vertices[1].setPosition( 0.5, -0.5, -2.5);
    vertices[2].setPosition(-0.5,  0.5, -2.5);
    vertices[3].setPosition( 0.5,  0.5, -2.5);
    vertices[4].setPosition(-0.5, -0.5, -2);
    vertices[5].setPosition( 0.5, -0.5, -2);
    vertices[6].setPosition(-0.5,  0.5, -2);
    vertices[7].setPosition( 0.5,  0.5, -2);

    vertices[0].setColor(1, 0, 0);
    vertices[1].setColor(1, 0, 0);
    vertices[2].setColor(1, 0, 0);
    vertices[3].setColor(1, 0, 0);
    vertices[4].setColor(0, 0, 1);
    vertices[5].setColor(0, 0, 1);
    vertices[6].setColor(0, 0, 1);
    vertices[7].setColor(0, 0, 1);
}

Cube::~Cube()
{
}

void Cube::render(RenderMode mode) const
{
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getColorPointer());

    if (mode == wireframe) {
        static GLushort wireframeIndices [] = {0, 1, 3, 2, 0, 4, 5, 7, 6, 4, 0, 2, 6, 7, 3, 1, 5};

        glDrawElements(GL_LINE_STRIP, 17, GL_UNSIGNED_SHORT, wireframeIndices);
    }
    else
    {
        static GLushort solidIndices [] = {4, 5, 7, 4, 7, 6, 1, 0, 2, 1, 2, 3, 5, 1, 3, 5, 3, 7, 0, 4, 6, 0, 6, 2};

        glDrawElements(GL_TRIANGLES, sizeof(solidIndices)/sizeof(GLushort), GL_UNSIGNED_SHORT, solidIndices);
    }
}
