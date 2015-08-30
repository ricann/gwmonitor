#ifndef VIDEO_RECV_H
#define VIDEO_RECV_H

#include "externvar.h"

typedef struct _udppkt_info_{
    QHostAddress ip;
    quint16 port;

    Frame_header frame_hdr;
    char frame_buf[MAXLINE];
}udppkt_info_t;

typedef struct _udppkt_ring_{
    udppkt_info_t frame[VIDEO_RING_NUM];
    int head;
    int tail;
}udppkt_ring_t;

#define VIDEO_HEART_FILE        "videoHeartLog.txt"
#define VIDEO_HEART_CHECK       1*60*1000
#define VIDEO_HEART_TIMEOUT     5*60*1000


//to operate video_ring easily
#define VRING_HEAD              video_ring.head
#define VRING_TAIL              video_ring.tail

#define VRING_HEAD_FARAME_IP    video_ring.frame[video_ring.head].ip
#define VRING_TAIL_FARAME_IP    video_ring.frame[video_ring.tail].ip

#define VRING_HEAD_FARAME_PORT  video_ring.frame[video_ring.head].port
#define VRING_TAIL_FARAME_PORT  video_ring.frame[video_ring.tail].port

#define VRING_HEAD_FARAME_HDR   video_ring.frame[video_ring.head].frame_hdr
#define VRING_TAIL_FARAME_HDR   video_ring.frame[video_ring.tail].frame_hdr

#define VRING_HEAD_FARAME_BUF   video_ring.frame[video_ring.head].frame_buf
#define VRING_TAIL_FARAME_BUF   video_ring.frame[video_ring.tail].frame_buf

class VideoRecv:public QObject{
Q_OBJECT
private:
    QUdpSocket *heart_sock;
    QUdpSocket *udp_sock;
    QTimer *ptmr;
    QFile *pfile;

public:
    VideoRecv();
    ~VideoRecv();

signals:
    void sig_dataready();
    void sig_setvtree();

private slots:
    void slot_recvdata();
    void slot_recvheart();
    //每隔一分钟检查一下摄像头活动节点有无超时的节点
    void slot_timeout();
};

class RecvThread:public QThread{
Q_OBJECT
private:

public:
    RecvThread();
    ~RecvThread();
    void run();

signals:
    void sig_setvtree();
};

extern udppkt_ring_t video_ring;

extern RecvThread *recv_thread;

#endif // VIDEO_RECV_H
