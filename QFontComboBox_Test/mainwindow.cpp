#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontComboBox>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include "ttffiletransform.h"
static void loadfile(const QString &str)
{
    QVector<int> vec;
    QDir dir(str);
    if(dir.exists())
    {
//        qDebug() << dir.entryInfoList();
        foreach(QFileInfo mfi, dir.entryInfoList())
        {
            if(mfi.isFile())
            {
                //qDebug()<< "File :" << mfi.fileName();
                int index = QFontDatabase::addApplicationFont( mfi.absoluteFilePath());

                if(index == -1)
                {
                    qDebug() << "error font file:" << mfi.fileName();
                }
                else {
                    QStringList lst(QFontDatabase::applicationFontFamilies(index));
                    qDebug() << "font families" << lst;
                    vec.push_back(index);


                }
            }
            else
            {
                if(mfi.fileName()=="." || mfi.fileName() == "..")
                    continue;
                //qDebug() << "Entry Dir" << mfi.absoluteFilePath();
            }
        }
    }
    else {
        //TODO Log
    }

    for(int i = 0; i < vec.size(); ++i)
    {
        QStringList lst(QFontDatabase::applicationFontFamilies(vec[i]));
        qDebug() << "font families22222222" << lst;
        //qDebug() << "font" << QGuiApplicationPrivate::platformIntegration()->fontDatabase()->resolveFontFamilyAlias(lst.at(0));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFont f("Arial");
    qDebug() << f ;
    this->setFont(f);
    QFontDatabase fdb;
    QStringList list = fdb.families(QFontDatabase::Any);
    qDebug() << list;
    QFontDatabase::removeAllApplicationFonts();

    int i(1);
    QDir dir("D:/LyWork/DToolsPro/Demo/build-QFontComboBox_Test-Qt5_9_9_Mingw-Debug/debug/");
    if(dir.exists())
    {
//        qDebug() << dir.entryInfoList();
        foreach(QFileInfo mfi, dir.entryInfoList())
        {
            if(mfi.isFile())
            {
                //qDebug()<< "File :" << mfi.fileName();
                //int index = QFontDatabase::addApplicationFont( mfi.absoluteFilePath());
                qDebug() << mfi.suffix();
                if(mfi.suffix() != "ttf")
                {
                    continue;
                }
                TTFFileTransForm::transFile(mfi.absoluteFilePath(), mfi.absolutePath() + "/../out/" + QString::number(i) +".ttf", i);
                i++;
            }
            else
            {
                if(mfi.fileName()=="." || mfi.fileName() == "..")
                    continue;
                //qDebug() << "Entry Dir" << mfi.absoluteFilePath();
            }
        }
    }
    else {
        //TODO Log
    }


    //loadfile("D:/LyWork/DToolsPro/Demo/build-QFontComboBox_Test-Qt5_9_9_Mingw-Debug/debug");


//    QVector<FONTSIGNATURE> signatures;
//    QList<FontNames> families;
//    QStringList familyNames;
//    QFile file("D:/LyWork/DToolsPro/Demo/build-QFontComboBox_Test-Qt5_9_9_Mingw-Debug/debug/AlibabaPuHuiTi-2-95-ExtraBold.ttf");
//    file.open(QFile::ReadOnly);


//    QFile file2("D:/LyWork/DToolsPro/Demo/build-QFontComboBox_Test-Qt5_9_9_Mingw-Debug/debug/3.ttf");
//    auto temp = file.readAll();
//    file.close();
//    getFamiliesAndSignatures(temp, &families, &signatures, 4);
//    file2.open(QFile::WriteOnly);
//    file2.write(temp);
//    file2.close();
//    for(int i = 0; i < families.size(); ++i)
//    {
//        qDebug() << families[i].name << families[i].preferredName << families[i].style << families[i].preferredStyle;
//    }


    ui->setupUi(this);
    new QFontComboBox(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

