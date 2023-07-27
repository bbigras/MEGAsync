import QtQuick 2.0
import QtQuick.Dialogs 1.3

Item {
    id: root

    property string textForTextField: ""
    property url selectedUrl: ""

    signal folderChanged(string folder)

    function openFolderSelector() {
        console.debug("mockup ChooseLocalFolder::openFilePicker()");
        fileDialog.open();
    }

    function getFolder() {
        console.debug("mockup ChooseLocalFolder::getFolder() : selectedUrl -> " + selectedUrl);
        return selectedUrl;
    }

    function reset() {
        console.debug("mockup ChooseLocalFolder::reset()");
        selectedUrl = "";
        folderChanged("");
    }

    FileDialog {
        id: fileDialog

        title: "Please choose a folder"
        folder: shortcuts.documents
        selectFolder: true
        onAccepted: {
            textForTextField =
                fileDialog.fileUrl.toString().slice(fileDialog.fileUrl.toString().lastIndexOf("/"));
            selectedUrl = fileDialog.fileUrl;
            root.folderChanged(textForTextField);
        }
    }
}
