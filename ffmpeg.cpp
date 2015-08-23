#include "ffmpeg.h"


FFmpeg::FFmpeg(QWidget *parent)
    : QWidget(parent)
{
    ffmpegProcess = new QProcess(this);
    timer = new QTimer(this);
    connect(ffmpegProcess, SIGNAL(started()), this, SLOT(startedFFmpeg()));
    connect(ffmpegProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(errorFFmpeg(QProcess::ProcessError)));
    connect(ffmpegProcess, SIGNAL(finished(int, QProcess::ExitStatus)),this, SLOT(finishedFFmpeg(int, QProcess::ExitStatus)));
    connect(timer,SIGNAL(timeout()),this,SLOT(formatToSwf()));
    setFFmpegWorkingPaths();
    //timer->start(5000);
    timer->start(2*60*60*1000);//两个小时自动转码一次
}

FFmpeg::~FFmpeg()
{
    delete ffmpegProcess;
    delete timer;
}

void FFmpeg::setFFmpegWorkingPaths()
{
    QString ffmpegWorkingDir = ".//ffmpegServer//"; //设置外部程序的工作目录为源代码所在目录
    ffmpegProcess->setWorkingDirectory(ffmpegWorkingDir);

    QString errFilePath = ffmpegWorkingDir + "error.txt";
    //QString outFilePath = ffmpegWorkingDir + "out.txt";
    ffmpegProcess->setStandardErrorFile(errFilePath);  //重定向外部程序的标准出错至error.txt
    //ffmpegProcess->setStandardOutputFile(outFilePath); //重定向外部程序的标准输出至out.txt

    ffmpegExePath = ffmpegWorkingDir + "ffmpeg.exe";
}

void FFmpeg::executeFFmpeg(QStringList order)
{
    qDebug() << "in executeFFmpeg";
    ffmpegProcess->start(ffmpegExePath, order);
    ffmpegProcess->waitForStarted();
    ffmpegProcess->waitForFinished();
    qDebug() << "end executeFFmpeg";
}

void executeRmFile(QString file)
{
    if(file == "") return;
    if(QFile::remove(file))
        qDebug() << "remove "+file+" successful";
}

void FFmpeg::formatToSwf()
{
    QString path = ".//";
    QDir dir(path);
    QStringList filter;
    filter << "*.264";

    QString lastFile = "";
    foreach (QString file, dir.entryList(filter, QDir::Files)) {
        if(lastFile != "" && lastFile != "1.264")
            executeRmFile(".//"+lastFile);

        QString swfFile = file;
        swfFile.replace(QString("264"),QString("swf"));
        qDebug() << swfFile;
        executeRmFile("D://swf//"+swfFile);

        QStringList order;
        order <<"-i"<<"..//"+file<<"-f"<<"swf"<<"D://swf//"+swfFile;
        executeFFmpeg(order);
        lastFile = file;
    }
}

void FFmpeg::startedFFmpeg()
{
    qDebug()<<tr("外部程序ffmpeg.exe启动成功...");
}

void FFmpeg::errorFFmpeg(QProcess::ProcessError error)
{
    QString info;
    switch(error)
    {
    case QProcess::FailedToStart:
        info = tr("警告: 程序ffmpeg.exe启动失败.\n"
                  "Either the invoked program is missing, or you may have insufficient permissions to invoke the program.");
        break;
    case QProcess::Crashed:
        info = tr("警告: 程序ffmpeg.exe启动失败.\n"
                  "The process crashed some time after starting successfully.");
        break;
    default:
        info = tr("警告: 程序ffmpeg.exe启动失败.\n"
                  "An unknown error occurred.");
    }

    QMessageBox::warning(this, tr("ffmpeg.exe"),info);
}

void FFmpeg::finishedFFmpeg(int, QProcess::ExitStatus exitStatus)
{
    QString info;
    switch(exitStatus)
    {
    case QProcess::CrashExit:
        info = tr("警告: 程序ffmpeg.exe突然中断\n"
                  "The process crashed.");
        break;
    default:
        info = tr("警告: 程序ffmpeg.exe突然中断\n"
                  "An unknown error occurred.");
    }

    //QMessageBox::warning(this, tr("ffmpeg.exe"),info);
}
