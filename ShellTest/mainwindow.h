#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void readBashStandardOutputInfo();
    void readBashStandardErrorInfo();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *m_proces_bash;
};
#endif // MAINWINDOW_H
