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
    QUdpSocket *udp_sock;

public:
    VideoRecv();
    ~VideoRecv();

signals:
    void sig_dataready();

private slots:
    void slot_recvdata();
};

class RecvThread:public QThread{
Q_OBJECT
private:

public:
    RecvThread();
    ~RecvThread();
    void run();

signals:

};

extern udppkt_ring_t video_ring;

extern RecvThread *recv_thread;

#endif // VIDEO_RECV_H
