#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPluginLoader>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    echoInterface = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete echoInterface;
}

// loader plugin
void MainWindow::on_pushButton_clicked()
{
    static QWidget *pW = 0;
    if(!pW)
    {
        if (!loadPlugin()) {
            QMessageBox::information(this, "Error", "Could not load the plugin");
        }
        else {
            foreach(CustomWidgetInterface *p, echoInterface->customWidgets())
            {
                pW = p->createWidget(this);
                pW->setStyleSheet(" QWidget { background-color: red }");
                p->setData(QRect(100, 100, 50, 50), pW);
                pW->show();
                this->update();
            }
        }
    }
    else {
        pW->move(pW->geometry().x() + 10, pW->geometry().y() + 10);
        this->update();
    }
}

bool MainWindow::loadPlugin()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    const QStringList entries = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            echoInterface = qobject_cast<CustomWidgetCollectionInterface *>(plugin);
            if (echoInterface)
                return true;
            pluginLoader.unload();
        }
    }

    return false;
}
