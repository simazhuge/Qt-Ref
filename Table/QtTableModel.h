#ifndef QTTABLEMODEL_H
#define QTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>
class QTableView;
class QtTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    struct HeaderData{
        QString prop;
        QString label;
        int width;
        bool sortable ; //实现以该列为基准的排序
        HeaderData() : width(180),sortable(false){

        }
    };
    QtTableModel(QObject *parent = nullptr);
    ~QtTableModel();
    //行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    //列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    //表头的列表名称
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    //数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    void appendHeader(const QJsonObject &obj);
private:
    friend class QtTable;
    QList<HeaderData* > m_header;
    QVector<QVariantMap > m_data;
    int m_row;
    int m_col;

};

#endif // QTTABLEMODEL_H
