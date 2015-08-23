#include <QDebug>
#include "display_func.h"
#include <qpoint.h>

extern QList<QPoint> points;//存放SDL画线的点的集合

ShowObject::ShowObject(const DisplayPara myDispara){
//    hwnd = myDispara.my_hwnd;
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

//    qDebug()<<"ShwoObject-ID = "<<QThread::currentThreadId();

}

ShowObject::~ShowObject(){
    SDL_FreeYUVOverlay(bmp);
    SDL_FreeSurface(screen);
    SDL_Quit();

    av_free(pFrame);
//    avcodec_close(pCodecCtx);
//    av_close_input_file(pFormatCtx);
}

void ShowObject::deal_timeout(){
    if(yuv_debug){
        if(yuv_file){
            fclose(yuv_file);
            yuv_file = NULL;

            fileNum++;
        }
    }

    timer.stop();
}

void ShowObject::resetCamera(const int cameraNo,const int winNo){
    camera_no = cameraNo;
    win_no=winNo;

//    cout<<"show_thread-"<<QThread::currentThreadId()<<"-cameraNo = "<<camera_no
//       <<"  winNo = "<<win_no<<endl;
}

void ShowObject::resetDisPara(const DisplayPara myDispara){
    ww = myDispara.my_width;
    hh = myDispara.my_height;
}


void ShowObject::dealShowVideo(){
//    ////debug
//    if(camera_no==2)
//        cout<<"show_thread_"<<camera_no<<" is running! ID : "<<QThread::currentThreadId()<<endl;

    int frameFinished = 0;
    int decode = 0;

    int dataLength = 0;
    char *showData = NULL;

        switch(camera_no){
        case 1:
            if(fullShow0.tryAcquire(1,0)){
                pFrameNoNow = showBuf0[nextGetShow0].frameNo;
                dataLength = showBuf0[nextGetShow0].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf0[nextGetShow0].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow0.release();

                nextGetShow0++;
                nextGetShow0 %= MAX_BUF_SIZE;
            }

            break;

        case 2:
            if(fullShow1.tryAcquire(1,0)){
                pFrameNoNow = showBuf1[nextGetShow1].frameNo;
                dataLength = showBuf1[nextGetShow1].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf1[nextGetShow1].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow1.release();

                nextGetShow1++;
                nextGetShow1 %= MAX_BUF_SIZE;
            }

            break;

        case 3:
            if(fullShow2.tryAcquire(1,0)){
                pFrameNoNow = showBuf2[nextGetShow2].frameNo;
                dataLength = showBuf2[nextGetShow2].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf2[nextGetShow2].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow2.release();

                nextGetShow2++;
                nextGetShow2 %= MAX_BUF_SIZE;
            }

            break;

        case 4:
            if(fullShow3.tryAcquire(1,0)){
                pFrameNoNow = showBuf3[nextGetShow3].frameNo;
                dataLength = showBuf3[nextGetShow3].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf3[nextGetShow3].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow3.release();

                nextGetShow3++;
                nextGetShow3 %= MAX_BUF_SIZE;
            }

            break;

        case 5:
            if(fullShow4.tryAcquire(1,0)){
                pFrameNoNow = showBuf4[nextGetShow4].frameNo;
                dataLength = showBuf4[nextGetShow4].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf4[nextGetShow4].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow4.release();

                nextGetShow4++;
                nextGetShow4 %= MAX_BUF_SIZE;
            }

            break;

        case 6:
            if(fullShow5.tryAcquire(1,0)){
                pFrameNoNow = showBuf5[nextGetShow5].frameNo;
                dataLength = showBuf5[nextGetShow5].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf5[nextGetShow5].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow5.release();

                nextGetShow5++;
                nextGetShow5 %= MAX_BUF_SIZE;
            }

            break;

        case 7:
            if(fullShow6.tryAcquire(1,0)){
                pFrameNoNow = showBuf6[nextGetShow6].frameNo;
                dataLength = showBuf6[nextGetShow6].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf6[nextGetShow6].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow6.release();

                nextGetShow6++;
                nextGetShow6 %= MAX_BUF_SIZE;
            }

            break;

        case 8:
            if(fullShow7.tryAcquire(1,0)){
                pFrameNoNow = showBuf7[nextGetShow7].frameNo;
                dataLength = showBuf7[nextGetShow7].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf7[nextGetShow7].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow7.release();

                nextGetShow7++;
                nextGetShow7 %= MAX_BUF_SIZE;
            }

            break;

        case 9:
            if(fullShow8.tryAcquire(1,0)){
                pFrameNoNow = showBuf8[nextGetShow8].frameNo;
                dataLength = showBuf8[nextGetShow8].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf8[nextGetShow8].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow8.release();

                nextGetShow8++;
                nextGetShow8 %= MAX_BUF_SIZE;
            }

            break;

        case 10:
            if(fullShow9.tryAcquire(1,0)){
                pFrameNoNow = showBuf9[nextGetShow9].frameNo;
                dataLength = showBuf9[nextGetShow9].size;
                showData = (char*)malloc((dataLength+1)*sizeof(char));
                memcpy(showData, showBuf9[nextGetShow9].h264node, dataLength);
                showData[dataLength] = '\0';

                emptyShow9.release();

                nextGetShow9++;
                nextGetShow9 %= MAX_BUF_SIZE;
            }

            break;

        default:
            break;
        }

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
                //bresenham_line(bmp,sx,sy,ex,ey);
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
//    }
    //else
    //printf("....queue empty....\n");
}


ShowThread::ShowThread(DisplayPara myDisPara){
        myShowPara.my_width = myDisPara.my_width;
        myShowPara.my_height = myDisPara.my_height;

//        qDebug()<<"ShowThread-ID = "<<currentThreadId();

}

ShowThread::~ShowThread(){
    quit();
    wait();
    deleteLater();
}

void ShowThread::run(){
    ShowObject obj(myShowPara);
    obj.moveToThread(this);

    connect(this, SIGNAL(resetCamera(const int,const int)), &obj, SLOT(resetCamera(const int,const int)), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(dataArrived()), &obj, SLOT(dealShowVideo()), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(resetWinPara(const DisplayPara)), &obj, SLOT(resetDisPara(const DisplayPara)), Qt::BlockingQueuedConnection);

    exec();
}

int ShowObject::changePointsByWinNo(int &x, int &y)
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

void ShowObject::drawPoint(SDL_Overlay *yuv, int x, int y)
{
    drawHLine(yuv,x,y,1);
}

void ShowObject::drawHLine(SDL_Overlay *yuv, int sx, int sy, int len)
{
    SDL_Rect rect = {sx,sy, len, 1};
    fillRect(yuv, &rect, 255,255,255);
}

void ShowObject::drawHLine_(SDL_Overlay *yuv, int sx, int sy, int len)
{
    int w = yuv->pitches[0];
    memset(yuv->pixels[0]+sy*w + sx, 255, len*1);
    memset(yuv->pixels[1]+(sy*w + 2*sx)/4, 255, (len+1)/2);
    memset(yuv->pixels[2]+(sy*w + 2*sx)/4, 255, (len+1)/2);
}

void ShowObject::fillRect(SDL_Overlay *yuv, SDL_Rect *rect, int y0, int u, int v)
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

void ShowObject::drawLine(SDL_Overlay *yuv, int sx, int sy, int ex, int ey)
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

void ShowObject::bresenham_line(SDL_Overlay *yuv, int sx, int sy, int ex, int ey)
{
 int dx,dy,x,y,p,const1,const2,inc,tmp;
 dx = ex-sx;
 dy = ey-sy;
 if(dx*dy >= 0)
  inc = 1;
 else
  inc = -1;
 if(abs(dx)>abs(dy))
 {
  if(dx<0)
  {
   tmp = sx;
   sx = ex;
   ex = tmp;
   tmp = sy;
   sy = ey;
   ey = tmp;
   dx = -dx;
   dy = -dy;
  }
  p = 2*dy-dx;
  const1 = 2*dy;
  const2 = 2*(dy-dx);
  x = sx;
  y = sy;
  drawPoint(yuv,x,y);
  while(x<ex)
  {
   x++;
   if(p<0)
    p += const1;
   else
   {
    y += inc;
    p += const2;
   }
   drawPoint(yuv,x,y);
  }
 }
 else
 {
  if(dy<0)
  {
   tmp = sx;
   sx = ex;
   ex = tmp;
   tmp = sy;
   sy = ey;
   ey = tmp;
   dx = -dx;
   dy = -dy;
  }
  p = 2*dy-dx;
  const1 = 2*dy;
  const2 = 2*(dy-dx);
  x = sx;
  y = sy;
  drawPoint(yuv,x,y);
  while(y<ey)
  {
   y++;
   if(p<0)
    p += const1;
   else
   {
    x+=inc;
    p+=const2;
   }
   drawPoint(yuv,x,y);
  }
 }
}
