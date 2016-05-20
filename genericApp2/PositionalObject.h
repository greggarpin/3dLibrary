//
//  PositionalObject.h
//  genericApp2
//
//  Created by Arpin, Gregg on 12/10/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "Vector.h"
#include "IRenderable.h"

#ifndef genericApp2_PositionalObject_h
#define genericApp2_PositionalObject_h

class PositionalObject : public IRenderable
{
public:
    void PreRender(RenderMode mode) const;
    void PostRender(RenderMode mode) const;

    void SetPosition(float x, float y, float z);
    const Vector &GetPosition() const { return position; };
    void MoveBy(float x, float y, float z);

    // Rotations in radians
    void SetRotation(float xRot, float yRot, float zRot);
    const Vector &GetRotation() const { return rotation; };
    void RotateBy(float xRot, float yRot, float zRot);

private:
    void UpdateTransformMatrix();

    Vector position;
    Vector rotation;
    Matrix transformMatrix;
};

#endif
