#include <WinSock2.h>

#include "video_recv.h"
#include "video_show.h"

#include "video_decode.h"

using namespace std;

showfr_ring_t showfr_ring;

DecodeThread *decode_thread;

VideoDecode::VideoDecode()
{
    SRING_HEAD = 0;
    SRING_TAIL = 0;

    raptor_K_temp = 0;
    raptor_R_temp = 0;
    raptor_N_temp = 0;
    raptor_K_recieve = 0;
    raptor_R_recieve = 0;
    raptor_N_recieve = 0;

    output_buf_size = 0;
    input_buf_size = 0;

    cur_frame_no = 1;
    last_frame_no = 0;
    old_frame_no = -1;

    input_buf = NULL;
    output_buf = NULL;
    list_cur = NULL;
    para = NULL;
    temp = NULL;
    output = NULL;
    frame_data = NULL;

    decode_alloc();
}

VideoDecode::~VideoDecode()
{
    decode_free();
}

void VideoDecode::decode_alloc()
{
    decode_free();

    input_buf = (char *)malloc(MAX_BUF);
    if(!input_buf){
        qDebug() << "malloc input_buf failed!" << endl;
        exit(1);
    }

    output_buf = (char *)malloc(MAX_BUF);
    if(!output_buf){
        qDebug() << "malloc output_buf failed!" << endl;
        exit(1);
    }

    list_cur = (uint16*)malloc(MAX_BUF);
    if(!list_cur){
        qDebug() << "malloc list_cur failed!" << endl;
        exit(1);
    }

    para = (RParam_dec)malloc(sizeof(RaptorParam_dec));
    if(!para){
        qDebug() << "malloc para failed!" << endl;
        exit(1);
    }

    temp = (uint8*)malloc(MAX_BUF);
    if(!temp){
        qDebug() << "malloc para failed!" << endl;
        exit(1);
    }

    output = (uint8*)malloc(MAX_BUF);
    if(!output){
        qDebug() << "malloc output failed!" << endl;
        exit(1);
    }

    frame_data = (char *)malloc(MAX_BUF);
    if(!frame_data){
        qDebug() << "malloc frame_data failed!" << endl;
        exit(1);
    }
}

void VideoDecode::decode_free()
{

    qDebug() << "[decode_free]begin" << endl;
    if(input_buf)
        free(input_buf);
    if(output_buf)
        free(output_buf);
    if(list_cur)
        free(list_cur);
    if(para)
        free(para);
    if(temp)
        free(temp);
    if(output)
        free(output);
    if(frame_data)
        free(frame_data);

    input_buf = NULL;
    output_buf = NULL;
    list_cur = NULL;
    para = NULL;
    temp = NULL;
    output = NULL;
    frame_data = NULL;

    qDebug() << "[decode_free]end" << endl;
}

void VideoDecode::decode_init()
{
    //初始化相关变量
    frame_no = VRING_HEAD_FARAME_HDR.frame_no;
    slice_no = VRING_HEAD_FARAME_HDR.slice_no - 1;
    frame_type = VRING_HEAD_FARAME_HDR.frame_type;
    F = VRING_HEAD_FARAME_HDR.F;
    T = VRING_HEAD_FARAME_HDR.T;
    K = VRING_HEAD_FARAME_HDR.K;
    R = VRING_HEAD_FARAME_HDR.R;
    esi = VRING_HEAD_FARAME_HDR.esi - 1;
    camera_no = VRING_HEAD_FARAME_HDR.camera_no;

    K_old = K;
    R_old = R;

    memcpy(&loop_num, VRING_HEAD_FARAME_BUF + T + sizeof(Frame_header), 4);
    loop_num = ntohl(loop_num);

    qDebug() << "[decode_init]=============>" << endl
             << "frame_no = " << frame_no << endl
             << "slice_no = " << slice_no << endl
             << "frame_type = " << frame_type << endl
             << "F = " << F << endl
             << "T = " << T << endl
             << "K = " << K << endl
             << "R = " << R << endl
             << "esi = " << esi << endl
             << "camera_no = " << camera_no << endl
             << "loop_num = " << loop_num << endl;
}

int VideoDecode::pre_raptor(int i)
{
    //ricann debug
    qDebug() << "[pre_raptor] begin" <<endl;

    slice_no++;
    esi++;

    memset(frame_data, 0, MAX_FRAME_BUF);
    memcpy(frame_data, VRING_HEAD_FARAME_BUF + \
        i*T + sizeof(Frame_header) + sizeof(int), T);

    /*
    if((frame_no < cur_frame_no) &&
            (frame_no > 10)) {
        qDebug() << "[slot_decode]drop frame, "
                 << "cur_frame_no = " << cur_frame_no
                 << "frame_no = " << frame_no
                 << endl;
        //直接丢弃
        continue;
    }
    //*/

    //当收到的分片的帧号与预计收到的不同时，cur_frame_no 是当前应该收到的帧号
    //两种特殊情况：1.收到超前的分片 2.接收到已经过期的分片
    if(frame_no != cur_frame_no)
    {
        last_frame_no = cur_frame_no;
        cur_frame_no = frame_no;//重新开始计数

        if(frame_type == 1)//raptor
        {
            //保存上一帧的相关数据计数信息
            raptor_K_recieve = raptor_K_temp;
            raptor_R_recieve = raptor_R_temp;
            raptor_N_recieve = raptor_N_temp;

            //重新计数
            raptor_K_temp = 0;
            raptor_R_temp = 0;

            if(esi < K)
                raptor_K_temp = 1;
            else
                raptor_R_temp = 1;
            raptor_N_temp = 1;

            list_temp = esi;
        }

        return DECODE_LOOP_CUR;
    }

    //接收到预计帧的分片, frame_no == cur_frame_no
    if(frame_type != 1)//非raptor
    {
        output_buf_size = K*T;
        //将数据copy到等待加入264解码队列的输入区
        memcpy(output_buf+esi*T, frame_data, T);
        return DECODE_LOOP_NEXT;//继续接收分片
    }

    //raptor, frame_type == 1
    if((int)raptor_K_temp == K_old)
        return DECODE_LOOP_NEXT;

    //记录当前帧已经收到的分片数，同时区分是源分片，还是冗余分片
    if(esi < K)
        raptor_K_temp++;  //源数据
    else
        raptor_R_temp++;  //冗余分片
    raptor_N_temp++;  //总数

    //分片的esi存入list，用于raptor解码
    list_cur[raptor_N_temp-1] = esi;

    //将数据copy到解码用的输入区
    memcpy(input_buf+(raptor_N_temp-1)*T, frame_data, T);

    return DECODE_LOOP_NEXT;//继续接收分片
}

void VideoDecode::do_raptor()
{
    int result_dec = 0;

    //ricann debug
    qDebug() << "[do_raptor] begin" <<endl;

    if(frame_type != 1)
        return;

    if(raptor_N_recieve <= 0)
        return;

    //raptor解码
    //如果源分片全部接收到，则无需raptor解码，直接存入output_buf
    if(K_old == (int)raptor_K_recieve && K_old)
    {
        result_dec = 1;
        output_buf_size = K_old*T;

        if(output_buf_size){
            qDebug() << "[decode_init]output_buf_size = "
                     << output_buf_size << endl;
            memcpy(output_buf, input_buf, output_buf_size);
            output_buf[output_buf_size] = '\0';
        }

        K_old = 0;
        return;
    }

    //如果需要raptor解码
    //如果接收到的分片总数超过源分片的总数，则进行raptor解码
    if((int)raptor_N_recieve > K_old)
    {
        raptor_init(K_old, raptor_N_recieve, para);

        for(uint32 i = 0; i < raptor_N_recieve; i++)
            para->list[i] = list_cur[i];

        qDebug() << "[decode_init](para->S+para->H+raptor_N_recieve)*T = "
                 << (para->S+para->H+raptor_N_recieve)*T << endl;

        qDebug() << "[decode_init]raptor_N_recieve*T = "
                 << raptor_N_recieve*T << endl;

        memset(temp, 0, (para->S+para->H+raptor_N_recieve)*T);
        memcpy(temp+(para->S+para->H)*T,input_buf, raptor_N_recieve*T);

        result_dec = raptor_decode(para, temp, output, T);//解码

        if(result_dec){
            output_buf_size = K_old*T;

            qDebug() << "[decode_init]K_old*T = "
                     << K_old*T << endl;

            //解码成功后，将结果存入output_buf
            memcpy(output_buf, output, K_old*T);
            output_buf[K_old*T] = '\0';
        }
        else{
            output_buf_size = (K_old+R_old)*T;

            if(output_buf_size){
                for(uint32 i = 0; i < raptor_N_recieve; i++) {
                    qDebug() << "[decode_init]list_cur[i]*T = "
                             << list_cur[i]*T << endl;

                    memcpy(output_buf+list_cur[i]*T, input_buf+i*T, T);
                }
                input_buf_size = 0;
            }
        }
        raptor_parameterfree(para);
    }
    else//如果接收到的分片数不足，则将数据按esi存储进相应的位置
    {
        printf("can not raptor??????????????????\n");
        output_buf_size = T*(K_old+R_old);

        if(output_buf_size){
            memset(output_buf, 0, output_buf_size+1);
            for(uint32 i = 0; i < raptor_N_recieve; i++) {
                qDebug() << "[decode_init]2 list_cur[i]*T = "
                         << list_cur[i]*T << endl;
                memcpy(output_buf+list_cur[i]*T, input_buf+i*T, T);
            }
            input_buf_size = 0;
        }
    }//else分片数不足

    K_old = 0;
}

void VideoDecode::fol_raptor()
{
    //ricann debug
    qDebug() << "[fol_raptor] begin" <<endl;

    //视频存储帧号可能不从1开始，因而导致视与源视频帧不对齐
    if(output_buf_size)
    {
        SRING_TAIL_FARAME_FNO = last_frame_no;
        SRING_HEAD_FARAME_CNO = camera_no;
        SRING_TAIL_FARAME_SIZE = output_buf_size;
        memcpy(SRING_TAIL_FARAME_BUF, output_buf, output_buf_size);
        SRING_TAIL_FARAME_BUF[output_buf_size] = '\0';

        //update ring tail number
        SRING_TAIL = (SRING_TAIL+1) % VIDEO_RING_NUM;

        emit sig_dataready();

        //ricann todo
        //写视频到文件，并且多播到ffmpeg服务器
    }


    //解码上一帧后，处理当前帧的第一个分片相关数据
    if(frame_type == 1)
    {
        list_cur[0] = list_temp;
        K_old = K;
        R_old = R;
        /************************/
        memcpy(input_buf, frame_data, T);
        input_buf_size = T;
    }
    else
    {
        output_buf_size = K*T;
        memcpy(output_buf+esi*T, frame_data, T);
    }
}

void VideoDecode::slot_decode()
{
    //video_ring is empty
    if(VRING_HEAD == VRING_TAIL)
        return;

    while(1) {
        //ring is full, wait
        if(SRING_HEAD == ((SRING_TAIL+1) % VIDEO_RING_NUM)) {
            qDebug()<<"showfr ring is full!\n";
            continue;
        }
        break;
    }

    decode_init();

    for(int i = 0; i < loop_num + 1; i++)
    {
        if(pre_raptor(i) == DECODE_LOOP_NEXT)
            continue;

        do_raptor();

        fol_raptor();

    }//for

    //update vring head number
    VRING_HEAD = (VRING_HEAD+1) % VIDEO_RING_NUM;
}

DecodeThread::DecodeThread()
{

}

DecodeThread::~DecodeThread()
{
    quit();
    wait();
    deleteLater();
}


void DecodeThread::run()
{
    VideoDecode vd;
    vd.moveToThread(this);

    //到这来的信号
    connect(this, SIGNAL(sig_dataarrived()),
            &vd, SLOT(slot_decode()),
            Qt::BlockingQueuedConnection);

    //送出去的信号
    connect(&vd, SIGNAL(sig_dataready()),
            show_thread, SIGNAL(sig_dataarrived()));

    //(除ui线程之外的其他)线程用QThread::exec()开始事件循环
    exec();
}

