#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include <commoninc_qt.h>
#include <commoninc_std.h>

namespace Ui {
    class VideoControl;
}

class VideoControl : public QDialog
{
    Q_OBJECT

public:
    bool pass;

    explicit VideoControl(QWidget *parent = 0);
    ~VideoControl();
    void closeEvent(QCloseEvent *e);
    void sentOrderToCamera(int cameraNo, char order);
    void sentOrderToCameraAcrossList(char order);
    void sentPowerControlOrder(int num, char orders);
    void sentTimeControlOrder(int cameraNo, QTime startTime, QTime endTime);
    bool isPowerChecked(int powerNo);

signals:
    void freshCameraList();
    void freshPowerList(int No, char a, char b, char c, char d);

private slots:
    void freshCameraListAndShow();
    void freshMLinkListAndShow();
    void freshPowerListAndShow(int No, char a, char b, char c, char d);

    void on_windowList_currentIndexChanged(const QString &arg1);
    void on_windowList_MLink_currentIndexChanged(const QString &arg1);
    void on_windowList_No_currentIndexChanged(const QString &arg1);
    void on_sendControl_clicked();
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_pushButton_4_pressed();
    void on_pushButton_4_released();
    void on_pushButton_2_pressed();
    void on_pushButton_2_released();
    void on_pushButton_3_pressed();
    void on_pushButton_3_released();
    void on_pushButton_5_pressed();
    void on_pushButton_5_released();
    void on_pushButton_6_pressed();
    void on_pushButton_6_released();
    void on_pushButton_7_pressed();
    void on_pushButton_7_released();
    void on_pushButton_8_pressed();
    void on_pushButton_8_released();
    void on_pushButton_9_pressed();
    void on_pushButton_9_released();
    void on_pushButton_10_pressed();
    void on_pushButton_10_released();

    void power1Clicked(bool state);
    void power2Clicked(bool state);
    void power3Clicked(bool state);
    void power4Clicked(bool state);


private:
    Ui::VideoControl *ui;

    QString selectedCamera;
    QString selectedMLink;
    QString selectedPowerNo;

};

#endif // VIDEOCONTROL_H
