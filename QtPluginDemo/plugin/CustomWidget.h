#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include "CustomWidgetInterface.h"
class CustomWidget :public QObject, public CustomWidgetInterface
{

    Q_OBJECT
    Q_INTERFACES(CustomWidgetInterface)
public:

    CustomWidget(QObject *parent);
    virtual QString name() const;
    virtual QString group() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;
    virtual QIcon icon() const;

    virtual bool isInitialized() const;
    virtual void setData(const QXmlStreamAttributes &, QWidget *){};
    virtual void setData(const QDataStream &, QWidget *){};
    virtual void setData(const QVariant &, QWidget *){};
protected:
    QString m_name;
    QString m_toolTip;
    QString m_whatsThis;
    QIcon m_icon;
    QString m_group;
    bool m_isInitialized;
    //
};

#endif // CUSTOMWIDGET_H
