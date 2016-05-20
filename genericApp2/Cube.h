//
//  Cube.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Cube__
#define __genericApp2__Cube__

#include "IRenderable.h"

class Cube : public IRenderable
{
public:
    Cube();
    virtual ~Cube();

    void render(RenderMode mode) const;

private:
    VertexList vertices;
};

#endif /* defined(__genericApp2__Cube__) */
