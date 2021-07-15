#include "TextMovingWidget.h"
#include <QTimer>
#include <QPainter>
TextMovingWidget::TextMovingWidget(const QString str ,QWidget *parent)
    : QWidget(parent),_text(str),_x(0), _y(0)
{
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(slot_UpdateTextGeometry()));
    _timer->start(30);
    _yFlag = true;
    //_xFlag = false;
}

TextMovingWidget::~TextMovingWidget(){}

void TextMovingWidget::setText(const QString &t)
{
    _text = t;
    _x = 0;
    _y = 0;
    update();
}

void TextMovingWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::red);
    QFontMetrics metric(font());

    p.drawText(_x, _y, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
    if(_xFlag && getTextWidth() > width()){
        int endX = _x ? _x - getTextWidth() : _x + getTextWidth();
        if(endX < width()){
            p.drawText(endX, _y, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
        }
    }
    if(_yFlag && getTextHeight() > height()){
        int endY = _y ? _y - getTextHeight() : _y + getTextHeight();
        if(endY < height()){
            p.drawText(_x, endY, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
        }
    }
}

int TextMovingWidget::getTextWidth() const
{
     QFontMetrics metric(font());
     QStringList lst = _text.split("\n");
     int max(0);
     foreach(const QString &str, lst){
        int temp = metric.horizontalAdvance(str);
        if(temp > max){
            max = temp;
        }
     }
     return max + metric.averageCharWidth();
}

int TextMovingWidget::getTextHeight() const
{
    QFontMetrics metric(font());
    int rowsz = _text.count("\n");
    rowsz = rowsz > 0 ? rowsz + 1 : 1;
    return rowsz * metric.height() + 2* metric.leading();
}

void TextMovingWidget::slot_UpdateTextGeometry()
{
//    QFontMetrics metric(font());
//    if(m_x + getTextWidth() == 0){
//        m_x = 0;
//    }
//    m_x--;
//    update();

    updateTextGeometry(0, 1);
}

void TextMovingWidget::updateTextGeometry(int offsetX, int offsetY)
{
    QFontMetrics metric(font());
    metric.horizontalAdvance(_text);
    if(_x < 0 && _x + getTextWidth() == 0 ){
        _x = 0;
    }
    if(_x + getTextWidth() == 0 || _x - getTextWidth() == 0 ){
        _x = 0;
    }
    _x += offsetX;

    if(_y < 0 && _y + getTextHeight() == 0 ){
        _y = 0;
    }
    if(_y > 0 && _y - getTextHeight() == 0 ){
        _y = 0;
    }
    _y += offsetY;

    update();
}
