//
//  Vertex.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/4/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Vertex__
#define __genericApp2__Vertex__

#include "Matrix.h"
#include "Vector.h"

class Vertex : public Vector
{
public:
    Vertex();
    Vertex(float x, float y, float z);

    float color[4];

    Vertex& operator=(const Vertex &v);
    void setPosition(float x, float y, float z);
    void setColor(float r, float g, float b, float a = 1);
};

class VertexList
{
public:
    VertexList(unsigned int size = 10);
    ~VertexList();

    float *getPositionPointer() const;
    float *getColorPointer() const;

    void setSize(unsigned int size);

    Vertex &operator[](unsigned int index);

    unsigned int getStride() const;
    unsigned int getNumVertices() const;

private:
    Vertex *vertices;
    unsigned int numVertices;
};

#define VERTEX_SIZE (sizeof(Vertex))

#endif /* defined(__genericApp2__Vertex__) */
