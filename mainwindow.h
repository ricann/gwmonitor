#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <commoninc_qt.h>
#include <commoninc_std.h>

#include "info.h"
#include "datadialog.h"
#include "dataAnalysis.h"
#include "qcustomplot.h"
#include "videoControl.h"
#include "externvar.h"
#include "video_recv.h"
#include "video_decode.h"
#include "video_show.h"
#include "luagw.h"
#include "videoControl.h"
#include "resetTime.h"
#include "process.h"

#include <Winsock2.h>
#include <iostream>

using namespace std;


class Info;
class QUdpSocket;
class QTimer;
class QWebView;

//-------Agent模块节点状态信息------
typedef struct {
    int16_t index;
    int32_t method;
    uint16_t len;
} route_state_t;

//---------B/S控制命令格式----------
typedef struct {
    char type[2];
    char num[2];
    char arg[12];
} command_format_t;

//-------采集节点经纬度信息----------
typedef struct{
    int node;
    double latitude;
    double longitude;
    QTimer *timer;
} position_t;

typedef struct
{
    int gatewayNo;
    int sensorNo;
}NodeNo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    static void getDataFromDB(QVector<double> &data, QString code);
    static void getTimeFromDB(QVector<double> &time, QString code);
    void setupPlot();
    void setupDemo(QCustomPlot *customPlot);
    int showFlag;
    ~MainWindow();
    //---------------------------
    void paintTest();
    void setNodePos();
    void timeForecast(QString code2,int node2);

    QVector<int> nodeActive;
    QVector<int> nodeAsleep;
    QVector<int> order;

    ////////////////////////////////
    QList<QString> routes;
    QTimer *rplTimer;
    int routeCount;

    void setShowCamera(int*);//选择显示摄像头时调用

    //ricann 20150830
    void init_nodeinfo();

signals:
    void newsCome(int,int);
    void pointsReady(int);
    void freshCameraList();
    void freshPowerList(int,char,char,char,char);

    /*
    *线程间用“信号与槽”传递引用参数的话，一定要加const，
    *因为const文字常量存在常量区中，生命周期与程序一样的长。
    *这样可以避免slot调用的时候参数的运行期已过而使引用无效。
    //*/
    void resetWinCame0(const int,const int);//窗口显示的摄像头变动时发出
    void resetWinCame1(const int,const int);
    void resetWinCame2(const int,const int);
    void resetWinCame3(const int,const int);

    void resetWinHandle0(const DisplayPara);//放大或缩小窗口时发出
    void resetWinHandle1(const DisplayPara);
    void resetWinHandle2(const DisplayPara);
    void resetWinHandle3(const DisplayPara);
    /********************************/
    
private slots:

    //ricann todo
    void slot_vtree_set();
    void slot_vtree_click(QTreeWidgetItem * item, int column);
    void slot_vtree_play();

    void addJavaScriptObject();
    void test();
    void processPendingDatagram();
    void stateDatagram();
    void commandDatagram();
    void posDatagram();

    void bulbSlot();
    void refreshMapSlot();
    void refreshPlot(int gatewayNo, int sensorNo);
    void setShowFlag(int value);
    void treeItemClickSlot(QTreeWidgetItem* item,int column);

    void sendPoints(int);
    void processcHeartDatagram();
    void processPowerDatagram();
    void setCameraState();
    void setGPSState();

/**********************************/
    void all_stop();
/**********************************/

    void on_mapChgBtn_clicked();

    void on_scalarDbBtn_clicked();

    void on_mapReplayBtn_clicked();

    void replaySlot();

    void tabIndexChanged();
    void on_voltageBtn_clicked();

    void on_lightBtn_clicked();

    void on_temperatureBtn_clicked();

    void on_humidityBtn_clicked();

    void on_temperature_eBtn_clicked();

    void on_temperature_iBtn_clicked();

    void on_phBtn_clicked();

    void on_prainfallBtn_clicked();

    void on_wind_speedBtn_clicked();

    void on_wind_directionBtn_clicked();

    void on_power_voltageBtn_clicked();

    void on_temperature_30Btn_clicked();

    void on_humidity_30Btn_clicked();

    void on_temperature_15Btn_clicked();

    void on_humidity_15Btn_clicked();

    void on_temperature_5Btn_clicked();

    void on_humidity_5Btn_clicked();

    void on_temperatrue_earthBtn_clicked();

    void on_humidity_earthBtn_clicked();

    void on_vertical_salinityBtn_clicked();

    void on_surface_salinityBtn_clicked();

    void on_pushButton_clicked();

private:

    void initMap();
    void refreshMap();
    void refreshOfflineMap();
    void mapRouteReplay();

    void addToGraph(int index, double lon, double lat);

    void setVideoTree();
    void setScalarTree();

    Ui::MainWindow *ui;
    Info *info;
    Process *w;

    LuaGw *luaGw;
    ResetTimeThread * resetTime;

    QUdpSocket *receiver;
    QUdpSocket *stateReceiver;
    QUdpSocket *posReceiver;
    QUdpSocket *commandReceiver;
    QTimer *timer;
    //******记录标量界面选择的网关号,节点号，标量类型和当前活跃的折线图编号*******//
    static int gatewayNo;
    static int sensorNo;
    int cpIndex;
    QString code;
    //*****************************************************************//
    static QDateEdit *start;
    static QDateEdit *end;
    QTimer *replayer;

    VideoControl *vc;

    //------------------------------
    enum {
        NODE_NUM = 7
    };
    QPoint nodePosOffset[NODE_NUM];
    QPoint nodePos[NODE_NUM];

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // MAINWINDOW_H


