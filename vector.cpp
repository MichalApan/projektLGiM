#include "vector.h"

Vector::Vector(){}

Vector::Vector(Point a, Point b)
{
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
    normalize();
}

Vector::Vector(float x1, float y1, float z1)
{
    this->x = x1;
    this->y = y1;
    this->z = z1;
    this->normalize();
}

float Vector::lenght(){
    float lenght = sqrt((x*x)+(y*y)+(z*z));
    return lenght;
}

Vector Vector::operator+(Vector second){
    return Vector(x+second.x,y+second.y,z+second.z);
}

Vector Vector::crossProduct(Vector second){
    Vector v;
    v.x = (y*second.z)-(z*second.y);
    v.y = (z*second.x)-(x*second.z);
    v.z = (x*second.y)-(y*second.x);
    return v;
}

float Vector::dotProduct(Vector second){
    return (1.0)*x*second.x+y*second.y+z*second.z;

}

void Vector::normalize(){
    float l = lenght();
    if(l!=0){
        x = x/l;
        y = y/l;
        z = z/l;
    }

}

float Vector::getX(){
    return x;
}

float Vector::getY(){
    return y;
}

float Vector::getZ(){
    return z;
}



