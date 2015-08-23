#ifndef DECODE_FUNC_H
#define DECODE_FUNC_H

#include "commoninc_qt.h"
#include "commoninc_std.h"
#include "externvar.h"
#include "raptorcode.h"
#include "ffmpeg.h"
#include <iostream>

using namespace std;

extern FFmpeg *ffmpeg;

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
