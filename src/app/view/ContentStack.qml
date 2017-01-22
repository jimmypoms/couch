import QtQuick 2.4

ContentStackForm {
    function loadDetail(component, properties) {
        push(component, properties);
    }
}
