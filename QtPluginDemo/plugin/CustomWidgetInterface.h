#ifndef CUSTOMWIDGETINTERFACE_H
#define CUSTOMWIDGETINTERFACE_H
#include <QString>
#include <QIcon>
#include <QXmlStreamAttributes>
class CustomWidgetInterface
{
public:
    virtual ~CustomWidgetInterface() {}
    virtual QString name() const = 0;
    virtual QString group() const = 0;
    virtual QString toolTip() const = 0;
    virtual QString whatsThis() const = 0;
    virtual QIcon icon() const = 0;

    virtual QWidget *createWidget(QWidget *parent) = 0;
    virtual void setData(const QXmlStreamAttributes &, QWidget *) = 0;
    virtual void setData(const QDataStream &, QWidget *) = 0;
    virtual void setData(const QVariant &, QWidget *) = 0;

    virtual bool isInitialized() const { return false; }
};

#define CustomWidgetInterface_iid "org.qt-project.CustomWidgetInterface"

Q_DECLARE_INTERFACE(CustomWidgetInterface, CustomWidgetInterface_iid)
#endif // CUSTOMWIDGETINTERFACE_H
