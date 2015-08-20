#include "resetTime.h"

//extern from MainWindow
extern QUdpSocket *videoControlUDP;
extern QMap<int,QHostAddress> cameraNoToIp;
extern QMap<int,quint16> cameraNoToVPort;
extern QList<int> cameraAlive;

ResetTimeThread::ResetTimeThread()
{
    time = QTime::fromString("00:06:00","hh:mm:ss");
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(resetTimeAll()));
    setTimer();
}

void ResetTimeThread::run()
{
    exec();
}

void ResetTimeThread::resetTimeAll()
{
    qDebug() << "*******************in resetTimeAll()********************" << endl;
    for(int i = 0;i < cameraAlive.size();i++)
    {
        resetTimeByCameraNo(cameraAlive[i]);
    }
    setTimer();
}

void ResetTimeThread::resetTimeByCameraNo(int cameraNo)
{
    qDebug() << "*****************in resetTimeByCameraNo******************" << endl;
    QHostAddress ip;
    quint16 port;

    ip = cameraNoToIp[cameraNo];
    port = cameraNoToVPort[cameraNo];
    if(!ip.isNull()) {
        QByteArray datagram;
        QDataStream out(&datagram,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);
        int start,end;
        start = end = 0; 
        out << start << end;
        videoControlUDP->writeDatagram(datagram,ip,port);
    }
    else
         qDebug() << "IP is NULL" << endl;

    setTimer();
}

void ResetTimeThread::setTimer()
{
    QTime curTime;
    int distance;
    curTime = QTime::currentTime();
    distance = curTime.msecsTo(time);
    if(distance < 0)
        distance = distance + 24*60*60*1000;
    timer->start(distance);
}
