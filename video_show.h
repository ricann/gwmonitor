#ifndef VIDEO_SHOW_H
#define VIDEO_SHOW_H

#include "externvar.h"

class VideoShow:public QObject{
    Q_OBJECT
public:
    VideoShow(const DisplayPara myDispara);//contain initialization
    ~VideoShow();

public slots:
    void slot_showvideo();
    void resetDisPara(const DisplayPara myDispara);
    void resetCamera(const int cameraNo, const int winNo);
    void deal_timeout();

private:
    int camera_no;
    int win_no;

    int ww;
    int hh;

    AVCodecContext *pCodecCtxT;
    AVFrame *pFrame;

    SDL_Overlay *bmp;
    SDL_Rect dst;

    struct SwsContext *img_convert_ctx;
    SDL_Event event_sdl;
    AVPicture pict;


    int fileNum;
    FILE *yuv_file;
    int pFrameNoNext;
    int pFrameNoNow;

    QTimer timer;

    int changePointsByWinNo(int &x, int &y);
    void drawPoint(SDL_Overlay *yuv, int x, int y);
    void drawHLine(SDL_Overlay *yuv, int sx, int sy, int len);
    void fillRect(SDL_Overlay *yuv, SDL_Rect *rect, int y0, int u, int v);
    void drawLine(SDL_Overlay *yuv, int sx, int sy, int ex, int ey);

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
