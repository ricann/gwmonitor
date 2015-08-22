
#include "paintableVedio.h"
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>


PaintableVedio::PaintableVedio(QWidget *parent)
     :QWidget(parent){
    //this->setWindowOpacity(1);
    //this->setAttribute(Qt::WA_TranslucentBackground, true); //设置透明
    //this->setWindowFlags(Qt::FramelessWindowHint); //把窗口设置成没框架的
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->isPressed = false;
}

PaintableVedio::~PaintableVedio(){

}

void PaintableVedio::paintEvent(QPaintEvent*p){
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔

    //ricann 20150822
    Q_UNUSED(p);

    pen.setColor(Qt::darkCyan);
    pen.setWidth(5);
    painter.setPen(pen);

    for(int i=0; i<(int)lines.size(); i++){
        myLine* pLine = lines[i];
        painter.drawLine(pLine->startPnt,pLine->endPnt);
    }
}

void PaintableVedio::mousePressEvent(QMouseEvent *e){
    setCursor(Qt::PointingHandCursor);
    if(this->isPressed){
        endPnt = e->pos();

        myLine* line = new myLine;  //put the new line into vector
        line->startPnt = startPnt;
        line->endPnt = endPnt;
        this->lines.push_back(line);

        update();

        startPnt = endPnt;
    }
    else {
        startPnt = e->pos();
        endPnt = e->pos();
    }
    this->isPressed = true;
    qDebug() << "mousePressed" << endl;
    //QString msg ="("+QString::number(e->x())+","+QString::number(e->y())+")";
    //QMessageBox::warning(this,tr("Warning"),msg,QMessageBox::Ok);
}

void PaintableVedio::mouseMoveEvent(QMouseEvent *e){
    qDebug() << "mouse moves" << endl;
    if(this->isPressed){
        endPnt = e->pos();

        myLine* line = new myLine;  //put the new line into vector
        line->startPnt = startPnt;
        line->endPnt = endPnt;
        this->lines.push_back(line);

        update();

        qDebug() << "draw lines" << endl;
        startPnt = endPnt;
    }
}

void PaintableVedio::mouseReleaseEvent(QMouseEvent *e){
    //ricann 20150822
    Q_UNUSED(e);

    setCursor(Qt::ArrowCursor);
    qDebug() << "mouse moves" << endl;
    this->isPressed = false;
}
