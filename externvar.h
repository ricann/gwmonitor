#ifndef EXTERNVAR_H
#define EXTERNVAR_H

#include "commoninc_qt.h"
#include <Winsock2.h>
#include <list>
#include <iostream>

using namespace std;

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


extern int replay;
extern int yuv_debug;
extern int video_debug;

extern int play_or_not[MAX_CAMERA_NUM];
extern int camera_history[MAX_PLAY_NUM];


extern unsigned int nextPutFrame0;
extern unsigned int nextGetFrame0;
extern unsigned int nextPutFrame1;
extern unsigned int nextGetFrame1;
extern unsigned int nextPutFrame2;
extern unsigned int nextGetFrame2;
extern unsigned int nextPutFrame3;
extern unsigned int nextGetFrame3;
extern unsigned int nextPutFrame4;
extern unsigned int nextGetFrame4;
extern unsigned int nextPutFrame5;
extern unsigned int nextGetFrame5;
extern unsigned int nextPutFrame6;
extern unsigned int nextGetFrame6;
extern unsigned int nextPutFrame7;
extern unsigned int nextGetFrame7;
extern unsigned int nextPutFrame8;
extern unsigned int nextGetFrame8;
extern unsigned int nextPutFrame9;
extern unsigned int nextGetFrame9;

extern QSemaphore fullFrame0;
extern QSemaphore emptyFrame0;
extern QSemaphore fullFrame1;
extern QSemaphore emptyFrame1;
extern QSemaphore fullFrame2;
extern QSemaphore emptyFrame2;
extern QSemaphore fullFrame3;
extern QSemaphore emptyFrame3;
extern QSemaphore fullFrame4;
extern QSemaphore emptyFrame4;
extern QSemaphore fullFrame5;
extern QSemaphore emptyFrame5;
extern QSemaphore fullFrame6;
extern QSemaphore emptyFrame6;
extern QSemaphore fullFrame7;
extern QSemaphore emptyFrame7;
extern QSemaphore fullFrame8;
extern QSemaphore emptyFrame8;
extern QSemaphore fullFrame9;
extern QSemaphore emptyFrame9;


extern unsigned int nextPutShow0;
extern unsigned int nextGetShow0;
extern unsigned int nextPutShow1;
extern unsigned int nextGetShow1;
extern unsigned int nextPutShow2;
extern unsigned int nextGetShow2;
extern unsigned int nextPutShow3;
extern unsigned int nextGetShow3;
extern unsigned int nextPutShow4;
extern unsigned int nextGetShow4;
extern unsigned int nextPutShow5;
extern unsigned int nextGetShow5;
extern unsigned int nextPutShow6;
extern unsigned int nextGetShow6;
extern unsigned int nextPutShow7;
extern unsigned int nextGetShow7;
extern unsigned int nextPutShow8;
extern unsigned int nextGetShow8;
extern unsigned int nextPutShow9;
extern unsigned int nextGetShow9;

extern QSemaphore fullShow0;
extern QSemaphore emptyShow0;
extern QSemaphore fullShow1;
extern QSemaphore emptyShow1;
extern QSemaphore fullShow2;
extern QSemaphore emptyShow2;
extern QSemaphore fullShow3;
extern QSemaphore emptyShow3;
extern QSemaphore fullShow4;
extern QSemaphore emptyShow4;
extern QSemaphore fullShow5;
extern QSemaphore emptyShow5;
extern QSemaphore fullShow6;
extern QSemaphore emptyShow6;
extern QSemaphore fullShow7;
extern QSemaphore emptyShow7;
extern QSemaphore fullShow8;
extern QSemaphore emptyShow8;
extern QSemaphore fullShow9;
extern QSemaphore emptyShow9;

extern char frameBuf0[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf1[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf2[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf3[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf4[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf5[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf6[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf7[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf8[MAX_BUF_SIZE][MAXLINE];
extern char frameBuf9[MAX_BUF_SIZE][MAXLINE];

extern ShowNode showBuf0[MAX_BUF_SIZE];
extern ShowNode showBuf1[MAX_BUF_SIZE];
extern ShowNode showBuf2[MAX_BUF_SIZE];
extern ShowNode showBuf3[MAX_BUF_SIZE];
extern ShowNode showBuf4[MAX_BUF_SIZE];
extern ShowNode showBuf5[MAX_BUF_SIZE];
extern ShowNode showBuf6[MAX_BUF_SIZE];
extern ShowNode showBuf7[MAX_BUF_SIZE];
extern ShowNode showBuf8[MAX_BUF_SIZE];
extern ShowNode showBuf9[MAX_BUF_SIZE];

extern QMutex mutex_avcodec;//mutex是QT中预留的关键字，不能用来自定义变量!!
extern SDL_Surface *screen;
extern AVFormatContext *pFormatCtx;
extern AVCodecContext *pCodecCtx;
extern AVCodec *pCodec;


#endif // EXTERNVAR_H
