#ifndef DROPABLEPLOT_H
#define DROPABLEPLOT_H

#include "qcustomplot.h"

class DropablePlot : public QCustomPlot
{
    Q_OBJECT
public:
    DropablePlot(QWidget *parent = 0);
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);
    void setupDemo(QString bName);
};
#endif // DROPABLEPLOT_H
