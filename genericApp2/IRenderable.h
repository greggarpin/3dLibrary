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
    IRenderable();
    virtual ~IRenderable();

    inline unsigned int getId() const { return renderableId; };

    virtual void PreRender(RenderMode mode) const;
    virtual void render(RenderMode mode) const = 0;
    virtual void PostRender(RenderMode mode) const {};

    static IRenderable *findObjectById(unsigned int id);

private:
    static void registerRenderable(IRenderable *obj);
    static void deregisterRenderable(IRenderable *obj);

    unsigned int renderableId;
    // TODO:: get rid of the next two when a real hash is available
    IRenderable *next;
    static IRenderable *list;
};

class IRenderableTestSled : public TestSled
{
public:
    void test();
};


#endif // !__IRENDERABLE_H__