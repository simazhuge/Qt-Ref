#ifndef QTTABLE_H
#define QTTABLE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QTableView>
class QtTableModel;
class QtTableProxyModel;
class QtTable : public QTableView
{
    Q_OBJECT
public:
    QtTable(QWidget *parent = 0);
    //[{date: '2016-05-04',name: '王小虎',address: '上海市普陀区金沙江路 1517 弄'}]
    void setData(const QJsonArray& data);
    //[{pro:"date",label:"日期",width:"180"}]
    void setHeader(const QJsonArray& header);
    //设置行数
    void setRowCount(int row);
    //设置列数
    void setColumnCount(int col);
    //设置行距
    void setRowSectionSize(int sz);
    //设置列距
    void setColSectionSize(int sz);
    void initStyle();
protected:
    void updateHeader();
    QtTableModel *m_pModel;
    bool m_isInit;
    QtTableProxyModel *m_pProxyModel;
};

#endif // QTTABLE_H
