#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "QtTable.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTable w;
    QFile file(":/data.json");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QByteArray saveData = file.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        qDebug() << loadDoc;
        w.setHeader(loadDoc.object().value("header").toArray());
        w.setData( loadDoc.object().value("data").toArray());

    }

    w.show();
    return a.exec();
}
