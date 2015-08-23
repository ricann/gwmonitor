#include "decode_func.h"
#include "ffmpeg.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

extern FFmpeg *ffmpeg;

Object::Object(const int cameraNo):camera_no(cameraNo){

    char fileName[30];
    memset(fileName, 0, 30);
    sprintf(fileName, "%d", camera_no);
    char record_file_name[30];
    memset(record_file_name, 0, 30);
    strcpy(record_file_name, ".//log//record_");
    strcat(record_file_name, fileName);
    strcat(record_file_name, ".txt");

    record_v = fopen(record_file_name, "at+");
    if(record_v == NULL){
        printf("cannot open record.txt\n");
        exit(1);
    }

    input_buf = NULL;
    output_buf = NULL;
    list_cur = NULL;
    store_v = NULL;

    groupBroadcast = new QUdpSocket();

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

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(deal_timeout()));
}

Object::~Object(){

}

void Object::decode(){
//    cout<<"decode_thread_"<<camera_no<<" is running! ID : "<<QThread::currentThreadId()<<endl;

    char *tmp_buf_total = new char[MAXLINE];
    memset(tmp_buf_total, 0, MAXLINE);

    switch(camera_no){
    case 1:
        fullFrame0.acquire();
        memcpy(tmp_buf_total, frameBuf0[nextGetFrame0], MAXLINE);
        emptyFrame0.release();

        nextGetFrame0++;
        nextGetFrame0 %= MAX_BUF_SIZE;
        break;

    case 2:
        fullFrame1.acquire();
        memcpy(tmp_buf_total, frameBuf1[nextGetFrame1], MAXLINE);
        emptyFrame1.release();

        nextGetFrame1++;
        nextGetFrame1 %= MAX_BUF_SIZE;
        break;

    case 3:
        fullFrame2.acquire();
        memcpy(tmp_buf_total, frameBuf2[nextGetFrame2], MAXLINE);
        emptyFrame2.release();

        nextGetFrame2++;
        nextGetFrame2 %= MAX_BUF_SIZE;
        break;

    case 4:
        fullFrame3.acquire();
        memcpy(tmp_buf_total, frameBuf3[nextGetFrame3], MAXLINE);
        emptyFrame3.release();

        nextGetFrame3++;
        nextGetFrame3 %= MAX_BUF_SIZE;
        break;

    case 5:
        fullFrame4.acquire();
        memcpy(tmp_buf_total, frameBuf4[nextGetFrame4], MAXLINE);
        emptyFrame4.release();

        nextGetFrame4++;
        nextGetFrame4 %= MAX_BUF_SIZE;
        break;

    case 6:
        fullFrame5.acquire();
        memcpy(tmp_buf_total, frameBuf5[nextGetFrame5], MAXLINE);
        emptyFrame5.release();

        nextGetFrame5++;
        nextGetFrame5 %= MAX_BUF_SIZE;
        break;

    case 7:
        fullFrame6.acquire();
        memcpy(tmp_buf_total, frameBuf6[nextGetFrame6], MAXLINE);
        emptyFrame6.release();

        nextGetFrame6++;
        nextGetFrame6 %= MAX_BUF_SIZE;
        break;

    case 8:
        fullFrame7.acquire();
        memcpy(tmp_buf_total, frameBuf7[nextGetFrame7], MAXLINE);
        emptyFrame7.release();

        nextGetFrame7++;
        nextGetFrame7 %= MAX_BUF_SIZE;
        break;

    case 9:
        fullFrame8.acquire();
        memcpy(tmp_buf_total, frameBuf8[nextGetFrame8], MAXLINE);
        emptyFrame8.release();

        nextGetFrame8++;
        nextGetFrame8 %= MAX_BUF_SIZE;
        break;

    case 10:
        fullFrame9.acquire();
        memcpy(tmp_buf_total, frameBuf9[nextGetFrame9], MAXLINE);
        emptyFrame9.release();

        nextGetFrame9++;
        nextGetFrame9 %= MAX_BUF_SIZE;
        break;

    default:
        break;
    }

    frame_header = (Frame_header*)malloc(sizeof(Frame_header));
    memcpy((char *)frame_header, tmp_buf_total, sizeof(Frame_header));


    frame_header->T = ntohl(frame_header->T);
    int T_cur = frame_header->T;

    frame_header->slice_no = ntohl(frame_header->slice_no);

    int data_len;
    memcpy(&data_len, tmp_buf_total+T_cur+sizeof(Frame_header), 4);
    data_len = ntohl(data_len);

    for(int i = 0; i < data_len + 1; i++)
    {

        char *frame_data = new char[T_cur+1];
        memset(frame_data, 0, T_cur+1);

        if(i == 0){
            frame_header->frame_no = ntohl(frame_header->frame_no);
            frame_header->frame_type = ntohl(frame_header->frame_type);
            frame_header->F = ntohl(frame_header->F);
            frame_header->K = ntohl(frame_header->K);
            frame_header->R = ntohl(frame_header->R);
            frame_header->esi = ntohl(frame_header->esi);

//            frame_header->camera_no = ntohl(frame_header->camera_no);

//            cout<<"slice_no="<<frame_header->slice_no
//                <<" frame_no="<<frame_header->frame_no
//                <<" frame_type="<<frame_header->frame_type
//                <<" F="<<frame_header->F
//                <<" T="<<frame_header->T
//                <<" R="<<frame_header->R
//                <<" esi="<<frame_header->esi
//                <<" camera="<<frame_header->camera_no
//                <<endl;

            memcpy((char *)(frame_data), tmp_buf_total+sizeof(Frame_header), frame_header->T);

            if(i == data_len){
                free(tmp_buf_total);
                tmp_buf_total = NULL;
            }
        }
        else{
            (frame_header->slice_no)++;
            (frame_header->esi)++;

//            cout<<"slice_no="<<frame_header->slice_no
//                <<" frame_no="<<frame_header->frame_no
//                <<" frame_type="<<frame_header->frame_type
//                <<" F="<<frame_header->F
//                <<" T="<<frame_header->T
//                <<" R="<<frame_header->R
//                <<" esi="<<frame_header->esi
//                <<" camera="<<frame_header->camera_no
//                <<endl;

            memcpy((char *)(frame_data), tmp_buf_total+i*T_cur+sizeof(Frame_header)+sizeof(int), frame_header->T);

            if(i == data_len){
                free(tmp_buf_total);
                tmp_buf_total = NULL;
            }
        }

        //print the bassic message of current frame
//        if(old_frame_no != frame_header->frame_no){
//            old_frame_no = frame_header->frame_no;

//            if(frame_header->frame_type == 1){
//                printf("frame_no = %d K = %d K` = %d\n", frame_header->frame_no,
//                       frame_header->K,
//                       frame_header->K + frame_header->R);
//            }
//            else{
//                printf("frame_no = %d K = %d\n", frame_header->frame_no,
//                       frame_header->K);
//            }
//        }


        if(frame_header->frame_no != cur_frame_no)//当收到的分片的帧号与预计收到的不同时 cur_frame_no 是当前应该收到的帧号
            //两种特殊情况：1.收到超前的分片 2.接收到已经过期的分片
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
                if((/*INT_MAX - cur_frame_no <= 10 && */frame_header->frame_no <= 10) || replay == 1)
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

                if(frame_header->esi < frame_header->K){//记录当前帧已经收到的分片数，同时区分是源分片，还是冗余分片
                    raptor_K_temp++;  //源数据
                }else{
                    raptor_R_temp++;  //冗余分片
                }
                raptor_N_temp++;  //总数

                if(!list_cur){
                    list_cur = (uint16*)malloc(sizeof(uint16)*(frame_header->K+frame_header->R));
                }
                list_cur[raptor_N_temp-1] = frame_header->esi;//分片的esi存入list，用于raptor解码

                if(!input_buf){
                        int buf_size = (frame_header->K+frame_header->R)*T_cur;
                        input_buf = new char[buf_size+1];
                        memset(input_buf, 0, buf_size+1);

                        K_old = frame_header->K;
                        R_old = frame_header->R;
                }
                memcpy(input_buf+(raptor_N_temp-1)*T_cur, frame_data, T_cur);//将数据copy到解码用的输入区

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
                memcpy(output_buf+frame_header->esi*T_cur, frame_data, T_cur);//将数据copy到等待加入264解码队列的输入区

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
                if(K_old == (int)raptor_K_recieve && K_old)//如果源分片全部接收到，则无需raptor解码，直接存入output_buf
                {
                    result_dec = 1;
                    output_buf_size = K_old*T_cur;

                    if(output_buf_size){
//                        if(!output_buf){
//                            output_buf = new char[output_buf_size+1];
//                        }
//                        else{
//                            cout<<"error 1...!!!\n";
//                            exit(1);
//                        }

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
                    if((int)raptor_N_recieve > K_old)//如果接收到的分片总数超过源分片的总数  则进行raptor解码
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

                        uint8* output = (uint8*)malloc(K_old*T_cur);           //用于存储结果

                        result_dec = raptor_decode(para, temp, output, T_cur);//解码

                        if(result_dec){
                            output_buf_size = K_old*T_cur;
//                            if(!output_buf){
//                                output_buf = new char[K_old*T_cur+1];
//                            }else{
//                                cout<<"error 2...!!!\n";
//                                exit(1);
//                            }
                            if(output_buf){
                                delete[] output_buf;
                                output_buf = NULL;
                            }
                            output_buf = new char[K_old*T_cur+1];

                            memcpy(output_buf, output, K_old*T_cur);//解码成功后，将结果存入output_buf
                            output_buf[K_old*T_cur] = '\0';
                        }
                        else{
//                            printf("raptor error!!!!!!!!!!!!!!!!!!!!!!!!\n");

                            output_buf_size = (K_old+R_old)*T_cur;

                            if(output_buf_size){
//                                if(!output_buf){
//                                    output_buf = new char[output_buf_size+1];
//                                }else{
//                                    cout<<"error 3...!!!\n";
//                                    exit(1);
//                                }
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
//                            if(!output_buf){
//                                output_buf = new char[output_buf_size+1];
//                            }else{
//                                cout<<"error 4...!!!\n";
//                                exit(1);
//                            }
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

        ///////////////////视频存储帧号可能不从1开始，因而导致视与源视频帧不对齐
        if(output_buf_size)
        {
//            cout<<"frame= "<<last_frame_no<<" out_buf_size = "<<output_buf_size<<endl;

            if(play_or_not[camera_no-1]){
                switch(camera_no){
                case 1:
                    if(emptyShow0.tryAcquire(1,0)){
                        showBuf0[nextPutShow0].frameNo = last_frame_no;
                        showBuf0[nextPutShow0].size = output_buf_size;
                        memcpy(showBuf0[nextPutShow0].h264node, output_buf, output_buf_size);
                        showBuf0[nextPutShow0].h264node[output_buf_size] = '\0';
                        fullShow0.release();

                        nextPutShow0++;
                        nextPutShow0 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(1);
//                    cout<<"emit dataReady_obj(1)"<<endl;
                    break;

                case 2:
                    if(emptyShow1.tryAcquire(1,0)){
                        showBuf1[nextPutShow1].frameNo = last_frame_no;
                        showBuf1[nextPutShow1].size = output_buf_size;
                        memcpy(showBuf1[nextPutShow1].h264node, output_buf, output_buf_size);
                        showBuf1[nextPutShow1].h264node[output_buf_size] = '\0';
                        fullShow1.release();

                        nextPutShow1++;
                        nextPutShow1 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(2) ;
//                    cout<<"emit dataReady_obj(2)"<<endl;
                    break;

                case 3:
                    if(emptyShow2.tryAcquire(1,0)){
                        showBuf2[nextPutShow2].frameNo = last_frame_no;
                        showBuf2[nextPutShow2].size = output_buf_size;
                        memcpy(showBuf2[nextPutShow2].h264node, output_buf, output_buf_size);
                        showBuf2[nextPutShow2].h264node[output_buf_size] = '\0';
                        fullShow2.release();

                        nextPutShow2++;
                        nextPutShow2 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(3);
//                    cout<<"emit dataReady_obj(3)"<<endl;
                    break;

                case 4:
                    if(emptyShow3.tryAcquire(1,0)){
                        showBuf3[nextPutShow3].frameNo = last_frame_no;
                        showBuf3[nextPutShow3].size = output_buf_size;
                        memcpy(showBuf3[nextPutShow3].h264node, output_buf, output_buf_size);
                        showBuf3[nextPutShow3].h264node[output_buf_size] = '\0';
                        fullShow3.release();

                        nextPutShow3++;
                        nextPutShow3 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(4);
//                    cout<<"emit dataReady_obj(4)"<<endl;
                    break;

                case 5:
                    if(emptyShow4.tryAcquire(1,0)){
                        showBuf4[nextPutShow4].frameNo = last_frame_no;
                        showBuf4[nextPutShow4].size = output_buf_size;
                        memcpy(showBuf4[nextPutShow4].h264node, output_buf, output_buf_size);
                        showBuf4[nextPutShow4].h264node[output_buf_size] = '\0';
                        fullShow4.release();

                        nextPutShow4++;
                        nextPutShow4 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(5);
//                    cout<<"emit dataReady_obj(5)"<<endl;
                    break;

                case 6:
                    if(emptyShow5.tryAcquire(1,0)){
                        showBuf5[nextPutShow5].frameNo = last_frame_no;
                        showBuf5[nextPutShow5].size = output_buf_size;
                        memcpy(showBuf5[nextPutShow5].h264node, output_buf, output_buf_size);
                        showBuf5[nextPutShow5].h264node[output_buf_size] = '\0';
                        fullShow5.release();

                        nextPutShow5++;
                        nextPutShow5 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(6) ;
//                    cout<<"emit dataReady_obj(6)"<<endl;
                    break;

                case 7:
                    if(emptyShow6.tryAcquire(1,0)){
                        showBuf6[nextPutShow6].frameNo = last_frame_no;
                        showBuf6[nextPutShow6].size = output_buf_size;
                        memcpy(showBuf6[nextPutShow6].h264node, output_buf, output_buf_size);
                        showBuf6[nextPutShow6].h264node[output_buf_size] = '\0';
                        fullShow6.release();

                        nextPutShow6++;
                        nextPutShow6 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(7) ;
//                    cout<<"emit dataReady_obj(7)"<<endl;
                    break;

                case 8:
                    if(emptyShow7.tryAcquire(1,0)){
                        showBuf7[nextPutShow7].frameNo = last_frame_no;
                        showBuf7[nextPutShow7].size = output_buf_size;
                        memcpy(showBuf7[nextPutShow7].h264node, output_buf, output_buf_size);
                        showBuf7[nextPutShow7].h264node[output_buf_size] = '\0';
                        fullShow7.release();

                        nextPutShow7++;
                        nextPutShow7 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(8) ;
//                    cout<<"emit dataReady_obj(8)"<<endl;
                    break;

                case 9:
                    if(emptyShow8.tryAcquire(1,0)){
                        showBuf8[nextPutShow8].frameNo = last_frame_no;
                        showBuf8[nextPutShow8].size = output_buf_size;
                        memcpy(showBuf8[nextPutShow8].h264node, output_buf, output_buf_size);
                        showBuf8[nextPutShow8].h264node[output_buf_size] = '\0';
                        fullShow8.release();

                        nextPutShow8++;
                        nextPutShow8 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(9) ;
//                    cout<<"emit dataReady_obj(9)"<<endl;
                    break;

                case 10:
                    if(emptyShow9.tryAcquire(1,0)){
                        showBuf9[nextPutShow9].frameNo = last_frame_no;
                        showBuf9[nextPutShow9].size = output_buf_size;
                        memcpy(showBuf9[nextPutShow9].h264node, output_buf, output_buf_size);
                        showBuf9[nextPutShow9].h264node[output_buf_size] = '\0';
                        fullShow9.release();

                        nextPutShow9++;
                        nextPutShow9 %= MAX_BUF_SIZE;
                    }

                    emit dataReady_obj(10) ;
//                    cout<<"emit dataReady_obj(10)"<<endl;
                    break;

                default:
                    break;
                }
            }

            if(!replay && video_debug){
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

//                if(!timer->isActive()){
//                    timer->start(10000);
//                }
//                else{
//                    timer->stop();
//                    timer->start(10000);
//                }

                fwrite(output_buf, 1, output_buf_size, store_v);
                fflush(store_v);
                //将视频帧组播到指定UDP地址供ffmpeg转码

                QHostAddress ip(QString("239.255.1.%1").arg(camera_no)) ;
                quint16 port = 8899;
                groupBroadcast->writeDatagram(output_buf, output_buf_size,ip,port);

                /*QStringList order;
                order <<"-i"<<QString("udp://239.255.1.%1:%2").arg(camera_no).arg(port)<<"-f"<<"flv"<<QString(swfFile);
                ffmpeg->executeFFmpeg(order);*/
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

    free(frame_header);
    frame_header = NULL;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++deal with camera's timeout++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//void Object::deal_timeout(){
//    if(video_debug && store_v){
//        fclose(store_v);
//        store_v = NULL;
//    }

//    timer->stop();

//    raptor_K_temp = 0;
//    raptor_R_temp = 0;
//    raptor_N_temp = 0;
//    raptor_K_recieve = 0;
//    raptor_R_recieve = 0;
//    raptor_N_recieve = 0;

//    output_buf_size = 0;
//    input_buf_size = 0;

//    cur_frame_no = 1;
//    last_frame_no = 0;
//    old_frame_no = -1;
//}


DecodeThread::DecodeThread(const int cameraNo):camera_no(cameraNo){
}

DecodeThread::~DecodeThread(){
    quit();
    wait();
    deleteLater();
}


void DecodeThread::run(){
    Object obj(camera_no);
    obj.moveToThread(this);

    connect(this, SIGNAL(dataArrived()), &obj, SLOT(decode()), Qt::BlockingQueuedConnection);
    connect(&obj, SIGNAL(dataReady_obj(const int)), this, SIGNAL(dataReady_deco(const int)));

    exec();//(除ui线程之外的其他)线程用QThread::exec()开始事件循环
}




