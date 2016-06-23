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
    setColor(1, 1, 1, 1);
    setNormal(0, 1, 0);
}

Vertex::Vertex(float x, float y, float z) : Vector(x, y, z)
{
    setColor(1, 1, 1, 1);
    setNormal(0, 1, 0);
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

void Vertex::setNormal(float x, float y, float z)
{
    normal[0] = x;
    normal[1] = y;
    normal[2] = z;
}

Vertex& Vertex::operator=(const Vertex &v)
{
    set(v.getX(), v.getY(), v.getZ());

    setColor(v.color[0], v.color[1], v.color[2], v.color[3]);

    setNormal(v.normal[0], v.normal[1], v.normal[2]);

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

float * VertexList::getNormalPointer() const
{
    return vertices[0].normal;
}

unsigned int VertexList::getStride() const
{
    return VERTEX_SIZE;
}

unsigned int VertexList::getNumVertices() const
{
    return numVertices;
}
