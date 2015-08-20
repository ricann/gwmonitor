#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>

static bool createConnection()
{
    qDebug()<<"Available drivers :";
    QStringList drivers=QSqlDatabase::drivers();
    foreach (QString driver, drivers) {
        qDebug()<<driver;
    }

    //--------------打开MySQL----------------------
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("stnproject");
    db.setUserName("root");
    db.setPassword("632");
    if(!db.open())
    {
        qDebug()<<"Failed to connect to mysql";
        return false;
    }

    /*
    QSqlQuery query(db);

    query.exec(QString("insert into scalardata(code,name,node,time,value) values('015','c',3,now(),9)"));

    query.exec(QString("insert into scalardata(code,name,node,time,value) values('ph',1,'2013-11-22 16:26:30',0.9)"));

    query.exec("select * from scalardata");
    while(query.next())
    {
        qDebug()<<query.value(0).toString()<<query.value(1).toInt()<<query.value(2).toDateTime()
                    <<query.value(3).toDouble()<<query.value(4).toInt();
    }
    */
    return true;
}


#endif // CONNECTION_H
