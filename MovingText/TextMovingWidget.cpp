#include "TextMovingWidget.h"
#include <QTimer>
#include <QPainter>
TextMovingWidget::TextMovingWidget(const QString str ,QWidget *parent)
    : QWidget(parent),_text(str),m_x(0), _y(0)
{
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(slot_UpdateTextGeometry()));
    _timer->start(30);
    _yFlag = false;
    //_xFlag = false;
}

TextMovingWidget::~TextMovingWidget(){}

void TextMovingWidget::setText(const QString &t)
{
    _text = t;
    m_x = 0;
    _y = 0;
    update();
}

void TextMovingWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::red);
    QFontMetrics metric(font());

    p.drawText(m_x, _y, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
    if(_xFlag && getTextWidth() > width()){
        int endX = m_x ? m_x - getTextWidth() : m_x + getTextWidth();
        if(endX < width()){
            p.drawText(endX, _y, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
        }
    }
    if(_yFlag && getTextHeight() > height()){
        int endY = _y ? _y - getTextHeight() : _y + getTextHeight();
        if(endY < height()){
            p.drawText(m_x, endY, getTextWidth(), getTextHeight(),Qt::AlignLeft,_text);
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
    if(m_x < 0 && m_x + getTextWidth() == 0 ){
        m_x = 0;
    }
    if(m_x + getTextWidth() == 0 || m_x - getTextWidth() == 0 ){
        m_x = 0;
    }
    m_x += offsetX;

    if(_y < 0 && _y + getTextHeight() == 0 ){
        _y = 0;
    }
    if(_y > 0 && _y - getTextHeight() == 0 ){
        _y = 0;
    }
    _y += offsetY;

    update();
}
