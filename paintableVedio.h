#ifndef PAINTABLEVEDIO_H
#define PAINTABLEVEDIO_H

#include "commoninc_qt.h"

using namespace std;

//线段
typedef struct myLine{
    QPoint startPnt;
    QPoint endPnt;
}myLine;

class PaintableVedio: public QWidget
{
public:
    PaintableVedio(QWidget* parent);
    ~PaintableVedio();

    //继承
    void paintEvent(QPaintEvent* p);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


    QPoint startPnt;   //起点
    QPoint endPnt;     //终点
    bool isPressed;    //鼠标是否按下

    vector<myLine*> lines; //存放所有的线段
};

#endif // PAINTABLEVEDIO_H
