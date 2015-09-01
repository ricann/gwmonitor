#include "video_recv.h"
#include "video_decode.h"

#include "video_show.h"

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
        qDebug() << "img_convert_ctx == NULL" << endl;
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
        qDebug() << "avcodec_open failure" <<endl;
        exit(-1);
    }

    fileNum = 0;
    pFrameNoNext = 1;
    pFrameNoNow = -1;

    yuv_file = NULL;
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
        qDebug() << "SDL_Init() failure" << endl;
        exit(1);
    }

    screen = SDL_SetVideoMode(ww, hh, 0,
        SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_DOUBLEBUF);

    if(!screen){
        qDebug() << "screen == NULL" <<endl;
        exit(1);
    }

    //ricann change, 20150822
    //use avformat_alloc_context instead of av_alloc_format_context
    //use avformat_open_input instead of av_open_input_file
    //use av_dump_format instead of dump_format

    av_register_all();//注册库中含有的所有可用的文件格式和编码器，当打开一个文件时，能够自动选择相应的文件格式和编码器
    pFormatCtx = avformat_alloc_context();//给pFormatCtx分配内存
    if (!pFormatCtx){
        qDebug() << "avformat_alloc_context() failure" << endl;
        exit(-1);
    }

    if(avformat_open_input(&pFormatCtx, filename, NULL, NULL) !=0 ){// 打开视频文件
        qDebug() << "avformat_open_input() failure" << endl;
        exit(-1);
    }

    if(av_find_stream_info(pFormatCtx)<0){//取出包含在文件中的流信息
        qDebug() << "av_find_stream_info() failure" << endl;
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
        qDebug() << "videoStream = -1" << endl;
        exit(-1);
    }

    pCodecCtx=pFormatCtx->streams[videoStream]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);//寻找解码器

    if(pCodec == NULL){
        qDebug() << "pCodec == NULL" << endl;
        exit(-1);
    }

    if(avcodec_open(pCodecCtx, pCodec)<0){//打开解码器
        qDebug() << "cannot open accodec" << endl;
        exit(-1);
    }
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
    win_no = node_info[camera_no].cam_info.cam_winid;
    pFrameNoNow = SRING_HEAD_FARAME_FNO;
    dataLength = SRING_HEAD_FARAME_SIZE;

    qDebug() << "[slot_showvideo]"
             << "camera_no = " << camera_no
             << "win_no = " << win_no
             << "pFrameNoNow = " << pFrameNoNow
             << "dataLength = " << dataLength
             << endl;

    showData = (char*)malloc((dataLength+1)*sizeof(char));
    if(!showData) {
        qDebug() <<"malloc failed!" <<endl;
        exit(-1);
    }

    //ricann todo,知道SRING_HEAD_FARAME_SIZE的常见大小之后，考虑用数组
    memcpy(showData, SRING_HEAD_FARAME_BUF, dataLength);
    showData[dataLength] = '\0';
    decode = avcodec_decode_video(pCodecCtxT, pFrame,
        &frameFinished, (const unsigned char*)showData, dataLength);
    free(showData);
    showData = NULL;

    //update sring head number
    SRING_HEAD = (SRING_HEAD+1) % VIDEO_RING_NUM;

    if(frameFinished > 0) {
        SDL_LockYUVOverlay(bmp);
        pict.data[0] = bmp->pixels[0];
        pict.data[1] = bmp->pixels[2];
        pict.data[2] = bmp->pixels[1];

        pict.linesize[0] = bmp->pitches[0];
        pict.linesize[1] = bmp->pitches[2];
        pict.linesize[2] = bmp->pitches[1];

        sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0,
            pCodecCtxT->height, pict.data, pict.linesize);
        SDL_UnlockYUVOverlay(bmp);

        screen = SDL_SetVideoMode(ww, hh, 0,
            SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_DOUBLEBUF);

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
    } else if(decode <= 0)
        qDebug() <<"frameFinished <= 0 ; decode <= 0" << endl;
    else
        qDebug() <<"frameFinished <= 0 ; decode > 0" << endl;

    //update pFrameNo
    pFrameNoNext = pFrameNoNow + 1;

    frameFinished = 0;

    SDL_DisplayYUVOverlay(bmp, &dst);
    SDL_PollEvent(&event_sdl);
    switch(event_sdl.type){
    case SDL_KEYDOWN:
        qDebug() << "SDL_KEYDOWN" << endl;
        break;
    case SDL_VIDEORESIZE:
        qDebug() << "SDL_VIDEORESIZE" << endl;
        screen = SDL_SetVideoMode(event_sdl.resize.w, event_sdl.resize.h, 0,
            SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL);
        break;
    case SDL_QUIT:
        qDebug() << "SDL_QUIT" << endl;
        SDL_FreeSurface(screen);
        SDL_Quit();
        av_free(pFrame);
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

    exec();
}
