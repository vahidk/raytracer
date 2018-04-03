/*
 * global.h
 * Global definitions and declerations
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <vector>


//#include "../MMGR/MMGR.h"

// TODO: convet macros to constants and inline functions

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#define PI 3.14159265358979323846f
#define PIx2 6.28318530717958647692f
#define halfPI 1.57079632679489661923f
#define qrtPI 0.785398163397448309615f
#define RAD(x) (PI * (x) / 180)
#define DEG(x) (180 * (x) / PI)
#define P2(x) ((x) * (x))
#define P3(x) ((x) * (x) * (x))
#define CLAMP(x, min, max)                                                     \
  (((x) > (max)) ? (max) : (((x) < (min)) ? (min) : (x)))
#define SATURATE(x) CLAMP(x, 0, 1)
#define EPSILON 0.001f
#define FRAND (2 * ((float)rand() / RAND_MAX - 0.5f))
#define AFRAND ((float)rand() / RAND_MAX)
#define PFMOD(x, y) (fmodf(fmodf(x, y) + y, y))

namespace vrt {

typedef unsigned int uint;
typedef unsigned char uchar;

}  // namespace vrt
