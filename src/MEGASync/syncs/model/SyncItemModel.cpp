#include "syncs/model/SyncItemModel.h"
#include "syncs/gui/SyncTooltipCreator.h"
#include "syncs/control/SyncInfo.h"

#include "control/Utilities.h"
#include "MegaApplication.h"

#include <QCoreApplication>
#include <QIcon>
#include <QFileInfo>
#include <QDebug>

const int SyncItemModel::ICON_SIZE = 24;
const int SyncItemModel::WARNING_ICON_SIZE = 18;


SyncItemModel::SyncItemModel(QObject *parent)
    : QAbstractItemModel(parent),
    mSyncInfo (SyncInfo::instance())
{
    connect(mSyncInfo, &SyncInfo::syncStateChanged, this, &SyncItemModel::insertSync);
    connect(mSyncInfo, &SyncInfo::syncStatsUpdated, this, &SyncItemModel::updateSyncStats);
    connect(mSyncInfo, &SyncInfo::syncRemoved, this, &SyncItemModel::removeSync);
}

QVariant SyncItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case Column::ENABLED:
            if(role == Qt::ToolTipRole)
                return tr("Sort by state");
            break;
        case Column::LNAME:
            if(role == Qt::DisplayRole)
                return tr("Sync Name");
            if(role == Qt::ToolTipRole)
                return tr("Sort by sync name");
            break;
        case Column_STATE:
            if(role == Qt::DisplayRole)
                return tr("State");
            if(role == Qt::ToolTipRole)
                return tr("Sort by sync state");
            break;
        case Column_FILES:
            if(role == Qt::DisplayRole)
                return tr("Files");
            if(role == Qt::ToolTipRole)
                return tr("Sort by file count");
            break;
        case Column_FOLDERS:
            if(role == Qt::DisplayRole)
                return tr("Folders");
            if(role == Qt::ToolTipRole)
                return tr("Sort by folder count");
            break;
        case Column_DOWNLOADS:
            if(role == Qt::DisplayRole)
                return tr("Downloading");
            if(role == Qt::ToolTipRole)
                return tr("Sort by Downloading");
            break;
        case Column_UPLOADS:
            if(role == Qt::DisplayRole)
                return tr("Uploading");
            if(role == Qt::ToolTipRole)
                return tr("Sort by Uploading");
            break;
        }
    }
    return QVariant();
}

Qt::ItemFlags SyncItemModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && (index.column() == Column::ENABLED))
        return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;

    return QAbstractItemModel::flags(index);
}

QModelIndex SyncItemModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column, nullptr);
}

QModelIndex SyncItemModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    // NOTE: Implement me for the tree view
    return QModelIndex();
}

int SyncItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mList.size();
}

int SyncItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return kColumns;
}

QVariant SyncItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(mList.size() <= index.row())
    {
        return QVariant();
    }
    auto sync = mList.at(index.row());
    if(!sync)
    {
        return QVariant();
    }

    if(role == Qt::UserRole)
        return QVariant::fromValue(sync);

    switch(index.column())
    {
    case Column::ENABLED:
        if(role == Qt::CheckStateRole)
            return sync->getRunState() == ::mega::MegaSync::RUNSTATE_RUNNING ? Qt::Checked : Qt::Unchecked;
        else if(role == Qt::ToolTipRole)
            return sync->getRunState() == ::mega::MegaSync::RUNSTATE_RUNNING ? tr("Sync is enabled") : tr("Sync is disabled");
        break;
    case Column::LNAME:
        if(role == Qt::DecorationRole)
        {
            QIcon syncIcon;
            if(sync->getError())
            {
                syncIcon.addFile(QLatin1String(":/images/ic_sync_warning.png"), QSize(WARNING_ICON_SIZE, WARNING_ICON_SIZE), QIcon::Normal);
            }
            else
            {
                syncIcon.addFile(QLatin1String(":/images/icons/synced-ico-rest.png"), QSize(ICON_SIZE, ICON_SIZE), QIcon::Normal);
                syncIcon.addFile(QLatin1String(":/images/icons/synced-ico-hover.png"), QSize(ICON_SIZE, ICON_SIZE), QIcon::Selected);
            }
            return syncIcon;
        }
        else if(role == Qt::DisplayRole)
        {
            return sync->name(false, true);
        }
        else if(role == Qt::ToolTipRole)
        {
            QString toolTip;
            if(sync->getError())
            {
                toolTip += QCoreApplication::translate("MegaSyncError", mega::MegaSync::getMegaSyncErrorCode(sync->getError()));
                toolTip += QChar::LineSeparator;
            }
            toolTip += SyncTooltipCreator::createForLocal(sync->getLocalFolder());
            toolTip += QChar::LineSeparator;
            toolTip += SyncTooltipCreator::createForRemote(sync->getMegaFolder());
            return toolTip;
        }
        break;
    case Column_STATE:
        if(role == Qt::DisplayRole)
        {
            std::string s;
            switch (sync->getRunState())
            {
            case ::mega::MegaSync::RUNSTATE_PENDING: s = "Pending"; break;
            case ::mega::MegaSync::RUNSTATE_LOADING: s = "Loading"; break;
            case ::mega::MegaSync::RUNSTATE_PAUSED: s = "Paused"; break;
            case ::mega::MegaSync::RUNSTATE_SUSPENDED: s = "Suspended"; break;
            case ::mega::MegaSync::RUNSTATE_DISABLED: s = "Disabled"; break;
            case ::mega::MegaSync::RUNSTATE_RUNNING:
                {
                    auto it = mSyncInfo->mSyncStatsMap.find(sync->backupId());
                    if (it != mSyncInfo->mSyncStatsMap.end())
                    {
                        ::mega::MegaSyncStats& stats = *it->second;
                        if (stats.isScanning())
                        {
                            s = "Scanning";
                        }
                        else if (stats.isSyncing())
                        {
                            s = "Syncing";
                        }
                        else
                        {
                            s = "Monitoring";
                        }
                    }
                }
            }
            return QString::fromStdString(s);
        }
        break;
    case Column_FILES:
        if(role == Qt::DisplayRole)
        {
            auto it = mSyncInfo->mSyncStatsMap.find(sync->backupId());
            if (it != mSyncInfo->mSyncStatsMap.end())
            {
                ::mega::MegaSyncStats& stats = *it->second;
                return QString::fromStdString(std::to_string(stats.getFileCount()));
            }
        }
        break;
    case Column_FOLDERS:
        if(role == Qt::DisplayRole)
        {
            auto it = mSyncInfo->mSyncStatsMap.find(sync->backupId());
            if (it != mSyncInfo->mSyncStatsMap.end())
            {
                ::mega::MegaSyncStats& stats = *it->second;
                return QString::fromStdString(std::to_string(stats.getFolderCount()));
            }
        }
        break;
    case Column_DOWNLOADS:
        if(role == Qt::DisplayRole)
        {
            auto it = mSyncInfo->mSyncStatsMap.find(sync->backupId());
            if (it != mSyncInfo->mSyncStatsMap.end())
            {
                ::mega::MegaSyncStats& stats = *it->second;
                return QString::fromStdString(std::to_string(stats.getDownloadCount()));
            }
        }
        break;
    case Column_UPLOADS:
        if(role == Qt::DisplayRole)
        {
            auto it = mSyncInfo->mSyncStatsMap.find(sync->backupId());
            if (it != mSyncInfo->mSyncStatsMap.end())
            {
                ::mega::MegaSyncStats& stats = *it->second;
                return QString::fromStdString(std::to_string(stats.getUploadCount()));
            }
        }
        break;
    case Column::MENU:

        if(role == Qt::DecorationRole)
        {
            QIcon dotsMenu;
            dotsMenu.addFile(QLatin1String("://images/icons/options_dots/options-rest.png"), QSize(ICON_SIZE, ICON_SIZE), QIcon::Normal);
            dotsMenu.addFile(QLatin1String("://images/icons/options_dots/options-press.png"), QSize(ICON_SIZE, ICON_SIZE), QIcon::Selected);
            dotsMenu.addFile(QLatin1String("://images/icons/options_dots/options-hover.png"), QSize(ICON_SIZE, ICON_SIZE), QIcon::Active);
            return dotsMenu;
        }
        else if(role == Qt::ToolTipRole)
            return tr("Click menu for more Sync actions");
        else if(role == Qt::TextAlignmentRole)
            return QVariant::fromValue<Qt::Alignment>(Qt::AlignHCenter);
        break;
    }
    return QVariant();
}

bool SyncItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || (index.column() != Column::ENABLED))
        return false;

    if ((role == Qt::CheckStateRole) || (role == Qt::EditRole))
    {
        auto sync = mList.at(index.row());
        if(!sync)
        {
            return false;
        }
        if (value.toInt() == Qt::Checked)
            emit signalSyncCheckboxOn(sync);
        else if (value.toInt() == Qt::Unchecked)
            emit signalSyncCheckboxOff(sync);
        emit dataChanged(index, index, QVector<int>(role));
        return true;
    }

    return false;
}

void SyncItemModel::fillData()
{
    setMode(mega::MegaSync::SyncType::TYPE_TWOWAY);
}

void SyncItemModel::insertSync(std::shared_ptr<SyncSettings> sync)
{
    if(mList.contains(sync))
    {
        for(auto it = mList.cbegin(); it!=mList.cend();++it)
        {
            if((*it) == sync)
            {
                int pos = it - mList.cbegin();
                sendDataChanged(pos);
                break;
            }
        }
    }
    else
    {
        if(sync->getType() == mSyncType)
        {
            beginInsertRows(QModelIndex(), mList.size(), mList.size());
            mList.append(sync);
            endInsertRows();
        }
    }
    emit syncUpdateFinished(sync);
}

void SyncItemModel::updateSyncStats(std::shared_ptr<::mega::MegaSyncStats> stats)
{
    for(auto it = mList.cbegin(); it!=mList.cend();++it)
    {
        if((*it)->backupId() == stats->getBackupId())
        {
            int pos = it - mList.cbegin();
            sendDataChanged(pos);
            break;
        }
    }
}

void SyncItemModel::removeSync(std::shared_ptr<SyncSettings> sync)
{
    if(mList.contains(sync))
    {
        for(auto it = mList.cbegin(); it!=mList.cend();++it)
        {
            if((*it) == sync)
            {
                int pos = it - mList.cbegin();
                beginRemoveRows(QModelIndex(), pos, pos);
                mList.removeOne((*it));
                endRemoveRows();
                break;
            }
        }
    }
    emit syncUpdateFinished(sync);
}

void SyncItemModel::sendDataChanged(int row)
{
    emit dataChanged(index(row, Column::ENABLED, QModelIndex()),
                     index(row, Column::MENU, QModelIndex()),
                     QVector<int>()<< Qt::CheckStateRole << Qt::DecorationRole << Qt::ToolTipRole);
}


QList<std::shared_ptr<SyncSettings> > SyncItemModel::getList() const
{
    return mList;
}

void SyncItemModel::setList(QList<std::shared_ptr<SyncSettings> > list)
{
    mList = list;
}

void SyncItemModel::setMode(mega::MegaSync::SyncType syncType)
{
    mSyncType = syncType;
    setList(mSyncInfo->getSyncSettingsByType(mSyncType));
}

mega::MegaSync::SyncType SyncItemModel::getMode()
{
    return mSyncType;
}

SyncItemSortModel::SyncItemSortModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    mQCollator.setNumericMode(true);
    mQCollator.setCaseSensitivity(Qt::CaseInsensitive);
}

bool SyncItemSortModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(source_left.flags().testFlag(Qt::ItemIsUserCheckable)
            && source_right.flags().testFlag(Qt::ItemIsUserCheckable))
    {
        auto stateLeft (source_left.data(Qt::CheckStateRole).toInt());
        auto stateRight (source_right.data(Qt::CheckStateRole).toInt());
        if (stateLeft != stateRight)
        {
            return stateLeft > stateRight;

        }
    }

    return mQCollator.compare(source_left.data(Qt::DisplayRole).toString(),
                              source_right.data(Qt::DisplayRole).toString()) < 0;
}
