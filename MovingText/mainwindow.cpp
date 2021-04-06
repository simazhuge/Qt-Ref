#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TextMovingWidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TextMovingWidget *p = new TextMovingWidget("hello\nworld", this);
    p->setMaximumSize(40, 20);
    p->setMinimumSize(40, 20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

