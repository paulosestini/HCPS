#pragma once

namespace MathUtils
{
    struct Vector
    {
        double x, y;
    };

    double vectorMag(Vector v);
    Vector vectorAdd(Vector v1, Vector v2);
    Vector vectorSub(Vector v1, Vector v2);
    Vector normalize(Vector v);
    Vector vectorScale(Vector v, double a);
    double vectorDot(Vector v1, Vector v2);
    Vector vectorProj(Vector v1, Vector v2);
    Vector intersect(Vector p1, Vector v1, Vector p2, Vector v2);
}
