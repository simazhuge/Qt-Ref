#ifndef CUSTOMWIDGETCOLLECTION_H
#define CUSTOMWIDGETCOLLECTION_H

#include <QObject>
#include "CustomWidgetCollectionInterface.h"
class CustomWidgetCollection : public QObject,
        public CustomWidgetCollectionInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    //The Q_PLUGIN_METADATA macro is included next to the Q_OBJECT macro
    //The json file is compiled into the plugin and does not need to be installed
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.CustomWidgetCollectionInterface" FILE "Info.json")
#endif
    //The Q_INTERFACES macro tells Qt which interfaces the class implements
    Q_INTERFACES( CustomWidgetCollectionInterface )

public:
    CustomWidgetCollection( QObject *parent = 0);
    virtual QList<CustomWidgetInterface*> customWidgets() const;

private:
    QList<CustomWidgetInterface*> m_plugins;
};

#endif // CUSTOMWIDGETCOLLECTION_H
