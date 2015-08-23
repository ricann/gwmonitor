#ifndef PROCESS_H
#define PROCESS_H

#include "commoninc_qt.h"

class QProcess;

namespace Ui {
    class Process;
}

class Process : public QDialog
{
    Q_OBJECT
    
public:
    explicit Process(QWidget *parent = 0);
    ~Process();

private slots:
    void runClicked();
    void readOutput();

    void on_onlineButton_clicked();

    void on_offlineButton_clicked();
signals:
    void dlgReturn(int);

private:
    Ui::Process *ui;
    QProcess* cmd;
    QString output;
};

#endif // PROCESS_H

