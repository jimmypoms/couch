import QtQuick 2.4

import "../controls"

ItemDelegate {
    highlighted: ListView.isCurrentItem
    width: ListView.view ? ListView.view.width : implicitWidth
}
