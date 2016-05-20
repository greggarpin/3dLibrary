//
//  Matrix.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "Matrix.h"
#include <cmath>

Matrix::Matrix()
{
    makeIdentityMatrix();
}

void Matrix::multiply(const Matrix &other, Matrix &out) const
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            out.set(row, col,
                    get(row,0) * other.get(0,col) +
                    get(row,1) * other.get(1,col) +
                    get(row,2) * other.get(2,col) +
                    get(row,3) * other.get(3,col));
        }
    }
}

void Matrix::multiply(const Matrix &other)
{
    Matrix m;
    multiply(other, m);
    set(m);
}

void Matrix::set(unsigned int row, unsigned int col, float value)
{
    // assert(row < 4 && col < 4);
    els[row * 4 + col] = value;
}

float Matrix::get(unsigned int row, unsigned int col) const
{
    return els[row * 4 + col];
}

void Matrix::set(float v00, float v01, float v02, float v03,
                 float v10, float v11, float v12, float v13,
                 float v20, float v21, float v22, float v23,
                 float v30, float v31, float v32, float v33)
{
    els[0]  = v00; els[1]  = v01; els[2]  = v02; els[3]  = v03;
    els[4]  = v10; els[5]  = v11; els[6]  = v12; els[7]  = v13;
    els[8]  = v20; els[9]  = v21; els[10] = v22; els[11] = v23;
    els[12] = v30; els[13] = v31; els[14] = v32; els[15] = v33;
}

void Matrix::makeRotationMatrix(float *axis, float radians)
{
    // assert(axis[0] + axis[1] + axis[2] == 1);

    float c = cos(radians);
    float s = sin(radians);

    // Rotate about the x-axis
    if (axis[0]) {
        set(
            1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1
        );
    }
    if (axis[1])
    {
        set(
            c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1
        );
    }
    if (axis[2])
    {
        set(
            c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }
}

void Matrix::makeTranslationMatrix(float x, float y, float z)
{
    set(1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1);
}

void Matrix::makeIdentityMatrix()
{
    els[1] = els[2] = els[3] = els[4] = els[6] = els[7] = els[8] = els[9] = els[11] = els[12] = els[13] = els[14] = 0;

    els[0] = els[5] = els[10] = els[15] = 1;
}

void Matrix::set(const Matrix &other)
{
    set(other.els[0], other.els[1], other.els[2], other.els[3],
        other.els[4], other.els[5], other.els[6], other.els[7],
        other.els[8], other.els[9], other.els[10], other.els[11],
        other.els[12], other.els[13], other.els[14], other.els[15]);
}

bool Matrix::getInverse(Matrix &matOut) const
{
    double out[16], det;
    int i;

    out[0] = els[5]  * els[10] * els[15] -
        els[5]  * els[11] * els[14] -
        els[9]  * els[6]  * els[15] +
        els[9]  * els[7]  * els[14] +
        els[13] * els[6]  * els[11] -
        els[13] * els[7]  * els[10];

    out[4] = -els[4]  * els[10] * els[15] +
        els[4]  * els[11] * els[14] +
        els[8]  * els[6]  * els[15] -
        els[8]  * els[7]  * els[14] -
        els[12] * els[6]  * els[11] +
        els[12] * els[7]  * els[10];

    out[8] = els[4]  * els[9] * els[15] -
        els[4]  * els[11] * els[13] -
        els[8]  * els[5] * els[15] +
        els[8]  * els[7] * els[13] +
        els[12] * els[5] * els[11] -
        els[12] * els[7] * els[9];

    out[12] = -els[4]  * els[9] * els[14] +
        els[4]  * els[10] * els[13] +
        els[8]  * els[5] * els[14] -
        els[8]  * els[6] * els[13] -
        els[12] * els[5] * els[10] +
        els[12] * els[6] * els[9];

    out[1] = -els[1]  * els[10] * els[15] +
        els[1]  * els[11] * els[14] +
        els[9]  * els[2] * els[15] -
        els[9]  * els[3] * els[14] -
        els[13] * els[2] * els[11] +
        els[13] * els[3] * els[10];

    out[5] = els[0]  * els[10] * els[15] -
        els[0]  * els[11] * els[14] -
        els[8]  * els[2] * els[15] +
        els[8]  * els[3] * els[14] +
        els[12] * els[2] * els[11] -
        els[12] * els[3] * els[10];

    out[9] = -els[0]  * els[9] * els[15] +
        els[0]  * els[11] * els[13] +
        els[8]  * els[1] * els[15] -
        els[8]  * els[3] * els[13] -
        els[12] * els[1] * els[11] +
        els[12] * els[3] * els[9];

    out[13] = els[0]  * els[9] * els[14] -
        els[0]  * els[10] * els[13] -
        els[8]  * els[1] * els[14] +
        els[8]  * els[2] * els[13] +
        els[12] * els[1] * els[10] -
        els[12] * els[2] * els[9];

    out[2] = els[1]  * els[6] * els[15] -
        els[1]  * els[7] * els[14] -
        els[5]  * els[2] * els[15] +
        els[5]  * els[3] * els[14] +
        els[13] * els[2] * els[7] -
        els[13] * els[3] * els[6];

    out[6] = -els[0]  * els[6] * els[15] +
        els[0]  * els[7] * els[14] +
        els[4]  * els[2] * els[15] -
        els[4]  * els[3] * els[14] -
        els[12] * els[2] * els[7] +
        els[12] * els[3] * els[6];

    out[10] = els[0]  * els[5] * els[15] -
        els[0]  * els[7] * els[13] -
        els[4]  * els[1] * els[15] +
        els[4]  * els[3] * els[13] +
        els[12] * els[1] * els[7] -
        els[12] * els[3] * els[5];

    out[14] = -els[0]  * els[5] * els[14] +
        els[0]  * els[6] * els[13] +
        els[4]  * els[1] * els[14] -
        els[4]  * els[2] * els[13] -
        els[12] * els[1] * els[6] +
        els[12] * els[2] * els[5];

    out[3] = -els[1] * els[6] * els[11] +
        els[1] * els[7] * els[10] +
        els[5] * els[2] * els[11] -
        els[5] * els[3] * els[10] -
        els[9] * els[2] * els[7] +
        els[9] * els[3] * els[6];

    out[7] = els[0] * els[6] * els[11] -
        els[0] * els[7] * els[10] -
        els[4] * els[2] * els[11] +
        els[4] * els[3] * els[10] +
        els[8] * els[2] * els[7] -
        els[8] * els[3] * els[6];

    out[11] = -els[0] * els[5] * els[11] +
        els[0] * els[7] * els[9] +
        els[4] * els[1] * els[11] -
        els[4] * els[3] * els[9] -
        els[8] * els[1] * els[7] +
        els[8] * els[3] * els[5];

    out[15] = els[0] * els[5] * els[10] -
        els[0] * els[6] * els[9] -
        els[4] * els[1] * els[10] +
        els[4] * els[2] * els[9] +
        els[8] * els[1] * els[6] -
        els[8] * els[2] * els[5];

    det = els[0] * out[0] + els[1] * out[4] + els[2] * out[8] + els[3] * out[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        matOut.els[i] = out[i] * det;

    return true;
}


void MatrixTestSled::test()
{
    Matrix identity;
    Matrix m;
    Matrix out;

    float v = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            m.set(row, col, v);
            test_fail_if(m.get(row, col) != v, "Failed to set matrix value");
            v++;
        }
    }

    m.multiply(identity, out);
    v = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            test_fail_if(m.get(row, col) != out.get(row, col), "Unexpected value after identity multiply");
            v++;
        }
    }

    identity.multiply(m, out);
    v = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            test_fail_if(m.get(row, col) != out.get(row, col), "Unexpected value after identity multiply");
            v++;
        }
    }

    m.set(1, 0, 0, 0,
          0, 0, 1, 0,
          0, 1, 0, 0,
          0, 0, 0, 1);
    m.getInverse(out);
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            test_fail_if(m.get(row, col) != out.get(row, col), "Unexpected value after inverse");
        }
    }

    test_pass;
}
