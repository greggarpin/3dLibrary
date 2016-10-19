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

class Vertex
{
public:
    Vertex();

public:

    inline const float* getPositionPointer() const { return position.getPointer(); }
    inline const Vector& getPosition() const { return position; };
    inline void setPosition(float x, float y, float z) { position.set(x, y, z); }

    inline const float* getNormalPointer() const { return normal.getPointer(); }
    inline const Vector& getNormal() const { return normal; };
    inline void setNormal(float x, float y, float z) { normal.set(x, y, z); }

    inline const float* getColorPointer() const { return color.getPointer(); }
    inline const Vector& getColor() const { return color; };
    inline void setColor(float r, float g, float b, float a = 1) { color.set(r, g, b, a); }

    Vertex& operator=(const Vertex &v);

private:
    Vector position;
    Vector color;
    Vector normal;
};

class VertexList
{
public:
    VertexList(unsigned int size = 10);
    ~VertexList();

    inline const float *getPositionPointer() const { return vertices[0].getPositionPointer(); }
    inline const float *getColorPointer() const { return vertices[0].getColorPointer(); }
    inline const float *getNormalPointer() const { return vertices[0].getNormalPointer(); }

    void setSize(unsigned int size);

    Vertex &operator[](unsigned int index);

    unsigned int getStride() const { return sizeof(Vertex); };
    unsigned int getNumVertices() const { return numVertices; };

private:
    Vertex *vertices;
    unsigned int numVertices;
};

#endif /* defined(__genericApp2__Vertex__) */
