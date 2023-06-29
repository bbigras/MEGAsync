// System
import QtQuick 2.12
import QtQuick.Controls 2.12

// Local
import Onboard 1.0
import Onboard.Syncs_types.Left_panel 1.0

// C++
import BackupsProxyModel 1.0

StackView {
    id: backupsFlow

    readonly property string selectBackup: "selectBackup"
    readonly property string confirmBackup: "confirmBackup"

    state: selectBackup
    states: [
        State {
            name: selectBackup
            StateChangeScript {
                script: backupsFlow.replace(selectBackupFoldersPage);
            }
            PropertyChanges {
                target: stepPanel;
                state: stepPanel.step3;
                step3Text: OnboardingStrings.backupSelectFolders;
                step4Text: OnboardingStrings.confirm;
            }
        },
        State {
            name: confirmBackup
            StateChangeScript {
                script: backupsFlow.replace(confirmBackupFoldersPage);
            }
            PropertyChanges {
                target: stepPanel;
                state: stepPanel.step4;
                step3Text: OnboardingStrings.backupSelectFolders;
                step4Text: OnboardingStrings.backupConfirm;
            }
        }
    ]

    BackupsProxyModel {
        id: backupsProxyModel
    }

    Component {
        id: selectBackupFoldersPage

        SelectFoldersPage {
        }
    }

    Component {
        id: confirmBackupFoldersPage

        ConfirmFoldersPage {
        }
    }

}
