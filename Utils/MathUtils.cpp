#include "MathUtils.hpp"
#include <math.h>

namespace MathUtils
{
    double vectorMag(Vector v)
    {
        return std::sqrt(v.x*v.x + v.y*v.y);
    }

    Vector vectorAdd(Vector v1, Vector v2)
    {
        Vector newVector;
        newVector.x = v1.x + v2.x;
        newVector.y = v1.y + v2.y;
        return newVector;
    }

    Vector vectorSub(Vector v1, Vector v2)
    {
        Vector newVector;
        newVector.x = v1.x - v2.x;
        newVector.y = v1.y - v2.y;
        return newVector;

    }

    Vector normalize(Vector v)
    {   
        double mag = vectorMag(v);
        v.x /= mag;
        v.y /= mag;
        return v;
    }

    Vector vectorScale(Vector v, double a)
    {
        v.x *= a;
        v.y *= a;
        return v;
    }

    double vectorDot(Vector v1, Vector v2)
    {
        return v1.x*v2.x + v1.y*v2.y;
    }

    Vector vectorProj(Vector v1, Vector v2)
    {
        return vectorScale(normalize(v2),vectorDot(v1,v2)/vectorMag(v2));
    }

    Vector intersect(Vector p1, Vector v1, Vector p2, Vector v2)
    {
        Vector p;
        p.x  = (p2.y - p1.y + v1.y/v1.x*p1.x - v2.y/v2.x*p2.x) / (v1.y/v1.x - v2.y/v2.x);
        p.y = p1.y/p1.x * (p.x - p1.x) + p1.y;
        return p;
    }
}