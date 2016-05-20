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

struct Vertex
{
public:
    Vertex();
    Vertex(float x, float y, float z);

    float position[3];
    float color[4];

    Vertex operator=(const Vertex &v);
    void setPosition(float x, float y, float z);
    void setColor(float r, float g, float b, float a = 1);

    void multiplyByMatrix(const Matrix *m);

    inline float getX() const { return position[0]; };
    inline float getY() const { return position[1]; };
    inline float getZ() const { return position[2]; };

    float dot(const Vertex *v) const;
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
