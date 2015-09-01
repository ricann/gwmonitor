#include <WinSock2.h>
#include <iostream>

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

    input_buf = NULL;
    output_buf = NULL;
    list_cur = NULL;
    store_v = NULL;

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

    groupBroadcast = new QUdpSocket();
}

VideoDecode::~VideoDecode()
{
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

    frame_header = (Frame_header*)malloc(sizeof(Frame_header));
    memcpy((char *)frame_header, &VRING_HEAD_FARAME_HDR, sizeof(Frame_header));


    //ricann todo, 这一部分有待优化
    camera_no = ntohl(frame_header->camera_no);

    frame_header->T = ntohl(frame_header->T);
    int T_cur = frame_header->T;

    frame_header->slice_no = ntohl(frame_header->slice_no);

    int data_len;
    memcpy(&data_len, VRING_HEAD_FARAME_BUF + T_cur + sizeof(Frame_header), 4);
    data_len = ntohl(data_len);

    for(int i = 0; i < data_len + 1; i++)
    {
        char *frame_data = new char[T_cur+1];
        memset(frame_data, 0, T_cur+1);

        //ricann todo,感觉可优化
        if(i == 0){
            frame_header->frame_no = ntohl(frame_header->frame_no);
            frame_header->frame_type = ntohl(frame_header->frame_type);
            frame_header->F = ntohl(frame_header->F);
            frame_header->K = ntohl(frame_header->K);
            frame_header->R = ntohl(frame_header->R);
            frame_header->esi = ntohl(frame_header->esi);

            memcpy((char *)(frame_data), VRING_HEAD_FARAME_BUF+sizeof(Frame_header), \
                   frame_header->T);
        } else {
            (frame_header->slice_no)++;
            (frame_header->esi)++;
            memcpy((char *)(frame_data), VRING_HEAD_FARAME_BUF+i*T_cur+sizeof(Frame_header)+ \
                   sizeof(int), frame_header->T);

            /*
            if(i == data_len){
                free(VRING_HEAD_FARAME_BUF);
                VRING_HEAD_FARAME_BUF = NULL;
            }
            //*/
        }

        //当收到的分片的帧号与预计收到的不同时，cur_frame_no 是当前应该收到的帧号
        //两种特殊情况：1.收到超前的分片 2.接收到已经过期的分片
        if(frame_header->frame_no != cur_frame_no)
        {
            if(frame_header->frame_no > cur_frame_no)//情况1
            {
                last_frame_no = cur_frame_no;

                if(frame_header->frame_type == 1)//raptor
                {
                    //printf("recount\n");
                    cur_frame_no = frame_header->frame_no;//重新开始计数

                    //保存上一帧的相关数据计数信息
                    raptor_K_recieve = raptor_K_temp;
                    raptor_R_recieve = raptor_R_temp;
                    raptor_N_recieve = raptor_N_temp;

                    //重新计数
                    raptor_K_temp = 0;
                    raptor_R_temp = 0;

                    if(frame_header->esi < frame_header->K)
                        raptor_K_temp = 1;
                    else
                        raptor_R_temp = 1;
                    raptor_N_temp = 1;

                    list_temp = frame_header->esi;
                }
                else//非raptor 直接进入解码上一帧的流程
                {
                    cur_frame_no = frame_header->frame_no;
                }
            }
            else//情况2
            {
                //视频持续播放但是帧编号达到最大值并从0开始 或 视频回放过程中后退进度条
                if(frame_header->frame_no <= 10)
                {
                    last_frame_no = cur_frame_no;

                    if(frame_header->frame_type == 1)//raptor
                    {
                        //printf("recount\n");
                        cur_frame_no = frame_header->frame_no;//重新开始计数

                        //保存上一帧的相关数据计数信息
                        raptor_K_recieve = raptor_K_temp;
                        raptor_R_recieve = raptor_R_temp;
                        raptor_N_recieve = raptor_N_temp;

                        //重新计数
                        raptor_K_temp = 0;
                        raptor_R_temp = 0;

                        if(frame_header->esi < frame_header->K)
                            raptor_K_temp = 1;
                        else
                            raptor_R_temp = 1;
                        raptor_N_temp = 1;

                        list_temp = frame_header->esi;
                    }
                    else//非raptor 直接进入解码上一帧的流程
                    {
                        cur_frame_no = frame_header->frame_no;
                    }
                }
                else//直接丢弃
                {
                    continue;
                }
            }//情况2
        }
        else//接收到预计帧的分片
        {
            if(frame_header->frame_type == 1)//raptor
            {
                if((int)raptor_K_temp == K_old){
                    //send a signal to the sender so as to skip the last slices
                    continue;
                }

                //记录当前帧已经收到的分片数，同时区分是源分片，还是冗余分片
                if(frame_header->esi < frame_header->K){
                    raptor_K_temp++;  //源数据
                }else{
                    raptor_R_temp++;  //冗余分片
                }
                raptor_N_temp++;  //总数

                if(!list_cur){
                    list_cur = (uint16*)malloc(sizeof(uint16) * \
                        (frame_header->K+frame_header->R));
                }
                //分片的esi存入list，用于raptor解码
                list_cur[raptor_N_temp-1] = frame_header->esi;

                if(!input_buf){
                        int buf_size = (frame_header->K+frame_header->R)*T_cur;
                        //ricann todo, to see how many bytes does input_buf have
                        input_buf = new char[buf_size+1];
                        memset(input_buf, 0, buf_size+1);

                        K_old = frame_header->K;
                        R_old = frame_header->R;
                }
                //将数据copy到解码用的输入区
                memcpy(input_buf+(raptor_N_temp-1)*T_cur, frame_data, T_cur);

                free(frame_data);
                frame_data = NULL;

                continue;//继续接收分片
            }
            else//非raptor
            {
                if(!output_buf){
                        int buf_size = frame_header->K*T_cur;
                        output_buf = new char[buf_size+1];
                }
                output_buf_size = frame_header->K*T_cur;
                //将数据copy到等待加入264解码队列的输入区
                memcpy(output_buf+frame_header->esi*T_cur, frame_data, T_cur);

                free(frame_data);
                frame_data = NULL;

                continue;//继续接收分片
            }
        }


        if(frame_header->frame_type == 1)//raptor解码
        {
            int result_dec = 0;

            if(raptor_N_recieve > 0)
            {
                //如果源分片全部接收到，则无需raptor解码，直接存入output_buf
                if(K_old == (int)raptor_K_recieve && K_old)
                {
                    result_dec = 1;
                    output_buf_size = K_old*T_cur;

                    if(output_buf_size){
                        if(output_buf){
                            delete[] output_buf;
                            output_buf = NULL;
                        }
                        output_buf = new char[output_buf_size+1];

                        memcpy(output_buf, input_buf, output_buf_size);
                        output_buf[output_buf_size] = '\0';
                    }

                }
                else//如果需要raptor解码
                {
                    //如果接收到的分片总数超过源分片的总数，则进行raptor解码
                    if((int)raptor_N_recieve > K_old)
                    {
                        RParam_dec para = (RParam_dec)malloc(sizeof(RaptorParam_dec));

                        raptor_init(K_old, raptor_N_recieve, para);

                        for(uint32 i = 0; i < raptor_N_recieve; i++)
                        {
                            para->list[i] = list_cur[i];
                        }
                        uint8* temp = (uint8*)malloc((para->S+para->H+raptor_N_recieve)*T_cur);
                        memset(temp, 0, (para->S+para->H+raptor_N_recieve)*T_cur);
                        memcpy(temp+(para->S+para->H)*T_cur,input_buf, raptor_N_recieve*T_cur);

                        //用于存储结果
                        uint8* output = (uint8*)malloc(K_old*T_cur);

                        result_dec = raptor_decode(para, temp, output, T_cur);//解码

                        if(result_dec){
                            output_buf_size = K_old*T_cur;
                            if(output_buf){
                                delete[] output_buf;
                                output_buf = NULL;
                            }
                            output_buf = new char[K_old*T_cur+1];

                            //解码成功后，将结果存入output_buf
                            memcpy(output_buf, output, K_old*T_cur);
                            output_buf[K_old*T_cur] = '\0';
                        }
                        else{

                            output_buf_size = (K_old+R_old)*T_cur;

                            if(output_buf_size){

                                if(output_buf){
                                    delete[] output_buf;
                                    output_buf = NULL;
                                }
                                output_buf = new char[output_buf_size+1];

                                memset(output_buf, 0, output_buf_size+1);

                                for(uint32 i = 0; i < raptor_N_recieve; i++){
                                    memcpy(output_buf+list_cur[i]*T_cur, input_buf+i*T_cur, T_cur);
                                }

                                input_buf_size = 0;
                            }
                        }
                        raptor_parameterfree(para);
                        free(para);
                        free(output);
                        free(temp);
                        para = NULL;
                        output = NULL;
                        temp = NULL;

                    }
                    else//如果接收到的分片数不足，则将数据按esi存储进相应的位置
                    {
                        printf("can not raptor??????????????????\n");
                        output_buf_size = T_cur*(K_old+R_old);

                        if(output_buf_size){

                            if(output_buf){
                                delete[] output_buf;
                                output_buf = NULL;
                            }
                            output_buf = new char[output_buf_size+1];

                            memset(output_buf, 0, output_buf_size+1);

                            for(uint32 i = 0; i < raptor_N_recieve; i++){
                                memcpy(output_buf+list_cur[i]*T_cur, input_buf+i*T_cur, T_cur);
                            }

                            input_buf_size = 0;
                        }

                    }//else分片数不足

                }//需要raptor解码

                /************************/
                delete[] input_buf;
                input_buf = NULL;
                /************************/

                K_old = 0;

            }

        }//raptor解码


        //ricann todo
        //if(play_or_not[camera_no-1]){

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
            if(1){
                char swfFile[30];
                memset(swfFile, 0, 30);
                if(store_v == NULL){
                    time_t timestamp;
                    time(&timestamp);
                    struct tm*now = localtime(&timestamp);

                    memset(fileName, 0, 30);
                    strftime(fileName,30,"%Y%m%d%H",now);

                    char cameraNumber[2]={0};
                    sprintf(cameraNumber, "%d", camera_no);

                    strcat(fileName, "_");
                    strcat(fileName, cameraNumber);
                    //add for fileName for .swf
                    strcpy(swfFile, fileName);
                    strcat(fileName, ".264");
                    strcat(swfFile, ".swf");

                    store_v = fopen(fileName, "wb+");

                    if(store_v == NULL){
                        cout<<"store_v fopen error\n";
                        return;
                    }
                }else{
                    time_t timestamp;
                    time(&timestamp);
                    struct tm*now = localtime(&timestamp);

                    char timenow[15];
                    memset(timenow, 0, 15);
                    strftime(timenow,15,"%Y%m%d%H",now);

                    if(strncmp(timenow, fileName, 10)){
                        fclose(store_v);
                        store_v = NULL;

                        memset(fileName, 0, 30);
                        strncpy(fileName, timenow, 10);

                        char cameraNumber[2]={0};
                        sprintf(cameraNumber, "%d", camera_no);

                        strcat(fileName, "_");
                        strcat(fileName, cameraNumber);
                        strcat(fileName, ".264");

                        store_v = fopen(fileName, "wb+");

                        if(store_v == NULL){
                            cout<<"store_v fopen error\n";
                            return;
                        }
                    }
                }

                fwrite(output_buf, 1, output_buf_size, store_v);
                fflush(store_v);

                //将视频帧组播到指定UDP地址供ffmpeg转码
                QHostAddress ip(QString("239.255.1.%1").arg(camera_no)) ;
                quint16 port = 8899;
                groupBroadcast->writeDatagram(output_buf, output_buf_size,ip,port);

            }

            output_buf_size = 0;

            /*************************/
            delete[] output_buf;
            output_buf = NULL;
            /*************************/
        }


        //解码上一帧后，处理当前帧的第一个分片相关数据
        if(frame_header->frame_type == 1)
        {
            if(list_cur){
                free(list_cur);
                list_cur = NULL;
            }
            list_cur = (uint16*)malloc(sizeof(uint16)*(frame_header->K+frame_header->R));

            list_cur[0] = list_temp;

            /************************/
            int buf_size = (frame_header->K+frame_header->R)*T_cur;
            input_buf = new char[buf_size+1];
            memset(input_buf, 0, buf_size+1);

            K_old = frame_header->K;
            R_old = frame_header->R;
            /************************/

            memcpy(input_buf, frame_data, T_cur);

            free(frame_data);
            frame_data = NULL;

            input_buf_size = T_cur;
        }
        else
        {
            /************************/
            int buf_size = frame_header->K*T_cur;//cannot frame_header->F!!!
            output_buf = new char[buf_size+1];
            /************************/

            output_buf_size = frame_header->K*T_cur;
            memcpy(output_buf+frame_header->esi*T_cur, frame_data, T_cur);

            free(frame_data);
            frame_data = NULL;
        }
    }//for

    //update vring head number
    VRING_HEAD = (VRING_HEAD+1) % VIDEO_RING_NUM;

    free(frame_header);
    frame_header = NULL;
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

