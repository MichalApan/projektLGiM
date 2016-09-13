#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    width = ui->drawFrame->width();
    height = ui->drawFrame->height();
    firstX = ui->drawFrame->x();
    firstY = ui->drawFrame->y();

    bg = new QImage(width,height,QImage::Format_RGB32);

    drawBall(b);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(firstX,firstY,*bg);

    update();
}

void MainWindow::normalize(float v[3]){
    float a = v[0];
    float b = v[1];
    float c = v[2];
    float d = sqrt(a*a+b*b+c*c);
    if (d == 0.0) {
        return;
    }
    v[0] = a*100/d; v[1] = b*100/d; v[2] = c*100/d;
    a = v[0];
    b = v[1];
    c = v[2];
}

void MainWindow::drawtriangle(float *v1, float *v2, float *v3, int x, int y){
    if(v1[2]>0 || v2[2]>0 || v3[2]>0){
        int d = 800;
        int xA = v1[0]/(1+v1[2]/d)+x;
        int yA = v1[1]/(1+v1[2]/d)+y;
        int xB = v2[0]/(1+v2[2]/d)+x;
        int yB = v2[1]/(1+v2[2]/d)+y;
        int xC = v3[0]/(1+v3[2]/d)+x;
        int yC = v3[1]/(1+v3[2]/d)+y;

        QPoint A = QPoint(xA, yA);
        QPoint B = QPoint(xB, yB);
        QPoint C = QPoint(xC, yC);

        drawLine(A,B, QColor(Qt::blue));
        drawLine(A,C, QColor(Qt::red));
        drawLine(B,C, QColor(Qt::green));

        int a1 = v1[0];
        int a2 = v1[1];
        int a3 = v1[2];
        int b1 = v2[0];
        int b2 = v2[1];
        int b3 = v2[2];
        int ab1 = a2*b3 - a3*b2;
        int ab2 = a3*b1 - a1*b3;
        int ab3 = a1*b2 - a2*b1;
        float ab[] = {ab1,ab2,ab3};
        normalize(ab);
        int abX = ab[0]/(1+ab[2]/d)+300;
        int abY = ab[1]/(1+ab[2]/d)+300;

        drawLine(QPoint(abX,abY),QPoint(300,300),Qt::black);

    }
}

void MainWindow::subdivide(float v1[], float v2[], float v3[], long depth, int x, int y)
{
    float a[3];
    float b[3];
    float c[3];
    for(int i=0; i<3; i++){
        a[i] = v1[i];
        b[i] = v2[i];
        c[i] = v3[i];
    }

    float v12[3], v23[3], v31[3];
    int i;

    if (depth == 0) {
        drawtriangle(a, b, c, x, y);
        return;
    }
    for (i = 0; i < 3; i++) {
        v12[i] = a[i]+b[i];
        v23[i] = b[i]+c[i];
        v31[i] = c[i]+a[i];
    }
    normalize(v12);
    normalize(v23);
    normalize(v31);
    subdivide(a, v12, v31, depth-1, x, y);
    subdivide(b, v23, v12, depth-1, x, y);
    subdivide(c, v31, v23, depth-1, x, y);
    subdivide(v12, v23, v31, depth-1, x, y);
}

void MainWindow::drawPoint(QPoint p, QColor c){
    unsigned char *ptr;
    ptr = bg->bits();

    int x = p.x();
    int y = p.y();
    int b = c.blue();
    int g = c.green();
    int r = c.red();

    if ((x>=0)&&(y>=0)&&(x<width)&&(y<height))
    {
        ptr[width*4*y + 4*x] = b;
        ptr[width*4*y + 4*x + 1] = g;
        ptr[width*4*y + 4*x + 2] = r;
    }
    update();
}

void MainWindow::drawLine(QPoint p1, QPoint p2, QColor c){
    int x1 = p1.x(), y1 = p1.y();
    int x2 = p2.x(), y2 = p2.y();
    int b = c.blue();
    int g = c.green();
    int r = c.red();

    unsigned char *ptr;
    ptr = bg->bits();
    double ao,bo;
    double x,y;

    ao=(y2-y1)*1.0/(x2-x1);
    bo=(y1);

    if(x1>x2){
        int t = x1;
        x1 = x2;
        x2 = t;
        bo=bo-(y1-y2);
    }
    if(abs(x1-x2)<abs(y1-y2)){
        for(int y=y1; y>=y2; y--){
            x=(y-bo)/ao+x1;
            x=round(x);
            drawPoint(QPoint(x,y),QColor(r,g,b));
        }
        for(int y=y1; y<=y2; y++){
            x=(y-bo)/ao+x1;
            x=round(x);
            drawPoint(QPoint(x,y),QColor(r,g,b));
        }
    }
    else{
        for(int x=x1; x<=x2; x++){
            y=ao*(x-x1)+bo;
            y=round(y);
            drawPoint(QPoint(x,y),QColor(r,g,b));
        }
    }
    update();
}

float vdata[12][3] = {
    {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
    {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
    {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static int tindices[20][3] = {
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
};


void MainWindow::drawBall(Ball b){
    int x = b.getActualPosition().x();
    int y = b.getActualPosition().y();

    for (int i = 0; i < 20; i++) {
        float v1[] = {vdata[tindices[i][0]][0],vdata[tindices[i][0]][1],vdata[tindices[i][0]][2]};
        float v2[] = {vdata[tindices[i][1]][0],vdata[tindices[i][1]][1],vdata[tindices[i][1]][2]};
        float v3[] = {vdata[tindices[i][2]][0],vdata[tindices[i][2]][1],vdata[tindices[i][2]][2]};

        subdivide(v1,v2,v3,2,x,y);
    }
}

int acc = 5;
int odbicie = 0;
void MainWindow::on_pushButton_clicked()
{
    bg->fill(Qt::gray);
    int size = b.getSize();
    int speedY = b.getSpeedY();
    int x = b.getActualPosition().x();

    if(odbicie == 0){
        if(b.getActualPosition().y()>=height-size){
            odbicie = 1;
            b.setSpeedY((-0.6)*speedY);//razy wspolczynnik
        }
        else{
            b.setSpeedY(speedY+acc);
        }
    }else if(odbicie == 1){
        if(speedY>0) odbicie = 0;
        b.setSpeedY(speedY+acc);
    }
    if(x>width-size || x<size){
        b.setPosition(QPoint(width-size,b.getActualPosition().y()));
        b.setSpeedX(b.getSpeedX()*(-0.8));
    }

    b.setPosition(b.getNextPosition());

    if(b.getActualPosition().y()>=500){
        b.setPosition(QPoint(b.getActualPosition().x(),500));
        if(b.getSpeedY()<-3) b.setSpeedY(0);
    }
//    if(x>=width-size){
//        b.setPosition(QPoint(width-size,b.getActualPosition().y()));
//        if(abs(b.getSpeedX())<5) b.setSpeedX(0);
//    }

    QString text = QString("speedY: %1").arg(b.getSpeedY());
    ui->textEdit->append(text);
    text = QString("speedX: %1").arg(b.getSpeedX());
        ui->textEdit->append(text);
    text = QString("y: %1, x: %2").arg(b.getActualPosition().y()).arg(b.getActualPosition().x());
    ui->textEdit->append(text);

    drawBall(b);
}
