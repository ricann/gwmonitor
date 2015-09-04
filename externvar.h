#ifndef EXTERNVAR_H
#define EXTERNVAR_H

#include <QDebug>
#include <QFile>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QHostAddress>

#include <WinSock2.h>

#define MAX_NODE_NUM        7
#define MAX_CAMERA_NUM      MAX_NODE_NUM
#define MAX_PLAY_NUM        4
#define MAX_STR_LEN         256

#define MAX_FRAME_BUF       1522

#define MAX_BUF             4096

#define VIDEO_RING_NUM    100

typedef struct Frame_header{
    int frame_no;
    long slice_no;
    int frame_type;
    long F;
    int T;
    int K;
    int R;
    int esi;
    int camera_no;
}Frame_header;

typedef struct ShowNode
{
    char h264node[1000000];
    int size;
    int frameNo;
    int cameraNo;
}ShowNode;

typedef struct DisplayPara{
    int my_width;
    int my_height;
    unsigned int my_winid;
}DisplayPara;

//摄像头信息
typedef struct _cam_info_{
    //目前设置节点号等于摄像头编号
    int camid;
    //摄像头是打开的还是关闭的
    int cam_on;
    //是否有视频心跳
    int cam_alive;
    //是否为选中播放的节点
    int cam_play;
    //选中为播放节点之后所占用的播放窗口
    int cam_winid;
    //记录心跳来的时间
    QTime htime;
}cam_info_t;

//标量信息
//ricann todo
typedef struct _scalar_info_{
    //目前还没改到标量部分，先留好接口
    int scalar_todo;
}scalar_info_t;

//节点的详细信息
//必须注意节点号等于摄像头编号，还等于数组下标
typedef struct _node_info_{
    //节点号，目前设置节点号等于数组下标
    int nodeid;
    //节点有没有被使用
    int is_used;
    //节点名称
    char name[MAX_STR_LEN];

    //节点的ip和port
    QHostAddress ip;
    quint16 port;

    cam_info_t cam_info;
    scalar_info_t scalar_info;

}node_info_t;

extern node_info_t node_info[];

extern int play_or_not[MAX_CAMERA_NUM];
extern int camera_history[MAX_PLAY_NUM];

#endif // EXTERNVAR_H
