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

    void multiplyByMatrix(const Matrix &m);

    inline float getX() const { return els[0]; };
    inline float getY() const { return els[1]; };
    inline float getZ() const { return els[2]; };
    inline float * getPointer() { return els; };

    void add(float x, float y, float z);

    float dot(const Vector &v) const;

    inline float getR() const { return els[0]; };
    inline float getG() const { return els[1]; };
    inline float getB() const { return els[2]; };
};


class VectorTestSled : public TestSled
{
public:
    void test();
};

#endif /* defined(__genericApp2__Vector__) */
