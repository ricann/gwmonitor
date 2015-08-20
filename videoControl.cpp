#include "videoControl.h"
#include "ui_videoControl.h"

#define MAX_PLAY_NUM 4

//extern from MainWindow
extern QUdpSocket *videoControlUDP;
extern QUdpSocket *cameraControlUDP;
extern QUdpSocket *powerUDP;
extern QMap<int,QHostAddress> cameraNoToIp;
extern QMap<int,quint16> cameraNoToVPort;
extern QMap<int,QHostAddress> cameraNoToCIp;
extern QMap<int,quint16> cameraNoToCPort;
extern QMap<int,QHostAddress> powerNoToIp;
extern QMap<int,quint16> powerNoToPort;
extern QMap<int,quint8> powerNoToState;
extern QList<int> cameraAlive;

enum {MCOUNT=8,PCOUNT=4};

VideoControl::VideoControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoControl)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("控制台"));

    connect(this, SIGNAL(freshCameraList()), this, SLOT(freshCameraListAndShow()));
    connect(this, SIGNAL(freshPowerList(int,char,char,char,char)), this, SLOT(freshPowerListAndShow(int,char,char,char,char)));
    connect(ui->power1, SIGNAL(clicked(bool)), this, SLOT(power1Clicked(bool)));
    connect(ui->power2, SIGNAL(clicked(bool)), this, SLOT(power2Clicked(bool)));
    connect(ui->power3, SIGNAL(clicked(bool)), this, SLOT(power3Clicked(bool)));
    connect(ui->power4, SIGNAL(clicked(bool)), this, SLOT(power4Clicked(bool)));

    pass = false;

    emit freshCameraList();
    freshMLinkListAndShow();
}


VideoControl::~VideoControl()
{
    delete ui;
}

void VideoControl::sentOrderToCamera(int cameraNo, char order)
{
    quint8 orders = order;
    QHostAddress ip;
    quint16 port;

    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    ip = cameraNoToCIp[cameraNo];
    port = cameraNoToCPort[cameraNo];
    if(!ip.isNull()) {
        out << orders;
        cameraControlUDP->writeDatagram(datagram,ip,port);
    }
    else
        qDebug() << "IP is NULL" << endl;

}

void VideoControl::on_windowList_currentIndexChanged(const QString &arg1)
{
    this->selectedCamera = arg1;
}

void VideoControl::on_windowList_MLink_currentIndexChanged(const QString &arg1)
{
    this->selectedMLink = arg1;
    int No = this->selectedMLink.toInt();
    if(powerNoToState.contains(No)) {
        char state = powerNoToState[this->selectedMLink.toInt()];
        char a,b,c,d;
        a = state & 0x3;
        b = state>>2 & 0x3;
        c = state>>4 & 0x3;
        d = state>>6 & 0x3;
        qDebug() << (int)a << (int)b << (int)c << (int)d;
        emit freshPowerList(No,a,b,c,d);
    }
    else
        emit freshPowerList(No,0,0,0,0);
}

void VideoControl::on_windowList_No_currentIndexChanged(const QString &arg1)
{
    QMap<QString,QString> nameToNo;
    nameToNo.insert(tr("路由器"),tr("1"));
    nameToNo.insert(tr("mesh"),tr("2"));
    nameToNo.insert(tr("卫星"),tr("3"));
    nameToNo.insert(tr("摄像头"),tr("4"));
    if(nameToNo[arg1] != NULL)
        this->selectedPowerNo = nameToNo[arg1];
    else
        this->selectedPowerNo = "1";
}

void VideoControl::sentTimeControlOrder(int cameraNo, QTime startTime, QTime endTime)
{
    QHostAddress ip;
    quint16 port;
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    ip = cameraNoToIp[cameraNo];
    port = cameraNoToVPort[cameraNo];
    if(!ip.isNull()) {
        int start = startTime.toString("hh").toInt()*60 + startTime.toString("mm").toInt();
        int end = endTime.toString("hh").toInt()*60 + endTime.toString("mm").toInt();

        out << start << end;
        videoControlUDP->writeDatagram(datagram,ip,port);
    }
    else
         qDebug() << "IP is NULL" << endl;
}

void VideoControl::on_sendControl_clicked()
{
    QTime startTime=ui->startTimeEdit->time();
    QTime endTime=ui->endTimeEdit->time();
    if(selectedCamera == tr("全部"))
    {
        for(int i = 0;i < cameraAlive.size();i++)
        {
            sentTimeControlOrder(cameraAlive[i],startTime,endTime);
        }
    }
    else
    {
        int No = selectedCamera.toInt();
        sentTimeControlOrder(No,startTime,endTime);
    }
}

void VideoControl::freshCameraListAndShow()
{
    this->selectedCamera = tr("全部");//默认选中全部窗口

    QStringList names;
    names<< tr("全部");

    for(int i=0;i < cameraAlive.size();i++)
    {
        QString s = QString("%1").arg(cameraAlive[i]);
        names << s;
    }

    ui->windowList->clear();
    ui->windowList->addItems(names);
    ui->windowList->show();
}

void VideoControl::freshMLinkListAndShow()
{
    this->selectedMLink = "1";//默认选中1号MLINK

    QStringList names;

    for(int i=0;i < MCOUNT;i++)
    {
        QString s = QString("%1").arg(i+1);
        names << s;
    }

    ui->windowList_MLink->clear();
    ui->windowList_MLink->addItems(names);
    ui->windowList_MLink->show();
}

void VideoControl::freshPowerListAndShow(int No, char a, char b, char c, char d)
{
    int cNo = this->selectedMLink.toInt();
    qDebug() << cNo << No;
    if(cNo == No) {
        ui->power1->setChecked(a==1);
        ui->power2->setChecked(b==1);
        ui->power3->setChecked(c==1);
        ui->power4->setChecked(d==1);
    }
}

bool VideoControl::isPowerChecked(int powerNo)
{
    switch(powerNo) {
        case 1: return ui->power1->isChecked();
        case 2: return ui->power2->isChecked();
        case 3: return ui->power3->isChecked();
        case 4: return ui->power4->isChecked();
    }
    return false;
}

void VideoControl::sentOrderToCameraAcrossList(char order)
{
    if(selectedCamera == tr("全部"))
    {
        for(int i = 0;i < cameraAlive.size();i++)
            sentOrderToCamera(cameraAlive[i],order);
    }
    else
    {
        int No = selectedCamera.toInt();
        sentOrderToCamera(No,order);
    }
}

//button up pressed
void VideoControl::on_pushButton_pressed()
{
    sentOrderToCameraAcrossList('u');
}
//button up released
void VideoControl::on_pushButton_released()
{
    sentOrderToCameraAcrossList('s');
}
//button down pressed
void VideoControl::on_pushButton_4_pressed()
{
    sentOrderToCameraAcrossList('d');
}
//button down released
void VideoControl::on_pushButton_4_released()
{
    sentOrderToCameraAcrossList('s');
}
//button left pressed
void VideoControl::on_pushButton_2_pressed()
{
    sentOrderToCameraAcrossList('l');
}
//button left released
void VideoControl::on_pushButton_2_released()
{
    sentOrderToCameraAcrossList('s');
}
//button right pressed
void VideoControl::on_pushButton_3_pressed()
{
    sentOrderToCameraAcrossList('r');
}
//button right released
void VideoControl::on_pushButton_3_released()
{
    sentOrderToCameraAcrossList('s');
}
//button near pressed
void VideoControl::on_pushButton_5_pressed()
{
    sentOrderToCameraAcrossList('n');
}
//button near released
void VideoControl::on_pushButton_5_released()
{
    sentOrderToCameraAcrossList('s');
}
//button far pressed
void VideoControl::on_pushButton_6_pressed()
{
    sentOrderToCameraAcrossList('f');
}
//button far released
void VideoControl::on_pushButton_6_released()
{
    sentOrderToCameraAcrossList('s');
}
//button wide pressed
void VideoControl::on_pushButton_7_pressed()
{
    sentOrderToCameraAcrossList('w');
}
//button wide released
void VideoControl::on_pushButton_7_released()
{
    sentOrderToCameraAcrossList('s');
}
//button tele pressed
void VideoControl::on_pushButton_8_pressed()
{
    sentOrderToCameraAcrossList('t');
}
//button tele released
void VideoControl::on_pushButton_8_released()
{
    sentOrderToCameraAcrossList('s');
}

void VideoControl::on_pushButton_9_pressed()
{
    sentOrderToCameraAcrossList('o');
}

void VideoControl::on_pushButton_9_released()
{
    sentOrderToCameraAcrossList('s');
}

void VideoControl::on_pushButton_10_pressed()
{
    sentOrderToCameraAcrossList('c');
}

void VideoControl::on_pushButton_10_released()
{
    sentOrderToCameraAcrossList('s');
}

void VideoControl::power1Clicked(bool state)
{
    char order = state ? '1':'0';
    sentPowerControlOrder(0,order);
}

void VideoControl::power2Clicked(bool state)
{
    char order = state ? '1':'0';
    sentPowerControlOrder(1,order);
}

void VideoControl::power3Clicked(bool state)
{
    char order = state ? '1':'0';
    sentPowerControlOrder(2,order);
}

void VideoControl::power4Clicked(bool state)
{
    char order = state ? '1':'0';
    sentPowerControlOrder(3,order);
}

void VideoControl::sentPowerControlOrder(int num, char order)
{
    quint8 orders = order;
    QHostAddress ip;
    quint16 port;
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    if(selectedMLink == tr("全部"))
    {
        for(int i = 0;i < MCOUNT;i++)
        {
            ip = powerNoToIp[i+1];
            port = powerNoToPort[i+1];
            if(!ip.isNull()) {
                out << (quint8)(num+'0') << orders;
                powerUDP->writeDatagram(datagram,ip,port);
            }
            else
                qDebug() << "IP is NULL" << endl;
        }
    }
    else
    {
        int No = selectedMLink.toInt();
        ip = powerNoToIp[No];
        port = powerNoToPort[No];
        if(!ip.isNull()) {
            out << (quint8)(num+'0') << orders;
            powerUDP->writeDatagram(datagram,ip,port);
        }
        else
             qDebug() << "IP is NULL" << endl;
    }
}

void VideoControl::closeEvent(QCloseEvent *e)
{
    pass = false;
    e->accept();
}
