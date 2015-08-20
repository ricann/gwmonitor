/********************************************************************************
** Form generated from reading UI file 'paintdialog.ui'
**
** Created: Tue Apr 22 15:36:10 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTDIALOG_H
#define UI_PAINTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_paintDialog
{
public:

    void setupUi(QDialog *paintDialog)
    {
        if (paintDialog->objectName().isEmpty())
            paintDialog->setObjectName(QString::fromUtf8("paintDialog"));
        paintDialog->resize(663, 488);

        retranslateUi(paintDialog);

        QMetaObject::connectSlotsByName(paintDialog);
    } // setupUi

    void retranslateUi(QDialog *paintDialog)
    {
        paintDialog->setWindowTitle(QApplication::translate("paintDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class paintDialog: public Ui_paintDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTDIALOG_H
