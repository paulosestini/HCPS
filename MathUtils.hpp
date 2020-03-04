#ifndef MATHUTILS_H
#define MATHUTILS_H

struct Vector
{
    float x, y;
};

float vectorMag(Vector v);
Vector vectorAdd(Vector v1, Vector v2);
Vector vectorSub(Vector v1, Vector v2);
Vector normalize(Vector v);
Vector vectorScale(Vector v, float a);

#endif
