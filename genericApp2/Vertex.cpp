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

// TODO:: Need a separation between Vector and Vertex concepts.  This munges them together
Vertex::Vertex() : Vector(0, 0, 0)
{
    color[0] = color[1] = color[2] = color[3] = 1;
}

Vertex::Vertex(float x, float y, float z) : Vector(x, y, z)
{
    color[0] = color[1] = color[2] = color[3] = 1;
}

void Vertex::setPosition(float x, float y, float z)
{
    set(x, y, z);
}

void Vertex::setColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

Vertex& Vertex::operator=(const Vertex &v)
{
    set(v.getX(), v.getY(), v.getZ());

    color[0] = v.color[0];
    color[1] = v.color[1];
    color[2] = v.color[2];
    color[3] = v.color[3];

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

float * VertexList::getPositionPointer() const
{
    return vertices[0].getPointer();
}

float * VertexList::getColorPointer() const
{
    return vertices[0].color;
}

unsigned int VertexList::getStride() const
{
    return VERTEX_SIZE;
}

unsigned int VertexList::getNumVertices() const
{
    return numVertices;
}
