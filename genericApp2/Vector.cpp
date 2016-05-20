#include <stdio.h>
#include "Vector.h"

Vector::Vector()
{
    set(0, 0, 0);
}

Vector::Vector(float x, float y, float z)
{
    set(x, y, z);
}

bool Vector::operator==(const Vector &v) const
{
    return  getX() == v.getX() &&
            getY() == v.getY() &&
            getZ() == v.getZ();
}

Vector& Vector::operator=(const Vector &v)
{
    set(v.getX(), v.getY(), v.getZ());

    return *this;
}

void Vector::set(float x, float y, float z)
{
    els[0] = x;
    els[1] = y;
    els[2] = z;
}

void Vector::multiplyByMatrix(const Matrix &m)
{
    set(getX() * m.get(0, 0) + getY() * m.get(0, 1) + getZ() * m.get(0, 2) + m.get(0, 3),
        getX() * m.get(1, 0) + getY() * m.get(1, 1) + getZ() * m.get(1, 2) + m.get(1, 3),
        getX() * m.get(2, 0) + getY() * m.get(2, 1) + getZ() * m.get(2, 2) + m.get(2, 3));
}

float Vector::dot(const Vector &v) const
{
    return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

void VectorTestSled::test()
{
    Vector u;
    Vector v(1, 2, 3);
    Vector w(1, 2, 3);

    test_fail_if(u == v, "u and v should not be equal");
    test_fail_if(!(v == w), "v and w should be equal");

    u = v;
    test_fail_if(!(u == v), "u and v should be equal");

    float vwDp = v.dot(w);
    float vvDp = v.dot(v);
    float expDp = 1*1 + 2*2 + 3*3;

    test_fail_if(expDp != vwDp, "vwDp unexpected dot product");
    test_fail_if(vvDp != vwDp, "vvDP unexpected dot product");

    test_pass;
}