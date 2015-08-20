#include "dropableplot.h"
#include "dragablebutton.h"
#include "dataAnalysis.h"
#include "mainwindow.h"

DropablePlot::DropablePlot(QWidget *parent)
    :QCustomPlot(parent)
{
    setAcceptDrops(true);
}

void DropablePlot::dragEnterEvent(QDragEnterEvent *e)
{
    DragableButton *source = qobject_cast<DragableButton *>(e->source());
    if(source)
    {
        e->setDropAction(Qt::MoveAction);
        e->accept();
    }
}

void DropablePlot::dragMoveEvent(QDragMoveEvent *e)
{
    DragableButton *source = qobject_cast<DragableButton *>(e->source());
    if(source)
    {
        e->setDropAction(Qt::MoveAction);
        e->accept();
    }
}

void DropablePlot::dropEvent(QDropEvent *e)
{
    DragableButton *source = qobject_cast<DragableButton *>(e->source());
    if(source)
    {
        setupDemo(e->mimeData()->text());
        qDebug() << "Drop success!!!";
    }
}

void DropablePlot::setupDemo(QString bName)
{
    //建立code和name的对应关系方便显示
    mapCodeName mCodeName[] =
    {{"1_voltage","电压"}, {"1_light","光照"}, {"1_a01001","温度"}, {"1_a01002","湿度"},
     {"2_a01001_e","外部温度"}, {"2_a01001_i","内部温度"}, {"2_a06003","PH"}, {"2_a06001","雨量"},
     {"2_a01007","风速"}, {"2_a01008","风向"}, {"2_voltage","电源电压"}, {"2_a06002","是否降雨"},
     {"3_a01001_30","温度(30cm)"}, {"3_a01002_30","湿度(30cm)"}, {"3_a01001_15","温度(15cm)"},
     {"3_a01002_15","湿度(15cm)"}, {"3_a01001_05","温度(5cm)"}, {"3_a01002_05","湿度(5cm)"},
     {"4_a01001","温度(土)"}, {"4_a01002","湿度(土)"}, {"4_w01008_v","垂直盐分"}, {"4_w01008_s","表面盐分"}};
    enum {LENGTH_M = 22};
    QMap<QString,QString>nameCode;
    for(int i = 0; i < LENGTH_M; i++)
    {
        nameCode.insert(mCodeName[i].name,tr(mCodeName[i].code));
    }
    this->clearGraphs();
    this->legend->setVisible(true);
    this->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

    QVector<double> time, value;
    this->addGraph();
    pen.setColor(QColor(Qt::red));
    this->graph()->setPen(pen);
    this->graph()->setName(bName);

    this->graph()->setLineStyle(QCPGraph::lsLine);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    MainWindow::getDataFromDB(value,nameCode[bName]);
    MainWindow::getTimeFromDB(time,nameCode[bName]);

    if(time.count()==0)
    {
        //QMessageBox::about(NULL, tr("警告"), tr("没有查询到相关数据"));
        this->replot();
        return ;
    }
    this->graph()->setData(time, value);
      //This format can be retrieved from QDateTime objects with the QDateTime::toTime_t() function.
    this->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    this->xAxis->setDateTimeFormat("yy-MM-dd\nhh:mm:ss");

    this->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    this->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    // set a fixed tick-step to one tick per month:
    this->xAxis->setAutoTickStep(true);
    this->xAxis->setTickStep(30); // one month in seconds

    this->xAxis->setLabel("Date");
    this->yAxis->setLabel("Value");

    double now=time.at(0);
    int len=time.size()-1;
    double low, high;
    low = value.at(0);
    high = value.at(value.size()-1);

    if(low == high)
    {
        low = low - 1;
        high = high + 1;
    }
    // set axis ranges to show all data:
    this->xAxis->setRange(now, time.at(len));
    this->yAxis->setRange(low, high);

    this->graph()->rescaleAxes(true);
    this->axisRect()->setupFullAxesBox();
    this->replot();
}
