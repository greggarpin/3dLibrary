//
//  Polygon.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Polygon__
#define __genericApp2__Polygon__

#include "IRenderable.h"

class Polygon : public IRenderable
{
public:
    Polygon();
    virtual ~Polygon();

    void render(RenderMode mode) const;

private:
    VertexList vertices;
};

#endif /* defined(__genericApp2__Polygon__) */
