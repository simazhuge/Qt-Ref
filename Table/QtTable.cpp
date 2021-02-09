#include "QtTable.h"
#include "QtTableModel.h"
#include "QtTableProxyModel.h"
#include <QDebug>
#include <QHeaderView>
QtTable::QtTable(QWidget *parent)
    : QTableView(parent)
{
    m_pModel = new QtTableModel(this);
    m_pProxyModel = new QtTableProxyModel(this);
    m_isInit = false;
    initStyle();
}

void QtTable::setData(const QJsonArray &data)
{
    m_pModel->m_data.reserve(data.size());
    //读数组
    for (int index = 0; index < data.size(); ++index) {
        QJsonObject object = data[index].toObject();
        m_pModel->m_data.append(object.toVariantMap());
    }

    m_pProxyModel->setSourceModel(m_pModel);
    setModel(m_pProxyModel);
    setSortingEnabled(true);
    sortByColumn(1, Qt::AscendingOrder);
    updateHeader();
}

void QtTable::setHeader(const QJsonArray &data)
{
    m_pModel->m_header.reserve(data.size());
    //读数组
    for (int index = 0; index < data.size(); ++index) {
        QJsonObject object = data[index].toObject();
        m_pModel->appendHeader(object);
    }
}

void QtTable::setRowCount(int row)
{
    m_pModel->m_row = row;
}

void QtTable::setColumnCount(int col)
{
    m_pModel->m_col = col;
}

void QtTable::setRowSectionSize(int sz)
{
    verticalHeader()->setDefaultSectionSize(sz);
    verticalHeader()->setMinimumSectionSize(sz);
}

void QtTable::setColSectionSize(int sz)
{
    horizontalHeader()->setDefaultSectionSize(sz);
    horizontalHeader()->setMinimumSectionSize(sz);
}

void QtTable::initStyle()
{
    this->horizontalHeader()->setStyleSheet("QHeaderView {color: white;}" //前景色
                                            "QHeaderView::section{background-color: rgb(250, 250, 115);}"
                                            "QHeaderView{background-color: rgb(250, 250, 115);}"//设置表头空白区域背景色
                                            "QHeaderView {font:italic bold 15px arial;}");//字体
//    this->setStyleSheet("QTableView{font:italic bold 15px arial;}"
//                        //"QTableView{background-color: rgb(250, 250, 115)}" //背景色
//                        "QTableView{gridline-color: rgb(250, 250, 115)}" //分隔线
//                        "QTableView::item{border:2px solid rgb(250, 250, 115);margin:6px;}"
//                        "QTableView{border: 10px groove gray;}");//边框

    setFocusPolicy(Qt::NoFocus);
    //只显示横分割线，不显示竖分割线
    setShowGrid(false);// 不显示网格线
    this->setStyleSheet("QTableView{font:italic bold 15px arial;}"
                        "QTableView::item{border:0px solid rgb(255,0,0);}"
                        "QTableView::item:selected { background-color: rgb(255,235,205)}" //选中背景
                        "QTableView::item{border-bottom:1px solid rgb(255,0,0)}");//边框

}

void QtTable::updateHeader()
{
    for(int i = 0; i < m_pModel->m_header.size(); ++i)
    {
        setColumnWidth(i, m_pModel->m_header.at(i)->width);
        sortByColumn(i, Qt::DescendingOrder);
    }
}
