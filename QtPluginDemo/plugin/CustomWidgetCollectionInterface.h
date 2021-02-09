#ifndef CUSTOMWIDGETCOLLECTIONINTERFACE_H
#define CUSTOMWIDGETCOLLECTIONINTERFACE_H
#include <QList>
#include <QtPlugin>
class CustomWidgetInterface;
class CustomWidgetCollectionInterface
{
public:
    virtual ~CustomWidgetCollectionInterface() {}

    virtual QList<CustomWidgetInterface*> customWidgets() const = 0;

};

#define CustomWidgetCollectionInterface_iid "org.qt-project.Qt.CustomWidgetCollectionInterface"

// Q_DECLARE_INTERFACE macro to let Qt's meta object system aware of the interface
Q_DECLARE_INTERFACE(CustomWidgetCollectionInterface, CustomWidgetCollectionInterface_iid)
#endif // CUSTOMWIDGETCOLLECTIONINTERFACE_H
