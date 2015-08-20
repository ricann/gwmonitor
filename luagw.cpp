#include "luagw.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>

LuaGw::LuaGw(QWidget *parent)
    : QWidget(parent)
{
    luaProcess = new QProcess(this);
    connect(luaProcess, SIGNAL(started()), this, SLOT(startedLua()));
    connect(luaProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(errorLua(QProcess::ProcessError)));
    connect(luaProcess, SIGNAL(finished(int, QProcess::ExitStatus)),this, SLOT(finishedLua(int, QProcess::ExitStatus)));
    startLua();
}

LuaGw::~LuaGw()
{
}

void LuaGw::startLua()
{
    luaProcess->execute("taskkill", QStringList()<<"-f"<<"-im"<<"lua.exe"); //强制终止系统所有lua.exe进程,确保QProcess打开的外部程序为唯一打开

#ifdef LUA_DEBUG_DIR
    QString luaWorkingDir = QCoreApplication::applicationDirPath() + "/luadir/"; //设置外部程序的工作目录为debug/Release目录
#else
    QString luaWorkingDir = ".//luadir//"; //设置外部程序的工作目录为源代码所在目录
#endif

    luaProcess->setWorkingDirectory(luaWorkingDir);

    QString errFilePath = luaWorkingDir + "error.txt";
    //QString outFilePath = luaWorkingDir + "out.txt";
    luaProcess->setStandardErrorFile(errFilePath);  //重定向外部程序的标准出错至error.txt
    //luaProcess->setStandardOutputFile(outFilePath); //重定向外部程序的标准输出至out.txt

    QString luaExePath = luaWorkingDir + "lua.exe";
    luaProcess->start(luaExePath, QStringList()<<"main.lua");
}

void LuaGw::startedLua()
{
    qDebug()<<tr("外部程序lua.exe启动成功...");
}

void LuaGw::errorLua(QProcess::ProcessError error)
{
    QString info;
    switch(error)
    {
    case QProcess::FailedToStart:
        info = tr("警告: 程序lua.exe启动失败.\n"
                  "Either the invoked program is missing, or you may have insufficient permissions to invoke the program.");
        break;
    case QProcess::Crashed:
        info = tr("警告: 程序lua.exe启动失败.\n"
                  "The process crashed some time after starting successfully.");
        break;
    default:
        info = tr("警告: 程序lua.exe启动失败.\n"
                  "An unknown error occurred.");
    }

    QMessageBox::warning(this, tr("lua.exe"),info);
}

void LuaGw::finishedLua(int, QProcess::ExitStatus exitStatus)
{
    QString info;
    switch(exitStatus)
    {
    case QProcess::NormalExit:
        info = tr("警告: 程序lua.exe突然中断\n"
                  "The process exited normally, maybe meeted errors when executing");
        break;
    case QProcess::CrashExit:
        info = tr("警告: 程序lua.exe突然中断\n"
                  "The process crashed.");
        break;
    default:
        info = tr("警告: 程序lua.exe突然中断\n"
                  "An unknown error occurred.");
    }

    QMessageBox::warning(this, tr("lua.exe"),info);
}
