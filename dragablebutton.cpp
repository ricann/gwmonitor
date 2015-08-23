#include "dragablebutton.h"

DragableButton::DragableButton(QWidget *parent)
    :QPushButton(parent)
{
    setAcceptDrops(true);
}

void DragableButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        startPos = e->pos();
    QPushButton::mousePressEvent(e);
}

void DragableButton::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        int dis = (e->pos()-startPos).manhattanLength();
        if(dis >= QApplication::startDragDistance())
            performDrag();
    }
    QPushButton::mouseMoveEvent(e);
}

void DragableButton::performDrag()
{
    QMimeData *mimeData = new QMimeData();
    mimeData->setText(this->text());
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(":/img/bullet_red.png"));
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        qDebug() << "Drag Finished !!!";
        this->repaint();
    }
}
