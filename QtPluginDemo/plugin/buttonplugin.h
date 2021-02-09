#ifndef BUTTONPLUGIN_H
#define BUTTONPLUGIN_H

#include <QPushButton>
#include "CustomWidget.h"
class ButtonPlugin : public CustomWidget
{
    Q_OBJECT
    Q_INTERFACES(CustomWidgetInterface)
public:
    ButtonPlugin(QObject *parent = 0);
    virtual QWidget *createWidget(QWidget *parent);
    virtual void setData(const QVariant &data, QWidget *pW);
};

#endif // BUTTONPLUGIN_H
