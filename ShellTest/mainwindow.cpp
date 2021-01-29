#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_proces_bash = new QProcess;
    m_proces_bash->start("bash");
    m_proces_bash->waitForStarted();
    connect(m_proces_bash,SIGNAL(readyReadStandardOutput()),this,SLOT(readBashStandardOutputInfo()));
    connect(m_proces_bash,SIGNAL(readyReadStandardError()),this,SLOT(readBashStandardErrorInfo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readBashStandardOutputInfo()
{
    qDebug() << "readBashStandardOutputInfo";
    QByteArray cmdout = m_proces_bash->readAllStandardOutput();
    if(!cmdout.isEmpty()){
        ui->textEdit_bashmsg->append(QString::fromLocal8Bit(cmdout));
    }
    QScrollBar* scroll = ui->textEdit_bashmsg->verticalScrollBar();
    scroll->setSliderPosition(scroll->maximum());

}

void MainWindow::readBashStandardErrorInfo()
{
    qDebug() << "readBashStandardErrorInfo";
    QByteArray cmdout = m_proces_bash->readAllStandardError();
    if(!cmdout.isEmpty()){
        ui->textEdit_bashmsg->append(QString::fromLocal8Bit(cmdout));
    }
    QScrollBar* scroll = ui->textEdit_bashmsg->verticalScrollBar();
    scroll->setSliderPosition(scroll->maximum());
}


void MainWindow::on_pushButton_clicked()
{
    QString strCmd = ui->lineEdit_bashcmd->text();
    ui->textEdit_bashmsg->append("Linux:~$ "+strCmd);
    m_proces_bash->write(ui->lineEdit_bashcmd->text().toLocal8Bit() + '\n');
    ui->lineEdit_bashcmd->clear();
}
