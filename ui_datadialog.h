/********************************************************************************
** Form generated from reading UI file 'datadialog.ui'
**
** Created: Fri Jun 12 09:55:55 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIALOG_H
#define UI_DATADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataDialog
{
public:
    QTableView *tableView;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QComboBox *nameList;
    QLabel *label;
    QComboBox *nodeList;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QLabel *label_2;

    void setupUi(QDialog *DataDialog)
    {
        if (DataDialog->objectName().isEmpty())
            DataDialog->setObjectName(QString::fromUtf8("DataDialog"));
        DataDialog->resize(773, 587);
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
        DataDialog->setPalette(palette);
        DataDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(95, 95, 95);\n"
"color: rgb(255, 255, 255);"));
        tableView = new QTableView(DataDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(30, 40, 551, 511));
        tableView->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0);"));
        pushButton = new QPushButton(DataDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(630, 250, 96, 20));
        pushButton->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(DataDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(602, 70, 152, 111));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        nameList = new QComboBox(layoutWidget);
        nameList->setObjectName(QString::fromUtf8("nameList"));
        nameList->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);\n"
"font: 9pt \"\345\256\213\344\275\223\";\n"
"\n"
""));
        nameList->setIconSize(QSize(16, 16));
        nameList->setFrame(true);

        gridLayout->addWidget(nameList, 0, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        nodeList = new QComboBox(layoutWidget);
        nodeList->setObjectName(QString::fromUtf8("nodeList"));
        nodeList->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);\n"
"font: 9pt \"\345\256\213\344\275\223\";"));

        gridLayout->addWidget(nodeList, 2, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        gridLayout->addWidget(dateEdit, 3, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        retranslateUi(DataDialog);

        QMetaObject::connectSlotsByName(DataDialog);
    } // setupUi

    void retranslateUi(QDialog *DataDialog)
    {
        DataDialog->setWindowTitle(QApplication::translate("DataDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DataDialog", "\346\237\245\350\257\242\345\205\250\351\203\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DataDialog", "\346\261\241\346\237\223\345\205\203", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DataDialog", "\346\243\200\346\265\213\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DataDialog", "\350\212\202\347\202\271\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataDialog: public Ui_DataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIALOG_H
