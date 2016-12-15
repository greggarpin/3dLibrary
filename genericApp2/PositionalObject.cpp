//
//  PositionalObject.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 12/10/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "PositionalObject.h"
#include "RenderContext.h"
#include "Matrix.h"

void PositionalObject::PreRender(RenderMode mode) const
{
    IRenderable::PreRender(mode);

    RenderContext::getMutableContext()->pushMatrix();

    RenderContext::getMutableContext()->modelviewMatrix.multiply(transformMatrix);

    RenderContext::getMutableContext()->applyModelviewMatrix();
}

void PositionalObject::PostRender(RenderMode mode) const
{
    RenderContext::getMutableContext()->popMatrix();
}

void PositionalObject::SetPosition(const Vector &newPos)
{
    position = newPos;
    UpdateTransformMatrix();
}

void PositionalObject::SetPosition(float x, float y, float z)
{
    position.set(x, y, z);
    UpdateTransformMatrix();
}

void PositionalObject::MoveBy(float x, float y, float z)
{
    position.add(x, y, z);
    UpdateTransformMatrix();
}

void PositionalObject::SetRotation(const Vector &newRot)
{
    rotation = newRot;
    UpdateTransformMatrix();
}

void PositionalObject::SetRotation(float xRot, float yRot, float zRot)
{
    rotation.set(xRot, yRot, zRot);
    UpdateTransformMatrix();
}

void PositionalObject::RotateBy(float xRot, float yRot, float zRot)
{
    rotation.add(xRot, yRot, zRot);
    UpdateTransformMatrix();
}

void PositionalObject::UpdateTransformMatrix()
{
    Matrix m;

    transformMatrix.makeTranslationMatrix(position.getX(), position.getY(), position.getZ());

    static float xAxis[3] {1, 0, 0};
    static float yAxis[3] {0, 1, 0};
    static float zAxis[3] {0, 0, 1};

    m.makeRotationMatrix(xAxis, rotation.getX());
    transformMatrix.multiply(m);

    m.makeRotationMatrix(yAxis, rotation.getY());
    transformMatrix.multiply(m);

    m.makeRotationMatrix(zAxis, rotation.getZ());
    transformMatrix.multiply(m);
}
