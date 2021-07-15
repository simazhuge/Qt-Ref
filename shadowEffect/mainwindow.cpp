#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
#include <QDebug>
#include <QPainter>
#include <QPaintEngine>
#include <private/qpixmapfilter_p.h>
QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
QT_END_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QMovie *movie = new QMovie("./image/"
//                               "lAHPDfJ6ScRNZFPM-sz6_250_250.gif");
//    qDebug() << movie->frameCount();

//    ui->label->setMovie(movie);
//    movie->start();
    QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
    e->setColor(Qt::red);
    e->setOffset(QPoint(20,20));
    ui->label->setGraphicsEffect(e);
   f = new QPixmapDropShadowFilter();


}
MainWindow::~MainWindow()
{

}
#define RADIUS 5
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap px(":/k.button30_01.png");

    QPainter p(this);

    if (px.isNull())
        return;
    QSize sz(1000, 1000);
    QImage tmp(px.size() *1.5, QImage::Format_ARGB32_Premultiplied);
    tmp.setDevicePixelRatio(px.devicePixelRatio());
    tmp.fill(0);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawPixmap(QPoint(10, 10), px);
    tmpPainter.end();

    // blur the alpha channel
    QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.setDevicePixelRatio(px.devicePixelRatio());
    blurred.fill(0);
    QPainter blurPainter(&blurred);
    qt_blurImage(&blurPainter, tmp, 4, false, true);
    blurPainter.end();

    tmp = std::move(blurred);

    // blacken the image...
    tmpPainter.begin(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(tmp.rect(), Qt::red);
    tmpPainter.end();

    // draw the blurred drop shadow...
    qDebug() << tmp.size();
    p.drawImage(QPoint(0, 0), tmp);

    // Draw the actual pixmap...
//    p.drawPixmap(QRect(0, 0, 1000, 1000), px, px.rect());


   p.setWorldTransform(QTransform());

    f->setColor(Qt::red);
//    f->setOffset(QPoint(12, 12));
//    f->setBlurRadius(4);

    //temp.drawPixmap(temppx.rect(), px, px.rect());

    f->draw(&p, QPoint(0, 0), px);


}

