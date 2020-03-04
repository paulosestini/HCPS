#include "MathUtils.hpp"
#include <math.h>

namespace MyMath
{
    float vectorGetMag(Vector v)
    {
        return std::sqrt(v.x*v.x + v.y*v.y);
    }

    Vector vectorGetAdd(Vector v1, Vector v2)
    {
        Vector newVector;
        newVector.x = v1.x + v2.x;
        newVector.y = v1.y + v2.y;
        return newVector;
    }

    Vector vectorGetSub(Vector v1, Vector v2)
    {
        Vector newVector;
        newVector.x = v1.x - v2.x;
        newVector.y = v1.y - v2.y;
        return newVector;

    }

    Vector normalize(Vector v)
    {   
        float mag = vectorGetMag(v);
        v.x /= mag;
        v.y /= mag;
        return v;
    }

    Vector vectorSetScale(Vector v, float a)
    {
        v.x *= a;
        v.y *= a;
        return v;
    }
}