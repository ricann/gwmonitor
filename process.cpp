#include "process.h"
#include "ui_process.h"

Process::Process(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Process)
{
    ui->setupUi(this);
    ui->outputEdit->setReadOnly(true);
    cmd = new QProcess;
    connect(ui->inputEdit, SIGNAL(returnPressed()), this, SLOT(runClicked()));
    connect(ui->runButton, SIGNAL(clicked(bool)), this, SLOT(runClicked()));
    connect(cmd, SIGNAL(readyRead()), this, SLOT(readOutput()));
}

Process::~Process()
{
    delete ui;
}
void Process::runClicked()
{
    QString input = ui->inputEdit->text();
    cmd->start(input);
    output = tr("");
    ui->outputEdit->setText(output);
}
void Process::readOutput()
{
    output += cmd->readAll();
    ui->outputEdit->setText(output);
}
void Process::on_onlineButton_clicked()
{
    emit dlgReturn(0);
    close();
}

void Process::on_offlineButton_clicked()
{
    emit dlgReturn(1);
    close();
}
