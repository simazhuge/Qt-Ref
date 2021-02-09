#include "QtTableProxyModel.h"

//! [0]
QtTableProxyModel::QtTableProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}
//! [0]

//! [1]
void QtTableProxyModel::setFilterMinimumDate(const QDate &date)
{
    minDate = date;
    invalidateFilter();
}
//! [1]

//! [2]
void QtTableProxyModel::setFilterMaximumDate(const QDate &date)
{
    maxDate = date;
    invalidateFilter();
}
//! [2]

//! [3]
bool QtTableProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return (sourceModel()->data(index0).toString().contains(filterRegExp())
            || sourceModel()->data(index1).toString().contains(filterRegExp()))
            && dateInRange(sourceModel()->data(index2).toDate());
}
//! [3]

//! [4] //! [5]
bool QtTableProxyModel::lessThan(const QModelIndex &left,
                                      const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
//! [4]

//! [6]
    if (leftData.type() == QVariant::DateTime) {
        return leftData.toDateTime() < rightData.toDateTime();
    } else {
        static QRegExp emailPattern("[\\w\\.]*@[\\w\\.]*)");

        QString leftString = leftData.toString();
        if(left.column() == 1 && emailPattern.indexIn(leftString) != -1)
            leftString = emailPattern.cap(1);

        QString rightString = rightData.toString();
        if(right.column() == 1 && emailPattern.indexIn(rightString) != -1)
            rightString = emailPattern.cap(1);

        return QString::localeAwareCompare(leftString, rightString) < 0;
    }
}
//! [5] //! [6]

//! [7]
bool QtTableProxyModel::dateInRange(const QDate &date) const
{
    return (!minDate.isValid() || date > minDate)
            && (!maxDate.isValid() || date < maxDate);
}
//! [7]
