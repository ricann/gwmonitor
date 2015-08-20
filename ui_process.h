/********************************************************************************
** Form generated from reading UI file 'process.ui'
**
** Created: Fri Jun 12 09:55:55 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS_H
#define UI_PROCESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Process
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputEdit;
    QPushButton *runButton;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QTextEdit *outputEdit;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *onlineButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *offlineButton;

    void setupUi(QDialog *Process)
    {
        if (Process->objectName().isEmpty())
            Process->setObjectName(QString::fromUtf8("Process"));
        Process->resize(452, 374);
        verticalLayout = new QVBoxLayout(Process);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Process);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0,255,0);"));

        verticalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inputEdit = new QLineEdit(Process);
        inputEdit->setObjectName(QString::fromUtf8("inputEdit"));
        inputEdit->setStyleSheet(QString::fromUtf8("background-color:  rgb(216, 216, 216);\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(inputEdit);

        runButton = new QPushButton(Process);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout->addWidget(runButton);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(Process);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        verticalLayout->addWidget(label_2);

        verticalSpacer = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        outputEdit = new QTextEdit(Process);
        outputEdit->setObjectName(QString::fromUtf8("outputEdit"));
        outputEdit->setStyleSheet(QString::fromUtf8("background-color:  rgb(216, 216, 216);\n"
"color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(outputEdit);

        verticalSpacer_3 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        onlineButton = new QPushButton(Process);
        onlineButton->setObjectName(QString::fromUtf8("onlineButton"));
        onlineButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout_2->addWidget(onlineButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        offlineButton = new QPushButton(Process);
        offlineButton->setObjectName(QString::fromUtf8("offlineButton"));
        offlineButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout_2->addWidget(offlineButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Process);

        QMetaObject::connectSlotsByName(Process);
    } // setupUi

    void retranslateUi(QDialog *Process)
    {
        Process->setWindowTitle(QApplication::translate("Process", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Process", "\350\257\267\350\276\223\345\205\245\345\221\275\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        runButton->setText(QApplication::translate("Process", "\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Process", "\350\277\220\350\241\214\347\273\223\346\236\234\345\246\202\344\270\213\357\274\232", 0, QApplication::UnicodeUTF8));
        onlineButton->setText(QApplication::translate("Process", "\350\201\224\347\275\221\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        offlineButton->setText(QApplication::translate("Process", "\346\227\240\347\275\221\347\273\234\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Process: public Ui_Process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS_H
