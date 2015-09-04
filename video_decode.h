#ifndef VIDEO_DECODE_H
#define VIDEO_DECODE_H

#include "externvar.h"
#include "matrix.h"
#include "raptorcode.h"

typedef struct _showfr_ring_{
    ShowNode    frame[VIDEO_RING_NUM];
    int         head;
    int         tail;
}showfr_ring_t;

//to operate showfr_ring easily
#define SRING_HEAD              showfr_ring.head
#define SRING_TAIL              showfr_ring.tail

#define SRING_HEAD_FARAME_SIZE  showfr_ring.frame[showfr_ring.head].size
#define SRING_TAIL_FARAME_SIZE  showfr_ring.frame[showfr_ring.tail].size

#define SRING_HEAD_FARAME_FNO   showfr_ring.frame[showfr_ring.head].frameNo
#define SRING_TAIL_FARAME_FNO   showfr_ring.frame[showfr_ring.tail].frameNo

#define SRING_HEAD_FARAME_CNO   showfr_ring.frame[showfr_ring.head].cameraNo
#define SRING_TAIL_FARAME_CNO   showfr_ring.frame[showfr_ring.tail].cameraNo

#define SRING_HEAD_FARAME_BUF   showfr_ring.frame[showfr_ring.head].h264node
#define SRING_TAIL_FARAME_BUF   showfr_ring.frame[showfr_ring.tail].h264node


#define DECODE_LOOP_NEXT        0
#define DECODE_LOOP_CUR         1

class VideoDecode:public QObject{
Q_OBJECT
public:
    VideoDecode();
    ~VideoDecode();

private:
    void decode_alloc();
    void decode_free();
    void decode_init();

    int pre_raptor(int i);
    void do_raptor();
    void fol_raptor();

private:
    int frame_no;
    long slice_no;
    int frame_type;
    long F;
    int T;
    int K;
    int R;
    int esi;
    int camera_no;

    int loop_num;

private:
    char *input_buf;
    char *output_buf;
    uint16 *list_cur;
    RParam_dec para;
    uint8 *temp;
    uint8 *output;
    char *frame_data;

    long output_buf_size;
    long input_buf_size;

    int K_old;
    int R_old;

    int cur_frame_no;
    int last_frame_no;
    int old_frame_no;

    char fileName[30];

    uint32 raptor_K_recieve;
    uint32 raptor_R_recieve;
    uint32 raptor_N_recieve;
    uint32 raptor_K_temp;
    uint32 raptor_R_temp;
    uint32 raptor_N_temp;

    uint16 list_temp;

signals:
    void sig_dataready();

public slots:
    void slot_decode();
};

class DecodeThread:public QThread{
Q_OBJECT
private:

public:
    DecodeThread();
    ~DecodeThread();
    void run();

signals:
    void sig_dataarrived();
};

extern showfr_ring_t showfr_ring;

extern DecodeThread *decode_thread;

#endif // VIDEO_DECODE_H
