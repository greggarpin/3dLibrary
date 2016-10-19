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

    void setColor(float r, float g, float b);

private:
    VertexList vertices;

    float size;
};

#endif /* defined(__genericApp2__Cube__) */
