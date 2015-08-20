#include "plotdialog.h"
#include "ui_plotdialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>

plotDialog::plotDialog(int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotDialog)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("标量数据折线图"));
    nodeNo=index;
    setupPlot();


}

void plotDialog::setupPlot()
{
    setupDemo(ui->customPlot);
    setWindowTitle("QCustomPlot: "+demoName);
    ui->customPlot->replot();
}

plotDialog::~plotDialog()
{
    delete ui;

}


void plotDialog::setupDemo(QCustomPlot *customPlot)
{
  demoName = "Real Time Data Demo";

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
  code="001";
  getDataFromDB(value);
  getTimeFromDB(time);

  customPlot->graph()->setData(time, value);
    //This format can be retrieved from QDateTime objects with the QDateTime::toTime_t() function.
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh:mm:ss");
    //customPlot->xAxis->setAutoTickStep(false);

  // set a more compact font size for bottom and left axis tick labels:
  customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
  // set a fixed tick-step to one tick per month:
  customPlot->xAxis->setAutoTickStep(true);
  customPlot->xAxis->setTickStep(30); // one month in seconds
  //customPlot->xAxis->setSubTickCount(3);
  // apply manual tick and tick label for left axis:
  //customPlot->yAxis->setAutoTicks(false);
  //customPlot->yAxis->setAutoTickLabels(false);

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
  code="003";
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
  code="015";
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
  code="020";
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
  code="027";
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


void plotDialog::getDataFromDB(QVector<double> &data)
{
    QSqlQuery query;
    QString sql;
    sql = QString("select * from scalardata where code = '%1' and node = %2  order by time desc limit 8")
                .arg(code).arg(nodeNo);

    qDebug() << sql;
    query.exec(sql);
    while (query.next()) {
        qDebug() << query.value(4).toDouble();
        data.push_back(query.value(4).toDouble());
    }
}

void plotDialog::getTimeFromDB(QVector<double> &time)
{
    QSqlQuery query;
    QString sql;
    sql = QString("select * from scalardata where code = '%1'and node = %2  order by time desc limit 8")
                .arg(code).arg(nodeNo);
    qDebug() << sql;

    query.exec(sql);
    while (query.next()) {
        qDebug() << query.value(3).toDateTime();
        time.push_back(query.value(3).toDateTime().toTime_t());
    }

}
