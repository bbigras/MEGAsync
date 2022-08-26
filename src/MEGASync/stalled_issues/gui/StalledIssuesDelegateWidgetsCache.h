#ifndef STALLEDISSUEHEADERWIDGETMANAGER_H
#define STALLEDISSUEHEADERWIDGETMANAGER_H

#include "StalledIssue.h"
#include "megaapi.h"

#include <QMap>
#include <QModelIndex>
#include <QPointer>

class StalledIssueHeader;
class StalledIssueFilePath;
class StalledIssuesProxyModel;
class StalledIssueBaseDelegateWidget;

class StalledIssuesDelegateWidgetsCache
{
public:
    StalledIssuesDelegateWidgetsCache();

    StalledIssueHeader* getStalledIssueHeaderWidget(const QModelIndex& index, QWidget *parent, const StalledIssueVariant &issue) const;
    StalledIssueBaseDelegateWidget* getStalledIssueInfoWidget(const QModelIndex& index, QWidget *parent, const StalledIssueVariant &issue) const;

    StalledIssueHeader* getNonCacheStalledIssueHeaderWidget(const QModelIndex &index, QWidget *parent, const StalledIssueVariant &issue) const;
    StalledIssueBaseDelegateWidget* getNonCacheStalledIssueInfoWidget(const QModelIndex& index, QWidget *parent, const StalledIssueVariant &issue) const;

    static bool adaptativeHeight(mega::MegaSyncStall::SyncStallReason reason);

    void setProxyModel(StalledIssuesProxyModel *proxyModel);

    void reset();

private:
    mutable QMap<int, QPointer<StalledIssueHeader>> mStalledIssueHeaderWidgets;
    mutable QMap<int, QMap<int, QPointer<StalledIssueBaseDelegateWidget>>> mStalledIssueWidgets;

    StalledIssueBaseDelegateWidget* createBodyWidget(const QModelIndex& index, QWidget *parent, const StalledIssueVariant &issue) const;
    StalledIssueHeader* createHeaderWidget(const QModelIndex& index, QWidget *parent, const StalledIssueVariant &issue) const;

    StalledIssuesProxyModel* mProxyModel;
};

#endif // STALLEDISSUEHEADERWIDGETMANAGER_H
