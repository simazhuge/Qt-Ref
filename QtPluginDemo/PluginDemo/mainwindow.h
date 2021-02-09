#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../plugin/CustomWidgetCollectionInterface.h"
#include "../plugin/CustomWidgetInterface.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    bool loadPlugin();
    CustomWidgetCollectionInterface *echoInterface;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
