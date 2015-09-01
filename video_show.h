#ifndef VIDEO_SHOW_H
#define VIDEO_SHOW_H

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

#include "externvar.h"

class VideoShow:public QObject{
    Q_OBJECT
public:
    VideoShow(const DisplayPara myDispara);//contain initialization
    ~VideoShow();

    //找到并打开解码器(只能打开一个解码器)
    void SDL_init();

public slots:
    void slot_showvideo();

private:
    int camera_no;
    int win_no;

    int ww;
    int hh;
    unsigned int winid;

    SDL_Surface *screen;
    SDL_Overlay *bmp;
    SDL_Rect dst;

    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodecContext *pCodecCtxT;
    AVCodec *pCodec;
    AVFrame *pFrame;

    struct SwsContext *img_convert_ctx;
    SDL_Event event_sdl;
    AVPicture pict;

    int fileNum;
    FILE *yuv_file;
    int pFrameNoNext;
    int pFrameNoNow;

    QTimer timer;
};

class ShowThread:public QThread{
Q_OBJECT
public:
    ShowThread(DisplayPara myDisPara);
    ~ShowThread();
    void run();

signals:
    void sig_dataarrived();
    //void resetWinPara(const DisplayPara myDispara);
    //void resetCamera(const int cameraNo, const int winNo);

private:
    DisplayPara myShowPara;
};

extern ShowThread *show_thread;

#endif // VIDEO_SHOW_H
