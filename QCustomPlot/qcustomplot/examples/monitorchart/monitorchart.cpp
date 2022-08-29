#include "monitorchart.h"
#include "ui_monitorchart.h"

MonitorChart::MonitorChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorChart)
{
    ui->setupUi(this);
}

MonitorChart::~MonitorChart()
{
    delete ui;
}
