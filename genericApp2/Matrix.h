//
//  Matrix.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/6/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__Matrix__
#define __genericApp2__Matrix__

#include "TestSled.h"

class Matrix
{
public:
    Matrix();

    void multiply(const Matrix &other, Matrix &out) const;
    void multiply(const Matrix &other);
    inline float *getPointer() { return els; };
    inline void set(unsigned int row, unsigned int col, float value);
    inline float get(unsigned int row, unsigned col) const;
    void set(float v00, float v01, float v02, float v03,
             float v10, float v11, float v12, float v13,
             float v20, float v21, float v22, float v23,
             float v30, float v31, float v32, float v33);
    inline void set(const Matrix &other);

    void makeRotationMatrix(float *axis, float radians);
    void makeTranslationMatrix(float x, float y, float z);
    void makeIdentityMatrix();

private:
    float els[16];
};

class MatrixTestSled : public TestSled
{
public:
    void test();
};

#endif /* defined(__genericApp2__Matrix__) */
