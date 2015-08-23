
#include "mainwindow.h"
#include "ui_mainwindow.h"

QList<QPoint> points;
QList<QPoint> fourPointsWin[4];
QList<QPoint> *changedPoints = NULL;
QList<QPushButton*> buttonList;
QMap<int,QHostAddress> cameraNoToIp;//摄像头编号映射到节点ip
QMap<int,QHostAddress> cameraNoToCIp;//摄像头编号映射到摄像头控制节点ip
QMap<int,quint16> cameraNoToPort;//摄像头编号映射到视频发送端口
QMap<int,quint16> cameraNoToVPort;//摄像头编号映射到时间控制心跳发送端口
QMap<int,quint16> cameraNoToCPort;//摄像头编号映射到摄像头控制心跳发送端口
QMap<int,QHostAddress> powerNoToIp;//设备开关编号映射到节点ip
QMap<int,quint16> powerNoToPort;//设备开关编号映射到开关控制命令端口
QMap<int,quint8> powerNoToState;//节点编号映射节点开关状态

QUdpSocket *videoControlUDP;//传输视频控制命令的udpsocket
QUdpSocket *cameraControlUDP;//摄像头控制命令的udpsocket
QUdpSocket *powerUDP;//传输设备接口开关控制命令的udpsocket
QMap<int,QTimer*> cameraNoToTimer;
QList<int> cameraAlive;//摄像头存活节点维护表
QList<position_t> gpsAlive;//GPS活跃节点维护表
QMap<QString,int> treeNodeInt;
QMap<int,QString> treeIntNode;

int flag = 0;

QUdpSocket *udpSocket_video;

/************ffmpeg global variable**************/
FFmpeg *ffmpeg;
/************************************************/

/************************************************/
static int is_begin = 0;
int play_or_not[MAX_CAMERA_NUM] = {0};

int video_allowed = 0;
int video_sure=0;

int map_allowed=0;
int draw_allowed=0;
int plot_finished_flag=1;

enum {LENGTH_CP = 4};
QCustomPlot* cp[LENGTH_CP];

unsigned int nextPutFrame0(0);
unsigned int nextGetFrame0(0);
unsigned int nextPutFrame1(0);
unsigned int nextGetFrame1(0);
unsigned int nextPutFrame2(0);
unsigned int nextGetFrame2(0);
unsigned int nextPutFrame3(0);
unsigned int nextGetFrame3(0);
unsigned int nextPutFrame4(0);
unsigned int nextGetFrame4(0);
unsigned int nextPutFrame5(0);
unsigned int nextGetFrame5(0);
unsigned int nextPutFrame6(0);
unsigned int nextGetFrame6(0);
unsigned int nextPutFrame7(0);
unsigned int nextGetFrame7(0);
unsigned int nextPutFrame8(0);
unsigned int nextGetFrame8(0);
unsigned int nextPutFrame9(0);
unsigned int nextGetFrame9(0);

QSemaphore fullFrame0(0);
QSemaphore emptyFrame0(MAX_BUF_SIZE);
QSemaphore fullFrame1(0);
QSemaphore emptyFrame1(MAX_BUF_SIZE);
QSemaphore fullFrame2(0);
QSemaphore emptyFrame2(MAX_BUF_SIZE);
QSemaphore fullFrame3(0);
QSemaphore emptyFrame3(MAX_BUF_SIZE);
QSemaphore fullFrame4(0);
QSemaphore emptyFrame4(MAX_BUF_SIZE);
QSemaphore fullFrame5(0);
QSemaphore emptyFrame5(MAX_BUF_SIZE);
QSemaphore fullFrame6(0);
QSemaphore emptyFrame6(MAX_BUF_SIZE);
QSemaphore fullFrame7(0);
QSemaphore emptyFrame7(MAX_BUF_SIZE);
QSemaphore fullFrame8(0);
QSemaphore emptyFrame8(MAX_BUF_SIZE);
QSemaphore fullFrame9(0);
QSemaphore emptyFrame9(MAX_BUF_SIZE);


unsigned int nextPutShow0(0);
unsigned int nextGetShow0(0);
unsigned int nextPutShow1(0);
unsigned int nextGetShow1(0);
unsigned int nextPutShow2(0);
unsigned int nextGetShow2(0);
unsigned int nextPutShow3(0);
unsigned int nextGetShow3(0);
unsigned int nextPutShow4(0);
unsigned int nextGetShow4(0);
unsigned int nextPutShow5(0);
unsigned int nextGetShow5(0);
unsigned int nextPutShow6(0);
unsigned int nextGetShow6(0);
unsigned int nextPutShow7(0);
unsigned int nextGetShow7(0);
unsigned int nextPutShow8(0);
unsigned int nextGetShow8(0);
unsigned int nextPutShow9(0);
unsigned int nextGetShow9(0);

QSemaphore fullShow0(0);
QSemaphore emptyShow0(MAX_BUF_SIZE);
QSemaphore fullShow1(0);
QSemaphore emptyShow1(MAX_BUF_SIZE);
QSemaphore fullShow2(0);
QSemaphore emptyShow2(MAX_BUF_SIZE);
QSemaphore fullShow3(0);
QSemaphore emptyShow3(MAX_BUF_SIZE);
QSemaphore fullShow4(0);
QSemaphore emptyShow4(MAX_BUF_SIZE);
QSemaphore fullShow5(0);
QSemaphore emptyShow5(MAX_BUF_SIZE);
QSemaphore fullShow6(0);
QSemaphore emptyShow6(MAX_BUF_SIZE);
QSemaphore fullShow7(0);
QSemaphore emptyShow7(MAX_BUF_SIZE);
QSemaphore fullShow8(0);
QSemaphore emptyShow8(MAX_BUF_SIZE);
QSemaphore fullShow9(0);
QSemaphore emptyShow9(MAX_BUF_SIZE);

char frameBuf0[MAX_BUF_SIZE][MAXLINE];
char frameBuf1[MAX_BUF_SIZE][MAXLINE];
char frameBuf2[MAX_BUF_SIZE][MAXLINE];
char frameBuf3[MAX_BUF_SIZE][MAXLINE];
char frameBuf4[MAX_BUF_SIZE][MAXLINE];
char frameBuf5[MAX_BUF_SIZE][MAXLINE];
char frameBuf6[MAX_BUF_SIZE][MAXLINE];
char frameBuf7[MAX_BUF_SIZE][MAXLINE];
char frameBuf8[MAX_BUF_SIZE][MAXLINE];
char frameBuf9[MAX_BUF_SIZE][MAXLINE];

ShowNode showBuf0[MAX_BUF_SIZE];
ShowNode showBuf1[MAX_BUF_SIZE];
ShowNode showBuf2[MAX_BUF_SIZE];
ShowNode showBuf3[MAX_BUF_SIZE];
ShowNode showBuf4[MAX_BUF_SIZE];
ShowNode showBuf5[MAX_BUF_SIZE];
ShowNode showBuf6[MAX_BUF_SIZE];
ShowNode showBuf7[MAX_BUF_SIZE];
ShowNode showBuf8[MAX_BUF_SIZE];
ShowNode showBuf9[MAX_BUF_SIZE];

QMutex mutex_avcodec;

SDL_Surface *screen;
AVFormatContext *pFormatCtx;
AVCodecContext *pCodecCtx;
AVCodec *pCodec;


DisplayPara showPara;
int showCameList[MAX_PLAY_NUM];
int win_camera[MAX_PLAY_NUM];//0 default

int camera_no_real = 0;
int camera_no_local = 0;
char tmp_buf_r_total[MAXLINE];
char tmp_buf_l_total[MAXLINE];
Frame_header *frame_header_real = (Frame_header*)malloc(sizeof(Frame_header));
Frame_header *frame_header_local = (Frame_header*)malloc(sizeof(Frame_header));


int replay = 0;
int first_fb = 0;
int tick_now = 0;
int frame_cur_loca;
int speed_change_v = 0;
int continuous_change = 1;
uint_fast64_t totalRecords = 0;

FILE *existed_vs = NULL;
FILE *existed_v_s = NULL;
FILE *existed_v_e = NULL;

QStringList strlist;
QString strVideos;
QByteArray video_frag;
char *file_v;
QStringList::iterator ii;

int yuv_debug,
    video_debug;
void config_read(int* yuv_debug, int* video_debug);

/************************************************/
//***************静态成员初始化*********************/
int MainWindow::gatewayNo = -1;
int MainWindow::sensorNo = -1;
QDateEdit *MainWindow::start = NULL;
QDateEdit *MainWindow::end = NULL;

/********************主窗口界面开始*********************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->widget->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明
    luaGw = new LuaGw(this); //标量转发程序
    ffmpeg = new FFmpeg(this);//视频格式转换程序

    resetTime = new ResetTimeThread(); //定时关闭视频传输线程
    resetTime->start();
    /****************************************/
    config_read(&yuv_debug, &video_debug);

//    connect(ui->hSlider,SIGNAL(valueChanged(int)),this,SLOT(on_Slider_valueChanged(int)));
//    ui->hSlider->setVisible(false);
    /****************************************/

    connect(this,SIGNAL(newsCome(int,int)),this,SLOT(refreshPlot(int,int)));//有数据来到，刷新折线图

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(refreshMapSlot()));//定时刷新地图

    w=new Process(this);
    connect(w,SIGNAL(dlgReturn(int)),this,SLOT(setShowFlag(int)));//地图切换按钮

    vc = new VideoControl(this);//视频控制台界面
    connect(this, SIGNAL(freshCameraList()), vc, SIGNAL(freshCameraList()));
    connect(this, SIGNAL(freshPowerList(int, char,char,char,char)), vc, SIGNAL(freshPowerList(int, char,char,char,char)));
    vc->hide();

    connect(this, SIGNAL(pointsReady(int)), this, SLOT(sendPoints(int)));
    connect(this, SIGNAL(playnow()), this, SLOT(begin()));
    connect(this, SIGNAL(exitnow()), this, SLOT(all_stop()));    

    connect(ui->map_TabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabIndexChanged()));//获取当前tab页面index
    connect(ui->treeWidget_plot,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(treeItemClickSlot(QTreeWidgetItem*,int)));//获取选中标量
    //每次选中视频节点则触发播放按钮 add at 15/07/28
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(call_on_treeBtn_clicked(QTreeWidgetItem*,int)));//获取选中视频节点

    ui->video->installEventFilter(this);

    info = new Info(this);


    /*--------------指定端口7778接收标量数据--------------*/
    receiver = new QUdpSocket(this);
    receiver->bind(7778, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));


    /*-----------指定端口9999接收Agent状态数据------------*/
    stateReceiver = new QUdpSocket(this);
    stateReceiver->bind(9999, QUdpSocket::ShareAddress);
    connect(stateReceiver, SIGNAL(readyRead()), this, SLOT(stateDatagram()));

    /*-----------指定端口9998接收B/S服务端的控制命令------------*/
    commandReceiver = new QUdpSocket(this);
    commandReceiver->bind(9998, QUdpSocket::ShareAddress);
    connect(commandReceiver, SIGNAL(readyRead()), this, SLOT(commandDatagram()));

    /*-----------指定端口9992接收经纬度和心跳数据------------*/
    posReceiver = new QUdpSocket(this);
    posReceiver->bind(9992, QUdpSocket::ShareAddress);
    connect(posReceiver, SIGNAL(readyRead()), this, SLOT(posDatagram()));

    //////*********初始化控制台时间控制命令端口9091*************////////
    videoControlUDP = new QUdpSocket(this);
    videoControlUDP->bind(9091, QUdpSocket::ShareAddress);
    connect(videoControlUDP, SIGNAL(readyRead()), this, SLOT(processHeartDatagram()));

    //////*********初始化控制台摄像头控制命令端口9092*************////////
    cameraControlUDP = new QUdpSocket(this);
    cameraControlUDP->bind(9092, QUdpSocket::ShareAddress);
    connect(cameraControlUDP, SIGNAL(readyRead()), this, SLOT(processcHeartDatagram()));

    //////*********初始化设备开关控制端口9000************////////
    powerUDP = new QUdpSocket(this);
    powerUDP->bind(9000, QUdpSocket::ShareAddress);
    connect(powerUDP, SIGNAL(readyRead()), this, SLOT(processPowerDatagram()));

    showFlag=0;
    rplTimer=new QTimer(this);
    connect(rplTimer,SIGNAL(timeout()),this,SLOT(replaySlot()));

    initMap();
    test();


    emit playnow();

    ////////*-----------回放动图加载设置-----------*/////////
    QMovie *movie=new QMovie(":/img/replay.gif");
    ui->label->setMovie(movie);
    ////////*------------------------------------*////////

    /*------初始化节点编号与节点对应关系------*/
    treeNodeInt.clear();
    treeNodeInt.insert(tr("榆林镇北台"),4);
    treeNodeInt.insert(tr("榆林镇北台2"),7);
    treeNodeInt.insert(tr("测试1"),1);
    treeNodeInt.insert(tr("测试2"),2);
    treeNodeInt.insert(tr("测试3"),3);
    treeNodeInt.insert(tr("测试5"),5);
    treeNodeInt.insert(tr("测试6"),6);
    treeNodeInt.insert(tr("测试8"),8);
    treeNodeInt.insert(tr("测试9"),9);
    treeNodeInt.insert(tr("测试10"),10);

    treeIntNode.clear();
    treeIntNode.insert(4,tr("榆林镇北台"));
    treeIntNode.insert(7,tr("榆林镇北台2"));
    treeIntNode.insert(1,tr("测试1"));
    treeIntNode.insert(2,tr("测试2"));
    treeIntNode.insert(3,tr("测试3"));
    treeIntNode.insert(5,tr("测试5"));
    treeIntNode.insert(6,tr("测试6"));
    treeIntNode.insert(8,tr("测试8"));
    treeIntNode.insert(9,tr("测试9"));
    treeIntNode.insert(10,tr("测试10"));


    setVideoTree();
    setScalarTree();

    /*------将标量Button写入buttonList中-------*/
    buttonList << ui->voltageBtn << ui->lightBtn << ui->temperatureBtn << ui->humidityBtn << ui->temperature_eBtn
               << ui->temperature_iBtn << ui->phBtn << ui->prainfallBtn << ui->wind_speedBtn << ui->wind_directionBtn
               << ui->power_voltageBtn << ui->is_rainBtn << ui->temperature_30Btn << ui->humidity_30Btn << ui->temperature_15Btn
               << ui->humidity_15Btn << ui->temperature_5Btn << ui->humidity_5Btn << ui->temperatrue_earthBtn << ui->humidity_earthBtn
               << ui->vertical_salinityBtn << ui->surface_salinityBtn;

    /*------将折线图对象写入cp数组中-------*/
    cp[0] = ui->customPlot;
    cp[1] = ui->customPlot_2;
    cp[2] = ui->customPlot_3;
    cp[3] = ui->customPlot_4;

    /*------初始化默认选中的网关节点，传感器节点编号以及标量编码-------*/
    gatewayNo = 1;
    sensorNo = 1;
    code="1_a01001";
    cpIndex = -1;//初始化折线图编号

    start = ui->dateEdit_start;
    end = ui->dateEdit_end;

    /*******************视频部分*********************/
    my_deco_thread0 = new DecodeThread(1);
    my_deco_thread1 = new DecodeThread(2);
    my_deco_thread2 = new DecodeThread(3);
    my_deco_thread3 = new DecodeThread(4);
    my_deco_thread4 = new DecodeThread(5);
    my_deco_thread5 = new DecodeThread(6);
    my_deco_thread6 = new DecodeThread(7);
    my_deco_thread7 = new DecodeThread(8);
    my_deco_thread8 = new DecodeThread(9);
    my_deco_thread9 = new DecodeThread(10);


    connect(this, SIGNAL(frameReady0()), my_deco_thread0, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady1()), my_deco_thread1, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady2()), my_deco_thread2, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady3()), my_deco_thread3, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady4()), my_deco_thread4, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady5()), my_deco_thread5, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady6()), my_deco_thread6, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady7()), my_deco_thread7, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady8()), my_deco_thread8, SIGNAL(dataArrived()));
    connect(this, SIGNAL(frameReady9()), my_deco_thread9, SIGNAL(dataArrived()));

    connect(my_deco_thread0, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread1, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread2, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread3, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread4, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread5, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread6, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread7, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread8, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    connect(my_deco_thread9, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));


    (*my_deco_thread0).start();
    (*my_deco_thread1).start();
    (*my_deco_thread2).start();
    (*my_deco_thread3).start();
    (*my_deco_thread4).start();
    (*my_deco_thread5).start();
    (*my_deco_thread6).start();
    (*my_deco_thread7).start();
    (*my_deco_thread8).start();
    (*my_deco_thread9).start();



    showPara.my_height = ui->video->height();
    showPara.my_width = ui->video->width();

    my_show_thread0 = new ShowThread(showPara);
    my_show_thread1 = new ShowThread(showPara);
    my_show_thread2 = new ShowThread(showPara);
    my_show_thread3 = new ShowThread(showPara);

    connect(this, SIGNAL(showVideo0()), my_show_thread0, SIGNAL(dataArrived()));
    connect(this, SIGNAL(showVideo1()), my_show_thread1, SIGNAL(dataArrived()));
    connect(this, SIGNAL(showVideo2()), my_show_thread2, SIGNAL(dataArrived()));
    connect(this, SIGNAL(showVideo3()), my_show_thread3, SIGNAL(dataArrived()));

    connect(this, SIGNAL(resetWinCame0(const int,const int)), my_show_thread0, SIGNAL(resetCamera(const int,const int)));
    connect(this, SIGNAL(resetWinCame1(const int,const int)), my_show_thread1, SIGNAL(resetCamera(const int,const int)));
    connect(this, SIGNAL(resetWinCame2(const int,const int)), my_show_thread2, SIGNAL(resetCamera(const int,const int)));
    connect(this, SIGNAL(resetWinCame3(const int,const int)), my_show_thread3, SIGNAL(resetCamera(const int,const int)));

    connect(this, SIGNAL(resetWinHandle0(const DisplayPara)), my_show_thread0, SIGNAL(resetWinPara(const DisplayPara)));
    connect(this, SIGNAL(resetWinHandle1(const DisplayPara)), my_show_thread1, SIGNAL(resetWinPara(const DisplayPara)));
    connect(this, SIGNAL(resetWinHandle2(const DisplayPara)), my_show_thread2, SIGNAL(resetWinPara(const DisplayPara)));
    connect(this, SIGNAL(resetWinHandle3(const DisplayPara)), my_show_thread3, SIGNAL(resetWinPara(const DisplayPara)));

    (*my_show_thread0).start();
    (*my_show_thread1).start();
    (*my_show_thread2).start();
    (*my_show_thread3).start();
    /****************************************/

    int tabIndex=ui->map_TabWidget->currentIndex();
    switch(tabIndex)//判断当前Tab页面
    {
    case 0:
        map_allowed=1;
        refreshMap();
        timer->start(5000);
        break;
    case 1:
        video_allowed=1;
        break;
    case 2:
        draw_allowed=1;
        break;
    }



}

//------------------画折线图------------------
void MainWindow::setupPlot()
{
    plot_finished_flag=0;
    cpIndex = ++cpIndex%LENGTH_CP;
    setupDemo(cp[cpIndex]);
    ui->customPlot->replot();
    plot_finished_flag=1;
}

void MainWindow::setupDemo(QCustomPlot *customPlot)
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
    QMap<QString,QString>codeName;
    for(int i = 0; i < LENGTH_M; i++)
    {
        codeName.insert(mCodeName[i].code,tr(mCodeName[i].name));
    }
    customPlot->clearGraphs();
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

    QVector<double> time, value;
    customPlot->addGraph();
    pen.setColor(QColor(Qt::red));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(codeName[code]);

//    qDebug() << "codeName:" << codeName[code] << endl;

    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    getDataFromDB(value,code);
    getTimeFromDB(time,code);

    if(time.count()==0)
    {
        //QMessageBox::about(NULL, tr("警告"), tr("没有查询到相关数据"));
        customPlot->replot();
        return ;
    }
    customPlot->graph()->setData(time, value);
      //This format can be retrieved from QDateTime objects with the QDateTime::toTime_t() function.
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yy-MM-dd\nhh:mm:ss");

    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    // set a fixed tick-step to one tick per month:
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(30); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value");

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
    customPlot->xAxis->setRange(now, time.at(len));
    customPlot->yAxis->setRange(low, high);

    customPlot->graph()->rescaleAxes(true);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->replot();
}

MainWindow::~MainWindow()
{
    emit exitnow();
    delete ui;
}


/***********************新加本地地图*************************/

void MainWindow::paintTest()
{
    setNodePos();
    order.clear();
    nodeActive.clear();
    nodeAsleep.clear();
    /*
    nodeActive.append(1);
    nodeActive.append(3);
    nodeAsleep.append(2);
    nodeAsleep.append(4);

    order<<1<<3<<0<<2<<4<<0;*/

    int orderNum=info->getNo();//获取orders.count();
    for(int i=0;i<orderNum;i++)
        order.append(info->getOrder(i));
    for(int i=0;i<NODE_NUM;i++)
    {
        if(info->getMarks(i)>0)
            nodeActive.append(i);
        else
            nodeAsleep.append(i);
    }

    QRect rect=ui->webView->geometry();
//    qDebug()<<rect.width()<<rect.height();

    QPainter painter;
    //绘制image
    QImage image(rect.width(), rect.height(), QImage::Format_ARGB32);
    painter.begin(&image);

    int xBase=rect.width()/2-50;
    int yBase=rect.height()/2-50;
    for(int i=0;i<NODE_NUM;i++)
    {
        nodePos[i].setX(nodePosOffset[i].x()+xBase);
        nodePos[i].setY(nodePosOffset[i].y()+yBase);
    }

    painter.setPen(QPen(Qt::transparent, 3));
    painter.setBrush(QColor::QColor(255,245,190));
    painter.drawRect(0, 0, rect.width(),rect.height());

    painter.setPen(QPen(Qt::black, 3));
    QFont font("楷体", 18, QFont::Black);
    //设置字符间的间距
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
    //使用字体
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(rect.width()/2-200, 10, 400, 60, Qt::AlignCenter, tr("长城监测模拟地图"));
    //painter.drawText(100, 10, 200, 40, Qt::AlignCenter, tr("长城监测模拟地图"));


    /*---------画active节点-----------*/
    painter.setPen(QPen(Qt::transparent, 3));
    painter.setBrush(QColor(255 , 0, 0, 255));
    QFont font2("Times", 11, QFont::DemiBold);
    painter.setFont(font2);
    painter.drawEllipse(20,10,20,20);
    painter.setPen(Qt::black);
    painter.drawText(20, 30, 50, 20, Qt::AlignCenter, tr("active"));
    for(int i = 0; i < nodeActive.size(); i++)
    {
        painter.setPen(QPen(Qt::transparent, 2));
        int j=nodeActive.at(i);
        QString index="node_";
        index.append(QString::number(j,10));
        painter.drawEllipse(nodePos[j].x(),nodePos[j].y(),50,50);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawText(nodePos[j].x(), nodePos[j].y(), 50, 50, Qt::AlignCenter, index);
    }

    /*---------画asleep节点-----------*/
    painter.setPen(QPen(Qt::transparent, 3));
    painter.setBrush(QColor(0 , 0, 255, 255));
    painter.drawEllipse(20,50,20,20);
    painter.setPen(Qt::black);
    painter.drawText(20, 70, 50, 20, Qt::AlignCenter, tr("asleep"));
    for(int i = 0; i < nodeAsleep.size(); i++)
    {
        painter.setPen(QPen(Qt::transparent, 2));
        int j=nodeAsleep.at(i);
        QString index="node_";
        index.append(QString::number(j,10));
        painter.drawEllipse(nodePos[j].x(),nodePos[j].y(),50,50);
        painter.setPen(QPen(Qt::green, 2));
        painter.drawText(nodePos[j].x(), nodePos[j].y(), 50, 50, Qt::AlignCenter, index);
    }

    /*---------画服务器server节点-----------*/
    painter.setPen(QPen(Qt::transparent, 3));
    painter.setBrush(Qt::darkMagenta);    
    //painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(20,90,20,20);
    painter.setPen(Qt::black);
    painter.drawText(20, 110, 50, 20, Qt::AlignCenter, tr("Server"));
    painter.setPen(QPen(Qt::transparent, 3));
    painter.drawEllipse(nodePos[0].x(),nodePos[0].y(),50,50);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawText(nodePos[0].x(), nodePos[0].y(), 50, 50, Qt::AlignCenter, tr("Server"));

    painter.end();

    painter.begin(&image);
    QPainterPath path;
    if(order.size()!=0)
    {
        path.moveTo(nodePos[order.at(0)]);
        for(int k=1;k<order.size();k++)
        {
            if(order.at(k)==0&&k!=order.size()-1)
            {
                path.lineTo(nodePos[order.at(k)]);k++;
                path.moveTo(nodePos[order.at(k)]);
            }
            else
            path.lineTo(nodePos[order.at(k)]);
        }
        QPen pen(Qt::black,1,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);
        painter.setPen(pen);
        path.translate(18,18);
        painter.drawPath(path);
    }

    painter.end();

    image.save("C:/map.png");    
}

void MainWindow::setNodePos()
{/* //直接坐标
    nodePosOffset[0]=QPoint(220, 200);
    nodePosOffset[1]=QPoint(50, 290);
    nodePosOffset[2]=QPoint(150, 100);
    nodePosOffset[3]=QPoint(270, 80);
    nodePosOffset[4]=QPoint(380, 240);
    nodePosOffset[5]=QPoint(135, 250);
    nodePosOffset[6]=QPoint(310, 280);
    */

    //相对偏移坐标
    nodePosOffset[0]=QPoint(0, 0);
    nodePosOffset[1]=QPoint(-140, -170);
    nodePosOffset[2]=QPoint(-250, -60);
    nodePosOffset[3]=QPoint(-70, 120);
    nodePosOffset[4]=QPoint(280, 40);
    nodePosOffset[5]=QPoint(135, -180);
    nodePosOffset[6]=QPoint(210, 180);
}

void MainWindow::timeForecast(QString code2, int node2)
{
    const int count=500;
    double value[count];
    QSqlQuery query;
    QString sql;
    sql = QString("select * from scalardata where code = '%1' and node = %2  order by time desc limit 500")
                .arg(code2).arg(node2);
    query.exec(sql);
    int i=0;
    while (query.next()) {
        value[i++]=query.value(6).toDouble();
    }
    if(i<count)
    {
        QMessageBox::about(NULL, tr("警告"), tr("当前数据量不足"));
        return ;
    }

    //for(int i=0;i<count;i++)
        //qDebug()<<"value["<<i<<"]"<<value[i];
    double sum1,sum2,avg1,avg2;
    sum1=0;
    for(int i=0;i<count;i++)
        sum1+=value[i];
    avg1=sum1/count;
    //qDebug()<<"sum1="<<sum1<<"  avg1="<<avg1;

    sum2=0;
    for(int i=0;i<count;i++)
        sum2+=qPow((value[i]-avg1),2);
    avg2=sum2/(count-1);
}

void MainWindow::addJavaScriptObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("info",info);
}


void MainWindow::test()
{
    //addToGraph(0, 116.3522, 39.9599);//北邮
    //addToGraph(1, 111.490603, 32.683759);//西安
    addToGraph(0, 108.950243, 34.2853);//西安
    //addToGraph(7, 109.736727, 38.30119);//榆林
    /*addToGraph(2, 109.743608, 38.34496);//榆林镇北台
    addToGraph(3, 109.874723, 38.438241);//榆林十八墩
    addToGraph(4, 110.168465, 38.501817);//榆林建安堡
    addToGraph(5, 110.155266, 37.770065);//榆林米脂县
    addToGraph(6, 109.290593, 37.959678);//榆林衡山县*/
}

/*-----------接收标量数据报文，同时在主窗口滚动显示-----------*/
void MainWindow::processPendingDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    int gatewayNo = -1;
    int sensorNo = -1;

    QString path1=":/img/bulbOn.png";
    QString path2=":/img/bulbDown.png";
    QPixmap img1(path1);
    QPixmap img2(path2);
    // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        QString result;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        //qDebug()<<sender<<senderPort;
        qDebug()<<datagram;

        //发送回执信息
        QDateTime now;
        now=QDateTime::currentDateTime();
        QString nowReceive;
        nowReceive=now.toString("yyyy-MM-dd hh:mm:ss");
        QByteArray datagramBack=nowReceive.toAscii();
        receiver->writeDatagram(datagramBack.data(), datagramBack.size(),
                              QHostAddress(sender), senderPort);
        //QMap<QHostAddress,int>ipNode;  根据发送端ip获取节点信息
        //ui->dataPacket->append(datagram);
        //node=1;

        QTime t=QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);

        double v[8]; //8为单个Zigbee节点采集标量种类的上限
        char time[30]; //存储最后读取的标量的时间
        bool flag = false;
        bool newNode = false;
        dataAnalysis(datagram,result,v,gatewayNo,sensorNo,time,flag,newNode);
        //如果新的节点出现，刷新标量树形节点
        if(newNode)
            setScalarTree();
        if(flag) //draw_allowed==1 &&
        {
            ui->lcdTemp->setNumDigits(6);
            ui->lcdTemp->display(v[0]);
            ui->lcdHum->display(v[1]);
            ui->lcdMois->display(v[2]);
            ui->lcdC->display(v[3]);
            ui->lcdN->display(v[4]);

            ui->scalarTime->setText(time);
            ui->gatewayNo->setText(QString::number(gatewayNo,10));
            //ui->scalarTime->repaint();
            //ui->gatewayNo->repaint();
            //qApp->processEvents();

            emit newsCome(gatewayNo,sensorNo);

            ui->bulb->clearMask();
            ui->bulb->setPixmap(img1);
            QTimer::singleShot(2500, this, SLOT(bulbSlot()));
            //ui->bulb->setPixmap(img2);
        }
    }
}


void MainWindow::bulbSlot()
{
    QString path2=":/img/bulbDown.png";
    QPixmap img2(path2);
    ui->bulb->clearMask();
    ui->bulb->setPixmap(img2);
}

void MainWindow::refreshMapSlot()
{
    //timer->stop();
    refreshMap();
}

/*-----------接收Agent状态，根据状态画网络拓扑-----------*/
void MainWindow::stateDatagram()
{
    route_state_t temp;
    temp.index=0;
    temp.method=0;
    temp.len=0;
    memset(temp.states,'\0',sizeof(temp.states));

    QHostAddress sender2;
    quint16 senderPort2;

    while(stateReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(stateReceiver->pendingDatagramSize());
        stateReceiver->readDatagram(datagram.data(),datagram.size(),&sender2, &senderPort2);
//        qDebug()<<"size:"<<datagram.size();

        QDateTime now2;
        now2=QDateTime::currentDateTime();
        QString nowReceive2;
        nowReceive2=now2.toString("yyyy-MM-dd hh:mm:ss");
        QByteArray datagramBack2=nowReceive2.toAscii();
        stateReceiver->writeDatagram(datagramBack2.data(), datagramBack2.size(),
                                   QHostAddress(sender2), senderPort2);

        memcpy(&temp, datagram.data(), datagram.size());
//        qDebug()<<temp.index<<temp.method<<temp.len<<temp.states;
        if(temp.method==-62256)
        {
            //表示使用卫星
            info->setEdge(temp.index,-1);//即最后一跳到服务器            
        }
        else if(temp.method>0)
        {
            //地图上画流向
           info->setEdge(temp.index,temp.method);           
        }
        else if(temp.method==0)
        {
            //int netPort=qAbs(temp.method+1);//节点网口编号
            info->setEdge(temp.index,-1);//即最后一跳到服务器            
        }
    }

}

/*-----------接收B/S服务端发送的控制命令，解析控制命令并控制远端节点-----------*/
void MainWindow::commandDatagram()
{
    command_format_t command;

    QHostAddress sender;
    quint16 senderPort;

    int cameraNo;

    while(commandReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(commandReceiver->pendingDatagramSize());
        commandReceiver->readDatagram(datagram.data(),datagram.size(),&sender, &senderPort);

        memcpy(&command, datagram.data(), sizeof(command));
        datagram.clear();

        /*查询信息发送至端口9997*/
        senderPort = 9997;

        cameraNo = 0;
        cameraNo = (command.num[0]-'0')*10+(command.num[1]-'0');

        if(memcmp(command.type, "00", sizeof(command.type))==0) {
            //节点状态查询命令
            datagram.append("00");
            QString scameraNo;
            scameraNo.append(command.num[0]);
            scameraNo.append(command.num[1]);
            datagram.append(scameraNo);

            if(memcmp(command.arg, "00", 2*sizeof(char))==0) {
                //查询GPS信息
                datagram.append("00");
                char order = '0';
                position_t pos;
                for(int i=0; i<gpsAlive.size(); i++) {
                    if(gpsAlive[i].node == cameraNo) {
                        order = '1';
                        pos = gpsAlive[i];
                        break;
                    }
                }
                if(order == '1') {
                    datagram.append(order);
                    datagram.append(QString::number(pos.latitude));
                    datagram.append(',');
                    datagram.append(QString::number(pos.longitude));
                }
                else
                    datagram.append('0');
            }
            else if(memcmp(command.arg, "01", 2*sizeof(char))==0) {
                //查询路由开关状态
                datagram.append("01");
                char order;
                if(vc->isPowerChecked(1))
                    order = '1';
                else
                    order = '0';
                datagram.append(order);
            }
            else if(memcmp(command.arg, "02", 2*sizeof(char))==0) {
                //查询mesh开关状态
                datagram.append("02");
                char order;
                if(vc->isPowerChecked(2))
                    order = '1';
                else
                    order = '0';
                datagram.append(order);
            }
            else if(memcmp(command.arg, "03", 2*sizeof(char))==0) {
                //查询卫星开关状态
                datagram.append("03");
                char order;
                if(vc->isPowerChecked(3))
                    order = '1';
                else
                    order = '0';
                datagram.append(order);
            }
            else if(memcmp(command.arg, "04", 2*sizeof(char))==0) {
                //查询摄像头开关状态
                datagram.append("04");
                char order;
                if(vc->isPowerChecked(4))
                    order = '1';
                else
                    order = '0';
                datagram.append(order);
            }
            else if(memcmp(command.arg, "05", 2*sizeof(char))==0) {
                //查询摄像头是否活跃
                datagram.append("05");
                char order;
                if(cameraAlive.contains(cameraNo))
                    order = '1';
                else
                    order = '0';
                datagram.append(order);
            }
            else {
                //无法解析的命令
                qDebug() << "Can not explain the command from the B/S server";
            }
            commandReceiver->writeDatagram(datagram.data(), datagram.size(),
                                       QHostAddress(sender), senderPort);
        }
        else if(memcmp(command.type, "01", sizeof(command.type))==0) {
            //时间控制命令
            QString startS,endS;
            for(int i=0; i<12; i++) {
                if(i < 6)
                    startS.append(command.arg[i]);
                else
                    endS.append(command.arg[i]);
            }
            startS.insert(2,":");
            startS.insert(5,":");
            endS.insert(2,":");
            endS.insert(5,":");
            QTime startTime = QTime::fromString(startS,"hh:mm:ss");
            QTime endTime = QTime::fromString(endS,"hh:mm:ss");

            vc->sentTimeControlOrder(cameraNo,startTime,endTime);

            qDebug() << "time control";
            qDebug() << cameraNo;
            qDebug() << startS << " " << endS;
            //qDebug() << startTime.toString("hh:mm:ss") << " " << endTime.toString("hh:mm:ss");
        }
        else if(memcmp(command.type, "02", sizeof(command.type))==0) {
            //开关控制命令
            int num = 0;
            num = (command.arg[0]-'0')*10+(command.arg[1]-'0');
            vc->sentPowerControlOrder(num-1,command.arg[2]);
        }
        else if(memcmp(command.type, "03", sizeof(command.type))==0) {
            //摄像头控制命令
            vc->sentOrderToCamera(cameraNo,command.arg[0]);
        }
        else {
            //无法解析的命令
            qDebug() << "Can not explain the command from the B/S server";
        }
    }

}

/*-----------接收采集节点的经纬度信息，绘制地图标注-----------*/
void MainWindow::posDatagram()
{
    char tmp[100];
    QHostAddress sender3;
    quint16 senderPort3;

    while(posReceiver->hasPendingDatagrams())
    {
        memset(tmp, '\0', sizeof(tmp));
        posReceiver->readDatagram(tmp,sizeof(tmp),&sender3, &senderPort3);

        QDateTime now3;
        now3=QDateTime::currentDateTime();
        QString nowReceive3;
        nowReceive3=now3.toString("yyyy-MM-dd hh:mm:ss");
        QByteArray datagramBack3=nowReceive3.toAscii();
        posReceiver->writeDatagram(datagramBack3.data(), datagramBack3.size(),
                                   QHostAddress(sender3), senderPort3);

        char *bgn , *p = NULL;
        bgn = tmp;
        char node[3],lon[15],lat[15];

        p = strchr(bgn, '*');
        strncpy(node, bgn, p-bgn);
        bgn = p+1;
        p = strchr(bgn, '*');
        strncpy(lat, bgn, p-bgn);
        bgn = p+1;
        strncpy(lon, bgn, sizeof(lat));

        double latdu = 0.0, londu = 0.0;
        int no = 0;
        sscanf(node,"%d",&no);
        sscanf(lat,"%lf",&latdu);
        sscanf(lon,"%lf",&londu);
        if(no != 0)
            flag++;

        //判断节点gps信息是否已经存放在gpsAlive中
        bool contains = false;
        int i;
        for(i=0; i<gpsAlive.size(); i++) {
            if(gpsAlive[i].node == no) {
                contains = true;
                break;
            }
        }
        //若未保存gps信息则将新gps信息加入gpsAlive中
        if(!contains) {
            position_t pos;
            pos.node = no;
            pos.latitude = latdu;
            pos.longitude = londu;
            pos.timer = new QTimer(this);
            connect(pos.timer,SIGNAL(timeout()),this,SLOT(setGPSState()));
            //pos.timer->start(5*60*1000);
            pos.timer->start(60*1000);
            pos.timer->setSingleShot(true);
            gpsAlive.append(pos);
        }
        else {
            gpsAlive[i].timer->start(60*1000);
            gpsAlive[i].timer->setSingleShot(true);
        }

        //打印GPS数据到日志文件GPSLog.txt!
        std::ofstream fout("GPSLog.txt",ios::app);
        string time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        fout << time << ": Coming GPSNodeNO is: " << no << endl;

        if(flag == 1)
        {
            addToGraph(no,londu,latdu);
            flag = 0;
        }
    }
}


void MainWindow::addToGraph(int index, double lon, double lat)
{
    if(info->getMarks(index)>0) info->deCount(index);//若是更新的节点，节点个数不增加
    info->setPos(index, lon, lat);
//    qDebug()<<"addToGraph:  index:"<<index<<"lon:"<<lon<<"lat:"<<lat;
}


void MainWindow::getDataFromDB(QVector<double> &data, QString code)
{
    QSqlQuery query;
    QString sql;
    if(start != NULL && end != NULL)
        sql = QString("select value from scalardata where code = '%1' and gatewayNo = %2 and sensorNo = %3 and time between '%4' and '%5' order by time desc")
            .arg(code).arg(gatewayNo).arg(sensorNo).arg(start->date().toString("yyyy-MM-dd")).arg(end->date().toString("yyyy-MM-dd"));
    else
        sql = QString("select value from scalardata where code = '%1' and gatewayNo = %2 and sensorNo = %3 order by time desc limit 20")
                .arg(code).arg(gatewayNo).arg(sensorNo);
    //qDebug() << sql;

    query.exec(sql);
    while (query.next()) {
        data.push_back(query.value(0).toDouble());
    }
}

void MainWindow::getTimeFromDB(QVector<double> &time, QString code)
{
    QSqlQuery query;
    QString sql;
    if(start != NULL && end != NULL)
        sql = QString("select time from scalardata where code = '%1' and gatewayNo = %2 and sensorNo = %3 and time between '%4' and '%5' order by time desc")
            .arg(code).arg(gatewayNo).arg(sensorNo).arg(start->date().toString("yyyy-MM-dd")).arg(end->date().toString("yyyy-MM-dd"));
    else
        sql = QString("select time from scalardata where code = '%1' and gatewayNo = %2 and sensorNo = %3 order by time desc limit 20")
                .arg(code).arg(gatewayNo).arg(sensorNo);
    //qDebug() << sql;

    query.exec(sql);
    while (query.next()) {
        time.push_back(query.value(0).toDateTime().toTime_t());
    }
}


void MainWindow::initMap()
{
    ui->webView->settings()->setAttribute
(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute
(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute
(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute
(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute
(QWebSettings::JavaEnabled, true);
    connect(ui->webView->page()->mainFrame(),SIGNAL
(javaScriptWindowObjectCleared()),this,SLOT(addJavaScriptObject
()));
}


void MainWindow::refreshMap()
{
    if(map_allowed==1)
    {
//        qDebug()<<tr("准备刷新地图啦");
        info->setNodeIn();
        info->setOrder();
        if(showFlag==0)
        {
            ui->webView->load(QUrl("qrc:/map/map.html"));
            ui->webView->show();
        }
        else if(showFlag==1)
            refreshOfflineMap();
    }
}

void MainWindow::refreshOfflineMap()
{
    paintTest();
    ui->webView->load(QUrl::fromUserInput("C:/map.png"));
    ui->webView->show();
}

void MainWindow::mapRouteReplay()
{
    ui->label->movie()->start();//增加回放标识
    ui->label->show();
    ui->webView->load(QUrl("qrc:/map/map.html"));
    ui->webView->show();
}

void MainWindow::on_mapChgBtn_clicked()
{
    w->show();
}

void MainWindow::on_scalarDbBtn_clicked()//标量数据库查询
{
    DataDialog *dataDlg=new DataDialog(this);
    dataDlg->show();
    /*timeForecast("001",1);
    timeForecast("003",1);
    timeForecast("015",1);
    timeForecast("020",1);
    timeForecast("027",1);*/

}

void MainWindow::on_mapReplayBtn_clicked()//拓扑回放
{
    if(!ui->mapReplayBtn->text().compare(tr("拓扑回放")))
    {
        routeCount=0;
        QDate date=ui->dateEdit->date();
        QString str=date.toString("yyyy-MM-dd");
        QTime startTime=ui->startTimeEdit->time();
        QString str2=startTime.toString("hh:mm:ss");
        QTime endTime=ui->endTimeEdit->time();
        QString str3=endTime.toString("hh:mm:ss");

        QString strBuffer1,strBuffer2;
        strBuffer1 = str+" "+str2;
        strBuffer2 = str+" "+str3;

        QSqlQuery query;
        QString sql;
        sql = QString("select * from topology where time between '%1' and '%2' ").arg(strBuffer1).arg(strBuffer2);
        query.exec(sql);
        while (query.next()) {
//            qDebug() << query.value(1).toString();
            routes<<query.value(1).toString();
        }
        if(routes.count()==0)
        {
//            qDebug()<<tr("查询结果为零");
            QMessageBox::about(NULL, tr("警告"), tr("未查询到任何记录！"));
            return ;
        }
        ui->mapReplayBtn->setText(tr("停止回放"));//修改button的名字
        for(int i=0;i<routes.count();i++)
//            qDebug()<<"routes  :  "<<routes.at(i);

        timer->stop();//系统停止自动实时刷新
        replaySlot();//第一条回放拓扑手动调用，避免等待槽函数15s
        if(routes.count()>1) rplTimer->start(15000);
    }
    else if(ui->mapReplayBtn->text() == tr("停止回放"))
    {
        ui->mapReplayBtn->setText(tr("拓扑回放"));
        rplTimer->stop();
        timer->start(30000);
        refreshMap();
        ui->label->movie()->stop();//隐藏回放标识
        ui->label->hide();
    }

}

void MainWindow::replaySlot()//槽函数，拓扑分次回放
{
//    qDebug()<<"i="<<routeCount<<"  routes[i]="<<routes.at(routeCount);
    info->setMapRepaly(routes.at(routeCount));
    mapRouteReplay();
    routeCount++;

    if(routeCount==routes.length())//回放完成，重新开始地图刷新
    {
        ui->mapReplayBtn->setText(tr("拓扑回放"));
        rplTimer->stop();
        timer->start(30000);
        refreshMap();
        ui->label->movie()->stop();//隐藏回放标识
        ui->label->hide();
    }
}

/*----------动态折线图按钮部分 ---------*/

void MainWindow::refreshPlot(int gatewayNo,int sensorNo)
{
    if(gatewayNo==this->gatewayNo && sensorNo==this->sensorNo && draw_allowed==1 && cpIndex != -1)//只在当前收到新报文节点编号和折线图一致时，才更新折线图
    {
        plot_finished_flag=0;
        cpIndex = cpIndex%LENGTH_CP;
        setupDemo(cp[cpIndex]);
        ui->customPlot->replot();
        plot_finished_flag=1;
    }
}

void MainWindow::setShowFlag(int value)
{
    showFlag=value;
    refreshMap();

}

//设置标量树形节点
void MainWindow::setScalarTree()
{
    QSqlQuery queryType;
    QString sql;
    sql = QString("select distinct gatewayNo,sensorNo from scalartype order by sensorNo");
    queryType.exec(sql);
    QList<NodeNo> scalarNodeList;
    NodeNo n;
    while (queryType.next()) {
        n.gatewayNo = queryType.value(0).toInt();
        n.sensorNo = queryType.value(1).toInt();
        scalarNodeList.push_back(n);
    }
//    qDebug() << "**********list size***********" << scalarNodeList.size();
    QMap<int,QTreeWidgetItem*> intToTree;

    ui->treeWidget_plot->clear();
    ui->treeWidget_plot->setColumnCount(1);
    ui->treeWidget_plot->setHeaderLabel(tr("标量节点"));
    for(int i=0; i<scalarNodeList.size(); i++)
    {
        NodeNo nodeNo = scalarNodeList.at(i);
        if(treeIntNode.contains(nodeNo.gatewayNo))
        {
            if(intToTree.contains(nodeNo.gatewayNo))
            {
                QString schild = QString("zigbee%1").arg(nodeNo.sensorNo);
                QTreeWidgetItem *cnode=new QTreeWidgetItem(QStringList(schild));
                intToTree[nodeNo.gatewayNo]->addChild(cnode);
                cnode->setCheckState(0, Qt::Unchecked);
            }
            else
            {
                QTreeWidgetItem *node=new QTreeWidgetItem(QStringList(treeIntNode[nodeNo.gatewayNo]));
                intToTree[nodeNo.gatewayNo]=node;
                ui->treeWidget_plot->addTopLevelItem(node);
                QString schild = QString("zigbee%1").arg(nodeNo.sensorNo);
                QTreeWidgetItem *cnode=new QTreeWidgetItem(QStringList(schild));
                node->addChild(cnode);
                cnode->setCheckState(0, Qt::Unchecked);
            }
        }
    }
    ui->treeWidget_plot->expandAll();
    ui->treeWidget_plot->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->treeWidget_plot->setHeaderHidden(true);//treeWidget_plot的表头颜色不知道如何更改，所以直接将表头隐藏
}

//设置视频树形节点
void MainWindow::setVideoTree()
{
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("视频节点"));
    for(int i=0; i<cameraAlive.size(); i++)
    {
        int nodeNo = cameraAlive.at(i);
        if(treeIntNode.contains(nodeNo))
        {
            QTreeWidgetItem *note=new QTreeWidgetItem(QStringList(treeIntNode[nodeNo]));
            ui->treeWidget->addTopLevelItem(note);
            note->setCheckState(0, Qt::Unchecked);
        }
    }
    ui->treeWidget->expandAll();
    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->treeWidget->setHeaderHidden(true);//treeWidget的表头颜色不知道如何更改，所以直接将表头隐藏
}

//////////////******视频部分*******////////////////

void config_read(int* yuv_debug, int* video_debug)
{
    FILE *fd;
    fd = fopen("./conf_video.ini", "r");
    char read[100] = {'\0'},pres[100] = {'\0'};
    char *now, *post = NULL;

    now = fgets(read, 100, fd);
    while(now != NULL)
    {
        post = strchr(read, '=');
        strncpy(pres, now, post-now);
        if(post != NULL)
        {
            post++;
            if(!(strcmp(pres,"YUV_DEBUG")))
            {
                *yuv_debug = atoi(post);
            }

            else if(!(strcmp(pres,"VIDEO_DEBUG")))
                *video_debug = atoi(post);

        }
        memset(pres,'\0',100);
        now = fgets(read, 100, fd);
    }
    fclose(fd);
}

void MainWindow::begin()
{
    /*************************************/
    if(is_begin == 0)
    {
        SDL_init();

        udpSocket_video = new QUdpSocket(this);
        udpSocket_video->bind(8888);
        connect(udpSocket_video, SIGNAL(readyRead()),this, SLOT(recv_real_videodata()));

        is_begin = 1;
    }
    /*************************************/
}

void MainWindow::all_stop()
{

    avcodec_close(pCodecCtx);
    av_close_input_file(pFormatCtx);

    free(frame_header_real);
    free(frame_header_local);

    disconnect(this, SIGNAL(frameReady0()), my_deco_thread0, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady1()), my_deco_thread1, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady2()), my_deco_thread2, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady3()), my_deco_thread3, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady4()), my_deco_thread4, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady5()), my_deco_thread5, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady6()), my_deco_thread6, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady7()), my_deco_thread4, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady8()), my_deco_thread5, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(frameReady9()), my_deco_thread6, SIGNAL(dataArrived()));

    disconnect(my_deco_thread0, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread1, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread2, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread3, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread4, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread5, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread6, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread7, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread8, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));
    disconnect(my_deco_thread9, SIGNAL(dataReady_deco(const int)), this, SLOT(sendShowSignal(const int)));

    disconnect(this, SIGNAL(showVideo0()), my_show_thread0, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(showVideo1()), my_show_thread1, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(showVideo2()), my_show_thread2, SIGNAL(dataArrived()));
    disconnect(this, SIGNAL(showVideo3()), my_show_thread3, SIGNAL(dataArrived()));

    disconnect(this, SIGNAL(resetWinCame0(const int,const int)), my_show_thread0, SIGNAL(resetCamera(const int,const int)));
    disconnect(this, SIGNAL(resetWinCame1(const int,const int)), my_show_thread1, SIGNAL(resetCamera(const int,const int)));
    disconnect(this, SIGNAL(resetWinCame2(const int,const int)), my_show_thread2, SIGNAL(resetCamera(const int,const int)));
    disconnect(this, SIGNAL(resetWinCame3(const int,const int)), my_show_thread3, SIGNAL(resetCamera(const int,const int)));

    disconnect(this, SIGNAL(resetWinHandle0(const DisplayPara)), my_show_thread0, SIGNAL(resetWinPara(const DisplayPara)));
    disconnect(this, SIGNAL(resetWinHandle1(const DisplayPara)), my_show_thread1, SIGNAL(resetWinPara(const DisplayPara)));
    disconnect(this, SIGNAL(resetWinHandle2(const DisplayPara)), my_show_thread2, SIGNAL(resetWinPara(const DisplayPara)));
    disconnect(this, SIGNAL(resetWinHandle3(const DisplayPara)), my_show_thread3, SIGNAL(resetWinPara(const DisplayPara)));

    if(is_begin)
    {
        cout<<"udpSocket_video disconnected!!!!!!!!!"<<endl;
        disconnect(udpSocket_video, SIGNAL(readyRead()),this, SLOT(recv_real_videodata()));
    }

    my_deco_thread0->terminate();
    my_deco_thread1->terminate();
    my_deco_thread2->terminate();
    my_deco_thread3->terminate();
    my_deco_thread4->terminate();
    my_deco_thread5->terminate();
    my_deco_thread6->terminate();
    my_deco_thread7->terminate();
    my_deco_thread8->terminate();
    my_deco_thread9->terminate();
    my_show_thread0->terminate();
    my_show_thread1->terminate();
    my_show_thread2->terminate();//add by zs
    my_show_thread3->terminate();//add by zs

    my_deco_thread0->wait();
    my_deco_thread1->wait();
    my_deco_thread2->wait();
    my_deco_thread3->wait();
    my_deco_thread4->wait();
    my_deco_thread5->wait();
    my_deco_thread6->wait();
    my_deco_thread7->wait();
    my_deco_thread8->wait();
    my_deco_thread9->wait();
    my_show_thread0->wait();
    my_show_thread1->wait();
    my_show_thread2->wait();//add by zs
    my_show_thread3->wait();//add by zs

    //this->close();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++init SDL && decode++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void MainWindow::SDL_init(){

    char variable[64];

#ifdef Q_OS_WIN
    sprintf(variable, "SDL_WINDOWID=0x%lx", (long unsigned int)ui->video->winId());
#else
    sprintf(variable, "SDL_WINDOWID=0x%lx", this->winId());
#endif
    putenv(variable);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        cout<<"SDL_Init() failure"<<endl;
        exit(1);
    }

#ifndef __DARWIN__
    screen = SDL_SetVideoMode(ui->video->width(), ui->video->height(), 0, SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_DOUBLEBUF);
#else
    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 24, 0);
#endif

    if(!screen){
        cout<<"screen == NULL\n";
        exit(1);
    }

    //ricann change, 20150822
    //use avformat_alloc_context instead of av_alloc_format_context
    //use avformat_open_input instead of av_open_input_file
    //use av_dump_format instead of dump_format

    av_register_all();//注册库中含有的所有可用的文件格式和编码器，当打开一个文件时，能够自动选择相应的文件格式和编码器
    pFormatCtx = avformat_alloc_context();//给pFormatCtx分配内存
    if (!pFormatCtx){
        cout<<"avformat_alloc_context() failure"<<endl;
        exit(-1);
    }


    char filename[] = "1.264";
    if(avformat_open_input(&pFormatCtx, filename, NULL, NULL) !=0 ){// 打开视频文件
        cout<<"avformat_open_input() failure"<<endl;
        exit(-1);
    }


    if(av_find_stream_info(pFormatCtx)<0){//取出包含在文件中的流信息
        cout<<"av_find_stream_info() failure"<<endl;
        exit(-1);
    }

    av_dump_format(pFormatCtx, 0, filename, 0);//把获取到得参数全部输出

    int videoStream = -1;
    for(int i=0; i < (int)(pFormatCtx->nb_streams); i++){
        if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO && videoStream<0)//找到视频流
            videoStream=i;
        break;
    }

    if(videoStream==-1){
        cout<<"videoStream = -1\n";
        exit(-1);
    }

    pCodecCtx=pFormatCtx->streams[videoStream]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);//寻找解码器

    if(pCodec==NULL){
        cout<<"pCodec == NULL\n";
        exit(-1);
    }

    if(avcodec_open(pCodecCtx, pCodec)<0){//打开解码器
        cout<<"cannot open accodec\n";
        exit(-1);
    }

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++get realtime video data+++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void MainWindow::recv_real_videodata()
{
//    cout<<"recv_real_videodata() has been called~~~~~~~"<<endl;

    QHostAddress sender4;
    quint16 senderPort4;

    while(udpSocket_video->hasPendingDatagrams())
    {
        memset(tmp_buf_r_total, '\0', sizeof(tmp_buf_r_total));
        udpSocket_video->readDatagram(tmp_buf_r_total, MAXLINE, &sender4, &senderPort4);



        if(video_allowed==1 && video_sure==1){
            if(tmp_buf_r_total[0] == '#'){
//                cout<<"##"<<endl;
                continue;
            }

//            cout<<"video_data coming"<<endl;

            memcpy((char *)frame_header_real, tmp_buf_r_total, sizeof(Frame_header));
            camera_no_real = ntohl(frame_header_real->camera_no);

            //将IP关联至cameraNo
            cameraNoToIp[camera_no_real] = sender4;
            cameraNoToPort[camera_no_real] = senderPort4;

            //回放时停止相应摄像头的实时数据接收
            if(!(replay && camera_no_real == camera_no_local && camera_no_real)){

                switch(camera_no_real-1){
                case 0:
                    emptyFrame0.acquire();

                    memset(frameBuf0[nextPutFrame0], 0, MAXLINE);
                    memcpy(frameBuf0[nextPutFrame0], tmp_buf_r_total, MAXLINE);

                    fullFrame0.release();

                    nextPutFrame0++;
                    nextPutFrame0 %= MAX_BUF_SIZE;

                    emit frameReady0();

                    break;

                case 1:
                    emptyFrame1.acquire();

                    memset(frameBuf1[nextPutFrame1], 0, MAXLINE);
                    memcpy(frameBuf1[nextPutFrame1], tmp_buf_r_total, MAXLINE);

                    fullFrame1.release();

                    nextPutFrame1++;
                    nextPutFrame1 %= MAX_BUF_SIZE;

                    emit frameReady1();

                    break;

                case 2:
                    emptyFrame2.acquire();

                    memset(frameBuf2[nextPutFrame2], 0, MAXLINE);
                    memcpy(frameBuf2[nextPutFrame2], tmp_buf_r_total, MAXLINE);

                    fullFrame2.release();

                    nextPutFrame2++;
                    nextPutFrame2 %= MAX_BUF_SIZE;

                    emit frameReady2();

                    break;

                case 3:
                    emptyFrame3.acquire();

                    memset(frameBuf3[nextPutFrame3], 0, MAXLINE);
                    memcpy(frameBuf3[nextPutFrame3], tmp_buf_r_total, MAXLINE);

                    fullFrame3.release();

                    nextPutFrame3++;
                    nextPutFrame3 %= MAX_BUF_SIZE;

                    emit frameReady3();

                    break;

                case 4:
                    emptyFrame4.acquire();

                    memset(frameBuf4[nextPutFrame4], 0, MAXLINE);
                    memcpy(frameBuf4[nextPutFrame4], tmp_buf_r_total, MAXLINE);

                    fullFrame4.release();

                    nextPutFrame4++;
                    nextPutFrame4 %= MAX_BUF_SIZE;

                    emit frameReady4();

                    break;

                case 5:
                    emptyFrame5.acquire();

                    memset(frameBuf5[nextPutFrame5], 0, MAXLINE);
                    memcpy(frameBuf5[nextPutFrame5], tmp_buf_r_total, MAXLINE);

                    fullFrame5.release();

                    nextPutFrame5++;
                    nextPutFrame5 %= MAX_BUF_SIZE;

                    emit frameReady5();

                    break;

                case 6:
                    emptyFrame6.acquire();

                    memset(frameBuf6[nextPutFrame6], 0, MAXLINE);
                    memcpy(frameBuf6[nextPutFrame6], tmp_buf_r_total, MAXLINE);

                    fullFrame6.release();

                    nextPutFrame6++;
                    nextPutFrame6 %= MAX_BUF_SIZE;

                    emit frameReady6();

                    break;

                case 7:
                    emptyFrame7.acquire();

                    memset(frameBuf7[nextPutFrame7], 0, MAXLINE);
                    memcpy(frameBuf7[nextPutFrame7], tmp_buf_r_total, MAXLINE);

                    fullFrame7.release();

                    nextPutFrame7++;
                    nextPutFrame7 %= MAX_BUF_SIZE;

                    emit frameReady7();

                    break;

                case 8:
                    emptyFrame8.acquire();

                    memset(frameBuf8[nextPutFrame8], 0, MAXLINE);
                    memcpy(frameBuf8[nextPutFrame8], tmp_buf_r_total, MAXLINE);

                    fullFrame8.release();

                    nextPutFrame8++;
                    nextPutFrame8 %= MAX_BUF_SIZE;

                    emit frameReady8();

                    break;

                case 9:
                    emptyFrame9.acquire();

                    memset(frameBuf9[nextPutFrame9], 0, MAXLINE);
                    memcpy(frameBuf9[nextPutFrame9], tmp_buf_r_total, MAXLINE);

                    fullFrame9.release();

                    nextPutFrame9++;
                    nextPutFrame9 %= MAX_BUF_SIZE;

                    emit frameReady9();

                    break;

                default:
                    break;
                }

            }

        }

    }//while
    //Sleep(10);

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++get local video data++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void MainWindow::recv_local_videodata()
{
    first_fb = 1;
    replay = 1;

    for(ii = strlist.begin(); ii != strlist.end(); ii++)
    {
        totalRecords = 0;

        strVideos = strlist.front();
        video_frag = strVideos.toLatin1();
        file_v = video_frag.data();
        printf("%s\n", file_v);

        existed_v_e = fopen(file_v, "rb");
        fseek(existed_v_e, -1L*sizeof(uint64_t), SEEK_END);
        fread(&totalRecords, sizeof(uint64_t), 1, existed_v_e);
        fclose(existed_v_e);
        existed_v_e = NULL;

        existed_vs = fopen(file_v, "rb");
        if(existed_vs == NULL)
            return;

        if(first_fb == 1)
        {
//            ui->hSlider->setVisible(true);

            first_fb = 0;
        }

        frame_cur_loca = 0;
        while(existed_vs != NULL && feof(existed_vs) == 0)
        {
            //qDebug()<<"local file data receiving...\n";
            if(speed_change_v == 0)
            {
                tick_now = floor(((float)(frame_cur_loca++)*100)/totalRecords);
            }
            else //if(speed_change_v == 1)
            {
                if(feof(existed_v_s) == 0)
                {
                    existed_vs = existed_v_s;
                }
                speed_change_v = 0;

                frame_cur_loca = ceil(((float)tick_now * totalRecords) / 100);

            }
//            ui->hSlider->setValue(tick_now);


            memset(tmp_buf_l_total, '\0', sizeof(tmp_buf_l_total));
            fread(tmp_buf_l_total, 1, sizeof(Frame_header)+T_MAX, existed_vs);

            memcpy((char*)frame_header_local, tmp_buf_l_total, sizeof(Frame_header));
            camera_no_local = ntohl(frame_header_local->camera_no);

            switch(camera_no_local - 1){
            case 0:
                emptyFrame0.acquire();
                memset(frameBuf0[nextPutFrame0], 0, MAXLINE);
                memcpy(frameBuf0[nextPutFrame0], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame0.release();

                nextPutFrame0++;
                nextPutFrame0 %= MAX_BUF_SIZE;

                emit frameReady0();
                break;

            case 1:
                emptyFrame1.acquire();
                memset(frameBuf1[nextPutFrame1], 0, MAXLINE);
                memcpy(frameBuf1[nextPutFrame1], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame1.release();

                nextPutFrame1++;
                nextPutFrame1 %= MAX_BUF_SIZE;

                emit frameReady1();
                break;

            case 2:
                emptyFrame2.acquire();
                memset(frameBuf2[nextPutFrame2], 0, MAXLINE);
                memcpy(frameBuf2[nextPutFrame2], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame2.release();

                nextPutFrame2++;
                nextPutFrame2 %= MAX_BUF_SIZE;

                emit frameReady2();
                break;

            case 3:
                emptyFrame3.acquire();
                memset(frameBuf3[nextPutFrame3], 0, MAXLINE);
                memcpy(frameBuf3[nextPutFrame3], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame3.release();

                nextPutFrame3++;
                nextPutFrame3 %= MAX_BUF_SIZE;

                emit frameReady3();
                break;

            case 4:
                emptyFrame4.acquire();
                memset(frameBuf4[nextPutFrame5], 0, MAXLINE);
                memcpy(frameBuf4[nextPutFrame4], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame5.release();

                nextPutFrame4++;
                nextPutFrame4 %= MAX_BUF_SIZE;

                emit frameReady4();
                break;

            case 5:
                emptyFrame5.acquire();
                memset(frameBuf5[nextPutFrame5], 0, MAXLINE);
                memcpy(frameBuf5[nextPutFrame5], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame5.release();

                nextPutFrame5++;
                nextPutFrame5 %= MAX_BUF_SIZE;

                emit frameReady5();
                break;

            case 6:
                emptyFrame6.acquire();
                memset(frameBuf6[nextPutFrame6], 0, MAXLINE);
                memcpy(frameBuf6[nextPutFrame6], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame6.release();

                nextPutFrame6++;
                nextPutFrame6 %= MAX_BUF_SIZE;

                emit frameReady6();
                break;

            case 7:
                emptyFrame7.acquire();
                memset(frameBuf7[nextPutFrame7], 0, MAXLINE);
                memcpy(frameBuf7[nextPutFrame7], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame7.release();

                nextPutFrame7++;
                nextPutFrame7 %= MAX_BUF_SIZE;

                emit frameReady7();
                break;

            case 8:
                emptyFrame8.acquire();
                memset(frameBuf8[nextPutFrame8], 0, MAXLINE);
                memcpy(frameBuf8[nextPutFrame8], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame8.release();

                nextPutFrame8++;
                nextPutFrame8 %= MAX_BUF_SIZE;

                emit frameReady8();
                break;

            case 9:
                emptyFrame9.acquire();
                memset(frameBuf9[nextPutFrame9], 0, MAXLINE);
                memcpy(frameBuf9[nextPutFrame9], tmp_buf_l_total, sizeof(Frame_header)+T_MAX);
                fullFrame9.release();

                nextPutFrame9++;
                nextPutFrame9 %= MAX_BUF_SIZE;

                emit frameReady9();
                break;

              default:
                break;
            }

            //ensure nomal speed of video repalying
            Sleep(5);
        }

        fclose(existed_vs);
        existed_vs = NULL;

//        ui->hSlider->setValue(0);

        strlist.removeFirst();
    }

    replay = 0;
    camera_no_local = 0;

//    qDebug()<<"recv_local_videodata complete"<<endl;
}


/****************************************/
void MainWindow::sendShowSignal(const int camera_no){

    for(int i = 0; i < MAX_PLAY_NUM; ++i){
        if(win_camera[i] == camera_no){
            switch(i){
            case 0:
                emit showVideo0();
//                cout<<"emit showVideo0"<<endl;
                break;
            case 1:
                emit showVideo1();
//                cout<<"emit showVideo1"<<endl;
                break;
            case 2:
                emit showVideo2();
//                cout<<"emit showVideo2"<<endl;
                break;
            case 3:
                emit showVideo3();
//                cout<<"emit showVideo3"<<endl;
                break;
            default:
                break;
            }
            break;
        }
    }
}



void MainWindow::setShowCamera(int *new_win_camera){
    for(int i = 0; i < MAX_PLAY_NUM; ++i){
        int old_camera = win_camera[i];

        if(old_camera > 0)
            play_or_not[old_camera-1] = 0;
    }

    for(int i = 0; i < MAX_PLAY_NUM; ++i){
        int new_camera = new_win_camera[i];
        win_camera[i] = new_camera;

        if(new_camera>0){
            switch(i){
            case 0:
                emit resetWinCame0(new_camera, 1);
//                cout<<"emit setWinCame0"<<endl;
                break;
            case 1:
                emit resetWinCame1(new_camera, 2);
//                cout<<"emit setWinCame1"<<endl;
                break;
            case 2:
                emit resetWinCame2(new_camera, 3);
//                cout<<"emit setWinCame2"<<endl;
                break;
            case 3:
                emit resetWinCame3(new_camera, 4);
//                cout<<"emit setWinCame3"<<endl;
                break;
            default:
                break;
            }

            play_or_not[new_camera-1] = 1;
        }

    }
}

///////////******在tab间切换槽函数******//////////////
void MainWindow::tabIndexChanged()
{
    int i=ui->map_TabWidget->currentIndex();
    switch(i)
    {
     case 0:
        video_allowed=0;
        draw_allowed=0;
        map_allowed=1;
        refreshMapSlot();
        if(!timer->isActive()) timer->start(10000);
        break;
    case 1:
        map_allowed=0;
        draw_allowed=0;
        if(timer->isActive()){
            timer->stop();
        }

        video_allowed=1;
        break;
    case 2:
        if(timer->isActive()) timer->stop();
        map_allowed=0;
        video_allowed=0;
        draw_allowed=1;
        break;
    }
}

/////////////////----------触发播放按钮-------------///////////////////
void MainWindow::call_on_treeBtn_clicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    Q_UNUSED(column);
    on_treeBtn_clicked();
}

/////////////////---------树形节点视频选择播放----------////////////////
void MainWindow::on_treeBtn_clicked()
{
    QList<int> treeLeaf;
    treeLeaf.clear();  

    int selectedCount = 0;
    int topChildCount=ui->treeWidget->topLevelItemCount();
    for(int i=0;i<topChildCount;i++)
    {
        QTreeWidgetItem *childItem=ui->treeWidget->topLevelItem(i);

        if(childItem->checkState(0) == Qt::Checked) {
            selectedCount++;
            treeLeaf.append(treeNodeInt[childItem->text(0)]);
            qDebug()<<childItem->text(0)<<"  ## "<<treeNodeInt[childItem->text(0)];
        }

        //QTreeWidgetItem *cchild;

        /*for(int j=0;j<childItem->childCount();j++)
        {
            cchild=childItem->child(j);
            if (cchild->checkState(0) == Qt::Checked)
            {
                if(treeNode.contains(cchild->text(0)))
                {
                    selectedCount++;
                    qDebug()<<cchild->text(0)<<"  ## "<<treeNode[cchild->text(0)];
                    treeLeaf.append(treeNode[cchild->text(0)]);
                }
            }
        }*/
    }

    ///************清空存储的SDL窗口绘图的点集***********///
    //清除本地点的数组
    points.clear();
    //清除发送端点的数组
    if(changedPoints != NULL) {
        changedPoints->clear();
        for(int i = 0;i < 4;i++) {
            emit pointsReady(win_camera[i]);
        }
    }
    ///**********************************************///
    int new_win_came[4] = {0};
    for(int i = 0;i<4&&i!=treeLeaf.size();i++){
        new_win_came[i] = treeLeaf.at(i);
    }

    if(video_allowed==1){
        setShowCamera(new_win_came);
        video_sure=1;
    }

}

////////********获取选中的网关节点和采集子节点编号并将其赋给变量gatewayNo和sensorNo**********///////
void MainWindow::treeItemClickSlot(QTreeWidgetItem* item,int column)
{
    QMap<QString,int> childNodeInt;
    childNodeInt.insert("zigbee0",0);
    childNodeInt.insert("zigbee1",1);
    childNodeInt.insert("zigbee2",2);
    childNodeInt.insert("zigbee3",3);
    childNodeInt.insert("zigbee4",4);

//**********************清空未选中的树形结构的复选框************************//
    int topChildCount=ui->treeWidget_plot->topLevelItemCount();
    for(int i=0;i<topChildCount;i++)
    {
        QTreeWidgetItem *childItem=ui->treeWidget_plot->topLevelItem(i);
        QTreeWidgetItem *cchild;
        for(int j=0;j<childItem->childCount();j++)
        {
            cchild=childItem->child(j);
            if(cchild != item)
                cchild->setCheckState(0,Qt::Unchecked);
        }
    }

    if(item->checkState(column) == Qt::Checked)
    {
        if(item->parent() == NULL)
        {
            gatewayNo = treeNodeInt[item->text(0)];
            sensorNo = 1;
//            qDebug() << "item:" << item->text(0) << "gatewayNo:" << gatewayNo << "sensorNo:" << sensorNo << endl;
        }
        else
        {
            gatewayNo = treeNodeInt[item->parent()->text(0)];
            sensorNo = childNodeInt[item->text(0)];
//            qDebug() << "root item:" << item->parent()->text(0) << endl;
//            qDebug() << "item:" << item->text(0) << "gatewayNo:" << gatewayNo << "sensorNo:" << sensorNo << endl;
        }
    }
    else
    {
        gatewayNo = -1;//设置不存在的gatewayNo
        sensorNo = -1; //设置不存在的sensorNo
    }

    QSqlQuery query;
    QString sql;

    sql = QString("select name from scalartype where gatewayNo = %1 and sensorNo = %2")
                .arg(gatewayNo).arg(sensorNo);
    query.exec(sql);

    if(!query.isActive())
    {
        if(QSqlDatabase::database().open()) {
            query.exec(sql);
        }
        else
            qDebug() << "打开数据库失败！！！";
    }//检查MySQL数据库连接是否断开，若断开则重新连接数据库！

    QList<QString> nameList;
    while (query.next()) {
        nameList << query.value(0).toString();
    }

    for(int i=0; i <buttonList.size(); i++)
    {
        if(!nameList.contains(buttonList[i]->text()))
        {
            buttonList[i]->setStyleSheet("color: rgb(255,255,255);");
            buttonList[i]->setEnabled(false);
        }
        else
        {
            //按钮pushButton的字体颜色为红色
            buttonList[i]->setStyleSheet("color: rgb(255,0,0);");
            buttonList[i]->setEnabled(true);
        }
    }
}

///////******“电压”按钮单击事件绘图*****///////
void MainWindow::on_voltageBtn_clicked()
{
    code = "1_voltage";
    setupPlot();
}

void MainWindow::on_lightBtn_clicked()
{
    code = "1_light";
    setupPlot();
}

void MainWindow::on_temperatureBtn_clicked()
{
    code = "1_a01001";
    setupPlot();
}

void MainWindow::on_humidityBtn_clicked()
{
    code = "1_a01002";
    setupPlot();
}

void MainWindow::on_temperature_eBtn_clicked()
{
    code = "2_a01001_e";
    setupPlot();
}

void MainWindow::on_temperature_iBtn_clicked()
{
    code = "2_a01001_i";
    setupPlot();
}

void MainWindow::on_phBtn_clicked()
{
    code = "2_a06003";
    setupPlot();
}

void MainWindow::on_prainfallBtn_clicked()
{
    code = "2_a06001";
    setupPlot();
}

void MainWindow::on_wind_speedBtn_clicked()
{
    code = "2_a01007";
    setupPlot();
}

void MainWindow::on_wind_directionBtn_clicked()
{
    code = "2_a01008";
    setupPlot();
}

void MainWindow::on_power_voltageBtn_clicked()
{
    code = "2_voltage";
    setupPlot();
}

void MainWindow::on_temperature_30Btn_clicked()
{
    code = "3_a01001_30";
    setupPlot();
}

void MainWindow::on_humidity_30Btn_clicked()
{
    code = "3_a01002_30";
    setupPlot();
}

void MainWindow::on_temperature_15Btn_clicked()
{
    code = "3_a01001_15";
    setupPlot();
}

void MainWindow::on_humidity_15Btn_clicked()
{
    code = "3_a01002_15";
    setupPlot();
}

void MainWindow::on_temperature_5Btn_clicked()
{
    code = "3_a01001_05";
    setupPlot();
}

void MainWindow::on_humidity_5Btn_clicked()
{
    code = "3_a01002_05";
    setupPlot();
}

void MainWindow::on_temperatrue_earthBtn_clicked()
{
    code = "4_a01001";
    setupPlot();
}

void MainWindow::on_humidity_earthBtn_clicked()
{
    code = "4_a01002";
    setupPlot();
}

void MainWindow::on_vertical_salinityBtn_clicked()
{
    code = "4_w01008_v";
    setupPlot();
}

void MainWindow::on_surface_salinityBtn_clicked()
{
    code = "4_w01008_s";
    setupPlot();
}

//SDL视频窗口事件过滤器
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->video) {
        //处理鼠标双击事件
        if (event->type() == QEvent::MouseButtonDblClick) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            int x = mouseEvent->x();
            int y = mouseEvent->y();  
            int ww = ui->video->width();
            int hh = ui->video->height();
            int winNo = 0;
            int cameraNo = 0;

            if(mouseEvent->button() == Qt::LeftButton) {
                QPoint lPoint;
                QPoint bPoint;

                bPoint.setX(x);
                bPoint.setY(y);
                points.append(bPoint);//bPoint的缩放在了display_fuc.cpp的changePointsByWinNo函数中
                //判定触发鼠标双击事件位置对应的视频窗口号并转换出发点的坐标
                if(x>=0 && x<=(ww-5)/2 && y>=0 && y<=(hh-5)/2) {
                    //一号窗口
                    winNo = 1;
//                    qDebug() << "win_no:" << winNo << endl;
                }
                else if(x>=(ww+5)/2 && x<=ww-1 && y>=0 && y<=(hh-5)/2) {
                    //二号窗口
                    x = x-(ww+5)/2;

                    winNo = 2;
//                    qDebug() << "win_no:" << winNo << endl;
                }
                else if(x>=0 && x<=(ww-5)/2 && y>=(hh+5)/2 && y<=hh-1) {
                    //三号窗口
                    y = y-(hh+5)/2;

                    winNo = 3;
//                    qDebug() << "win_no:" << winNo << endl;
                }
                else if(x>=(ww+5)/2 && x<=ww-1 && y>=(hh+5)/2 && y<=hh-1) {
                    //四号窗口
                    x = x-(ww+5)/2;
                    y = y-(hh+5)/2;

                    winNo = 4;
//                    qDebug() << "win_no:" << winNo << endl;
                }

                //resize point坐标 按比例转换到480*272的yuv帧中的位置
                lPoint.setX(x/(double)(ww/2)*480.0);
                lPoint.setY(y/(double)(hh/2)*272.0);
                fourPointsWin[winNo-1].append(lPoint);
                changedPoints = fourPointsWin+winNo-1;

                cameraNo = win_camera[winNo-1];
                emit pointsReady(cameraNo);
            }
            else if(mouseEvent->button() == Qt::RightButton) {
                //判定触发鼠标双击事件位置对应的视频窗口号并转换出发点的坐标
                 if(x>=0 && x<=(ww-5)/2 && y>=0 && y<=(hh-5)/2) {
                     //一号窗口
                     winNo = 1;
                 }
                 else if(x>=(ww+5)/2 && x<=ww-1 && y>=0 && y<=(hh-5)/2) {
                     //二号窗口
                     winNo = 2;
                 }
                 else if(x>=0 && x<=(ww-5)/2 && y>=(hh+5)/2 && y<=hh-1) {
                     //三号窗口
                     winNo = 3;
                 }
                 else if(x>=(ww+5)/2 && x<=ww-1 && y>=(hh+5)/2 && y<=hh-1) {
                     //四号窗口
                     winNo = 4;
                 }
                 ///************清空存储的SDL窗口绘图的点集***********///
                 //清除本地点的数组
                 points.clear();
                 //清除发送端点的数组
                 fourPointsWin[winNo-1].clear();
                 changedPoints = fourPointsWin+winNo-1;
                 cameraNo = win_camera[winNo-1];
                 emit pointsReady(cameraNo);
                 ///**********************************************///
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

void MainWindow::sendPoints(int cameraNo)
{
    QHostAddress sender = cameraNoToIp[cameraNo];
    quint16 senderPort = cameraNoToPort[cameraNo];
    if(!sender.isNull()) {
//        qDebug() << "cameraNo:" << cameraNo << "senderIP:" << sender << endl;
        QByteArray datagram;
        QDataStream out(&datagram,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);
        out << changedPoints->size();
        for(int i = 0;i < changedPoints->size();i++) {
            out << changedPoints->at(i);
        }
        udpSocket_video->writeDatagram(datagram,sender,senderPort);
    }
    else
         qDebug() << "IP is NULL" << endl;
}

void MainWindow::on_pushButton_clicked() //进入视频控制台
{
    bool ok;
    int times = 3;
    while(!vc->pass && times-- > 0) {
        QString str = QInputDialog::getText(this,tr("密码核对"),tr("请输入密码："),QLineEdit::Password,"",&ok);
        if(ok)
        {
            if(str == QString("632"))
            {
                vc->pass = true;
            }
        }
    }
    if(times > 0)
        vc->show();
}

void MainWindow::processHeartDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    // 拥有等待的数据报
    while(videoControlUDP->hasPendingDatagrams())
    {
        QByteArray datagram;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(videoControlUDP->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        videoControlUDP->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        // 读取cameraNo
        int *pcameraNo;
        pcameraNo = (int *)datagram.data();
        ///***********小端转大端**********///
        quint8 *p = (quint8*)pcameraNo;
        int cameraNo = ((quint32)*p<<24)+((quint32)*(p+1)<<16)+
               ((quint32)*(p+2)<<8)+(quint32)*(p+3);
        ///*****************************///
        //************更新ip和端口***********//
        cameraNoToIp[cameraNo] = sender;
        cameraNoToVPort[cameraNo] = senderPort;

        if(!cameraAlive.contains(cameraNo))
        {
            resetTime->resetTimeByCameraNo(cameraNo);
            cameraAlive.append(cameraNo);
            setVideoTree();
            emit freshCameraList();
        }
        if(cameraNoToTimer[cameraNo] == NULL)
        {
            cameraNoToTimer[cameraNo] = new QTimer(this);
            connect(cameraNoToTimer[cameraNo],SIGNAL(timeout()),this,SLOT(setCameraState()));
        }

        cameraNoToTimer[cameraNo]->start(300*1000);
        cameraNoToTimer[cameraNo]->setSingleShot(true);
        //打印视频控制程序心跳到日志文件videoHeartLog.txt!
        std::ofstream fout("videoHeartLog.txt",ios::app);
        string time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        fout << time << ": Coming cameraNO is: " << cameraNo << endl;
    }
}

void MainWindow::processcHeartDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    // 拥有等待的数据报
    while(cameraControlUDP->hasPendingDatagrams())
    {
        QByteArray datagram;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(cameraControlUDP->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        cameraControlUDP->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        // 读取cameraNo
        int *pcameraNo;
        pcameraNo = (int *)datagram.data();
        ///***********小端转大端**********///
        quint8 *p = (quint8*)pcameraNo;
        int cameraNo = ((quint32)*p<<24)+((quint32)*(p+1)<<16)+
               ((quint32)*(p+2)<<8)+(quint32)*(p+3);
        ///*****************************///
        //************更新ip和端口***********//
        cameraNoToCIp[cameraNo] = sender;
        cameraNoToCPort[cameraNo] = senderPort;

        if(!cameraAlive.contains(cameraNo))
        {
            resetTime->resetTimeByCameraNo(cameraNo);
            cameraAlive.append(cameraNo);
            setVideoTree();
            emit freshCameraList();
        }
        if(cameraNoToTimer[cameraNo] == NULL)
        {
            cameraNoToTimer[cameraNo] = new QTimer(this);
            connect(cameraNoToTimer[cameraNo],SIGNAL(timeout()),this,SLOT(setCameraState()));
        }

        cameraNoToTimer[cameraNo]->start(300*1000);
        cameraNoToTimer[cameraNo]->setSingleShot(true);

        //打印摄像头控制程序心跳到日志文件cameracontrolHeartLog.txt!
        std::ofstream fout("cameraControlHeartLog.txt",ios::app);
        string time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        fout << time << ": Coming cameraNO is: " << cameraNo << endl;
    }
    
}

void MainWindow::processPowerDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    // 拥有等待的数据报
    while(powerUDP->hasPendingDatagrams())
    {
        QByteArray datagram;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(powerUDP->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        powerUDP->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        // 读取网关No
        char *pNo;
        char *state;
        pNo = (char *)datagram.data();
        int No = *pNo;

        state = pNo+1;
        powerNoToState[No] = *state;
        char a,b,c,d;
        a = *state & 0x3;
        b = *state>>2 & 0x3;
        c = *state>>4 & 0x3;
        d = *state>>6 & 0x3;
        qDebug() << No << (int)a << (int)b << (int)c << (int)d;
        emit freshPowerList(No,a,b,c,d);

        //************更新ip和端口***********//
        powerNoToIp[No] = sender;
        powerNoToPort[No] = senderPort;

        //打印开关控制程序心跳到日志文件powerlHeartLog.txt!
        std::ofstream fout("powerHeartLog.txt",ios::app);
        string time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        fout << time << ": Coming cameraNO is: " << No << endl;
    }
}

void MainWindow::setCameraState()
{
    QMap<int,QTimer*>::const_iterator i;
    cameraAlive.clear();
    for (i = cameraNoToTimer.constBegin(); i != cameraNoToTimer.constEnd(); ++i)
    {
        if(i.value()->isActive())
        {
            cameraAlive.append(i.key());
//            qDebug() << "cameraAlive:" << i.key() << endl;
        }
        else
        {
//            qDebug() << "cameraDied:" << i.key() << endl;
        }
    }
    setVideoTree();
    emit freshCameraList();
}
//?
void MainWindow::setGPSState()
{
    for(int i=0; i<gpsAlive.size(); i++)
    {
        if(gpsAlive[i].timer->isActive())
        {
            qDebug() << "gpsAlive:" << gpsAlive[i].node;
        }
        else
        {
            delete gpsAlive[i].timer;
            qDebug() << "gpsDied:" << gpsAlive[i].node;
            gpsAlive.removeAt(i);
            i--;
        }
    }
}
