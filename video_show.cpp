#include <QPoint>

#include <iostream>

#include "video_recv.h"
#include "video_decode.h"

#include "video_show.h"

using namespace std;

extern QList<QPoint> points;//存放SDL画线的点的集合

extern showfr_ring_t showfr_ring;

ShowThread *show_thread;

VideoShow::VideoShow(const DisplayPara myDispara)
{
    ww = myDispara.my_width;
    hh = myDispara.my_height;

    pFrame=avcodec_alloc_frame();//给视频帧分配空间以便存储解码后的图片

    mutex_avcodec.lock();

    bmp = SDL_CreateYUVOverlay(pCodecCtx->width, pCodecCtx->height, SDL_YV12_OVERLAY, screen);
    img_convert_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,pCodecCtx->width,pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
    if (img_convert_ctx == NULL){
        cout<<"img_convert_ctx == NULL\n";
        exit(-1);
    }

    pCodecCtxT=avcodec_alloc_context();
    pCodecCtxT->width = pCodecCtx->width;
    pCodecCtxT->height = pCodecCtx->height;
    pCodecCtxT->time_base.num = pCodecCtx->time_base.num;
    pCodecCtxT->time_base.den = pCodecCtx->time_base.den;
    pCodecCtxT->codec_type = pCodecCtx->codec_type;
    pCodecCtxT->bit_rate = pCodecCtx->bit_rate;
    pCodecCtxT->frame_number = pCodecCtx->frame_number;
    pCodecCtxT->coded_frame = pCodecCtx->coded_frame;
    pCodecCtxT->extradata = pCodecCtx->extradata;
    pCodecCtxT->extradata_size = pCodecCtx->extradata_size;

    if(avcodec_open(pCodecCtxT, pCodec)<0){
        cout<<"avcodec_open failure\n";
        exit(-1);
    }

    mutex_avcodec.unlock();

    fileNum = 0;
    pFrameNoNext = 1;
    pFrameNoNow = -1;

    yuv_file = NULL;

    connect(&timer,SIGNAL(timeout()),this,SLOT(deal_timeout()));
}

VideoShow::~VideoShow()
{
    SDL_FreeYUVOverlay(bmp);
    SDL_FreeSurface(screen);
    SDL_Quit();

    av_free(pFrame);
//    avcodec_close(pCodecCtx);
//    av_close_input_file(pFormatCtx);
}

void VideoShow::deal_timeout()
{
    if(yuv_debug){
        if(yuv_file){
            fclose(yuv_file);
            yuv_file = NULL;

            fileNum++;
        }
    }

    timer.stop();
}

void VideoShow::resetCamera(const int cameraNo,const int winNo)
{
    camera_no = cameraNo;
    win_no=winNo;
}

void VideoShow::resetDisPara(const DisplayPara myDispara)
{
    ww = myDispara.my_width;
    hh = myDispara.my_height;
}


void VideoShow::slot_showvideo()
{

    int frameFinished = 0;
    int decode = 0;

    int dataLength = 0;
    char *showData = NULL;

    //showfr_ring is empty
    if(SRING_HEAD == SRING_TAIL)
        return;

    camera_no = SRING_HEAD_FARAME_CNO;
    pFrameNoNow = SRING_HEAD_FARAME_FNO;
    dataLength = SRING_HEAD_FARAME_SIZE;
    showData = (char*)malloc((dataLength+1)*sizeof(char));
    memcpy(showData, SRING_HEAD_FARAME_BUF, dataLength);
    showData[dataLength] = '\0';



        if(!timer.isActive()){
            timer.start(10 * 1000);
        }
        else{
            timer.stop();
            timer.start(10 * 1000);
        }

        if(yuv_debug){
            if(pFrameNoNext == 1){//当发送端不停顿但接收端重启时，防止因填充帧使程序阻塞在此处
                pFrameNoNext = pFrameNoNow;
            }
            else if(pFrameNoNext < pFrameNoNow){
                if(!yuv_file){
                    char fileName[10];
                    memset(fileName, 0, 10);
                    sprintf(fileName, "%d", fileNum);

                    char yuv_file_name[30];
                    memset(yuv_file_name, 0, 30);
                    sprintf(yuv_file_name, "%d", camera_no);
                    strcat(yuv_file_name, "_");
                    strcat(yuv_file_name, fileName);
                    strcat(yuv_file_name, ".yuv");

                    yuv_file = fopen(yuv_file_name, "wb");
                }

                //initialize buffer
                char k_yuv[(480*272)+(480*272)/2];
                memset(k_yuv, 255, (480*272)+(480*272)/2);

                //make up lost_frames
                for(int i = pFrameNoNext; i < pFrameNoNow; i++){
                    fwrite(k_yuv, 1, (480*272)+(480*272)/2, yuv_file);
                    fflush(yuv_file);
                }
            }
        }

        if(showData){
            decode = avcodec_decode_video(pCodecCtxT, pFrame, &frameFinished,(const unsigned char*)showData, dataLength);
            free(showData);
            showData = NULL;
        }


        if(frameFinished > 0){

            //////retore video data after 264-decoder///////
            if(yuv_debug){
                if(!yuv_file){
                    char fileName[10];
                    memset(fileName, 0, 10);
                    sprintf(fileName, "%d", fileNum);

                    char yuv_file_name[30];
                    memset(yuv_file_name, 0, 30);
                    sprintf(yuv_file_name, "%d", camera_no);
                    strcat(yuv_file_name, "_");
                    strcat(yuv_file_name, fileName);
                    strcat(yuv_file_name, ".yuv");

                    yuv_file = fopen(yuv_file_name, "wb");
                }

                int xx, yy, zz;
                char g_yuv[(480*272)+(480*272)/2];

                for(xx=0;xx<pCodecCtxT->height;xx++)
                    memcpy(g_yuv+pCodecCtxT->width*xx, pFrame->data[0]+pFrame->linesize[0]*xx,pCodecCtxT->width);
                for(yy=0;yy<pCodecCtxT->height/2;yy++)
                    memcpy(g_yuv+pCodecCtxT->width*xx+pCodecCtxT->width/2*yy,pFrame->data[1]+pFrame->linesize[1]*yy,pCodecCtxT->width/2);
                for(zz=0;zz<pCodecCtxT->height/2;zz++)
                    memcpy(g_yuv+pCodecCtxT->width*xx+pCodecCtxT->width/2*yy+pCodecCtxT->width/2*zz, pFrame->data[2]+pFrame->linesize[2]*zz, pCodecCtxT->width/2);

                fwrite(g_yuv, 1, (480*272)+(480*272)/2, yuv_file);
                fflush(yuv_file);

            }

            SDL_LockYUVOverlay(bmp);
            pict.data[0] = bmp->pixels[0];
            pict.data[1] = bmp->pixels[2];
            pict.data[2] = bmp->pixels[1];

            pict.linesize[0] = bmp->pitches[0];
            pict.linesize[1] = bmp->pitches[2];
            pict.linesize[2] = bmp->pitches[1];

            sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtxT->height, pict.data, pict.linesize);
            SDL_UnlockYUVOverlay(bmp);

            screen = SDL_SetVideoMode(ww, hh, 0, SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_DOUBLEBUF);


                switch(win_no){
                case 1:
                    dst.x = 0;
                    dst.y = 0;
                    dst.w =(ww-5)/2;
                    dst.h =(hh-5)/2;
                    break;
                case 2:
                    dst.x = (ww+5)/2;
                    dst.y = 0;
                    dst.w = (ww-5)/2;
                    dst.h = (hh-5)/2;
                    break;
                case 3:
                    dst.x = 0;
                    dst.y = (hh+5)/2;
                    dst.w = (ww-5)/2;
                    dst.h = (hh-5)/2;
                    break;
                case 4:
                    dst.x = (ww+5)/2;
                    dst.y = (hh+5)/2;
                    dst.w = (ww-5)/2;
                    dst.h = (hh-5)/2;
                    break;
                default:
                    break;
                }
        }

        else if(decode <= 0){
           cout<<"frameFinished <= 0 ; decode > 0"<<endl;
           if(yuv_debug){
                if(!yuv_file){
                    char fileName[10];
                    memset(fileName, 0, 10);
                    itoa(fileNum, fileName, 10);

                    char yuv_file_name[30];
                    memset(yuv_file_name, 0, 30);
                    itoa(camera_no, yuv_file_name, 10);
                    strcat(yuv_file_name, "_");
                    strcat(yuv_file_name, fileName);
                    strcat(yuv_file_name, ".yuv");

                    yuv_file = fopen(yuv_file_name, "wb");
                }

                char k_yuv[(480*272)+(480*272)/2];
                memset(k_yuv, 0,(480*272)+(480*272)/2);
                fwrite(k_yuv, 1, (480*272)+(480*272)/2, yuv_file);
                fflush(yuv_file);
            }
        }else
            cout<<"frameFinished <= 0 ; decode <= 0"<<endl;

        //update pFrameNo
        pFrameNoNext = pFrameNoNow + 1;

        frameFinished = 0;

        //添加函数在SDL窗口画线
        if(points.size() >= 2){
            int sWinNo,eWinNo;
            for(int i = 0;i < points.size()-1;i++) {
                int sx = points[i].x();
                int sy = points[i].y();
                sWinNo = changePointsByWinNo(sx,sy);
                int ex = points[i+1].x();
                int ey = points[i+1].y();
                eWinNo = changePointsByWinNo(ex,ey);
                if(sWinNo == eWinNo && win_no == sWinNo) {
                    drawLine(bmp,sx,sy,ex,ey);
                }
            }
        }

        SDL_DisplayYUVOverlay(bmp, &dst);
        SDL_PollEvent(&event_sdl);
        switch(event_sdl.type){
        case SDL_KEYDOWN:
            switch(event_sdl.key.keysym.sym){
            case SDLK_UP: break;
            case SDLK_DOWN: break;
            default: break;
            }
            cout<<"SDL_KEYDOWN"<<endl;
            break;
        case SDL_VIDEORESIZE:
            screen = SDL_SetVideoMode(event_sdl.resize.w, event_sdl.resize.h, 0,
                                      SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL);
            break;
        case SDL_QUIT:
            SDL_FreeSurface(screen);
            SDL_Quit();
            if(yuv_debug){
                if(yuv_file){
                    fclose(yuv_file);
                    yuv_file = NULL;

                    fileNum++;
                }
            }
            av_free(pFrame);
//            avcodec_close(pCodecCtx);
//            av_close_input_file(pFormatCtx);
            cout<<"event SDL_QUIT occurred"<<endl;
            exit(0);
            break;
        default:
            break;
        }
}

int VideoShow::changePointsByWinNo(int &x, int &y)
{
    int winNo = 0;
    //判定点所在的窗口并转换点的坐标
    if(x>=0 && x<=(ww-5)/2 && y>=0 && y<=(hh-5)/2) {
        //一号窗口
        winNo = 1;
    }
    else if(x>=(ww+5)/2 && x<=ww-1 && y>=0 && y<=(hh-5)/2) {
        //二号窗口
        x = x-(ww+5)/2;

        winNo = 2;
    }
    else if(x>=0 && x<=(ww-5)/2 && y>=(hh+5)/2 && y<=hh-1) {
        //三号窗口
        y = y-(hh+5)/2;

        winNo = 3;
    }
    else if(x>=(ww+5)/2 && x<=ww-1 && y>=(hh+5)/2 && y<=hh-1) {
        //四号窗口
        x = x-(ww+5)/2;
        y = y-(hh+5)/2;

        winNo = 4;
    }
    //resize point坐标 按比例转换到480*272的yuv帧中的位置
    x = x/(double)(ww/2)*480.0;
    y = y/(double)(hh/2)*272.0;
    return winNo;
}

void VideoShow::drawPoint(SDL_Overlay *yuv, int x, int y)
{
    drawHLine(yuv,x,y,1);
}

void VideoShow::drawHLine(SDL_Overlay *yuv, int sx, int sy, int len)
{
    SDL_Rect rect = {sx,sy, len, 1};
    fillRect(yuv, &rect, 255,255,255);
}

void VideoShow::fillRect(SDL_Overlay *yuv, SDL_Rect *rect, int y0, int u, int v)
{
    int y;
    int size = rect->w;
    int uv_size = (size-1)/2+1;
    int uv_off = 0;

    for(y = 0; y< rect->h; ++y)
    {
        memset(yuv->pixels[0] + (rect->y + y) * yuv->pitches[0] + rect->x, y0, size);
        if(y%2 == 0)
        {
            memset(yuv->pixels[1] + (uv_off + rect->y /2) * yuv->pitches[1] + rect->x/2, v, uv_size);
            memset(yuv->pixels[2] + (uv_off + rect->y /2) * yuv->pitches[2] + rect->x/2, u, uv_size);
            ++uv_off;
        }
    }
}

void VideoShow::drawLine(SDL_Overlay *yuv, int sx, int sy, int ex, int ey)
{
    float delta_x,delta_y,x,y;
    int dx,dy,steps,k;
    dx = ex-sx;
    dy = ey-sy;

    if(abs(dx)>abs(dy))
      steps = abs(dx);
    else
      steps = abs(dy);

    delta_x = (float)dx/(float)steps;
    delta_y = (float)dy/(float)steps;
    x = sx;
    y = sy;
    drawPoint(yuv,x,y);
    for(k = 0;k<steps;k++)
    {
     x+=delta_x;
     y+=delta_y;
     drawPoint(yuv,x,y);
    }
}

ShowThread::ShowThread(DisplayPara myDisPara)
{
        myShowPara.my_width = myDisPara.my_width;
        myShowPara.my_height = myDisPara.my_height;
}

ShowThread::~ShowThread()
{
    quit();
    wait();
    deleteLater();
}

void ShowThread::run()
{
    VideoShow vs(myShowPara);
    vs.moveToThread(this);


    connect(this, SIGNAL(sig_dataarrived()),
            &vs, SLOT(slot_showvideo()),
            Qt::BlockingQueuedConnection);

/*    connect(this, SIGNAL(resetCamera(const int,const int)), &obj, SLOT(resetCamera(const int,const int)), Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(resetWinPara(const DisplayPara)), &obj, SLOT(resetDisPara(const DisplayPara)), Qt::BlockingQueuedConnection);
//*/
    exec();
}
