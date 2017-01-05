import QtQuick 2.4
import QtQuick.Layouts 1.3
import "../controls"

FocusScope {
    id: control

    readonly property int typeAlphabetical: 0
    readonly property int typeNumerical: 1
    property alias type: listview.currentIndex

    signal clicked(string character);
    signal backspace();

    RowLayout {
        anchors.fill: parent

        Button {
            id: typeButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            text: "123"

            onClicked: {
                control.type = control.type === control.typeAlphabetical ? control.typeNumerical : control.typeAlphabetical;
            }

            Behavior on text {
                SequentialAnimation {
                    PauseAnimation {
                        duration: 100
                    }
                    PropertyAction {}
                    PauseAnimation {
                        duration: 100
                    }
                }
            }
        }

        ListView {
            id: listview

            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: 0
            preferredHighlightEnd: 0
            orientation: ListView.Vertical
            interactive: true
            focus: true
            model: [
                ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', ' '],
                ['0','1','2','3','4','5','6','7','8','9','.']
            ]

            delegate: ListView {
                spacing: 5
                orientation: ListView.Horizontal
                anchors.horizontalCenter: parent.horizontalCenter
                model: modelData
                height: listview.height
                width: contentWidth
                delegate: Button {
                    property string character: modelData
                    text: modelData === ' ' ? 'space' : modelData.toUpperCase()

                    onClicked: {
                        control.clicked(character);
                    }
                }
            }

            KeyNavigation.left: typeButton
            KeyNavigation.right: backspace
        }

        Button {
            id: backspace

            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            text: 'backspace'

            onClicked: {
                control.backspace();
            }
        }
    }

    states: [
        State {
            name: "numerical"
            when: control.type === control.typeNumerical
            PropertyChanges {
                target: typeButton
                text: "ABC"
            }
        }
    ]
}
