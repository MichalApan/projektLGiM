#include "ball.h"


Ball::Ball(QPoint position, int speedX, int speedY){
    this->position = position;
    this->speedX = speedX;
    this->speedY = speedY;
    this->size = 100;
}

Ball::Ball(QPoint position)
{
    this->speedX = 25;
    this->speedY = 0;
    this->size = 100;
}

Ball::Ball()
{
    this->size = 100;
    this->position = QPoint(100,100);
    this->speedX = 25;
    this->speedY = 0;
}

QPoint Ball::getActualPosition(){
    return position;
}

QPoint Ball::getNextPosition(){
    int speedX = this->position.x()+this->getSpeedX();
    int speedY = this->position.y()+this->getSpeedY();
    return QPoint(speedX,speedY);
}

void Ball::setPosition(QPoint p){
    this->position = p;
}

int Ball::getSpeedY(){
    return this->speedY;
}


void Ball::setSpeedY(int s){
    this->speedY = s;
}

int Ball::getSpeedX(){
    return this->speedX;
}

void Ball::setSpeedX(int s){
    this->speedX = s;
}


int Ball::getSize(){
    return this->size;
}
