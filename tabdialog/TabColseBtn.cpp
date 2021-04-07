#include "TabColseBtn.h"
#include <QDebug>
#include <QMouseEvent>


TabColseBtn::TabColseBtn(QWidget *parent)
    :QPushButton(parent)
{
    this->tabWidget=parent;
    resize(12,12);
    setCursor(QCursor(Qt::PointingHandCursor));
    QIcon icon1;
    icon1.addFile(QString(":/image/tab_del.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    setIcon(icon1);
    setIconSize(QSize(12, 12));
    connect(this, &QAbstractButton::clicked, [this](){
        emit clicked(tabWidget);
    });
}


TabColseBtn::~TabColseBtn()
{

}

