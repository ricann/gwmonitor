#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T15:20:53
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = demoSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datadialog.cpp \
    infodialog.cpp \
    info.cpp \
    dataAnalysis.cpp \
    qcustomplot.cpp \
    plotdialog.cpp \
    process.cpp \
    raptorcode.cpp \
    matrix.cpp \
    paintableVedio.cpp \
    luagw.cpp \
    videoControl.cpp \
    resetTime.cpp \
    dragablebutton.cpp \
    dropableplot.cpp \
    power.cpp \
    video_recv.cpp \
    video_decode.cpp \
    video_show.cpp

HEADERS  += mainwindow.h \
    datadialog.h \
    infodialog.h \
    info.h \
    dataAnalysis.h \
    qcustomplot.h \
    plotdialog.h \
    process.h \
    gilbert.h \
    externvar.h \
    raptorcode.h \
    matrix.h \
    paintableVedio.h \
    luagw.h \
    videoControl.h \
    resetTime.h \
    dragablebutton.h \
    dropableplot.h \
    power.h \
    commoninc_qt.h \
    commoninc_std.h \
    video_recv.h \
    video_decode.h \
    video_show.h

FORMS    += mainwindow.ui \
    datadialog.ui \
    infodialog.ui \
    plotdialog.ui \
    process.ui \
    videoControl.ui

RESOURCES += \
    final.qrc

LIBS += -lWs2_32

INCLUDEPATH +=  SDL/include
LIBS += SDL/lib/libSDL.dll.a

INCLUDEPATH +=  ffmpeg/include
LIBS += ffmpeg/lib/libavcodec.dll.a \
        ffmpeg/lib/libavdevice.dll.a \
        ffmpeg/lib/libavfilter.dll.a \
        ffmpeg/lib/libavformat.dll.a \
        ffmpeg/lib/libavutil.dll.a \
        ffmpeg/lib/libpostproc.dll.a \
        ffmpeg/lib/libswscale.dll.a \




