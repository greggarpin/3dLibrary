//
//  Vertex.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/4/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <stdio.h>
#include "Vertex.h"

#define MIN(x, y) (x < y ? x : y)

Vertex::Vertex()
{
    setPosition(0, 0, 0);
    setColor(1, 1, 1, 1);
    setNormal(0, 1, 0);
}

Vertex& Vertex::operator=(const Vertex &v)
{
    position = v.getPosition();
    color = v.getColor();
    normal = v.getNormal();

    return *this;
}


VertexList::VertexList(unsigned int size)
{
////    assert(presize > 0)

    vertices = NULL;
    setSize(size);
}

VertexList::~VertexList()
{
    delete [] vertices;
}

void VertexList::setSize(unsigned int size)
{
    Vertex *newArray = new Vertex[size];

    if (vertices)
    {
        unsigned int minVert = (size < numVertices ? size : numVertices);

        for (unsigned int i = 0; i < minVert; i++)
        {
            newArray[i] = vertices[i];
        }

        delete [] vertices;
    }
    vertices = newArray;

    numVertices = size;
}

Vertex & VertexList::operator[](unsigned int index)
{
    //// assert(index < numVertices);
    return vertices[index];
}
