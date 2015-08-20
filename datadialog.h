#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>
#include <QDate>

class QSqlTableModel;

namespace Ui {
class DataDialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DataDialog(QWidget *parent = 0);
    ~DataDialog();
    
private:
    Ui::DataDialog *ui;
    //QSqlTableModel *model;

private slots:

    void on_pushButton_clicked();

    //void on_nameButton_clicked();
    void on_nameList_currentIndexChanged(const QString &arg1);

    void on_nodeList_currentIndexChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);
};

#endif // DATADIALOG_H
