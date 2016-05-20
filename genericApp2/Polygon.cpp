//
//  Polygon.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "Polygon.h"
#include "RenderContext.h"

Polygon::Polygon()
{
    vertices = new Vertex[3];

    vertices[0].Position[0] = 0;
    vertices[0].Position[1] = -0.866;
    vertices[0].Position[2] = 0;

    vertices[1].Position[0] = 1;
    vertices[1].Position[1] = -0.866;
    vertices[1].Position[2] = 0;

    vertices[2].Position[0] = 0.5;
    vertices[2].Position[1] = 1;
    vertices[2].Position[2] = 0;

    vertices[0].Color[0] = 1;
    vertices[0].Color[1] = .5;
    vertices[0].Color[2] = 1;
    vertices[0].Color[3] = 1;

    vertices[1].Color[0] = 1;
    vertices[1].Color[1] = .5;
    vertices[1].Color[2] = 1;
    vertices[1].Color[3] = 1;

    vertices[2].Color[0] = 1;
    vertices[2].Color[1] = .5;
    vertices[2].Color[2] = 1;
    vertices[2].Color[3] = 1;

    numVertices = 3;
}

Polygon::~Polygon()
{
    delete [] vertices;
}

void Polygon::render() const
{
    const GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &vertices[0].Position[0];
    const GLvoid *pColors = &vertices[0].Color[0];

    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}
