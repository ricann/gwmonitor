#include "infodialog.h"
#include "ui_infodialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPixmap>
#include <QMap>
#include "plotdialog.h"


InfoDialog::InfoDialog(int index, double lon, double lat, QWidget *parent):
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("节点名片"));
    nodeNo=index;
    longi=lon;lati=lat;
    qDebug()<<"index:"<<index<<"  nodeNo:"<<nodeNo;
    refresh();
    //setupPlot();
}

void InfoDialog::setDeviceImg()
{
    QMap<int,QString>img;
    img.insert(0,":/img/node_0.jpg");
    img.insert(1,":/img/node_1.jpg");
    img.insert(2,":/img/node_2.jpg");
    img.insert(3,":/img/node_3.jpg");
    img.insert(4,":/img/node_4.jpg");
    img.insert(5,":/img/node_5.jpg");
    img.insert(6,":/img/node_6.jpg");
    ui->photoLabel->setPixmap(QPixmap(img[nodeNo]));
    ui->photoLabel->show();
}


InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::getDataFromDB(QVector<double> &data)
{
    QSqlQuery query;
    QString sql;
    sql = QString("select value from scalardata where code = '%1' and gatewayNo = %2  order by time desc limit 20")
                .arg(code).arg(nodeNo);

    //qDebug() << sql;
    query.exec(sql);
    while (query.next()) {
        //qDebug() << query.value(0).toDouble();
        data.push_back(query.value(0).toDouble());
    }
}

void InfoDialog::getTimeFromDB(QVector<double> &time)
{
    QSqlQuery query;
    QString sql;
    sql = QString("select time from scalardata where code = '%1'and gatewayNo = %2  order by time desc limit 20")
                .arg(code).arg(nodeNo);
   // qDebug() << sql;

    query.exec(sql);
    while (query.next()) {
       // qDebug() << query.value(0).toDateTime();
        time.push_back(query.value(0).toDateTime().toTime_t());
    }
}


void InfoDialog::setDeviceNo()
{
    QString deviceNo;
    deviceNo=QString::number(nodeNo);
    qDebug()<<"deviceNo: "<<deviceNo;
    ui->deviceNoEdit->setText(deviceNo);
}

void InfoDialog::setDevicePosition()
{
    //----------暂时没写------------
    QString s=tr("经度:");
    s.append(QString::number(longi,10,5));
    s.append(tr("  纬度："));
    s.append(QString::number(lati,10,5));
    ui->positionEdit->setText(s);
}

void InfoDialog::setPh()
{
    QSqlQuery query;
    QString temp="001";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();
    /*
    while(query.next())
    {
        qDebug()<<query.value(4).toDouble()<<query.value(3).toString();
    }*/

    //获取”value”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("value");
    qDebug()<<"fieldNo:"<<fieldNo;
    double value = query.value(4).toDouble();
    qDebug()<<"ph"<<value;
    ui->phEdit->setText(QString::number(value));

}

void InfoDialog::setSuspendedSolids()
{
    QSqlQuery query;
    QString temp="003";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();

    //获取”value”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("value");
    qDebug()<<"fieldNo:"<<fieldNo;
    double value = query.value(4).toDouble();
    qDebug()<<tr("悬浮物")<<value;
    ui->solidsEdit->setText(QString::number(value));
}

void InfoDialog::setTotalHg()
{
    QSqlQuery query;
    QString temp="020";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();

    //获取”value”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("value");
    qDebug()<<"fieldNo:"<<fieldNo;
    double value = query.value(4).toDouble();
    qDebug()<<tr("总汞")<<value;
    ui->HgEdit->setText(QString::number(value));
}

void InfoDialog::setTotalPb()
{
    QSqlQuery query;
    QString temp="027";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();

    //获取”value”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("value");
    qDebug()<<"fieldNo:"<<fieldNo;
    double value = query.value(4).toDouble();
    qDebug()<<tr("总铅")<<value;
    ui->PbEdit->setText(QString::number(value));
}

void InfoDialog::setTotalC()
{
    QSqlQuery query;
    QString temp="015";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();

    //获取”value”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("value");
    qDebug()<<"fieldNo:"<<fieldNo;
    double value = query.value(4).toDouble();
    qDebug()<<tr("总有机碳")<<value;
    ui->cEdit->setText(QString::number(value));
}

void InfoDialog::setTime()
{
    QSqlQuery query;
    QString temp="015";
    QString sql = QString("select * from scalardata where code = '%1' and gatewayNo=%2 order by time desc").arg(temp).arg(nodeNo);
   // qDebug() << "sql = " << sql;
    query.exec(sql);

    query.first();

    //获取”time”属性所在列的编号，列从左向右编号，最左边的编号为0
    int fieldNo=query.record().indexOf("time");
    qDebug()<<"fieldNo:"<<fieldNo;
    QDateTime dt=query.value(fieldNo).toDateTime();
    QString timeStr=dt.toString("yyyy-MM-dd  hh:mm:ss");
    ui->timeEdit->setText(timeStr);
}


void InfoDialog::refresh()
{
    setDeviceNo();
    setDeviceImg();
    setDevicePosition();
    /*setPh();
    setSuspendedSolids();
    setTotalHg();
    setTotalPb();
    setTotalC();
    setTime();*/
}

void InfoDialog::setupPlot()
{
    setupDemo(ui->customPlot);
    ui->customPlot->replot();
}

void InfoDialog::setupDemo(QCustomPlot *customPlot)
{
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;
    //lineNames << "ph" << "solids" << "C" << "Hg"
     //            << "Pb";
    lineNames<<"Temperature"<<"Humidity"<<"Moisture"<<"C"<<"N";

    QVector<double> time, value;
    //-----------画ph值----------------
    customPlot->addGraph();
    pen.setColor(QColor(Qt::red));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(0));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    code="3_a01001_30";
    getDataFromDB(value);
    getTimeFromDB(time);

    customPlot->graph()->setData(time, value);
      //This format can be retrieved from QDateTime objects with the QDateTime::toTime_t() function.
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");

    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set a fixed tick-step to one tick per month:
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

    double now=time.at(0);
    int len=time.size()-1;

    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->yAxis->setRange(0, 35);


    customPlot->graph()->rescaleAxes(true);


    //-----------画悬浮物----------------------
    customPlot->addGraph();
    pen.setColor(QColor(Qt::green));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(1));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    code="3_a01002_30";
    value.clear();
    time.clear();
    getDataFromDB(value);
    getTimeFromDB(time);

    customPlot->graph()->setData(time, value);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");

    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

    now=time.at(0);
    len=time.size()-1;

    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->graph()->rescaleAxes(true);

    //-----------画总有机碳----------------------
    customPlot->addGraph();
    pen.setColor(QColor(Qt::magenta));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(2));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    code="3_a01001_15";
    value.clear();
    time.clear();
    getDataFromDB(value);
    getTimeFromDB(time);

    customPlot->graph()->setData(time, value);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");

    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

    now=time.at(0);
    len=time.size()-1;

    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->graph()->rescaleAxes(true);

    //-----------画总汞----------------------
    customPlot->addGraph();
    pen.setColor(QColor(Qt::blue));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(3));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    code="3_a01002_15";
    value.clear();
    time.clear();
    getDataFromDB(value);
    getTimeFromDB(time);

    customPlot->graph()->setData(time, value);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");

    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

    now=time.at(0);
    len=time.size()-1;

    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->graph()->rescaleAxes(true);

    //-----------画总铅----------------------
    customPlot->addGraph();
    pen.setColor(QColor(Qt::cyan));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(4));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    code="3_a01001_05";
    value.clear();
    time.clear();
    getDataFromDB(value);
    getTimeFromDB(time);

    customPlot->graph()->setData(time, value);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");

    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

    now=time.at(0);
    len=time.size()-1;

    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->graph()->rescaleAxes(true);

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->replot();
}


