#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MyMath
{
    struct Vector
    {
        float x, y;
    };

    float vectorGetMag(Vector v);
    Vector vectorGetAdd(Vector v1, Vector v2);
    Vector vectorGetSub(Vector v1, Vector v2);
    Vector normalize(Vector v);
    Vector vectorSetScale(Vector v, float a);
}

#endif
