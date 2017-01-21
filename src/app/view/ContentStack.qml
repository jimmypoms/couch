import QtQuick 2.4

ContentStackForm {
    id: control

    function loadDetail(component, properties) {
        push(component, properties);
    }

    Keys.onBackPressed: pop()
    Keys.onEscapePressed: pop()
}
