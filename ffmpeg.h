#ifndef FFMPEG_H
#define FFMPEG_H

#include <QWidget>
#include <QProcess>

class FFmpeg : public QWidget
{
    Q_OBJECT

public:
    FFmpeg(QWidget *parent = 0);
    ~FFmpeg();
    void setFFmpegWorkingPaths();
    void executeFFmpeg(QStringList order);

private slots:
    void startedFFmpeg();
    void errorFFmpeg(QProcess::ProcessError);
    void finishedFFmpeg(int, QProcess::ExitStatus);
    void formatToSwf();

private:
    QProcess *ffmpegProcess;
    QString ffmpegExePath;
    QTimer *timer;
};

#endif // FFMPEG_H
