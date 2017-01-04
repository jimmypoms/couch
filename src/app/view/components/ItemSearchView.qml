import QtQuick 2.4

ItemSearchViewForm {
    Behavior on opacity {
        SmoothedAnimation {
            duration: 200
        }
    }

    onFilterChanged: {
        searchField.textChanged.connect(function() {
            filter.text = searchField.text;
        });
    }

    Component.onCompleted: {
        filter.textChanged.connect(search);
    }

    transitions: [
        Transition {
            from: ""
            to: "searchVisible"
            reversible: true
            AnchorAnimation {
                duration: 200
            }
        }
    ]

    function search() {
        // TODO
        list.model = service.load(filter);
    }
}
