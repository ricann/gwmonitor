/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jul 14 15:23:39 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTimeEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include "dragablebutton.h"
#include "dropableplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QTabWidget *map_TabWidget;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QWebView *webView;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_9;
    QLabel *label;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QDateEdit *dateEdit;
    QLabel *label_11;
    QTimeEdit *startTimeEdit;
    QLabel *label_12;
    QTimeEdit *endTimeEdit;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *mapReplayBtn;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *mapChgBtn;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_9;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_34;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_30;
    QPushButton *treeBtn;
    QSpacerItem *horizontalSpacer_31;
    QLabel *video;
    QSpacerItem *horizontalSpacer_33;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_9;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_19;
    QTreeWidget *treeWidget_plot;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_14;
    DragableButton *voltageBtn;
    DragableButton *lightBtn;
    DragableButton *temperatureBtn;
    DragableButton *humidityBtn;
    DragableButton *temperature_eBtn;
    DragableButton *temperature_iBtn;
    DragableButton *phBtn;
    DragableButton *prainfallBtn;
    DragableButton *wind_speedBtn;
    DragableButton *wind_directionBtn;
    DragableButton *power_voltageBtn;
    QHBoxLayout *horizontalLayout_17;
    DragableButton *temperature_30Btn;
    DragableButton *humidity_30Btn;
    DragableButton *temperature_15Btn;
    DragableButton *humidity_15Btn;
    DragableButton *temperature_5Btn;
    DragableButton *humidity_5Btn;
    DragableButton *temperatrue_earthBtn;
    DragableButton *humidity_earthBtn;
    DragableButton *vertical_salinityBtn;
    DragableButton *surface_salinityBtn;
    DragableButton *is_rainBtn;
    QHBoxLayout *horizontalLayout_9;
    DropablePlot *customPlot;
    DropablePlot *customPlot_2;
    QHBoxLayout *horizontalLayout_11;
    DropablePlot *customPlot_3;
    DropablePlot *customPlot_4;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_29;
    QLabel *label_19;
    QDateEdit *dateEdit_start;
    QSpacerItem *horizontalSpacer_28;
    QLabel *label_20;
    QDateEdit *dateEdit_end;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_22;
    QLabel *bulb;
    QSpacerItem *horizontalSpacer_23;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_13;
    QSpacerItem *verticalSpacer;
    QLCDNumber *lcdTemp;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_14;
    QSpacerItem *verticalSpacer_17;
    QLCDNumber *lcdHum;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_15;
    QSpacerItem *verticalSpacer_18;
    QLCDNumber *lcdMois;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_16;
    QSpacerItem *verticalSpacer_19;
    QLCDNumber *lcdC;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_17;
    QSpacerItem *verticalSpacer_20;
    QLCDNumber *lcdN;
    QSpacerItem *horizontalSpacer_24;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_18;
    QSpacerItem *verticalSpacer_22;
    QLabel *gatewayNo;
    QSpacerItem *horizontalSpacer_27;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_21;
    QLabel *scalarTime;
    QSpacerItem *horizontalSpacer_26;
    QPushButton *scalarDbBtn;
    QSpacerItem *horizontalSpacer_25;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1191, 807);
        MainWindow->setMinimumSize(QSize(250, 0));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(70, 70, 70, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 20));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        QBrush brush3(QColor(127, 127, 127, 20));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush3);
        QBrush brush4(QColor(170, 170, 170, 20));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush5(QColor(255, 255, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush5);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush6(QColor(255, 255, 255, 137));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 70, 70);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(630, 60));
        label_2->setMaximumSize(QSize(630, 60));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush5);
        QBrush brush8(QColor(251, 251, 251, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        QBrush brush9(QColor(123, 123, 123, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush9);
        QBrush brush10(QColor(165, 165, 165, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush10);
        QBrush brush11(QColor(255, 170, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush11);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush5);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush8);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush12(QColor(247, 247, 247, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        label_2->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(28);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setTextFormat(Qt::AutoText);

        horizontalLayout_5->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_5);

        map_TabWidget = new QTabWidget(centralWidget);
        map_TabWidget->setObjectName(QString::fromUtf8("map_TabWidget"));
        map_TabWidget->setMinimumSize(QSize(400, 0));
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        webView = new QWebView(tab_4);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setMinimumSize(QSize(450, 400));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        horizontalLayout_7->addWidget(webView);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(40, 40));
        label_4->setMaximumSize(QSize(40, 40));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/img/server.png);"));

        horizontalLayout->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_5);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(40, 40));
        label_6->setMaximumSize(QSize(40, 40));
        label_6->setStyleSheet(QString::fromUtf8("image: url(:/img/node_active.png);"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(label_8);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(40, 40));
        label_7->setMaximumSize(QSize(40, 40));
        label_7->setStyleSheet(QString::fromUtf8("image: url(:/img/node_asleep.png);"));

        horizontalLayout_4->addWidget(label_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(label_9);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_4);

        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_6->addWidget(label);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(label_10);

        dateEdit = new QDateEdit(tab_4);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout_5->addWidget(dateEdit);

        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(label_11);

        startTimeEdit = new QTimeEdit(tab_4);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));
        startTimeEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout_5->addWidget(startTimeEdit);

        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(label_12);

        endTimeEdit = new QTimeEdit(tab_4);
        endTimeEdit->setObjectName(QString::fromUtf8("endTimeEdit"));
        endTimeEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout_5->addWidget(endTimeEdit);


        verticalLayout_6->addLayout(verticalLayout_5);

        verticalSpacer_7 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_6->addItem(verticalSpacer_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        mapReplayBtn = new QPushButton(tab_4);
        mapReplayBtn->setObjectName(QString::fromUtf8("mapReplayBtn"));
        mapReplayBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(mapReplayBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalSpacer_8 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_6->addItem(verticalSpacer_8);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_12 = new QSpacerItem(40, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        mapChgBtn = new QPushButton(tab_4);
        mapChgBtn->setObjectName(QString::fromUtf8("mapChgBtn"));
        mapChgBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(mapChgBtn);

        horizontalSpacer_13 = new QSpacerItem(40, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);


        verticalLayout_6->addLayout(horizontalLayout_8);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_9);


        horizontalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_7->setStretch(0, 6);
        horizontalLayout_7->setStretch(1, 1);
        horizontalLayout_7->setStretch(2, 1);

        verticalLayout_7->addLayout(horizontalLayout_7);

        map_TabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_34);

        treeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setMaximumSize(QSize(259, 500));
        treeWidget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"\n"
"alternate-background-color: rgb(85, 170, 0);"));

        horizontalLayout_3->addWidget(treeWidget);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_30 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_30);

        treeBtn = new QPushButton(tab);
        treeBtn->setObjectName(QString::fromUtf8("treeBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeBtn->sizePolicy().hasHeightForWidth());
        treeBtn->setSizePolicy(sizePolicy);
        treeBtn->setMinimumSize(QSize(50, 50));
        treeBtn->setMaximumSize(QSize(50, 50));
        treeBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/playBtn.png);"));

        horizontalLayout_18->addWidget(treeBtn);

        horizontalSpacer_31 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_31);


        horizontalLayout_3->addLayout(horizontalLayout_18);

        video = new QLabel(tab);
        video->setObjectName(QString::fromUtf8("video"));
        video->setEnabled(true);
        video->setMinimumSize(QSize(800, 500));
        video->setMaximumSize(QSize(800, 500));
        video->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_3->addWidget(video);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_33);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_8);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_16->addWidget(pushButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_9);


        verticalLayout_2->addLayout(horizontalLayout_16);

        map_TabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_12 = new QVBoxLayout(tab_2);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        treeWidget_plot = new QTreeWidget(tab_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        treeWidget_plot->setHeaderItem(__qtreewidgetitem1);
        treeWidget_plot->setObjectName(QString::fromUtf8("treeWidget_plot"));
        treeWidget_plot->setMinimumSize(QSize(250, 476));
        treeWidget_plot->setMaximumSize(QSize(250, 476));
        treeWidget_plot->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_19->addWidget(treeWidget_plot);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        voltageBtn = new DragableButton(tab_2);
        voltageBtn->setObjectName(QString::fromUtf8("voltageBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(voltageBtn->sizePolicy().hasHeightForWidth());
        voltageBtn->setSizePolicy(sizePolicy1);
        voltageBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(voltageBtn);

        lightBtn = new DragableButton(tab_2);
        lightBtn->setObjectName(QString::fromUtf8("lightBtn"));
        sizePolicy1.setHeightForWidth(lightBtn->sizePolicy().hasHeightForWidth());
        lightBtn->setSizePolicy(sizePolicy1);
        lightBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(lightBtn);

        temperatureBtn = new DragableButton(tab_2);
        temperatureBtn->setObjectName(QString::fromUtf8("temperatureBtn"));
        sizePolicy1.setHeightForWidth(temperatureBtn->sizePolicy().hasHeightForWidth());
        temperatureBtn->setSizePolicy(sizePolicy1);
        temperatureBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(temperatureBtn);

        humidityBtn = new DragableButton(tab_2);
        humidityBtn->setObjectName(QString::fromUtf8("humidityBtn"));
        sizePolicy1.setHeightForWidth(humidityBtn->sizePolicy().hasHeightForWidth());
        humidityBtn->setSizePolicy(sizePolicy1);
        humidityBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(humidityBtn);

        temperature_eBtn = new DragableButton(tab_2);
        temperature_eBtn->setObjectName(QString::fromUtf8("temperature_eBtn"));
        sizePolicy1.setHeightForWidth(temperature_eBtn->sizePolicy().hasHeightForWidth());
        temperature_eBtn->setSizePolicy(sizePolicy1);
        temperature_eBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(temperature_eBtn);

        temperature_iBtn = new DragableButton(tab_2);
        temperature_iBtn->setObjectName(QString::fromUtf8("temperature_iBtn"));
        sizePolicy1.setHeightForWidth(temperature_iBtn->sizePolicy().hasHeightForWidth());
        temperature_iBtn->setSizePolicy(sizePolicy1);
        temperature_iBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(temperature_iBtn);

        phBtn = new DragableButton(tab_2);
        phBtn->setObjectName(QString::fromUtf8("phBtn"));
        sizePolicy1.setHeightForWidth(phBtn->sizePolicy().hasHeightForWidth());
        phBtn->setSizePolicy(sizePolicy1);
        phBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(phBtn);

        prainfallBtn = new DragableButton(tab_2);
        prainfallBtn->setObjectName(QString::fromUtf8("prainfallBtn"));
        sizePolicy1.setHeightForWidth(prainfallBtn->sizePolicy().hasHeightForWidth());
        prainfallBtn->setSizePolicy(sizePolicy1);
        prainfallBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(prainfallBtn);

        wind_speedBtn = new DragableButton(tab_2);
        wind_speedBtn->setObjectName(QString::fromUtf8("wind_speedBtn"));
        sizePolicy1.setHeightForWidth(wind_speedBtn->sizePolicy().hasHeightForWidth());
        wind_speedBtn->setSizePolicy(sizePolicy1);
        wind_speedBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(wind_speedBtn);

        wind_directionBtn = new DragableButton(tab_2);
        wind_directionBtn->setObjectName(QString::fromUtf8("wind_directionBtn"));
        sizePolicy1.setHeightForWidth(wind_directionBtn->sizePolicy().hasHeightForWidth());
        wind_directionBtn->setSizePolicy(sizePolicy1);
        wind_directionBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(wind_directionBtn);

        power_voltageBtn = new DragableButton(tab_2);
        power_voltageBtn->setObjectName(QString::fromUtf8("power_voltageBtn"));
        sizePolicy1.setHeightForWidth(power_voltageBtn->sizePolicy().hasHeightForWidth());
        power_voltageBtn->setSizePolicy(sizePolicy1);
        power_voltageBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(power_voltageBtn);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        temperature_30Btn = new DragableButton(tab_2);
        temperature_30Btn->setObjectName(QString::fromUtf8("temperature_30Btn"));
        sizePolicy1.setHeightForWidth(temperature_30Btn->sizePolicy().hasHeightForWidth());
        temperature_30Btn->setSizePolicy(sizePolicy1);
        temperature_30Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(temperature_30Btn);

        humidity_30Btn = new DragableButton(tab_2);
        humidity_30Btn->setObjectName(QString::fromUtf8("humidity_30Btn"));
        sizePolicy1.setHeightForWidth(humidity_30Btn->sizePolicy().hasHeightForWidth());
        humidity_30Btn->setSizePolicy(sizePolicy1);
        humidity_30Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(humidity_30Btn);

        temperature_15Btn = new DragableButton(tab_2);
        temperature_15Btn->setObjectName(QString::fromUtf8("temperature_15Btn"));
        sizePolicy1.setHeightForWidth(temperature_15Btn->sizePolicy().hasHeightForWidth());
        temperature_15Btn->setSizePolicy(sizePolicy1);
        temperature_15Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(temperature_15Btn);

        humidity_15Btn = new DragableButton(tab_2);
        humidity_15Btn->setObjectName(QString::fromUtf8("humidity_15Btn"));
        sizePolicy1.setHeightForWidth(humidity_15Btn->sizePolicy().hasHeightForWidth());
        humidity_15Btn->setSizePolicy(sizePolicy1);
        humidity_15Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(humidity_15Btn);

        temperature_5Btn = new DragableButton(tab_2);
        temperature_5Btn->setObjectName(QString::fromUtf8("temperature_5Btn"));
        sizePolicy1.setHeightForWidth(temperature_5Btn->sizePolicy().hasHeightForWidth());
        temperature_5Btn->setSizePolicy(sizePolicy1);
        temperature_5Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(temperature_5Btn);

        humidity_5Btn = new DragableButton(tab_2);
        humidity_5Btn->setObjectName(QString::fromUtf8("humidity_5Btn"));
        sizePolicy1.setHeightForWidth(humidity_5Btn->sizePolicy().hasHeightForWidth());
        humidity_5Btn->setSizePolicy(sizePolicy1);
        humidity_5Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(humidity_5Btn);

        temperatrue_earthBtn = new DragableButton(tab_2);
        temperatrue_earthBtn->setObjectName(QString::fromUtf8("temperatrue_earthBtn"));
        sizePolicy1.setHeightForWidth(temperatrue_earthBtn->sizePolicy().hasHeightForWidth());
        temperatrue_earthBtn->setSizePolicy(sizePolicy1);
        temperatrue_earthBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(temperatrue_earthBtn);

        humidity_earthBtn = new DragableButton(tab_2);
        humidity_earthBtn->setObjectName(QString::fromUtf8("humidity_earthBtn"));
        sizePolicy1.setHeightForWidth(humidity_earthBtn->sizePolicy().hasHeightForWidth());
        humidity_earthBtn->setSizePolicy(sizePolicy1);
        humidity_earthBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(humidity_earthBtn);

        vertical_salinityBtn = new DragableButton(tab_2);
        vertical_salinityBtn->setObjectName(QString::fromUtf8("vertical_salinityBtn"));
        sizePolicy1.setHeightForWidth(vertical_salinityBtn->sizePolicy().hasHeightForWidth());
        vertical_salinityBtn->setSizePolicy(sizePolicy1);
        vertical_salinityBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(vertical_salinityBtn);

        surface_salinityBtn = new DragableButton(tab_2);
        surface_salinityBtn->setObjectName(QString::fromUtf8("surface_salinityBtn"));
        sizePolicy1.setHeightForWidth(surface_salinityBtn->sizePolicy().hasHeightForWidth());
        surface_salinityBtn->setSizePolicy(sizePolicy1);
        surface_salinityBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(surface_salinityBtn);

        is_rainBtn = new DragableButton(tab_2);
        is_rainBtn->setObjectName(QString::fromUtf8("is_rainBtn"));
        sizePolicy1.setHeightForWidth(is_rainBtn->sizePolicy().hasHeightForWidth());
        is_rainBtn->setSizePolicy(sizePolicy1);
        is_rainBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(is_rainBtn);


        verticalLayout->addLayout(horizontalLayout_17);


        verticalLayout_8->addLayout(verticalLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        customPlot = new DropablePlot(tab_2);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setMinimumSize(QSize(400, 200));
        customPlot->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_9->addWidget(customPlot);

        customPlot_2 = new DropablePlot(tab_2);
        customPlot_2->setObjectName(QString::fromUtf8("customPlot_2"));
        customPlot_2->setMinimumSize(QSize(400, 200));
        customPlot_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_9->addWidget(customPlot_2);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        customPlot_3 = new DropablePlot(tab_2);
        customPlot_3->setObjectName(QString::fromUtf8("customPlot_3"));
        customPlot_3->setMinimumSize(QSize(400, 200));
        customPlot_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_11->addWidget(customPlot_3);

        customPlot_4 = new DropablePlot(tab_2);
        customPlot_4->setObjectName(QString::fromUtf8("customPlot_4"));
        customPlot_4->setMinimumSize(QSize(400, 200));
        customPlot_4->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_11->addWidget(customPlot_4);


        verticalLayout_8->addLayout(horizontalLayout_11);


        verticalLayout_11->addLayout(verticalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_29 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_29);

        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_12->addWidget(label_19);

        dateEdit_start = new QDateEdit(tab_2);
        dateEdit_start->setObjectName(QString::fromUtf8("dateEdit_start"));
        dateEdit_start->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout_12->addWidget(dateEdit_start);

        horizontalSpacer_28 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_28);

        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_12->addWidget(label_20);

        dateEdit_end = new QDateEdit(tab_2);
        dateEdit_end->setObjectName(QString::fromUtf8("dateEdit_end"));
        dateEdit_end->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout_12->addWidget(dateEdit_end);

        horizontalSpacer_32 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_32);


        verticalLayout_11->addLayout(horizontalLayout_12);


        horizontalLayout_19->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_19);

        verticalSpacer_5 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_22);

        bulb = new QLabel(tab_2);
        bulb->setObjectName(QString::fromUtf8("bulb"));
        bulb->setMinimumSize(QSize(60, 60));
        bulb->setMaximumSize(QSize(60, 60));
        bulb->setPixmap(QPixmap(QString::fromUtf8(":/img/bulbDown.png")));

        horizontalLayout_15->addWidget(bulb);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_23);


        horizontalLayout_10->addLayout(horizontalLayout_15);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_14->addWidget(label_13);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_14->addItem(verticalSpacer);

        lcdTemp = new QLCDNumber(tab_2);
        lcdTemp->setObjectName(QString::fromUtf8("lcdTemp"));
        lcdTemp->setMinimumSize(QSize(80, 25));

        verticalLayout_14->addWidget(lcdTemp);


        horizontalLayout_10->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_15->addWidget(label_14);

        verticalSpacer_17 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_15->addItem(verticalSpacer_17);

        lcdHum = new QLCDNumber(tab_2);
        lcdHum->setObjectName(QString::fromUtf8("lcdHum"));
        lcdHum->setMinimumSize(QSize(80, 25));

        verticalLayout_15->addWidget(lcdHum);


        horizontalLayout_10->addLayout(verticalLayout_15);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_16->addWidget(label_15);

        verticalSpacer_18 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_16->addItem(verticalSpacer_18);

        lcdMois = new QLCDNumber(tab_2);
        lcdMois->setObjectName(QString::fromUtf8("lcdMois"));
        lcdMois->setMinimumSize(QSize(80, 25));

        verticalLayout_16->addWidget(lcdMois);


        horizontalLayout_10->addLayout(verticalLayout_16);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_16 = new QLabel(tab_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_17->addWidget(label_16);

        verticalSpacer_19 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_17->addItem(verticalSpacer_19);

        lcdC = new QLCDNumber(tab_2);
        lcdC->setObjectName(QString::fromUtf8("lcdC"));
        lcdC->setMinimumSize(QSize(80, 25));

        verticalLayout_17->addWidget(lcdC);


        horizontalLayout_10->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_17 = new QLabel(tab_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_18->addWidget(label_17);

        verticalSpacer_20 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_18->addItem(verticalSpacer_20);

        lcdN = new QLCDNumber(tab_2);
        lcdN->setObjectName(QString::fromUtf8("lcdN"));
        lcdN->setMinimumSize(QSize(80, 25));

        verticalLayout_18->addWidget(lcdN);


        horizontalLayout_10->addLayout(verticalLayout_18);


        horizontalLayout_13->addLayout(horizontalLayout_10);

        horizontalSpacer_24 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_24);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_9->addWidget(label_18);

        verticalSpacer_22 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_9->addItem(verticalSpacer_22);

        gatewayNo = new QLabel(tab_2);
        gatewayNo->setObjectName(QString::fromUtf8("gatewayNo"));
        gatewayNo->setMinimumSize(QSize(31, 31));
        gatewayNo->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_9->addWidget(gatewayNo);


        horizontalLayout_13->addLayout(verticalLayout_9);

        horizontalSpacer_27 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_27);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_10->addWidget(label_3);

        verticalSpacer_21 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_10->addItem(verticalSpacer_21);

        scalarTime = new QLabel(tab_2);
        scalarTime->setObjectName(QString::fromUtf8("scalarTime"));
        scalarTime->setMinimumSize(QSize(121, 31));
        scalarTime->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_10->addWidget(scalarTime);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_26 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_26);

        scalarDbBtn = new QPushButton(tab_2);
        scalarDbBtn->setObjectName(QString::fromUtf8("scalarDbBtn"));
        scalarDbBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 141, 10);"));

        horizontalLayout_13->addWidget(scalarDbBtn);

        horizontalSpacer_25 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_25);


        verticalLayout_12->addLayout(horizontalLayout_13);

        map_TabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(map_TabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1191, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        map_TabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\347\216\257\345\242\203\347\233\221\346\265\213\346\225\260\346\215\256\345\261\225\347\244\272\344\270\216\345\210\206\346\236\220\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\264\273\350\267\203\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        label_7->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\350\266\205\346\227\266\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        mapReplayBtn->setText(QApplication::translate("MainWindow", "\346\213\223\346\211\221\345\233\236\346\224\276", 0, QApplication::UnicodeUTF8));
        mapChgBtn->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\345\210\207\346\215\242", 0, QApplication::UnicodeUTF8));
        map_TabWidget->setTabText(map_TabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        treeBtn->setText(QString());
        video->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\345\217\260", 0, QApplication::UnicodeUTF8));
        map_TabWidget->setTabText(map_TabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        voltageBtn->setText(QApplication::translate("MainWindow", "\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        lightBtn->setText(QApplication::translate("MainWindow", "\345\205\211\347\205\247", 0, QApplication::UnicodeUTF8));
        temperatureBtn->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        humidityBtn->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246", 0, QApplication::UnicodeUTF8));
        temperature_eBtn->setText(QApplication::translate("MainWindow", "\345\244\226\351\203\250\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        temperature_iBtn->setText(QApplication::translate("MainWindow", "\345\206\205\351\203\250\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        phBtn->setText(QApplication::translate("MainWindow", "PH", 0, QApplication::UnicodeUTF8));
        prainfallBtn->setText(QApplication::translate("MainWindow", "\351\233\250\351\207\217", 0, QApplication::UnicodeUTF8));
        wind_speedBtn->setText(QApplication::translate("MainWindow", "\351\243\216\351\200\237", 0, QApplication::UnicodeUTF8));
        wind_directionBtn->setText(QApplication::translate("MainWindow", "\351\243\216\345\220\221", 0, QApplication::UnicodeUTF8));
        power_voltageBtn->setText(QApplication::translate("MainWindow", "\347\224\265\346\272\220\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        temperature_30Btn->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246(30cm)", 0, QApplication::UnicodeUTF8));
        humidity_30Btn->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246(30cm)", 0, QApplication::UnicodeUTF8));
        temperature_15Btn->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246(15cm)", 0, QApplication::UnicodeUTF8));
        humidity_15Btn->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246(15cm)", 0, QApplication::UnicodeUTF8));
        temperature_5Btn->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246(5cm)", 0, QApplication::UnicodeUTF8));
        humidity_5Btn->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246(5cm)", 0, QApplication::UnicodeUTF8));
        temperatrue_earthBtn->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246(\345\234\237)", 0, QApplication::UnicodeUTF8));
        humidity_earthBtn->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246(\345\234\237)", 0, QApplication::UnicodeUTF8));
        vertical_salinityBtn->setText(QApplication::translate("MainWindow", "\345\236\202\347\233\264\347\233\220\345\210\206", 0, QApplication::UnicodeUTF8));
        surface_salinityBtn->setText(QApplication::translate("MainWindow", "\350\241\250\351\235\242\347\233\220\345\210\206", 0, QApplication::UnicodeUTF8));
        is_rainBtn->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\351\231\215\351\233\250", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "\347\273\210\346\255\242\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        bulb->setText(QString());
        label_13->setText(QApplication::translate("MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Humidity", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Moisture", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "OrganicC", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "OrganicN", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "\347\275\221\345\205\263\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        gatewayNo->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\346\234\200\345\220\216\346\216\245\346\224\266\345\210\260\346\240\207\351\207\217\347\232\204\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        scalarTime->setText(QString());
        scalarDbBtn->setText(QApplication::translate("MainWindow", "\346\240\207\351\207\217\346\225\260\346\215\256\345\272\223", 0, QApplication::UnicodeUTF8));
        map_TabWidget->setTabText(map_TabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\347\233\221\346\265\213\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
