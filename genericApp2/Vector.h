#ifndef __genericApp2__Vector__
#define __genericApp2__Vector__

#include "Matrix.h"

class Vector
{
public:
    Vector();
    Vector(float x, float y, float z, float w = 1);

    bool operator==(const Vector &v) const;
    Vector& operator=(const Vector &v);
    void set(float x, float y, float z, float w = 1);
    void setX(float x) { els[0] = x; };
    void setY(float y) { els[1] = y; };
    void setZ(float z) { els[2] = z; };
    void setW(float w) { els[3] = w; };

    inline float getX() const { return els[0]; };
    inline float getY() const { return els[1]; };
    inline float getZ() const { return els[2]; };
    inline float getW() const { return els[3]; };

    inline const float * getPointer() const { return els; };

    // Note* All math functions operate on 3-element vectors unless otherwise noted
    void add(float x, float y, float z);
    inline void add(const Vector &v) { add(v.getX(), v.getY(), v.getZ()); };
    inline void subtract(const Vector &v) { add(-v.getX(), -v.getY(), -v.getZ()); };

    virtual void multiply(float  scalar);

    float dot(const Vector &v) const;

    float length() const;
    float distance(const Vector &other) const;

    inline float getR() const { return getX(); };
    inline float getG() const { return getY(); };
    inline float getB() const { return getZ(); };

    // Operates using all 4 elements
    void multiplyByMatrix(const Matrix &m);
private:
    float els[4];

};

class VectorTestSled : public TestSled
{
public:
    void test();
};

#endif /* defined(__genericApp2__Vector__) */
