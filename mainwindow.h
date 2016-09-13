#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"
#include "vector.h"
#include <QMainWindow>
#include <QDialog>
#include <QStack>
#include <cmath>
#include <algorithm>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawPoint(QPoint p, QColor c);
    void drawLine(QPoint p1, QPoint p2, QColor c);
    void normalize(float v[3]);
    void subdivide(float v1[], float v2[], float v3[], long depth, int x, int y);
    void drawtriangle(float *v1, float *v2, float *v3, int x, int y);

    void drawBall(Ball b);

    bool czyNalezyDoTrojkata(QPoint p, QPoint t[]);
    void teksturuj(QPoint bok[], QColor color);


    void paintEvent(QPaintEvent*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QImage *bg;
    int width;
    int height;
    int firstY;
    int firstX;

    Ball b;

};


#endif // MAINWINDOW_H
