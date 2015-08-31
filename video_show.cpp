#include <QPoint>

#include <iostream>

#include "video_recv.h"
#include "video_decode.h"

#include "video_show.h"

using namespace std;

ShowThread *show_thread;

VideoShow::VideoShow(const DisplayPara myDispara)
{
    ww = myDispara.my_width;
    hh = myDispara.my_height;
    winid = myDispara.my_winid;

    SDL_init();

    pFrame = avcodec_alloc_frame();//给视频帧分配空间以便存储解码后的图片

    bmp = SDL_CreateYUVOverlay(pCodecCtx->width,
        pCodecCtx->height, SDL_YV12_OVERLAY, screen);
    img_convert_ctx = sws_getContext(pCodecCtx->width,
        pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width,
        pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC,
        NULL, NULL, NULL);
    if (img_convert_ctx == NULL){
        cout<<"img_convert_ctx == NULL\n";
        exit(-1);
    }

    pCodecCtxT = avcodec_alloc_context();
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
    avcodec_close(pCodecCtx);
    av_close_input_file(pFormatCtx);
}

void VideoShow::SDL_init()
{
    char filename[] = "1.264";
    char variable[64];

    sprintf(variable, "SDL_WINDOWID=0x%x", winid);

    //ricann debug
    qDebug() << variable << endl;

    putenv(variable);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        cout<<"SDL_Init() failure"<<endl;
        exit(1);
    }

    screen = SDL_SetVideoMode(ww, hh, 0,
        SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_DOUBLEBUF);

    if(!screen){
        cout<<"screen == NULL\n";
        exit(1);
    }

    //ricann change, 20150822
    //use avformat_alloc_context instead of av_alloc_format_context
    //use avformat_open_input instead of av_open_input_file
    //use av_dump_format instead of dump_format

    av_register_all();//注册库中含有的所有可用的文件格式和编码器，当打开一个文件时，能够自动选择相应的文件格式和编码器
    pFormatCtx = avformat_alloc_context();//给pFormatCtx分配内存
    if (!pFormatCtx){
        cout<<"avformat_alloc_context() failure"<<endl;
        exit(-1);
    }

    if(avformat_open_input(&pFormatCtx, filename, NULL, NULL) !=0 ){// 打开视频文件
        cout<<"avformat_open_input() failure"<<endl;
        exit(-1);
    }

    if(av_find_stream_info(pFormatCtx)<0){//取出包含在文件中的流信息
        cout<<"av_find_stream_info() failure"<<endl;
        exit(-1);
    }

    av_dump_format(pFormatCtx, 0, filename, 0);//把获取到得参数全部输出

    int videoStream = -1;
    for(int i=0; i < (int)(pFormatCtx->nb_streams); i++){
        //找到视频流
        if((pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO)
                && (videoStream < 0))
            videoStream=i;
        break;
    }

    if(videoStream==-1){
        cout<<"videoStream = -1\n";
        exit(-1);
    }

    pCodecCtx=pFormatCtx->streams[videoStream]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);//寻找解码器

    if(pCodec==NULL){
        cout<<"pCodec == NULL\n";
        exit(-1);
    }

    if(avcodec_open(pCodecCtx, pCodec)<0){//打开解码器
        cout<<"cannot open accodec\n";
        exit(-1);
    }
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
        //ricann todo
        /*
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
        //*/

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

ShowThread::ShowThread(DisplayPara myDisPara)
{
        myShowPara.my_width = myDisPara.my_width;
        myShowPara.my_height = myDisPara.my_height;
        myShowPara.my_winid = myDisPara.my_winid;
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
