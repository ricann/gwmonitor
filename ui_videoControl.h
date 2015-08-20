/********************************************************************************
** Form generated from reading UI file 'videoControl.ui'
**
** Created: Fri Jul 3 11:37:27 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOCONTROL_H
#define UI_VIDEOCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <power.h>

QT_BEGIN_NAMESPACE

class Ui_VideoControl
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *windowList;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_11;
    QTimeEdit *startTimeEdit;
    QLabel *label_12;
    QTimeEdit *endTimeEdit;
    QSpacerItem *verticalSpacer_2;
    QPushButton *sendControl;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_24;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_13;
    QComboBox *windowList_MLink;
    QSpacerItem *verticalSpacer_13;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer;
    Power *power1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_2;
    Power *power2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_6;
    Power *power3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_7;
    Power *power4;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_14;
    QPushButton *pushButton_7;
    QSpacerItem *verticalSpacer_15;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_12;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer_16;
    QPushButton *pushButton_8;
    QSpacerItem *verticalSpacer_17;
    QPushButton *pushButton_10;

    void setupUi(QDialog *VideoControl)
    {
        if (VideoControl->objectName().isEmpty())
            VideoControl->setObjectName(QString::fromUtf8("VideoControl"));
        VideoControl->resize(289, 433);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(95, 95, 95, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        VideoControl->setPalette(palette);
        VideoControl->setStyleSheet(QString::fromUtf8("background-color: rgb(95, 95, 95);\n"
"color: rgb(255, 255, 255);"));
        verticalLayout_3 = new QVBoxLayout(VideoControl);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(VideoControl);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(label_2);

        windowList = new QComboBox(tab);
        windowList->setObjectName(QString::fromUtf8("windowList"));
        windowList->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);\n"
"font: 9pt \"\345\256\213\344\275\223\";"));

        verticalLayout_2->addWidget(windowList);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 98, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(label_11);

        startTimeEdit = new QTimeEdit(tab);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));
        startTimeEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout->addWidget(startTimeEdit);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(label_12);

        endTimeEdit = new QTimeEdit(tab);
        endTimeEdit->setObjectName(QString::fromUtf8("endTimeEdit"));
        endTimeEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout->addWidget(endTimeEdit);


        verticalLayout_4->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(18, 97, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        sendControl = new QPushButton(tab);
        sendControl->setObjectName(QString::fromUtf8("sendControl"));
        sendControl->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_4->addWidget(sendControl);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_24 = new QVBoxLayout(tab_2);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout_23->addWidget(label_13);

        windowList_MLink = new QComboBox(tab_2);
        windowList_MLink->setObjectName(QString::fromUtf8("windowList_MLink"));
        windowList_MLink->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);\n"
"font: 9pt \"\345\256\213\344\275\223\";"));

        verticalLayout_23->addWidget(windowList_MLink);


        verticalLayout_24->addLayout(verticalLayout_23);

        verticalSpacer_13 = new QSpacerItem(20, 189, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_24->addItem(verticalSpacer_13);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(30, 10));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_14);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        power1 = new Power(tab_2);
        power1->setObjectName(QString::fromUtf8("power1"));
        power1->setMinimumSize(QSize(71, 25));

        horizontalLayout->addWidget(power1);


        verticalLayout_11->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(30, 10));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(label_15);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        power2 = new Power(tab_2);
        power2->setObjectName(QString::fromUtf8("power2"));
        power2->setMinimumSize(QSize(71, 25));

        horizontalLayout_5->addWidget(power2);


        verticalLayout_11->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_16 = new QLabel(tab_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(30, 10));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(label_16);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        power3 = new Power(tab_2);
        power3->setObjectName(QString::fromUtf8("power3"));
        power3->setMinimumSize(QSize(71, 25));

        horizontalLayout_6->addWidget(power3);


        verticalLayout_11->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_17 = new QLabel(tab_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMinimumSize(QSize(30, 10));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(label_17);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        power4 = new Power(tab_2);
        power4->setObjectName(QString::fromUtf8("power4"));
        power4->setMinimumSize(QSize(71, 25));

        horizontalLayout_7->addWidget(power4);


        verticalLayout_11->addLayout(horizontalLayout_7);


        verticalLayout_24->addLayout(verticalLayout_11);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_7 = new QVBoxLayout(tab_3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("image: url(:/img/a_up.png);"));

        gridLayout_2->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setStyleSheet(QString::fromUtf8("image: url(:/img/a_left.png);"));

        gridLayout_2->addWidget(pushButton_2, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setStyleSheet(QString::fromUtf8("image: url(:/img/a_right.png);"));

        gridLayout_2->addWidget(pushButton_3, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(tab_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setStyleSheet(QString::fromUtf8("image: url(:/img/a_down.png);"));

        gridLayout_2->addWidget(pushButton_4, 2, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout_2);

        verticalSpacer_11 = new QSpacerItem(20, 127, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_11);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pushButton_5 = new QPushButton(tab_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(51, 31));
        pushButton_5->setMaximumSize(QSize(51, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8("image: url(:/img/zoom-in.png);"));

        verticalLayout_9->addWidget(pushButton_5);

        verticalSpacer_14 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_14);

        pushButton_7 = new QPushButton(tab_3);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(51, 31));
        pushButton_7->setMaximumSize(QSize(51, 31));
        pushButton_7->setStyleSheet(QString::fromUtf8("image: url(:/img/cam_add_48.ico);"));

        verticalLayout_9->addWidget(pushButton_7);

        verticalSpacer_15 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_15);

        pushButton_9 = new QPushButton(tab_3);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(51, 31));
        pushButton_9->setMaximumSize(QSize(51, 31));
        pushButton_9->setStyleSheet(QString::fromUtf8("image: url(:/img/cam_open_48.ico);"));

        verticalLayout_9->addWidget(pushButton_9);


        horizontalLayout_2->addLayout(verticalLayout_9);

        horizontalSpacer_3 = new QSpacerItem(13, 86, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(51, 31));
        pushButton_6->setMaximumSize(QSize(51, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("image: url(:/img/zoom-out.png);"));

        verticalLayout_12->addWidget(pushButton_6);

        verticalSpacer_16 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_16);

        pushButton_8 = new QPushButton(tab_3);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(51, 31));
        pushButton_8->setMaximumSize(QSize(51, 31));
        pushButton_8->setStyleSheet(QString::fromUtf8("image: url(:/img/cam_del_48.ico);"));

        verticalLayout_12->addWidget(pushButton_8);

        verticalSpacer_17 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_17);

        pushButton_10 = new QPushButton(tab_3);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(51, 31));
        pushButton_10->setMaximumSize(QSize(51, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("image: url(:/img/cam_close_48.ico);"));

        verticalLayout_12->addWidget(pushButton_10);


        horizontalLayout_2->addLayout(verticalLayout_12);


        verticalLayout_7->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_3->addWidget(tabWidget);


        retranslateUi(VideoControl);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(VideoControl);
    } // setupUi

    void retranslateUi(QDialog *VideoControl)
    {
        VideoControl->setWindowTitle(QApplication::translate("VideoControl", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VideoControl", "\350\212\202\347\202\271\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("VideoControl", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("VideoControl", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        sendControl->setText(QApplication::translate("VideoControl", "\345\217\221\351\200\201\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("VideoControl", "\344\274\240\350\276\223\346\216\247\345\210\266\345\231\250", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("VideoControl", "MLINK\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("VideoControl", "\350\267\257\347\224\261\345\231\250", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("VideoControl", "mesh", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("VideoControl", "\345\215\253\346\230\237", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("VideoControl", "\346\221\204\345\203\217\345\244\264", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("VideoControl", "\345\274\200\345\205\263\346\216\247\345\210\266\345\231\250", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_7->setText(QString());
        pushButton_9->setText(QString());
        pushButton_6->setText(QString());
        pushButton_8->setText(QString());
        pushButton_10->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("VideoControl", "\346\221\204\345\203\217\345\244\264\351\201\245\346\216\247\345\231\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VideoControl: public Ui_VideoControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOCONTROL_H
