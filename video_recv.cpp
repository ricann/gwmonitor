#include "video_decode.h"
#include "video_show.h"

#include "video_recv.h"

extern int video_allowed;
extern int video_sure;

RecvThread *recv_thread;

udppkt_ring_t video_ring;

VideoRecv::VideoRecv()
{
    //指定端口8888接收视频数据
    udp_sock = new QUdpSocket(this);
    udp_sock->bind(8888);
    connect(udp_sock, SIGNAL(readyRead()), this, SLOT(slot_recvdata()));

    //初始化环形接收缓冲区
    //head==tail相等表示缓冲区为空
    //head==(tail+1)%VIDEO_RING_NUM表示缓冲区已满
    VRING_HEAD = 0;
    VRING_TAIL = 0;
}

VideoRecv::~VideoRecv()
{
    //ricann todo
    //udp_sock不知道需不需要释放
}

void VideoRecv::slot_recvdata()
{
    while(udp_sock->hasPendingDatagrams())
    {
        if(video_allowed!=1 || video_sure!=1)
            continue;

        //ring is full, drop this frame
        if(VRING_HEAD == ((VRING_TAIL+1) % VIDEO_RING_NUM)) {
            qDebug()<<"video ring is full!!\n";
            continue;
        }

        //read udp data to ring tail node
        udp_sock->readDatagram(VRING_TAIL_FARAME_BUF,
                MAXLINE,
                &VRING_TAIL_FARAME_IP,
                &VRING_TAIL_FARAME_PORT);

        if(VRING_TAIL_FARAME_BUF[0] == '#')
            continue;

        //get frame header
        memcpy(&VRING_TAIL_FARAME_HDR, VRING_TAIL_FARAME_BUF, sizeof(Frame_header));

        //ricann todo
        //回放时停止相应摄像头的实时数据接收

        //update ring tail number
        VRING_TAIL = (VRING_TAIL+1) % VIDEO_RING_NUM;

        //inform decode thread to handle the received data
        emit sig_dataready();
    }//while
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
    //connect(this, SIGNAL(dataArrived()), &obj, SLOT(decode()), Qt::BlockingQueuedConnection);

    //送出去的信号
    connect(&vr, SIGNAL(sig_dataready()),
            decode_thread, SIGNAL(sig_dataarrived()));

    exec();//(除ui线程之外的其他)线程用QThread::exec()开始事件循环
}
