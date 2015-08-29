#ifndef INFO_H
#define INFO_H

#include "commoninc_qt.h"

class Info : public QObject
{
    Q_OBJECT
public:
    explicit Info(QObject *parent = 0);
    void setPos(int index, double lon, double lat);
    void setEdge(int src, int dst);
    void setOrder();    
    void setNodeIn();
    void setNodeOut();

    void deCount(int index);
    int getMarks(int index);
    int getOrder(int i);
    //void getState();
    void setMapRepaly(QString s);



signals:

public slots:
    int getCount();
    int getAsleepCount();
    double getLat(int i);
    double getLon(int i);
    int getDst(int src);
    int getNo();//获取orders.count();
    int getNextNo(int i);//获取下一跳
    void showInfoDlg(int index);
    void setPosNow(int scale,double lng,double lat);
    int getScaleNow();
    double getLngNow();
    double getLatNow();
    int getNodeIn(int i);
    int getNodeOut(int i);
    void nodeTimeOut();
    void edgeTimeOut();

    int getTotalCount();
//    void setActive();


private:

    enum {MAX_EDGE_NUM = 20};
    double lats[MAX_EDGE_NUM];
    double lons[MAX_EDGE_NUM];
    int edges[MAX_EDGE_NUM];
    int marks[MAX_EDGE_NUM];
    int edgeBeat[MAX_EDGE_NUM];
    int count;
    QList<int> order;
    QList<int> nodeIn;
    QList<int> nodeOut;

    QTimer *timer;
    QTimer *edgeBeatTimer;

    int now_scale;
    double now_lng;
    double now_lat;

};

#endif // INFO_H

