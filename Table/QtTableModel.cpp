#include "QtTableModel.h"
#include <QDebug>
#include <QColor>
QtTableModel::QtTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_row(-1)
    , m_col(-1)
{

}

QtTableModel::~QtTableModel()
{
    foreach(HeaderData* p, m_header){
        delete p;
    }
    m_header.clear();
}

int QtTableModel::rowCount(const QModelIndex &parent) const
{
    if(-1 != m_row){
        return m_row;
    }
    return m_data.size();
}

int QtTableModel::columnCount(const QModelIndex &parent) const
{
    if(-1 != m_col){
        return m_col;
    }
    return m_header.size();
}

QVariant QtTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant var ;
    switch(orientation)//方向
    {
    case Qt::Horizontal ://水平表头
        switch(role)//角色
        {
        case Qt::TextAlignmentRole://文本对齐
            var = int (Qt::AlignHCenter | Qt::AlignVCenter);
            break;
        case Qt::DisplayRole://显示文本

            if(section < m_header.size())
            {
                var = m_header.at(section)->label;
            }
            break;
        }
        break;
    case Qt::Vertical ://垂直表头
        switch(role)
        {
        case Qt::TextAlignmentRole:
            var= int (Qt::AlignCenter);
            break;
        case Qt::DisplayRole: //显示行号
            //TODO
             //headName = section + 1+ m_startRow;
            break;
        }
        break;
    }
    return var;
}

QVariant QtTableModel::data(const QModelIndex &index, int role) const
{
    QVariant dt;
    switch(role)
    {
    case Qt::TextAlignmentRole:
        dt = int (Qt::AlignHCenter | Qt::AlignVCenter);
        break;
    case Qt::DisplayRole: //显示数据
    {
        if(index.isValid()){
            int row = index.row();
            int col = index.column();
            QVariantMap d = m_data.at(row);
            dt = d.value(m_header.at(col)->prop);
        }
        break;
    }
    case Qt::TextColorRole://文本颜色
        break;
    case Qt::BackgroundColorRole:
        break;
    default:
        break;
    }
    return dt;
}

void QtTableModel::appendHeader(const QJsonObject &obj)
{
    HeaderData *pD = new HeaderData();
    pD->prop = obj["prop"].toString();
    pD->label = obj["label"].toString();
    pD->width = obj["width"].toInt(pD->width);
    pD->sortable = obj["sortable"].toBool(pD->sortable);
    m_header.append(pD);
}




