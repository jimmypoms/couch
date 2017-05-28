import QtQuick 2.4

MenuPage {
    content: actions

    readonly property alias list: actions
    property alias model: actions.model
    property alias delegate: actions.delegate
    property alias menuItems: actionsModel.children

    ListView {
        id: actions

        x: actionsPane.contentItem.x
        y: actionsPane.contentItem.y
        width: actionsPane.contentItem.width
        height: actionsPane.contentItem.height

        displayMarginBeginning: actionsPane.height / 2
        displayMarginEnd: actionsPane.height / 2
        preferredHighlightBegin: actionsPane.height / 2
        preferredHighlightEnd: preferredHighlightBegin + 48
        highlightRangeMode: ListView.StrictlyEnforceRange

        focus: true
        model: VisualItemModel {
            id: actionsModel
        }
    }
}
