#ifndef TEXTMOVINGWIDGET_H
#define TEXTMOVINGWIDGET_H

#include <QWidget>
class TextMovingWidget : public QWidget
{
    Q_OBJECT

public:
    TextMovingWidget(const QString str="" ,QWidget *parent = 0);
    ~TextMovingWidget();
    void setText(const QString&);
    void updateTextGeometry(int offsetX, int offsetY);
protected:
    virtual void paintEvent(QPaintEvent*);
    //要显示的文本的宽度
    int getTextWidth() const;
    //要显示的文本的高度
    int getTextHeight() const;
private slots:
    void slot_UpdateTextGeometry();
private:
    QTimer *_timer;
    QString _text;
    int m_x;
    int _y;
    bool _yFlag;//Y轴走马灯
    bool _xFlag;//X轴走马灯
};

#endif // TEXTMOVINGWIDGET_H
