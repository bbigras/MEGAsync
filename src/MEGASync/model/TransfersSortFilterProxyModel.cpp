#include "TransfersSortFilterProxyModel.h"
#include <megaapi.h>

TransfersSortFilterProxyModel::TransfersSortFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent),
      mTransferType (QSet<int>()),
      mTransferState (QSet<int>()),
      mFileType (QSet<TransferData::FileTypes>()),
      mSortCriterion (SORT_BY::PRIORITY)
{
}

void TransfersSortFilterProxyModel::setTransferType(const QSet<int> transferTypes)
{
    mTransferType = transferTypes;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::addTransferType(const QSet<int> transferTypes)
{
    mTransferType += transferTypes;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::setTransferState(const QSet<int> transferStates)
{
    mTransferState = transferStates;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::addTransferState(const QSet<int> transferStates)
{
    mTransferState += transferStates;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::setFileType(const QSet<TransferData::FileTypes> fileTypes)
{
    mFileType = fileTypes;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::addFileType(const QSet<TransferData::FileTypes> fileTypes)
{
    mFileType += fileTypes;
    invalidateFilter();
}

void TransfersSortFilterProxyModel::resetAllFilters()
{
    mTransferType = {};
    mFileType = {};
    mTransferState = {};
    invalidateFilter();
}

void TransfersSortFilterProxyModel::setSortBy(SORT_BY sortCriterion)
{
    mSortCriterion = sortCriterion;
}

bool TransfersSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    auto d (qvariant_cast<TransferItem2>(index.data()).getTransferData());

    return     (mTransferState.isEmpty() || mTransferState.contains(d->mState))
            && (mTransferType.isEmpty()  || mTransferType.contains(d->mType))
            && (mFileType.isEmpty()      || mFileType.contains(d->mFileType))
            && d->mFilename.contains(filterRegExp());
}

bool TransfersSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    bool lessThan (false);
    const auto leftItem (qvariant_cast<TransferItem2>(left.data()).getTransferData());
    const auto rightItem (qvariant_cast<TransferItem2>(right.data()).getTransferData());

    switch (mSortCriterion)
    {
        case SORT_BY::PRIORITY:
        {
            lessThan = leftItem->mPriority < rightItem->mPriority;

            break;
        }
        case SORT_BY::TOTAL_SIZE:
        {
            lessThan = leftItem->mTotalSize < rightItem->mTotalSize;
            break;
        }
        case SORT_BY::NAME:
        {
            lessThan = leftItem->mFilename < rightItem->mFilename;
            break;
        }
        default:
            break;
    }

    return lessThan;
}

bool TransfersSortFilterProxyModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
              const QModelIndex &destinationParent, int destinationChild)
{
    bool moveOk(true);
    int row(sourceRow);
    while (moveOk && row < (sourceRow+count))
    {
        auto sourceIndex(mapToSource(index(sourceRow, 0, sourceParent)));
        int destRow;
        if (destinationChild == rowCount())
        {
            destRow = sourceModel()->rowCount();
        }
        else
        {
            destRow = mapToSource(index(destinationChild, 0, destinationParent)).row();
        }
        moveOk = sourceModel()->moveRows(sourceIndex.parent(), sourceIndex.row(), 1,
                                         sourceIndex.parent(), destRow);
        row++;
    }
    return moveOk;
}
