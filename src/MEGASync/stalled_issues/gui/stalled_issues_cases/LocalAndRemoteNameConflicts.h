#ifndef LOCALANDREMOTENAMECONFLICTS_H
#define LOCALANDREMOTENAMECONFLICTS_H

#include "StalledIssueBaseDelegateWidget.h"

namespace Ui {
class LocalAndRemoteNameConflicts;
}

class LocalAndRemoteNameConflicts : public StalledIssueBaseDelegateWidget
{
    static const QString FILES_DESCRIPTION;
    static const QString FOLDERS_DESCRIPTION;
    static const QString FILES_AND_FOLDERS_DESCRIPTION;

    Q_OBJECT

    std::shared_ptr<mega::MegaSyncStall> originalStall;

public:
    explicit LocalAndRemoteNameConflicts(std::shared_ptr<mega::MegaSyncStall> originalstall, QWidget *parent = nullptr);
    ~LocalAndRemoteNameConflicts();

public slots:
    void refreshUi() override;

private slots:
    void onNameConflictSolved();

private:
    Ui::LocalAndRemoteNameConflicts *ui;
};

#endif // LOCALANDREMOTENAMECONFLICTS_H
