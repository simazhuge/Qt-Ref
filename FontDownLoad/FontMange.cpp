#include "FontMange.h"
#include <QFontDatabase>
#include <QApplication>
#include <QDir>
#include <QDebug>
static FontMange *g_instance = new FontMange();
FontMange::FontMange(QObject *parent) : QObject(parent)
{

}

FontMange *FontMange::getInstance()
{
    return g_instance;
}

void FontMange::loadFontFile()
{
    QDir dir(QApplication::applicationDirPath() + "/fontstring");
    if(dir.exists())
    {
        qDebug() << dir.entryInfoList();
        foreach(QFileInfo mfi, dir.entryInfoList())
        {
            if(mfi.isFile())
            {
                qDebug()<< "File :" << mfi.fileName();
                int index = QFontDatabase::addApplicationFont( mfi.absoluteFilePath());

                if(index == -1)
                {
                    qDebug() << "error font file";
                }
                else {
                    QStringList lst(QFontDatabase::applicationFontFamilies(index));
                    qDebug() << "font families" << lst;
                }
            }
            else
            {
                if(mfi.fileName()=="." || mfi.fileName() == "..")
                    continue;
                qDebug() << "Entry Dir" << mfi.absoluteFilePath();
            }
        }
    }
    else {
        //TODO Log
    }

}

FontMange::GarbageCollector::~GarbageCollector()
{
    delete g_instance;
    g_instance = 0;
}
