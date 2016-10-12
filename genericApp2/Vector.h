#ifndef __genericApp2__Vector__
#define __genericApp2__Vector__

#include "Matrix.h"

struct Vector
{
public:
    Vector();
    Vector(float x, float y, float z);

    float els[3];

    bool operator==(const Vector &v) const;
    Vector& operator=(const Vector &v);
    void set(float x, float y, float z);

    inline float getX() const { return els[0]; };
    inline float getY() const { return els[1]; };
    inline float getZ() const { return els[2]; };
    inline float * getPointer() { return els; };

    void add(float x, float y, float z);
    inline void add(const Vector &v) { add(v.getX(), v.getY(), v.getZ()); };
    inline void subtract(const Vector &v) { add(-v.getX(), -v.getY(), -v.getZ()); };

    virtual void multiply(float  scalar);

    float dot(const Vector &v) const;

    float length() const;
    float distance(const Vector &other) const;

    inline float getR() const { return els[0]; };
    inline float getG() const { return els[1]; };
    inline float getB() const { return els[2]; };
};

// TODO:: Merge these into one class
class Vector4 : public Vector
{
public:
    Vector4();
    Vector4(float x, float y, float z, float w);

    void set(float x, float y, float z, float w);
    
    inline float getW() const { return w_el; };

    virtual void multiply(float scalar);
    void multiplyByMatrix(const Matrix &m);

private:
    float w_el;
};

class VectorTestSled : public TestSled
{
public:
    void test();
};

#endif /* defined(__genericApp2__Vector__) */
