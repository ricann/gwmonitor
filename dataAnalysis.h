#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

/**
 * struct to resotre information on contaminant of realtime-data-msg
 */
typedef struct
{
    char code[15];       //code of contaminant
    char name[20];      //name of contaminant
    char dimen[10];      //dimension of contaminant 单位
    float rtd;          //value of contaminant
    char flag;          //flag ot contaminant
}contami;

/**
 * struct to restore information on contaminant of history-data-msg
 */
typedef struct
{
    char code[15];       //code of contaminant
    char name[20];      //name of contaminant
    char dimen[10];      //dimension of contaminant
    float cou;
    float min;
    float avg;
    float max;
}hismsg;

/**
 * struct to restore information on a realtime-data-msg
 */
typedef struct
{
    int count;            //number of contaminants in array contamis
    int GatewayNO;        //Gateway NO of M_Link
    int SensorNO;         //Sensor NO of Zigbee
    char datatime[20];
    contami contamis[34];
}rtdrecord;

/**
 * struct to restore information on a history-data-msg
 */
typedef struct
{
    int count;
    char datatime[20];
    hismsg hismsgs[34];
}hisrecord;

/**
 * struct to restore mapping-msg with code and name of contaminant acting as subscript
 */
typedef struct
{
    char code[15];
    char name[20];
}mapCodeName;

/**
 * struct to restore mapping-msg with name of and dimension contaminant acting as subscript
 */
typedef struct
{
    char name[20];
    char dimen[10];
}mapNameDimen;
/**
 * [map code of realtime-data-msg with name and dimension]
 * @param recoarry [record of realtime-data-msg]
 */
void mapRtd(rtdrecord*recoarry);

/**
 * [analysis realtime-data paket]
 * @param paket  [realtime-data paket]
 * @param result [restore record of packet]
 */
void analyRtd(char*paket, rtdrecord*result);

/**
 * [map code of history-data-msg with name and dimension]
 * @param recoarry [record of history-data-msg]
 */
void mapHis(hisrecord*recoarry);

/**
 * [analysis history-data paket]
 * @param paket  [history-data paket]
 * @param result [restore record of packet]
 */
void initMaplist();
void analyHis(char*paket, hisrecord*result);
void dataAnalysis(QByteArray str, QString& result, double *v, int &gatewayNo, int &sensorNo, char *time, bool &flag, bool newNode);
void time_convert(char* timestemp,char* time_rtn);
#endif // DATAANALYSIS_H


