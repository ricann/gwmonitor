
//#include <iostream>
//#include <fstream>

//#include <pthread.h>
//#include <sys/socket.h>
/*#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>*/


//extern "C"
//{
    //#include <unistd.h>
#include <map>
#include <time.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gilbert.h"

long cnt_lost = 0;
//}


extern float global_PB;

void calcute(struct EBR_data * data, float P_b, int L_b)
{
    //struct EBR_data data;
    data->P_bg = (float)1/L_b;//1/150
    data->P_gb = (data->P_bg)*(P_b/(1-P_b));//150*（0.009/0.991)
    //printf("transfer_thread : after calculate\np_bg = %f\np_gb = %f\nL_b = %d\nP_b = %f\n", data->P_bg, data->P_gb, L_b, P_b);
}

int gilbert(void * EBR_data_addr, int frame_len, FILE * fd, int state, long Fnum)
{
    struct EBR_data * data;
    data = (struct EBR_data *)EBR_data_addr;
    float P_B;
    float P_BG, P_GB;
    float tmp;
    int P_GB_int, P_BG_int;
    //int L_B;
    int i;
    int ran;

    for(i = 0, tmp = 1; i < frame_len; ++i)
        tmp = tmp*(1 - data->P_gb);//（1-0.009=0.991）
    //printf("####### %f %f\n", data->P_gb, data->P_bg);
    //printf("####### %f %d\n", P_b, L_b);
    P_B = 1 - (1 - P_b)*tmp;
//	printf("\n   ^^^^^^^^^^^ P_B:%f ^^^^^^^^^^",P_B);
    global_PB = P_B;
    if(Fnum == 1) printf(">>>>>> P_B = %lf\n", P_B);
    P_GB = 1 - (1 - data->P_gb)*tmp;
    P_BG = P_GB*(1 - P_B)/P_B;
    //L_B = 1/P_BG;

    P_GB_int = (int)(P_GB*10000);
    P_BG_int = (int)(P_BG*10000);
    //printf("transfer_thread : after calculate\nP_B = %f\nP_GB = %f\nP_BG = %f\nP_GB_int = %d\nP_BG_int = %d\n", P_B, P_GB, P_BG, P_GB_int, P_BG_int);
    //printf("sizeof(int): %d\n", sizeof(int));

    ran = (int)(10000*rand()/(RAND_MAX+1.0));
    switch(state)
    {
        fprintf(fd, "%ld ", (long int)state);
        fflush(fd);
        case 0:
            //if(((float)1/rand()) <= P_GB)
            //if(rand%10000 <= P_GB_int)
            if(ran <= P_GB_int)
            {
                //printf("******package lost !******\n");
                cnt_lost++;
                /*printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");*/
                //printf("%ld\n", Fnum);
                if(fprintf(fd, "%ld ", Fnum) < 0)
                {
                    fprintf(fd, "error");
                    fflush(fd);
                    //printf("transfer_thread : error in write 'gil_slm.txt'\n");
                    exit(1);
                }
                fflush(fd);
                state = 1;
                break;
            }
            else
            {
                //printf("transfer_thread : write frame : No.%ld\n", Fnum);
                //printf("transfer_thread : write %d byte\n", write(sock_s_fd, framebuf, frame_len));
                //frame_cnt++;
                state = 0;
                break;
            }
        case 1:
            //if(((float)1/rand()) <= P_BG)
            //if(rand()%10000 <= P_BG_int)
            if(ran <= P_BG_int)
            {
                //printf("transfer_thread : write frame : No.%ld\n", Fnum);
                //printf("transfer_thread : write %d byte\n", write(sock_s_fd, framebuf, frame_len));
                //frame_cnt++;
                state = 0;
                break;
            }
            else
            {
                //printf("******package lost !******\n");
                cnt_lost++;
                /*printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");
                printf("*********************************************************************************************************************\n");*/
                //printf("%ld\n", Fnum);
                if(fprintf(fd, "%ld ", Fnum) < 0)
                {
                    //printf("transfer_thread : error in write 'lose.txt'\n");
                    exit(1);
                }
                fflush(fd);
                state = 1;
                break;
            }
        default:
            break;
    }//switch
    //printf(">>>>>> cnt_lost: %ld, Fnum: %ld, rate: %lf%%\n", cnt_lost, Fnum, 100*double(cnt_lost)/Fnum);
    return state;
}

