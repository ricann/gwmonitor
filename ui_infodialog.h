/********************************************************************************
** Form generated from reading UI file 'infodialog.ui'
**
** Created: Fri Jun 12 09:55:55 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QLabel *photoLabel;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *PbEdit;
    QLineEdit *phEdit;
    QLineEdit *cEdit;
    QLineEdit *deviceNoEdit;
    QLabel *label_5;
    QLineEdit *solidsEdit;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *HgEdit;
    QLabel *label_8;
    QLineEdit *timeEdit;
    QLabel *label;
    QLineEdit *positionEdit;
    QCustomPlot *customPlot;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QString::fromUtf8("InfoDialog"));
        InfoDialog->resize(1086, 457);
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
        InfoDialog->setPalette(palette);
        InfoDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(95, 95, 95);\n"
"color: rgb(255, 255, 255);"));
        photoLabel = new QLabel(InfoDialog);
        photoLabel->setObjectName(QString::fromUtf8("photoLabel"));
        photoLabel->setGeometry(QRect(10, 20, 251, 181));
        photoLabel->setFrameShape(QFrame::Box);
        layoutWidget = new QWidget(InfoDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 210, 251, 231));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PbEdit = new QLineEdit(layoutWidget);
        PbEdit->setObjectName(QString::fromUtf8("PbEdit"));
        PbEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(PbEdit, 6, 1, 1, 1);

        phEdit = new QLineEdit(layoutWidget);
        phEdit->setObjectName(QString::fromUtf8("phEdit"));
        phEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(phEdit, 2, 1, 1, 1);

        cEdit = new QLineEdit(layoutWidget);
        cEdit->setObjectName(QString::fromUtf8("cEdit"));
        cEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(cEdit, 4, 1, 1, 1);

        deviceNoEdit = new QLineEdit(layoutWidget);
        deviceNoEdit->setObjectName(QString::fromUtf8("deviceNoEdit"));
        deviceNoEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(deviceNoEdit, 0, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        solidsEdit = new QLineEdit(layoutWidget);
        solidsEdit->setObjectName(QString::fromUtf8("solidsEdit"));
        solidsEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(solidsEdit, 3, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        HgEdit = new QLineEdit(layoutWidget);
        HgEdit->setObjectName(QString::fromUtf8("HgEdit"));
        QPalette palette1;
        QBrush brush2(QColor(255, 170, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        HgEdit->setPalette(palette1);
        HgEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(HgEdit, 5, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        timeEdit = new QLineEdit(layoutWidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(timeEdit, 7, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 7, 0, 1, 1);

        positionEdit = new QLineEdit(layoutWidget);
        positionEdit->setObjectName(QString::fromUtf8("positionEdit"));
        positionEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(positionEdit, 1, 1, 1, 1);

        customPlot = new QCustomPlot(InfoDialog);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(290, 40, 721, 381));

        retranslateUi(InfoDialog);

        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        photoLabel->setText(QString());
        label_5->setText(QApplication::translate("InfoDialog", "\346\200\273\346\260\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("InfoDialog", "\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InfoDialog", "\350\212\202\347\202\271\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("InfoDialog", "\350\212\202\347\202\271\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("InfoDialog", "\346\271\277\345\272\246", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("InfoDialog", "\345\220\253\346\260\264\351\207\217", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("InfoDialog", "\346\200\273\346\234\211\346\234\272\347\242\263", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InfoDialog", "\351\207\207\351\233\206\346\227\266\351\227\264 ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InfoDialog: public Ui_InfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
