#ifndef DISPLAY_FUNC_H
#define DISPLAY_FUNC_H

#include "externvar.h"
#include <QThread>
#include <QTimer>
#include <iostream>
#include <string.h>
using namespace std;



class ShowObject:public QObject{
    Q_OBJECT
public:
    ShowObject(const DisplayPara myDispara);//contain initialization
    ~ShowObject();

public slots:
    void dealShowVideo();
    void resetDisPara(const DisplayPara myDispara);
    void resetCamera(const int cameraNo, const int winNo);
    void deal_timeout();

private:
    int camera_no;
    int win_no;

    int ww;
    int hh;
//    HWND hwnd;

    AVCodecContext *pCodecCtxT;
    AVFrame *pFrame;

//    SDL_Surface *screen;
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
    void drawHLine_(SDL_Overlay *yuv, int sx, int sy, int len);
    void fillRect(SDL_Overlay *yuv, SDL_Rect *rect, int y0, int u, int v);
    void drawLine(SDL_Overlay *yuv, int sx, int sy, int ex, int ey);
    void bresenham_line(SDL_Overlay *yuv, int sx, int sy, int ex, int ey);

};

class ShowThread:public QThread{
Q_OBJECT
public:
    ShowThread(DisplayPara myDisPara);
    ~ShowThread();
    void run();

signals:
    void dataArrived();
    void resetWinPara(const DisplayPara myDispara);
    void resetCamera(const int cameraNo, const int winNo);

private:
    DisplayPara myShowPara;
};

#endif // DISPLAY_FUNC_H
