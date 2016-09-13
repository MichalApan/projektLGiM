#ifndef BALL_H
#define BALL_H

#include <cmath>
#include <QPainter>
#include <QImage>
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QPixmap>
#include <QGenericMatrix>

#define X  53.0f
#define Z  85.0f


class Ball
{
public:
    Ball(QPoint position);
    Ball();
    QPoint getNextPosition();
    void setPosition(QPoint p);
    QPoint getActualPosition();

    int getSpeedY();
    void setSpeedY(int s);

    int getSpeedX();
    void setSpeedX(int s);

    int getSize();

private:
    int size;
    QPoint position;
    int speedX;
    int speedY;
};

#endif // BALL_H
