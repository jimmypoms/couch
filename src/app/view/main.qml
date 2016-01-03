import QtQuick 2.2
import QtQuick.Controls 1.2
import QtMultimedia 5.0

import "components"
import "playback"
import "content"
import org.couch.player 1.0
import org.couch.filter.movie 1.0

ApplicationWindow {
    id: applicationWindow

    property color backgroundColor: "#193441"
    property color focusColor: "grey"

    visible: true
    visibility: "FullScreen"
    flags: Qt.FramelessWindowHint
    width: dp(1024)
    height: dp(768)

    Item {
        id: application
        anchors.fill: parent

        Background {
            id: backgroundView
            anchors.fill: parent
            color: backgroundColor
        }
        Loading {
            id: loadingView
            anchors.fill: parent
            opacity: 0
            visible: false
            enabled: false
        }
        Player {
            id: playerView
            anchors.fill: parent
            opacity: 0
            visible: false
            enabled: false

            onBackClicked: {
                player.stop();
            }
        }
        Rectangle {
            id: curtain
            anchors.fill: parent
            color: "black"
            opacity: 0.5
        }
        CouchTabView {
            id: tabView
            focus: true
            visible: true
            anchors.fill: parent
            tabbarBackground: Item {
                Rectangle {
                    anchors.fill: parent
                    color: "#193441"
                }
                Rectangle {
                    anchors.fill: parent
                    color: "black"
                    opacity: 0.5
                }
            }
            rightCorner: CouchWindowControls {
            }
            tabbarDelegate: Item {
                width: Math.max(implicitWidth + dp(10), application.width * 0.15)
                height: dp(40)

                Rectangle {
                    anchors.fill: parent
                    visible: ! styleData.selected
                    color: "#193441"
                }
                Rectangle {
                    anchors.fill: parent
                    visible: ! styleData.selected
                    color: "black"
                    opacity: 0.5
                }
                Rectangle {
                    anchors.fill: parent
                    color: styleData.selected && styleData.item ? styleData.item.highlightColor : "transparent"
                    opacity: styleData.item ? styleData.item.highlightOpacity : 1
                }
                CouchButton {
                    id: button
                    anchors.fill: parent
                    color: "transparent"
                    fontColor: "white"
                    fontWeight: Font.Bold
                    fontPointSize: fp(11)
                    text: styleData.title

                    onClicked: {
                        tabView.currentIndex = styleData.index;
                    }
                }
                onActiveFocusChanged: {
                    if (activeFocus) {
                        button.forceActiveFocus();
                    }
                }
            }
        }
        Notifications {
            id: notifications
            anchors.top: parent.top
            anchors.topMargin: dp(100)
            anchors.horizontalCenter: parent.horizontalCenter
            height: dp(80)
            width: parent.width * 0.7
        }

        Connections {
            target: player
            onError: {
                console.log('player error', player.error);
                notifications.error(qsTr(player.error));
            }
        }

        function hideBackground() {
            backgroundView.visible = false;
            backgroundView.enabled = false;
        }
        function showBackground() {
            backgroundView.visible = true;
            backgroundView.enabled = true;
        }
        function hidePlayer() {
            showBackground();
            playerView.opacity = 0;
            playerView.visible = false;
            playerView.enabled = false;
        }
        function showPlayer() {
            hideBackground();
            playerView.opacity = 1;
            playerView.visible = true;
            playerView.enabled = true;
            playerView.forceActiveFocus();
        }
        function hideLoading() {
            loadingView.opacity = 0;
            loadingView.visible = false;
            loadingView.enabled = false;
        }
        function showLoading() {
            showBackground();
            loadingView.opacity = 1;
            loadingView.visible = true;
            loadingView.enabled = true;
            loadingView.forceActiveFocus();
        }
        function hideMenu() {
            curtain.opacity = 0;
            curtain.enabled = false;
            tabView.opacity = 0;
            tabView.enabled = false;
        }
        function showMenu() {
            showBackground();
            curtain.opacity = 0.5;
            curtain.enabled = true;
            tabView.opacity = 1;
            tabView.enabled = true;
            tabView.forceActiveFocus();
        }
        function load() {
            console.log("loading state");
            showLoading();
            hideMenu();
            hidePlayer();
        }
        function play() {
            console.log("playing state");
            hideLoading();
            hideMenu();
            showPlayer();
        }
        function pause() {
            console.log("pausing state");
            hideLoading();
            showMenu();
            showPlayer();
        }
        function stop() {
            console.log("stopping state");
            hideLoading();
            hidePlayer();
            showMenu();
        }
        function buffer() {
            console.log("buffering state");
            hideLoading();
            hideMenu();
            showPlayer();
        }

        states: [
            State {
                name: "playing"
                when: (player.playbackStatus == CouchPlayer.Playing)
                StateChangeScript {
                    script: application.play()
                }
            },
            State {
                name: "paused"
                when: (player.playbackStatus == CouchPlayer.Paused)
                StateChangeScript {
                    script: application.pause()
                }
            },
            State {
                name: "stopped"
                when: (player.playbackStatus == CouchPlayer.Stopped)
                StateChangeScript {
                    script: application.stop()
                }
            },
            State {
                name: "buffering"
                when: (player.sourceStatus == CouchPlayer.Buffering)
                StateChangeScript {
                    script: application.buffer()
                }
            },
            State {
                name: "loading"
                when: (player.sourceStatus == CouchPlayer.Loading)
                StateChangeScript {
                    script: application.load()
                }
            }
        ]
    }

    Component.onCompleted: {
        var services = couch.services,
            serviceCount = services.length;
        if (serviceCount === 0) {
            var component = Qt.createComponent("components/CouchInfoBox.qml");
            var info = component.createObject(tabView, {
                text: qsTr("no services loaded"),
                'anchors.fill': tabView
            });
            if (info == null) {
                console.log("Error creating object: "+component.errorString());
            }
        }

        for (var i = 0; i < serviceCount; ++ i) {
            var service = services[i];
            var component = Qt.createComponent(service.name + "/main.qml");

            var tab = tabView.addTab(qsTr(service.name), component);
        }
    }

    function dp(dpVal) {
        var px = Math.round(dpVal * (screenPixelDensity / 160));

        if (Qt.platform.os == "windows" || Qt.platform.os == "mac")
            return px * 2;
        else
            return px;
    }

    function fp(dpVal) {
        var px = Math.round(dpVal * (screenPixelDensity / 190));

        if (Qt.platform.os == "windows" || Qt.platform.os == "mac")
            return px * 2;
        else
            return px;
    }

    function formatMicroseconds(microseconds) {
        var seconds = Math.floor(microseconds / 1000);
        var hours   = Math.floor(seconds / 3600);
        var minutes = Math.floor((seconds - (hours * 3600)) / 60);
        seconds = seconds - (hours * 3600) - (minutes * 60);

        if (hours < 10) {hours = '0'+hours;}
        if (minutes < 10) {minutes = '0'+minutes;}
        if (seconds < 10) {seconds = '0'+seconds;}
        if (hours != '00') {
            return hours+':'+minutes+':'+seconds;
        }
        return minutes+':'+seconds;
    }

    function formatMinutes(minutes) {
        var hours   = Math.floor(minutes / 60);
        var minutes = Math.floor(minutes - (hours * 60));

        if (hours < 10) {hours = '0'+hours}
        if (minutes < 10) {minutes = '0'+minutes}
        return hours+':'+minutes;
    }
}
