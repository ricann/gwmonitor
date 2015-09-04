#include "video_decode.h"
#include "video_show.h"

#include "video_recv.h"

RecvThread *recv_thread;

udppkt_ring_t video_ring;

VideoRecv::VideoRecv()
{
    //指定端口9091接收视频心跳
    heart_sock = new QUdpSocket(this);
    heart_sock->bind(9091, QUdpSocket::ShareAddress);
    connect(heart_sock, SIGNAL(readyRead()), this, SLOT(slot_recvheart()));

    //指定端口8888接收视频数据
    udp_sock = new QUdpSocket(this);
    udp_sock->bind(8888);
    connect(udp_sock, SIGNAL(readyRead()), this, SLOT(slot_recvdata()));

    //初始化环形接收缓冲区
    //head==tail相等表示缓冲区为空
    //head==(tail+1)%VIDEO_RING_NUM表示缓冲区已满
    VRING_HEAD = 0;
    VRING_TAIL = 0;

    //建立摄像头心跳超时的信号槽
    ptmr = new QTimer();
    connect(ptmr, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    ptmr->start(VIDEO_HEART_CHECK);
    ptmr->setSingleShot(false);

    //初始化每个摄像头节点的当前时间
    for(int i=1; i<=MAX_CAMERA_NUM; i++) {
        node_info[i].cam_info.htime.start();
    }

    //打开心跳文件
    pfile = new QFile(VIDEO_HEART_FILE);
    if(!pfile->open(QIODevice::WriteOnly |
                    QIODevice::Append |
                    QIODevice::Text)) {
        qDebug()<<"Can't open file "<< VIDEO_HEART_FILE << endl;
        //ricann todo, 退出程序
    }
}

VideoRecv::~VideoRecv()
{
    //ricann todo, 下面的代码不知道有没有问题
    //udp_sock需要释放
    heart_sock->deleteLater();
    udp_sock->deleteLater();
}

void VideoRecv::slot_recvdata()
{
    int camid;
    Frame_header *p;

    while(udp_sock->hasPendingDatagrams())
    {
        //ring is full, drop this frame
        if(VRING_HEAD == ((VRING_TAIL+1) % VIDEO_RING_NUM)) {
            qDebug()<<"video ring is full!!\n";
            continue;
        }

        //read udp data to ring tail node
        udp_sock->readDatagram(VRING_TAIL_FARAME_BUF,
                MAX_FRAME_BUF,
                &VRING_TAIL_FARAME_IP,
                &VRING_TAIL_FARAME_PORT);

        //ricann todo, 不知道这个判断是什么意思
        if(VRING_TAIL_FARAME_BUF[0] == '#') {
            qDebug() << "[slot_recvdata]"
                     << VRING_TAIL_FARAME_BUF << endl;
            continue;
        }

        //不在播放列表里的视频数据包不进行解析
        p = (Frame_header *)VRING_TAIL_FARAME_BUF;
        camid = (int)ntohl(p->camera_no);
        if(camid<1 || camid>=MAX_CAMERA_NUM) {
            qDebug() << "[slot_recvdata]wrong camera number:"
                     << camid << endl;
            continue;
        }
        if(node_info[camid].cam_info.cam_play == FALSE) {
            qDebug() << "[slot_recvdata]cam_play is FALSE,camid = "
                     << camid << endl;
            continue;
        }

        //get frame header
        memcpy(&VRING_TAIL_FARAME_HDR, VRING_TAIL_FARAME_BUF, sizeof(Frame_header));
        VRING_TAIL_FARAME_HDR.frame_no = ntohl(VRING_TAIL_FARAME_HDR.frame_no);
        VRING_TAIL_FARAME_HDR.slice_no = ntohl(VRING_TAIL_FARAME_HDR.slice_no);
        VRING_TAIL_FARAME_HDR.frame_type = ntohl(VRING_TAIL_FARAME_HDR.frame_type);
        VRING_TAIL_FARAME_HDR.F = ntohl(VRING_TAIL_FARAME_HDR.F);
        VRING_TAIL_FARAME_HDR.T = ntohl(VRING_TAIL_FARAME_HDR.T);
        VRING_TAIL_FARAME_HDR.K = ntohl(VRING_TAIL_FARAME_HDR.K);
        VRING_TAIL_FARAME_HDR.R = ntohl(VRING_TAIL_FARAME_HDR.R);
        VRING_TAIL_FARAME_HDR.esi = ntohl(VRING_TAIL_FARAME_HDR.esi);
        VRING_TAIL_FARAME_HDR.camera_no = ntohl(VRING_TAIL_FARAME_HDR.camera_no);

        qDebug() << "[slot_recvdata]=============>" << endl
                 << "ip = " << VRING_TAIL_FARAME_IP << endl
                 << "port = " << VRING_TAIL_FARAME_PORT << endl
                 << "frame_no = " << VRING_TAIL_FARAME_HDR.frame_no << endl
                 << "slice_no = " << VRING_TAIL_FARAME_HDR.slice_no << endl
                 << "frame_type = " << VRING_TAIL_FARAME_HDR.frame_type << endl
                 << "F = " << VRING_TAIL_FARAME_HDR.F << endl
                 << "T = " << VRING_TAIL_FARAME_HDR.T << endl
                 << "K = " << VRING_TAIL_FARAME_HDR.K << endl
                 << "R = " << VRING_TAIL_FARAME_HDR.R << endl
                 << "esi = " << VRING_TAIL_FARAME_HDR.esi << endl
                 << "camera_no = " << VRING_TAIL_FARAME_HDR.camera_no << endl;

        //update ring tail number
        VRING_TAIL = (VRING_TAIL+1) % VIDEO_RING_NUM;

        //inform decode thread to handle the received data
        emit sig_dataready();
    }//while
}

void VideoRecv::slot_recvheart()
{
    //video heart file
    QTextStream vhf(pfile);

    QHostAddress sip;
    quint16 sport;
    QByteArray datagram;
    int camid;

    //ricann debug
    qDebug() << "[slot_recvheart] begin" <<endl;

    while(heart_sock->hasPendingDatagrams()) {

        //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(heart_sock->pendingDatagramSize());
        //接收数据报，将其存放到datagram中
        heart_sock->readDatagram(datagram.data(), datagram.size(), &sip, &sport);
        //读取cameraNo
        camid = (int)ntohl(*(int *)datagram.data());
        if(camid<=0 || camid>MAX_CAMERA_NUM) {
            qDebug() << "wrong camera id: " << camid <<endl;
            continue;
        }

        if(node_info[camid].cam_info.cam_alive == FALSE) {
            node_info[camid].cam_info.cam_alive = TRUE;
            emit sig_setvtree();
        }

        //更新node_info
        node_info[camid].is_used = TRUE;
        memcpy(&node_info[camid].ip, &sip, sizeof(QHostAddress));
        node_info[camid].port = sport;
        node_info[camid].cam_info.htime.restart();

        //心跳信息写入文件
        vhf << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
            << "    " << camid << endl;

        //ricann debug
        qDebug() << "[slot_recvheart]"
                 << "camid = " << camid
                 << "ip = " << node_info[camid].ip
                 << "port = " << node_info[camid].port
                 << endl;
    }
}

void VideoRecv::slot_timeout()
{
    for(int i=1; i<=MAX_CAMERA_NUM; i++) {
        if(node_info[i].cam_info.cam_alive == FALSE)
            continue;

        qDebug() << "[slot_timeout]" << node_info[i].cam_info.htime.elapsed() << endl;

        if(node_info[i].cam_info.htime.elapsed() > VIDEO_HEART_TIMEOUT) {
            node_info[i].cam_info.cam_alive = FALSE;
            node_info[i].cam_info.cam_play = FALSE;
            //ricann todo
            emit sig_setvtree();
        }
    }
}

void VideoRecv::slot_sendtime(int camid)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    QTime startTime(0, 0, 0);
    QTime endTime(23, 0, 0);
    int start;
    int end;

    //ricann todo,仅作测试用，用于打开远端视频传输
    out.setVersion(QDataStream::Qt_4_8);
    start = startTime.toString("hh").toInt()*60 + startTime.toString("mm").toInt();
    end = endTime.toString("hh").toInt()*60 + endTime.toString("mm").toInt();
    out << start << end;

    qDebug() << "[slot_sendtime]"
             << "datagram = " << datagram
             << "ip = " << node_info[camid].ip
             << "port = " << node_info[camid].port
             << endl;
    heart_sock->writeDatagram(datagram, node_info[camid].ip, node_info[camid].port);
}

RecvThread::RecvThread()
{

}

RecvThread::~RecvThread()
{
    quit();
    wait();
    deleteLater();
}

void RecvThread::run()
{
    VideoRecv vr;
    vr.moveToThread(this);

    //到这来的信号

    //送出去的信号
    connect(&vr, SIGNAL(sig_dataready()),
            decode_thread, SIGNAL(sig_dataarrived()));

    connect(&vr, SIGNAL(sig_setvtree()),
            this, SIGNAL(sig_setvtree()));

    exec();//(除ui线程之外的其他)线程用QThread::exec()开始事件循环
}
