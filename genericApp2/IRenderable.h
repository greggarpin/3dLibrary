#ifndef __IRENDERABLE_H__
#define __IRENDERABLE_H__

#include "Vertex.h"

enum RenderMode {
    normal,
    wireframe,
    selection
};

class IRenderable
{
public:
    IRenderable() {
        static unsigned long idIndex = 0;
        renderableId = idIndex++;
    };

    inline unsigned long int getId() const { return renderableId; };

    virtual void render(RenderMode mode) const = 0;

private:
    unsigned long int renderableId;
};

#endif // !__IRENDERABLE_H__