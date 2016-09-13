#ifndef VECTOR_H
#define VECTOR_H
#include "point.h"
#include <cmath>

class Vector
{
public:
    Vector(Point a, Point b);
    Vector();
    Vector(float x, float y, float z);
    float lenght();
    Vector operator+(Vector second);
    Vector crossProduct(Vector second);
    float dotProduct(Vector second);
    void normalize();
    float getX();
    float getY();
    float getZ();

    float x,y,z;
};

#endif // VECTOR_H
