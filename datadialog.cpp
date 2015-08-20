#include "datadialog.h"
#include "ui_datadialog.h"

#include "dataAnalysis.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QComboBox>
#include <QTableView>

#include <QTextCodec>
DataDialog::DataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialog)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("标量数据库"));

    QStringList names=QStringList()
            <<tr("全部")<<tr("电压")<<tr("光照")<<tr("温度")<<tr("湿度")
            <<tr("外部温度")<< tr("内部温度")<<tr("PH")<<tr("雨量")
            <<tr("风速")<<tr("风向")<<tr("电源电压")<<tr("是否降雨")
            <<tr("温度(30cm)")<<tr("湿度(30cm)") << tr("温度(15cm)")<<tr("湿度(15cm)")
            <<tr("温度(5cm)")<<tr("湿度(5cm)")<<tr("温度(土)")<<tr("湿度(土)")
            <<tr("垂直盐分")<<tr("表面盐分");
    ui->nameList->addItems(names);
    ui->nameList->show();
    names.clear();

    names<<tr("全部")<<"1"<<"2"<<"3"<<"4";
    ui->nodeList->addItems(names);
}




DataDialog::~DataDialog()
{
    delete ui;
}


/*----------查询数据库全体-------------*/
void DataDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    query.exec("drop view if exists temp");
    query.exec("create view temp as(select id,name,dimen,gatewayNo,sensorNo,time,value from scalardata)");
    if(!query.isActive())
    {
        if(QSqlDatabase::database().open())
        {
            query.exec("drop view if exists temp");
            query.exec("create view temp as(select id,name,dimen,gatewayNo,sensorNo,time,value from scalardata)");
        }
    }//重连数据库
    QSqlTableModel *m = new QSqlTableModel(this);
    m->setTable("temp");
    m->select();
    m->setHeaderData(0,Qt::Horizontal,tr("编号"));
    m->setHeaderData(1,Qt::Horizontal,tr("标量名称"));
    m->setHeaderData(2,Qt::Horizontal,tr("标量单位"));
    m->setHeaderData(3,Qt::Horizontal,tr("网关编号"));
    m->setHeaderData(4,Qt::Horizontal,tr("传感器编号"));
    m->setHeaderData(5,Qt::Horizontal,tr("检测时间"));
    m->setHeaderData(6,Qt::Horizontal,tr("检测值"));
    ui->tableView->setModel(m);

}


/*----------用pushbutton实现-----------
void DataDialog::on_nameButton_clicked()
{
   QString name=ui->nameList->currentText();
   QSqlTableModel *m = new QSqlTableModel(this);
   if(name=="ttt")
   {
    on_pushButton_clicked();
       return ;
   }

   else
   {

   QSqlQuery query;
   query.exec("drop view if exists temp1");
   QString sql = QString("create view temp1 as(select id,name,node,time,value from scalardata where name ='%1')").arg(name);
   qDebug() << "sql = " << sql;
   query.exec(sql);

   m->setTable("temp1");
   m->select();
   m->setHeaderData(0,Qt::Horizontal,tr("编号"));
   m->setHeaderData(1,Qt::Horizontal,tr("污染元"));
   m->setHeaderData(2,Qt::Horizontal,tr("节点编号"));
   m->setHeaderData(3,Qt::Horizontal,tr("检测时间"));
   m->setHeaderData(4,Qt::Horizontal,tr("检测值"));
   ui->tableView->setModel(m);
   }
}
*/

/*----------根据污染元筛选查询数据库-------------*/
void DataDialog::on_nameList_currentIndexChanged(const QString &arg1)
{
    //建立code和name的对应关系方便显示
    mapCodeName mCodeName[] =
    {{"1_voltage","电压"}, {"1_light","光照"}, {"1_a01001","温度"}, {"1_a01002","湿度"},
     {"2_a01001_e","外部温度"}, {"2_a01001_i","内部温度"}, {"2_a06003","PH"}, {"2_a06001","雨量"},
     {"2_a01007","风速"}, {"2_a01008","风向"}, {"2_voltage","电源电压"}, {"2_a06002","是否降雨"},
     {"3_a01001_30","温度(30cm)"}, {"3_a01002_30","湿度(30cm)"}, {"3_a01001_15","温度(15cm)"},
     {"3_a01002_15","湿度(15cm)"}, {"3_a01001_05","温度(5cm)"}, {"3_a01002_05","湿度(5cm)"},
     {"4_a01001","温度"}, {"4_a01002","湿度"}, {"4_w01008_v","垂直盐分"}, {"4_w01008_s","表面盐分"}};
    enum {LENGTH_M = 22};
    QMap<QString,QString>nameCode;

    for(int i = 0; i < LENGTH_M; i++)
    {
        nameCode.insert(tr(mCodeName[i].name),mCodeName[i].code);
    }

    QSqlTableModel *m = new QSqlTableModel(this);
    if(arg1==tr("全部"))
    {
        on_pushButton_clicked();
        return ;
    }

    else
    {

    QSqlQuery query;

    query.exec("drop view if exists temp1");

    QString sql = QString("create view temp1 as(select id,name,dimen,gatewayNo,sensorNo,time,value from scalardata where code = '%1')").arg(nameCode[arg1]);
    qDebug() << "sql = " << sql;
    query.exec(sql);

    m->setTable("temp1");
    m->select();
    m->setHeaderData(0,Qt::Horizontal,tr("编号"));
    m->setHeaderData(1,Qt::Horizontal,tr("标量名称"));
    m->setHeaderData(2,Qt::Horizontal,tr("标量单位"));
    m->setHeaderData(3,Qt::Horizontal,tr("网关编号"));
    m->setHeaderData(4,Qt::Horizontal,tr("传感器编号"));
    m->setHeaderData(5,Qt::Horizontal,tr("检测时间"));
    m->setHeaderData(6,Qt::Horizontal,tr("检测值"));
    ui->tableView->setModel(m);
    }
}


/*------------根据节点编号筛选查询数据库------------*/
void DataDialog::on_nodeList_currentIndexChanged(const QString &arg1)
{
    QSqlTableModel *m = new QSqlTableModel(this);
    if(arg1==tr("全部"))
        {
        on_pushButton_clicked();
        return ;
    }
    else
    {
        QSqlQuery query;
        query.exec("drop view if exists temp2");
        QString sql = QString("create view temp2 as(select id,name,dimen,gatewayNo,sensorNo,time,value from scalardata where gatewayNo = %1)").arg(arg1.toInt());
        qDebug() << "sql = " << sql;
        query.exec(sql);

        m->setTable("temp2");
        m->select();
        m->setHeaderData(0,Qt::Horizontal,tr("编号"));
        m->setHeaderData(1,Qt::Horizontal,tr("标量名称"));
        m->setHeaderData(2,Qt::Horizontal,tr("标量单位"));
        m->setHeaderData(3,Qt::Horizontal,tr("网关编号"));
        m->setHeaderData(4,Qt::Horizontal,tr("传感器编号"));
        m->setHeaderData(5,Qt::Horizontal,tr("检测时间"));
        m->setHeaderData(6,Qt::Horizontal,tr("检测值"));
        ui->tableView->setModel(m);
    }
}




/*------------根据日期筛选查询数据库------------*/
void DataDialog::on_dateEdit_dateChanged(const QDate &date)
{
    qDebug()<<date;
    QString str=date.toString("yyyy-MM-dd");
    qDebug()<<str;
    QSqlTableModel *m=new QSqlTableModel(this);
    QSqlQuery query;
    query.exec("drop view if exists temp3");
    QString sql = QString("create view temp3 as(select id,name,dimen,gatewayNo,sensorNo,time,value from scalardata where date_format(time,'%Y-%m-%d') ='%1')").arg(str);
    qDebug() << "sql = " << sql;
    query.exec(sql);

    m->setTable("temp3");
    m->select();
    m->setHeaderData(0,Qt::Horizontal,tr("编号"));
    m->setHeaderData(1,Qt::Horizontal,tr("标量名称"));
    m->setHeaderData(2,Qt::Horizontal,tr("标量单位"));
    m->setHeaderData(3,Qt::Horizontal,tr("网关编号"));
    m->setHeaderData(4,Qt::Horizontal,tr("传感器编号"));
    m->setHeaderData(5,Qt::Horizontal,tr("检测时间"));
    m->setHeaderData(6,Qt::Horizontal,tr("检测值"));
    ui->tableView->setModel(m);
}
