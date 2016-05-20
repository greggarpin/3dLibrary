#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__

#include "IRenderable.h"

class Landscape
{
public:

    static const Landscape *getLandscape();
    void render(RenderMode mode) const;

private:
    // Singleton - private constructor
    Landscape();

    VertexList gridVertices;
    VertexList domeVertices;
    VertexList cellarVertices;
};

#endif // !__LANDSCAPE_H__