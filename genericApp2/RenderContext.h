//
//  RenderContext.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__RenderContext__
#define __genericApp2__RenderContext__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

class RenderContext
{
public:
    static const RenderContext *getContext()
    {
        return &rc;
    };

    void setPositionHandle(GLuint handle)
    {
        positionHandle = handle;
    };
    GLuint getPositionHandle() const
    {
        return positionHandle;
    };

    void setColorHandle(GLuint handle)
    {
        colorHandle = handle;
    };
    GLuint getColorHandle() const
    {
        return colorHandle;
    };

    bool isValid() const;
private:
    // Singleton - no public constructor
    RenderContext() : positionHandle(0), colorHandle(0) {};

    GLuint positionHandle;
    GLuint colorHandle;

    static RenderContext rc;
};

#endif /* defined(__genericApp2__RenderContext__) */
