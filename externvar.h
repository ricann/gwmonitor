#ifndef EXTERNVAR_H
#define EXTERNVAR_H

/*
#include "commoninc_qt.h"
#include <Winsock2.h>
#include <list>
#include <iostream>

using namespace std;
//*/

#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <SDL_stdinc.h>
    #include <SDL_mutex.h>
    #include <SDL.h>
    #include <SDL_thread.h>
    #include <SDL_main.h>

    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/mathematics.h"
}

typedef struct Frame_header{
    int frame_no;
    long slice_no;
    int frame_type;
    long F;
    int T;
    int K;
    int R;
    int esi;
    int camera_no;
}Frame_header;

typedef struct ShowNode
{
    char h264node[1000000];
    int size;
    int frameNo;
    int cameraNo;
}ShowNode;

typedef struct DisplayPara{
    int my_width;
    int my_height;
}DisplayPara;

#define K1_MAX 10
#define T_MAX 1024

#define MAX_CAMERA_NUM 7
#define MAX_PLAY_NUM 4

#define MAX_BUF_SIZE 5
#define MAXLINE sizeof(Frame_header)+T_MAX

#define VIDEO_RING_NUM    100

extern int replay;
extern int yuv_debug;
extern int video_debug;

extern int play_or_not[MAX_CAMERA_NUM];
extern int camera_history[MAX_PLAY_NUM];

extern QMutex mutex_avcodec;//mutex是QT中预留的关键字，不能用来自定义变量!!
extern SDL_Surface *screen;
extern AVFormatContext *pFormatCtx;
extern AVCodecContext *pCodecCtx;
extern AVCodec *pCodec;

#endif // EXTERNVAR_H
