//
//  2DLayer.h
//  genericApp2
//
//  Created by Arpin, Gregg on 1/7/2017.
//  Copyright (c) 2017 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Overlay__
#define __genericApp2__Overlay__

#include "IRenderable.h"

class Overlay : public IRenderable
{
public:
    Overlay(float leftP, float topP, float widthP, float heightP, const char *imgPath);
    virtual ~Overlay();

    void PreRender(RenderMode mode) const;
    void render(RenderMode mode) const;
    void PostRender(RenderMode mode) const;

    void setBackgroundColor(float r, float g, float b);
private:
    float left, top, right, bottom;
    VertexList vertices;
};

#endif /* defined(__genericApp2__Overlay__) */
