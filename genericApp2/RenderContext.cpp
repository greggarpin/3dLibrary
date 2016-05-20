//
//  RenderContext.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "RenderContext.h"

bool RenderContext::isValid() const
{
    return positionHandle != 0 && colorHandle != 0;
}