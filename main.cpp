#include "mainwindow.h"

#undef main

static bool createConnection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    if(!createConnection())
        return 0;

    MainWindow w;
    w.setWindowTitle(QObject::tr("长城监测演示平台"));
    w.show();
    
    return a.exec();
}

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
    return true;
}
