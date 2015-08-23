#ifndef DRAGABLEBUTTON_H
#define DRAGABLEBUTTON_H

#include "commoninc_qt.h"

class DragableButton : public QPushButton
{
    Q_OBJECT

public:
    DragableButton(QWidget *parent=0);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    //void dragEnterEvent(QDragEnterEvent *e);
    //void dragMoveEvent(QDragMoveEvent *e);
    //void dropEvent(QDropEvent *e);
private:
    void performDrag();
    QPoint startPos;
};
#endif // DRAGABLEBUTTON_H
