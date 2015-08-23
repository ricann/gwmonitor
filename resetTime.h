#ifndef RESETTIME_H
#define RESETTIME_H

#include <commoninc_qt.h>
#include <commoninc_std.h>

class ResetTimeThread:public QThread{
Q_OBJECT
public:
    ResetTimeThread();


    void run();

public slots:
    void resetTimeAll();
    void resetTimeByCameraNo(int cameraNo);
    void setTimer();

private:
    QTime time;
    QTimer *timer;

};

#endif // RESETTIME_H
