#ifndef MONITORCHART_H
#define MONITORCHART_H

#include <QWidget>

namespace Ui {
class MonitorChart;
}

class MonitorChart : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorChart(QWidget *parent = nullptr);
    ~MonitorChart();

private:
    Ui::MonitorChart *ui;
};

#endif // MONITORCHART_H
