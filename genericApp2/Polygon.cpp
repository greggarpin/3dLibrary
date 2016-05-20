//
//  Polygon.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <cmath>

#include "Polygon.h"
#include "RenderContext.h"
#include "Vertex.h"

Polygon::Polygon() : vertices(3)
{
    vertices[0].setPosition(0, -0.866, 0);
    vertices[1].setPosition(1, -0.866, 0);
    vertices[2].setPosition(0.5, 1, 0);

    vertices[0].setColor(1, .5, 1);
    vertices[1].setColor(1, .5, 1);
    vertices[2].setColor(1, .5, 1);
}

Polygon::~Polygon()
{
}

//#define USE_DRAW_ELS
void Polygon::render(RenderMode mode) const
{
    static unsigned int t = 2;
    t++;
    if (t > 16) t = 3;

    VertexList vertices(t);
    float angleDelta = 2*3.14159/t;
    float angle = 0;
    for (int i = 0; i < t; i++) {
        angle += angleDelta;
        vertices[i].setPosition(cos(angle), sin(angle), 0);
    }
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, vertices.getStride(), vertices.getColorPointer());

    // TODO:: Consider VBOs?

#ifndef USE_DRAW_ELS
    glDrawArrays(GL_LINE_LOOP, 0, vertices.getNumVertices());
#else
    GLushort indices[3] = {0, 1 ,2};
    glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, indices);
#endif // !USE_DRAW_ELS
}
