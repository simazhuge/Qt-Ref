#include "CustomWidget.h"

CustomWidget::CustomWidget(QObject *parent):
    QObject( parent ),
    m_isInitialized( false )
{

}

QString CustomWidget::name() const
{
    return m_name;
}

QString CustomWidget::group() const
{
    return m_group;
}

QString CustomWidget::toolTip() const
{
    return m_toolTip;
}

QString CustomWidget::whatsThis() const
{
    return m_whatsThis;
}

QIcon CustomWidget::icon() const
{
    return m_icon;
}

bool CustomWidget::isInitialized() const
{
    return m_isInitialized;
}
