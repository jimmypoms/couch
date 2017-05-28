import QtQuick 2.4
import Qt.labs.folderlistmodel 2.1
import "../components"
import "../controls"

FolderSettingForm {
    Component.onCompleted: {
        var paths = [];
        var tmp = setting.value.split('/');
        var current = '';
        for (var i = 0; i < tmp.length - 1; ++i) {
            current += tmp[i] + '/';
            var list = stack.push(folderListComponent, {
                folder: current,
                initialSelection: tmp[i+1]
            });
        }
    }
    stack.onCurrentItemChanged: currentFolderListModel = stack.currentItem.model

    Component {
        id: folderListComponent

        ListView {
            id: folderListView

            property string folder: ''
            property alias initialSelection: folderListModel.initialSelection

            x: actionsPane.contentItem.x
            y: actionsPane.contentItem.y
            width: actionsPane.contentItem.width
            height: actionsPane.contentItem.height

            displayMarginBeginning: actionsPane.height / 2
            displayMarginEnd: actionsPane.height / 2
            preferredHighlightBegin: actionsPane.height / 2
            preferredHighlightEnd: preferredHighlightBegin + 48
            highlightRangeMode: ListView.StrictlyEnforceRange

            Keys.onLeftPressed: stack.pop()
            Keys.onRightPressed: {
                if (!currentItem) {
                    event.accepted = false;
                    return;
                }

                stack.push(folderListComponent, {
                    folder: folderListView.folder + currentItem.text + '/'
                })
            }

            model: FolderListModel {
                id: folderListModel

                property bool initialized: false
                property string initialSelection: ''

                folder: "file://" + folderListView.folder

                showDirs: true
                showDirsFirst: true
                showDotAndDotDot: false
                showFiles: false
                showHidden: false
                showOnlyReadable: true

                onCountChanged: {
                    if (count > 0 && !initialized) {
                        var index = indexOf(folder + initialSelection);
                        folderListView.currentIndex = index > 0 ? index : 0;
                        initialized = true;
                    }
                }
            }

            delegate: MenuItem {
                text: fileName
            }

            MediumLabel {
                id: emptyLabel

                anchors.topMargin: 48
                anchors.fill: parent
                //% "This folder is empty. Press the selection key to choose '%1'."
                text: qsTrId("settings.widget.folder.empty.select(%1)").arg(selectedFolder)
                secondary: true
                wrapMode: Text.Wrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                visible: false
            }

            states: [
                State {
                    name: "empty"
                    when: !folderListView.model || folderListView.model.count === 0
                    PropertyChanges {
                        target: emptyLabel
                        visible: true
                    }
                }
            ]
        }
    }
}
