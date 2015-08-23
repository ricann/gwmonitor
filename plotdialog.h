#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include "commoninc_qt.h"
#include "qcustomplot.h"

namespace Ui {
class plotDialog;
}

class plotDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit plotDialog(int index,QWidget *parent = 0);
    void setupPlot();
    void setName();
    void setNodeNo();    
    void setupDemo(QCustomPlot *customPlot);

    ~plotDialog();

signals:
    void plotDialogAccept();

private slots:
    //void processDialogAccept();
    
private:
    void getDataFromDB(QVector<double> &data);
    void getTimeFromDB(QVector<double> &time);
    int nodeNo;
    QString code;
    QString demoName;
    Ui::plotDialog *ui;
};



#endif // PLOTDIALOG_H
