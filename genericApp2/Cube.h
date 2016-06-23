//
//  Cube.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Cube__
#define __genericApp2__Cube__

#include "PositionalObject.h"

class Cube : public PositionalObject
{
public:
    Cube();
    virtual ~Cube();

    void render(RenderMode mode) const;
    void renderNormals() const;

    inline void setColor(const Vector &pColor) { setColor(pColor.getR(), pColor.getG(), pColor.getB()); };
    void setColor(float r, float g, float b);
    const Vector &getColor() const { return color; };

private:
    VertexList vertices;
    Vector color;

    float size;
};

#endif /* defined(__genericApp2__Cube__) */
