using namespace std;
#include <QtGui>
#include <QObject>
#include <stdio.h>
#include <stdlib.h>


#include "dataAnalysis.h"


#ifndef LENGTH_ND
#define LENGTH_ND 22
#endif

#ifndef LENGTH_CN
#define LENGTH_CN 22
#endif

mapNameDimen maplist[34] = {{"污水","\0"}, {"温度","1"}, {"色度","\0"},
                   {"湿度","mg/l"}, {"生化需氧量","mg/l"}, {"化学需氧量","mg/l"},
                   {"含水量","mg/l"}, {"总有机碳","mg/l"}, {"烷基汞","mg/l"},
                   {"总镉","mg/l"}, {"总铬","mg/l"}, {"六价铬","mg/l"},
                   {"三价铬","mg/l"}, {"总砷","mg/l"}, {"总氮","mg/l"},
                   {"总镍","mg/l"}, {"总铜","mg/l"}, {"总锌","mg/l"},
                   {"总锰","mg/l"}, {"总铁","mg/l"}, {"总银","mg/l"},
                   {"总铍","mg/l"}, {"总硒","mg/l"}, {"锡","mg/l"},
                   {"硼","mg/l"}, {"钼","mg/l"}, {"钡","mg/l"},
                   {"钴","mg/l"}, {"铊","mg/l"}, {"氨氮","mg/l"},
                   {"有机氮","mg/l"}, {"总氮","mg/l"}, {"石油类","mg/l"},
                   {"总磷","mg/l"}};

mapNameDimen nameDimen[] = {{"电压","v"}, {"光照","lux"}, {"温度","℃"},
                   {"湿度","mg/l"}, {"外部温度","℃"}, {"内部温度","℃"},
                   {"PH","ph"}, {"雨量","mm/min"}, {"风速","级"},
                   {"风向","度"}, {"电源电压","v"}, {"是否降雨","l"},
                   {"温度(30cm)","℃"}, {"湿度(30cm)","mg/l"}, {"温度(15cm)","℃"},
                   {"湿度(15cm)","mg/l"}, {"温度(5cm)","℃"}, {"湿度(5cm)","mg/l"},
                   {"温度(土)","℃"},{"湿度(土)","mg/l"},{"垂直盐分","mg/l"}, {"表面盐分","mg/l"}};

mapCodeName codeName[] = {{"1_voltage","电压"}, {"1_light","光照"}, {"1_a01001","温度"},
                          {"1_a01002","湿度"}, {"2_a01001_e","外部温度"}, {"2_a01001_i","内部温度"},
                          {"2_a06003","PH"}, {"2_a06001","雨量"}, {"2_a01007","风速"}, {"2_a01008","风向"},
                          {"2_voltage","电源电压"}, {"2_a06002","是否降雨"}, {"3_a01001_30","温度(30cm)"}, {"3_a01002_30","湿度(30cm)"},
                          {"3_a01001_15","温度(15cm)"}, {"3_a01002_15","湿度(15cm)"}, {"3_a01001_05","温度(5cm)"}, {"3_a01002_05","湿度(5cm)"},
                          {"4_a01001","温度(土)"}, {"4_a01002","湿度(土)"}, {"4_w01008_v","垂直盐分"}, {"4_w01008_s","表面盐分"}};

std::map<std::string,char*> changeCodeToName;
std::map<std::string,char*> changeNameToDimem;

void initMapList()
{
    changeCodeToName.clear();
    changeNameToDimem.clear();
    for(int i = 0; i < LENGTH_CN; i++)
    {
        changeCodeToName[codeName[i].code] = codeName[i].name;
    }
    for(int j = 0; j < LENGTH_ND; j++)
    {
        changeNameToDimem[nameDimen[j].name] = nameDimen[j].dimen;
    }
}

void mapRtd(rtdrecord*recoarry)
{
    int i;
    char *code;
    char *name;
    //qDebug() << "count:" << recoarry->count << endl;
    for (i = 0; i < recoarry->count; ++i)
    {
        code = recoarry->contamis[i].code;
        if(changeCodeToName[code])
        {
            strcpy((recoarry->contamis[i]).name, changeCodeToName[code]);
            name = recoarry->contamis[i].name;
            strcpy((recoarry->contamis[i]).dimen, changeNameToDimem[name]);
        }
    }
}

void mapHis(hisrecord*recoarry)
{
    int i, code = -1;
    for (i = 0; i < recoarry->count; ++i)
    {
        if(!strcmp((recoarry->hismsgs[i]).code, "B01"))
            code = 0;
        else
            code = atoi((recoarry->hismsgs[i]).code);

        if(code >= 1 && code <= 3)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[code].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[code].dimen);
        }
        else if(10 == code || 11 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[code-6].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[code-6].dimen);
        }
        else if(15 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[6].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[6].dimen);
        }
        else if(code >= 20 && code <= 41)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[code-13].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[code-13].dimen);
        }
        else if(60 == code || 61 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[code-31].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[code-31].dimen);
        }
        else if(65 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[31].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[31].dimen);
        }
        else if(80 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[32].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[32].dimen);
        }
        else if(101 == code)
        {
            strcpy((recoarry->hismsgs[i]).name, maplist[33].name);
            strcpy((recoarry->hismsgs[i]).dimen, maplist[33].dimen);
        }
    }
}

void analyRtd(char*paket, rtdrecord*result)
{
    char *ptr_1 = NULL,
         *ptr_2 = NULL;
    char toInt[15];
    int n = 0;

    ptr_1 = strstr(paket, "DataTime");//从字符串str1中查找是否有字符串str2，如果有，返回str1中str2起始位置的指针，如果没有，返回null。
    ptr_1 = strchr(ptr_1, '=');//char *strchr(const char *s,char c);查找字符串s中首次出现字符c的位置。
    ptr_1++;

    ptr_2 = strchr(ptr_1, ';');
    n = ptr_2 - ptr_1;
    strncpy(result->datatime, ptr_1, n) ;//char * strncpy( char *dest, char *src, size_t num );

    result->datatime[n] = '\0';

    ptr_1 = ptr_2 + 1;
    ptr_1 = strstr(ptr_1, "GatewayNO");
    ptr_1 = strchr(ptr_1, '=');
    ptr_1++;

    ptr_2 = strchr(ptr_1, ';');
    n = ptr_2 - ptr_1;
    strncpy(toInt, ptr_1, n) ;//char * strncpy( char *dest, char *src, size_t num );

    toInt[n] = '\0';
    result->GatewayNO = atoi(toInt);//将toInt字符数组转换成int。

    ptr_1 = ptr_2 + 1;
    ptr_2 = NULL;

    ptr_1 = strstr(ptr_1, "SensorNO");
    ptr_1 = strchr(ptr_1, '=');
    ptr_1++;

    ptr_2 = strchr(ptr_1, ';');
    n = ptr_2 - ptr_1;
    strncpy(toInt, ptr_1, n) ;//char * strncpy( char *dest, char *src, size_t num );

    toInt[n] = '\0';
    result->SensorNO = atoi(toInt);//将toInt字符数组转换成int。

    ptr_1 = ptr_2;
    ptr_2 = NULL;

    int i = 0;
    char value[15];

    result->count = 0;
    while(ptr_1)
    {
        ptr_1++;

        ptr_2 = strstr(ptr_1, "-Rtd");
        /***************/
        //addition
        if(ptr_2 == NULL)
            break;
        /***************/
        n = ptr_2 - ptr_1;
        strncpy(result->contamis[i].code, ptr_1, n);
        result->contamis[i].code[n] = '\0';
        memset(result->contamis[i].name, '\0', 20);//可删
        memset(result->contamis[i].dimen, '\0', 5);//可删
        ptr_1 = strchr(ptr_2, '=');
        ptr_1++;
        ptr_2 = strchr(ptr_1, ',');
        n = ptr_2 - ptr_1;
        memset(value,'\0', 15);
        strncpy(value, ptr_1, n);
        value[n] = '\0';
        result->contamis[i].rtd = atof(value);
        ptr_2 = strchr(ptr_2, '=');
        ++ptr_2;
        result->contamis[i++].flag = *ptr_2;
        result->count++;

        ptr_1 = strchr(ptr_2, ';');
        ptr_2 = NULL;

    }
    /***************/
    //addition
    if(ptr_1)
    {
        ptr_2 = strstr(ptr_1, "latitude");
        if(ptr_2)
        {
            ptr_1 = strchr(ptr_2, '=');
            ptr_1++;
            ptr_2 = strchr(ptr_2, ';');
            n = ptr_2 - ptr_1;

            char lati[10] = {'\0'};
            strncpy(lati, ptr_1, n);
            double latitude = atof(lati);
            qDebug()<<"latitude: "<<latitude;

            ptr_1 = strchr(ptr_2, '=');
            ptr_1++;
            ptr_2 = strchr(ptr_1, '.');
            ptr_2 += 4;
            n = ptr_2 - ptr_1;

            char longi[10] = {'\0'};
            strncpy(longi, ptr_1, n);
            double longitude = atof(longi);
            qDebug()<<"longitude: "<<longitude;
        }
    }
    /******************/
}

void analyHis(char*paket, hisrecord*result)
{
    char*ptr_1 = NULL,
        *ptr_2 = NULL;

    ptr_1 = strstr(paket, "DataTime");
    ptr_1 = strchr(ptr_1, '=');
    ptr_1++;

    ptr_2 = strchr(ptr_1, ';');
    int n = ptr_2 - ptr_1;
    strncpy(result->datatime, ptr_1, n) ;
    result->datatime[n] = '\0';

    int i = 0;
    char value[15];

    ptr_1 = ptr_2;
    ptr_2 = NULL;
    result->count = 0;
    while(ptr_1)
    {
        ptr_1++;
        ptr_2 = strstr(ptr_1, "_Cou");

        /***********/
        //addition
        if(ptr_2 == NULL)
            break;
        /***********/

        n = ptr_2 - ptr_1;
        strncpy(result->hismsgs[i].code, ptr_1, n);
        result->hismsgs[i].code[n] = '\0';

        if(!strcmp(result->hismsgs[i].code, "B01"))//int strcmp(const char *s1,const char * s2);当s1==s2时，返回值= 0
        {
            ptr_1 = strchr(ptr_2, ';');
            ptr_2 = NULL;
            continue;
        }

        memset(result->hismsgs[i].name,'\0', 20);//可删
        memset(result->hismsgs[i].dimen,'\0', 5);//可删

        ptr_1 = strchr(ptr_2, '=');
        ptr_1++;
        ptr_2 = strchr(ptr_1, ',');
        n = ptr_2 - ptr_1;
        memset(value,'\0', 15);
        strncpy(value, ptr_1, n);
        value[n] = '\0';
        result->hismsgs[i].cou = atof(value);

        ptr_1 = strchr(ptr_2, '=');
        ptr_1++;
        ptr_2 = strchr(ptr_1, ',');
        n = ptr_2 - ptr_1;
        memset(value,'\0', 15);
        strncpy(value, ptr_1, n);
        value[n] = '\0';
        result->hismsgs[i].min = atof(value);

        ptr_1 = strchr(ptr_2, '=');
        ptr_1++;
        ptr_2 = strchr(ptr_1, ',');
        n = ptr_2 - ptr_1;
        memset(value,'\0', 15);
        strncpy(value, ptr_1, n);
        value[n] = '\0';
        result->hismsgs[i].avg = atof(value);

        ptr_1 = strchr(ptr_2, '=');
        ptr_1++;
        if(strchr(ptr_1, ';'))
           ptr_2 = strchr(ptr_1, ';');
        else
           ptr_2 = strchr(ptr_1, '&');

        n = ptr_2 - ptr_1;
        memset(value,'\0', 15);
        strncpy(value, ptr_1, n);
        value[n] = '\0';
        result->hismsgs[i++].max = atof(value);

        result->count++;

        ptr_1 = strchr(ptr_2, ';');
        ptr_2 = NULL;
    }
    /******************
    //addition
    if(ptr_1)
    {
        ptr_2 = strstr(ptr_1, "latitude");
        if(ptr_2)
        {
            ptr_1 = strchr(ptr_2, '=');
            ptr_1++;
            ptr_2 = strchr(ptr_2, ';');
            n = ptr_2 - ptr_1;

            char lati[10] = {'\0'};
            strncpy(lati, ptr_1, n);
            //latitude = atof(lati);

            ptr_1 = strchr(ptr_2, '=');
            ptr_1++;
            ptr_2 = strchr(ptr_1, '.');
            ptr_2 += 4;
            n = ptr_2 - ptr_1;

            char longi[10] = {'\0'};
            strncpy(longi, ptr_1, n);
            //longitude = stof(longi);
        }
    }
    //*/
}

void time_convert(char* timestemp, char*time_rtn)
{
  int i, j;
  memset(time_rtn, '\0', 30);
  //qDebug()<<timestemp;

  for(i = 0,j = 0;i < 14;i++)
  {
     if(i == 4 || i == 6)
       time_rtn[j++] = '-';
     else
     {
         if(i==8)
                  time_rtn[j++]=' ';
              else if(i == 10 || i == 12)
                time_rtn[j++] = ':';
     }

     time_rtn[j] = timestemp[i];

     j++;
  }
}

void dataAnalysis(QByteArray str, QString& result, double *v, int &gatewayNo, int &sensorNo, char *time, bool &flag, bool newNode)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    std::ofstream fout("scalarDataLog.txt",ios::app);
    rtdrecord r;//real time data
    hisrecord s;//history data
    int i;

    char*  msg;
    msg=str.data();

    initMapList();

    if(strstr(msg, "-Rtd"))
    {
        flag = true;
        analyRtd(msg, &r);
        //printf("DataTime : %s\n", r.datatime);
        //printf("count : %d\n", r.count);

        time_convert(r.datatime, time);
        //printf("time : %s\n", time);

        mapRtd(&r);

        gatewayNo = r.GatewayNO;
        sensorNo = r.SensorNO;

        result.append("来自网关节点");
        result.append(QString::number(r.GatewayNO));
        result.append("下编号为");
        result.append(QString::number(r.SensorNO));
        result.append("节点的信息：\n");

        QSqlQuery queryType;
        QString sql;
        sql = QString("select count(*) from scalartype where gatewayNo = %1 and sensorNo = %2")
                    .arg(r.GatewayNO).arg(r.SensorNO);
        queryType.exec(sql);

        if(!queryType.isActive())
        {
            if(QSqlDatabase::database().open())
            {
                queryType.exec(sql);
            }
        }//若数据库断开，则重连数据库！

        int count = 0;
        while (queryType.next()) {
            count = queryType.value(0).toInt();
        }
        if(count == 0)
            newNode = true;
        else
            newNode = false;

        for (i = 0; i < r.count; ++i)
        {
            result.append("污染物编码:");
            result.append(r.contamis[i].code);
            result.append("  污染物：");
            result.append(r.contamis[i].name);
            result.append("  单位：");
            result.append(r.contamis[i].dimen);
            result.append("  检测值：");
            result.append(QString::number(r.contamis[i].rtd));
            result.append("\n");
            //*************新来的节点信息不存在将其写入数据库**************//
            if(newNode)
            {
                queryType.prepare("insert into scalartype(gatewayNo,sensorNo,code,name)values(?,?,?,?)");
                queryType.addBindValue(r.GatewayNO);
                queryType.addBindValue(r.SensorNO);
                queryType.addBindValue(r.contamis[i].code);
                queryType.addBindValue(r.contamis[i].name);
                queryType.exec();
            }

            QSqlQuery queryData;
            queryData.prepare("insert into scalardata(code,name,dimen,gatewayNo,sensorNo,time,value)values(?,?,?,?,?,?,?)");
            queryData.addBindValue(r.contamis[i].code);
            queryData.addBindValue(r.contamis[i].name);
            queryData.addBindValue(r.contamis[i].dimen);
            queryData.addBindValue(r.GatewayNO);
            queryData.addBindValue(r.SensorNO);
            queryData.addBindValue(time);
            queryData.addBindValue(r.contamis[i].rtd);
            queryData.exec();

            v[i] = r.contamis[i].rtd;
        }
        //打印标量数据至日志文件scalarDataLog.txt!
        string stime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
        fout << stime << ": " << result.toStdString();
    }

    else if(strstr(msg, "_Avg"))
    {
        analyHis(msg, &s);
        printf("DataTime : %s\n", s.datatime);
        printf("count : %d\n", s.count);

        mapHis(&s);

        for(i = 0; i < s.count; ++i)
        {
            qDebug()<<"code:"<<s.hismsgs[i].code<<"name:"<<s.hismsgs[i].name
                   <<"dimension:"<<s.hismsgs[i].dimen<<"cou:"<<s.hismsgs[i].cou
                  <<"min:"<<s.hismsgs[i].min<<"avg:"<<s.hismsgs[i].avg
                 <<"max:"<<s.hismsgs[i].max;
        }

    }
}
