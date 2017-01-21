import QtQuick 2.7
import Couch 1.0

QtObject {
    id: object
    
    property variant currentItem
    property variant currentSource
    property int duration: 336000
    property int position: 50000
    property bool playing: false
    property bool hasPrevious: false
    property bool hasNext: true
    property variant sourceStatus: Player.Ready
    property variant playbackStatus: Player.Stopped
    property string error: ""
    
    function play(item) {
        if (item) {
            currentItem = item;
        }
        playbackStatus = Player.Playing;
        playing = true;
    }
    
    function pause() {
        playbackStatus = Player.Paused;
        playing = false;
    }
    
    function stop() {
        currentItem = null;
        currentSource = null;
        playbackStatus = Player.Stopped;
        playing = false;
    }
    
    function togglePlay() {
        if (playing) {
            pause();
        } else {
            play();
        }
    }
    
    function seek(position) {
        position = position;
    }
    
    function previous() {
    }
    
    function next() {
    }
}