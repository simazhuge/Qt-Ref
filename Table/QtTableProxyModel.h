#ifndef QTTABLEPROXYMODEL_H
#define QTTABLEPROXYMODEL_H

#include <QDate>
#include <QObject>
#include <QSortFilterProxyModel>

//! [0]
class QtTableProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    QtTableProxyModel(QObject *parent = 0);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(const QDate &date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(const QDate &date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool dateInRange(const QDate &date) const;

    QDate minDate;
    QDate maxDate;
};
//! [0]

#endif // QTTABLEPROXYMODEL_H
