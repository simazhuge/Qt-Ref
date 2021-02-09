#include "CustomWidgetCollection.h"
#include "buttonplugin.h"
CustomWidgetCollection::CustomWidgetCollection(QObject *parent) :
    QObject(parent)
{
    m_plugins.append(new ButtonPlugin(this));
}

QList<CustomWidgetInterface *> CustomWidgetCollection::customWidgets() const
{
    return m_plugins;
}
