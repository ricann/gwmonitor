#ifndef INFODIALOG_H
#define INFODIALOG_H

#include "commoninc_qt.h"
#include "qcustomplot.h"
#include "plotdialog.h"

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    //explicit InfoDialog(QWidget *parent = 0);
    explicit InfoDialog( int index,double lon,double lat,QWidget *parent=0);


    void setDeviceImg();
    void setDeviceNo();
    void setDevicePosition();
    void setPh();
    void setSuspendedSolids();
    void setTotalHg();
    void setTotalPb();
    void setTotalC();
    void setTime();
    void refresh();

    void setupPlot();
    void setupDemo(QCustomPlot *customPlot);

    ~InfoDialog();
    
private slots:


private:
    Ui::InfoDialog *ui;
    int nodeNo;
    double lati;
    double longi;
    void getDataFromDB(QVector<double> &data);
    void getTimeFromDB(QVector<double> &time);
    QString code;
};

#endif // INFODIALOG_H
