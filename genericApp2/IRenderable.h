#ifndef __IRENDERABLE_H__
#define __IRENDERABLE_H__


struct Vertex{
    float Position[3];
    float Color[4];
};

class IRenderable
{
public:
    virtual void render() const = 0;
};

#endif // !__IRENDERABLE_H__