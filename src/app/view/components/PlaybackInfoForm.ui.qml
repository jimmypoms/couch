import QtQuick 2.4

import "../controls"

Column {
    property variant currentItem

    spacing: 16

    LargeLabel {
        text: currentItem ? currentItem.name : ""
    }

    MediumLabel {
        text: currentItem ? currentItem.metadata.artist + " - " + currentItem.metadata.album : ""
    }
}
