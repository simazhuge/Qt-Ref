#include "buttonplugin.h"
#include <QVariant>
ButtonPlugin::ButtonPlugin(QObject *parent) : CustomWidget(parent)
{
    m_name = tr("button");
    m_group = tr("buttongroup");
}

QWidget *ButtonPlugin::createWidget(QWidget *parent)
{
    return new QPushButton(parent);
}

void ButtonPlugin::setData(const QVariant &data, QWidget *pW)
{
    QPushButton *p = dynamic_cast<QPushButton *>(pW);
    if(p && data.canConvert(QMetaType::QRect))
    {
        p->setGeometry(data.toRect());
        p->update();
    }
}


