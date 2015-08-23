
#include "info.h"
#include "infodialog.h"


Info::Info(QObject *parent) :
    QObject(parent)
{
    count=0;

    now_scale=8;
    now_lng=109.4963;
    now_lat=36.5911;

    for(int i=0;i<MAX_EDGE_NUM;i++)
        marks[i]=0;

    for(int i=0;i<MAX_EDGE_NUM;i++)
        edges[i]=-1;
    for(int i=0;i<MAX_EDGE_NUM;i++)
        edgeBeat[i]=0;

    setNodeOut();
/*
    order.append(2);
    order.append(1);
    order.append(3);
    order.append(0);
    order.append(4);
    order.append(5);
    order.append(0);
*/
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nodeTimeOut()));
    timer->start(20000);//节点心跳计数器，每5秒减一

    edgeBeatTimer=new QTimer(this);
    connect(edgeBeatTimer,SIGNAL(timeout()),this,SLOT(edgeTimeOut()));
    edgeBeatTimer->start(20000);//有向边心跳计数器，每5秒减一
/*
    timer_active=new QTimer(this);
    connect(timer_active,SIGNAL(timeout()),this,SLOT(setActive()));
    timer_active->start(25000);*/
}

int Info::getCount()
{
    return nodeIn.length();
}

int Info::getAsleepCount()
{
    return nodeOut.length();
}

double Info::getLat(int i)
{
    return lats[i];
}

double Info::getLon(int i)
{
    return lons[i];
}

int Info::getDst(int src)
{
    return edges[src];
}

int Info::getNo()
{
//    qDebug()<<"order.count()="<<order.count();
    return order.count();
}

int Info::getNextNo(int i)
{
    assert(i>=0&&i<order.length());
    return order.at(i);
}

void Info::showInfoDlg(int index)
{
//    qDebug() << "index = " << index;
    if(index!=0)
    {
    InfoDialog infoDlg(index,lons[index],lats[index]);
    infoDlg.exec();
    }

}

void Info::setPosNow(int scale, double lng, double lat)
{
//    qDebug()<<"Info::setPosNow   scale:"<<scale<<"  lng:"<<lng<<"  lat:"<<lat;
    now_scale=scale;
    now_lng=lng;
    now_lat=lat;
}

int Info::getScaleNow()
{
    return now_scale;
}

double Info::getLngNow()
{
    return now_lng;
}

double Info::getLatNow()
{
    return now_lat;
}

int Info::getNodeIn(int i)//获取心跳节点
{
//    if(i<0||i>=nodeIn.length())
//        qDebug()<<"##############   out of range i="<<i<<"nodeIn.len="<<nodeIn.length();
    assert(i>=0&&i<nodeIn.length());
    return nodeIn.at(i);
}

int Info::getNodeOut(int i)
{
//    if(i<0||i>=nodeOut.length())
//        qDebug()<<"##############   out of range i="<<i<<"nodeOut.len="<<nodeOut.length();
    assert(i>=0&&i<nodeOut.length());
    return nodeOut.at(i);
}

void Info::nodeTimeOut()//节点心跳计数器递减
{
    for(int i=0;i<MAX_EDGE_NUM;i++)
    {
        if(marks[i]>0)
        {          
           marks[i]--;
           if(marks[i]==0)
           {
               nodeOut.append(i);
               deCount(i);
           }
//           qDebug()<<"marks["<<i<<"]="<<marks[i];
        }
    }
    marks[0]=5;
    //qDebug()<<"count="<<getCount()<<"  totalCount="<<getTotalCount();
}

void Info::edgeTimeOut()//拓扑边心跳计数器递减
{
    for(int i=0;i<MAX_EDGE_NUM;i++)
    {
        if(edgeBeat[i]>0)
        {
            edgeBeat[i]--;
//            qDebug()<<"edgeBeat["<<i<<"]="<<edgeBeat[i];
        }
    }
}

int Info::getTotalCount()
{
    return MAX_EDGE_NUM;
}
/*
void Info::setActive()
{
    setPos(5, 116.35615, 39.95624);
}
*/

void Info::setPos(int index, double lon, double lat) {
    if(index>=MAX_EDGE_NUM) return;    
    lons[index] = lon;
    lats[index] = lat;
//    qDebug()<<"index:"<<index<<" lon:"<<lon;
//    qDebug()<<"index:"<<index<<" lat:"<<lat;
    count++;
    marks[index]=5;
    //qDebug()<<"setPos:  count="<<getCount();
}

void Info::setEdge(int src, int dst)
{
    if(dst==-1)
    {
        edges[src] = 0;//默认0号节点为服务器
    }
    else
        edges[src] = dst;
    edgeBeat[src]=5;

}

void Info::setOrder()
{
    order.clear();
    int i,j,k,n=0;
    QList<int> endNode;
    endNode.clear();
    for(i=0;i<MAX_EDGE_NUM;i++)
    {
        if(edges[i]==0&&edgeBeat[i]>0&&marks[i]>0)   endNode.append(i);//寻找全部的最终节点
    }
    /*********绘制多条拓扑************/
    for(int m=0;m<endNode.length();m++)
    {
        i=endNode.at(m);
        if(i!=0) order.prepend(0);//将服务器加在最后
        order.prepend(i);//i为到服务器前的最后一个节点，倒序查找

        n=0;
        while(n<MAX_EDGE_NUM)
        {
            n++;
            k=0;
            for(j=0;j<MAX_EDGE_NUM;j++)
                if(edges[j]==i&&marks[j]>0&&edgeBeat[j]>0)
                {order.prepend(j);marks[j]=+2;i=j;k=1;break;}
            if(k==0) break;
        }
    }
    /*
    order.append(i);//i为到服务器前的最后一个节点，倒序查找
    if(i!=0) order.append(0);//将服务器加在最后

    while(n<MAX_EDGE_NUM)
    {
        n++;
        k=0;
        for(j=0;j<MAX_EDGE_NUM;j++)
            if(edges[j]==i)
            {order.prepend(j);i=j;k=1;break;}
        if(k==0) break;
    }*/
    for(i=0;i<order.length();i++)
//    qDebug()<<"^^^^^^^^^"<<order.at(i);
//    qDebug()<<"order.length="<<order.count();

    ///////*******拓扑存入数据库********///////
    if(order.count()>0)
    {
        QString route(order.at(0)+'0');
        for(i=1;i<order.length();i++)
            route.append(order.at(i)+'0');
//        qDebug()<<"route="<<route;

        QByteArray ba = route.toLatin1();
        char *mm = ba.data();
//        qDebug()<<tr("存入数据库  ")<<"###  route="<<mm;
        QSqlQuery query;
        query.prepare("insert into topology(time,path)values(now(),?)");
        query.addBindValue(mm);
        query.exec();
    }
}


void Info::setNodeIn()//目前仍有心跳节点列表
{
    nodeIn.clear();
    for(int i=0;i<MAX_EDGE_NUM;i++)
    {
        if(marks[i]>0) nodeIn.append(i);
    }
//    qDebug()<<"setNodeIn: count="<<getCount();
//    for(int i=0;i<nodeIn.length();i++)
//      qDebug()<<"nodeIn.at "<<i<<"="<<nodeIn.at(i);
    setNodeOut();
}

void Info::setNodeOut()
{
    nodeOut.clear();
    /*for(int i=0;i<MAX_EDGE_NUM;i++)
    {
        if(marks[i]==0) nodeOut.append(i);
    }*/
    //qDebug()<<"setNodeOut: count="<<getCount();
    //for(int i=0;i<nodeOut.length();i++)
    //qDebug()<<"nodeOut.at "<<i<<"="<<nodeOut.at(i);
}


void Info::deCount(int index)
{
    Q_UNUSED(index);

    count--;
    //qDebug()<<"index="<<index<<"  after count:"<<count;
}

int Info::getMarks(int index)
{
    return marks[index];
}

int Info::getOrder(int i)
{
//    if(i<0||i>=order.length())
//        qDebug()<<"##############   out of range i="<<i<<"order.len="<<order.length();
    assert(i>=0&&i<order.length());
    return order.at(i);
}

void Info::setMapRepaly(QString s)
{
    order.clear();
    int len=s.length();
//    qDebug()<<"len="<<len;
    for(int i=0;i<len;i++)
    {
        int j=s.at(i).toAscii()-'0';
        //qDebug()<<"Info::setMapRepaly   j="<<j;
        order.append(j);
    }
}
