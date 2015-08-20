#ifndef LUAGW_H
#define LUAGW_H

#include <QWidget>
#include <QProcess>

class LuaGw : public QWidget
{
    Q_OBJECT

public:
    LuaGw(QWidget *parent = 0);
    ~LuaGw();
    void startLua();

private slots:
    void startedLua();
    void errorLua(QProcess::ProcessError);
    void finishedLua(int, QProcess::ExitStatus);

private:
    QProcess *luaProcess;
};

#endif // LUAGW_H
