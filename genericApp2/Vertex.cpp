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
Vertex::Vertex()
{
    position[0] = position[1] = position[2] = 0;
    color[0] = color[1] = color[2] = color[3] = 1;
}

Vertex::Vertex(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    color[0] = color[1] = color[2] = color[3] = 1;
}

void Vertex::setPosition(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void Vertex::setColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

Vertex Vertex::operator=(const Vertex &v)
{
    position[0] = v.position[0];
    position[1] = v.position[1];
    position[2] = v.position[2];

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
    return vertices[0].position;
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

void Vertex::multiplyByMatrix(const Matrix *m)
{
    setPosition(
        getX() * m->get(0, 0) + getY() * m->get(0, 1) + getZ() * m->get(0, 2) + m->get(0, 3),
        getX() * m->get(1, 0) + getY() * m->get(1, 1) + getZ() * m->get(1, 2) + m->get(1, 3),
        getX() * m->get(2, 0) + getY() * m->get(2, 1) + getZ() * m->get(2, 2) + m->get(2, 3)
    );
}

float Vertex::dot(const Vertex *v) const
{
    return
        getX() * v->getX() +
        getY() * v->getY() +
        getZ() * v->getZ();
}