#include <stdio.h>
#include <math.h>
#include "Vector.h"

Vector::Vector()
{
    set(0, 0, 0, 1);
}

Vector::Vector(float x, float y, float z, float w)
{
    set(x, y, z, w);
}

bool Vector::operator==(const Vector &v) const
{
    return  getX() == v.getX() &&
            getY() == v.getY() &&
            getZ() == v.getZ() &&
            getW() == v.getW();
}

Vector& Vector::operator=(const Vector &v)
{
    set(v.getX(), v.getY(), v.getZ(), v.getW());

    return *this;
}

void Vector::set(float x, float y, float z, float w)
{
    els[0] = x;
    els[1] = y;
    els[2] = z;
    els[3] = w;
}

void Vector::add(float x, float y, float z)
{
    els[0] += x;
    els[1] += y;
    els[2] += z;
}

void Vector::multiply(float scalar)
{
    els[0] *= scalar;
    els[1] *= scalar;
    els[2] *= scalar;
}

float Vector::dot(const Vector &v) const
{
    return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

float Vector::length() const
{
    return sqrt(getX()*getX() + getY()*getY() + getZ()*getZ());
}

float Vector::distance(const Vector &other) const
{
    float dx = other.getX() - getX();
    float dy = other.getY() - getY();
    float dz = other.getZ() - getZ();

    return sqrt(dx*dx + dy*dy + dz*dz);
}

void Vector::multiplyByMatrix(const Matrix &m)
{
    set(getX() * m.get(0, 0) + getY() * m.get(0, 1) + getZ() * m.get(0, 2) + getW() * m.get(0, 3),
        getX() * m.get(1, 0) + getY() * m.get(1, 1) + getZ() * m.get(1, 2) + getW() * m.get(1, 3),
        getX() * m.get(2, 0) + getY() * m.get(2, 1) + getZ() * m.get(2, 2) + getW() * m.get(2, 3),
        getX() * m.get(3, 0) + getY() * m.get(3, 1) + getZ() * m.get(3, 2) + getW() * m.get(3, 3));
}


void VectorTestSled::test()
{
    Vector u;
    const Vector v(1, 2, 3);
    const Vector w(1, 2, 3);

    test_fail_if(u == v, "u and v should not be equal");
    test_fail_if(!(v == w), "v and w should be equal");

    u = v;
    test_fail_if(!(u == v), "u and v should be equal");

    float vwDp = v.dot(w);
    float vvDp = v.dot(v);
    float expDp = 1*1 + 2*2 + 3*3;

    test_fail_if(expDp != vwDp, "vwDp unexpected dot product");
    test_fail_if(vvDp != vwDp, "vvDP unexpected dot product");

    test_fail_if(fabs(v.length() - sqrt(14)) > 0.000001, "Incorrect length of Vector v");
    test_fail_if(fabs(v.distance(w)) > 0.000001, "Incorrect distance between v and w - expected 0");

    test_pass;
}