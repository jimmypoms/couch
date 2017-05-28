import QtQuick 2.4
import Qt.labs.folderlistmodel 2.1
import "../components"
import "../controls"

MenuPage {
    description: selectedFolder
    //% "Use the arrow keys to navigate. Use the selection key to choose the current folder."
    additionalDescription: qsTrId("settings.widget.folder.navigation")
    content: folderStack

    property FolderListModel currentFolderListModel: null
    property string selectedFolder: currentFolderListModel.folder.toString().replace(/^file:\/{2}/, '');
    property variant setting: QtObject {}
    readonly property alias folderStack: folderStack

    StackView {
        id: folderStack

        x: actionsPane.contentItem.x
        y: actionsPane.contentItem.y
        width: actionsPane.contentItem.width
        height: actionsPane.contentItem.height

        clip: true
        focus: true
        Keys.onBackPressed: event.accepted = false;
        Keys.onEscapePressed: event.accepted = false;
    }
}
