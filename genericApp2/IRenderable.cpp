#include "IRenderable.h"
#include "RenderContext.h"

IRenderable *IRenderable::list = NULL;

IRenderable::IRenderable() : next(NULL)
{
    static unsigned idIndex = 1;
    renderableId = idIndex++;
/*
    // Useful for visually debugging selection mode
    static int tester = -1;
    if (tester == 0)
        renderableId = 128;
    else if(tester ==1)
        renderableId = 255; // full red
    else if(tester ==2)
        renderableId = 255*256; // full green
    else if(tester ==3)
        renderableId = 256*256*255; // full blue
    else if(tester ==4)
        renderableId = 128*256*256 + 128*256 + 128; // 50% white
    tester++;
*/
    registerRenderable(this);
}

IRenderable::~IRenderable()
{
    deregisterRenderable(this);
}

void IRenderable::registerRenderable(IRenderable *obj)
{
    if (list == NULL)
    {
        list = obj;
    }
    else
    {
        IRenderable *curr;
        for (curr = list; curr->next != NULL; curr = curr->next);

        curr->next = obj;
    }
}

void IRenderable::deregisterRenderable(IRenderable *obj)
{
    if (list == NULL || obj == NULL)
    {
        return;
    }

    if (list == obj)
    {
        list = obj->next;
    }
    else
    {
        IRenderable *curr, *prev;
        for (prev = list, curr = list->next; curr != obj && curr != NULL; prev = curr, curr = curr->next);

        if (curr == obj)
        {
            prev->next = obj->next;
            obj->next = NULL;
        }
    }
}

IRenderable *IRenderable::findObjectById(unsigned int id)
{
    if (list == NULL)
        return NULL;

    IRenderable *curr;
    for (curr = list; curr != NULL; curr = curr->next)
    {
        if (curr->getId() == id)
            return curr;
    }

    return NULL;
}

void IRenderable::PreRender(RenderMode mode) const
{
    if (mode == selection)
    {
        RenderContext::getMutableContext()->applySelectionId(getId());
    }
}

class TestRenderable : public IRenderable
{
public:
    void render(RenderMode mode) const {};
};

void IRenderableTestSled::test()
{
    TestRenderable *test = new TestRenderable();
    IRenderable *foundObj = IRenderable::findObjectById(test->getId());

    test_fail_if(test != foundObj, "Expected to find 'test' registered");

    unsigned int testId = test->getId();

    delete test;

    foundObj = IRenderable::findObjectById(testId);

    test_fail_if(foundObj != NULL, "Did not expect to find 'test' registered after destruction");

    test_pass;
}