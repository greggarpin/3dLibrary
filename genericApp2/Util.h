#ifndef __UTIL_H__
#define __UTIL_H__

// Adding #define NDEBUG will disable assertions
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159
#define DEG_TO_RAD(x) (PI * x / 180)
#define RAD_TO_DEG(x) (x * 180 / PI)
#define CLAMP_RAD(x) if (x > PI) x -= 2*PI; else if (x <= -PI) x += 2*PI;

#endif // !__UTIL_H__
