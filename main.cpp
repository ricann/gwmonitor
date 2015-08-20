#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtGui>
#include <connection.h>
#undef main

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
