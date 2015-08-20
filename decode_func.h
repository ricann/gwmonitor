#ifndef DECODE_FUNC_H
#define DECODE_FUNC_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>

#include "externvar.h"
#include "raptorcode.h"

#ifdef GILBERT_DEBUG
#include "gilbert.h"
#endif


//#define MAX_WINDOW_SIZE 20
//#define GIL_PERIOD 1
//#define NI 1
//#define HI 66


/*
QObject的子对象必须在创建其parent的线程中创建。
这意味着，不能把QThread对象作为parent传递给创建在线程中的对象，
因为QThread 对象本身在另外一个线程中创建。
*/
class Object:public QObject{
Q_OBJECT
public:
    Object(const int cameraNo);//combine initOpporations
    ~Object();

private:
    Frame_header *frame_header;

    char *input_buf;
    char *output_buf;

    long output_buf_size;
    long input_buf_size;
    int K_old, R_old;
    int cur_frame_no;
    int last_frame_no;
    int old_frame_no;

    char fileName[30];


    uint32 raptor_K_recieve,
    raptor_R_recieve,
    raptor_N_recieve,
    raptor_K_temp,
    raptor_R_temp,
    raptor_N_temp;


    uint16 *list_cur;
    uint16 list_temp;

//    QTimer* timer;
    int camera_no;

    QUdpSocket *groupBroadcast;

    /******file*****/

    FILE *store_v;
    FILE *record_v;

#ifdef GILBERT_DEBUG
    long cnt_get;
    long pre_slice_no;
    long get_slice_no;
    long slice_no_pre;

    char fb_data[10];

    int L_b;
    int T_next;
    int cursor;
    int state_lost[NI];
    int n1[MAX_WINDOW_SIZE],
        n2[MAX_WINDOW_SIZE],
        n3[MAX_WINDOW_SIZE],
        n4[MAX_WINDOW_SIZE];

    double gil;
    double ber;
    double N1, N2, N3, N4;

    FILE * gil_sml;
    struct EBR_data *EBR_data_addr;

#endif

signals:
    void dataReady_obj(const int);

public slots:
    void decode();
//    void deal_timeout();
};

class DecodeThread:public QThread{
Q_OBJECT
public:
    DecodeThread(const int cameraNo);
    ~DecodeThread();
    void run();

signals:
    void dataArrived();
    void dataReady_deco(const int);


private:
    int camera_no;

};


#endif // DECODE_FUNC_H
