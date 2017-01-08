import QtQuick 2.7
import Couch 1.0

QtObject {
    property variant music: QtObject {
        id: music
        property string name: "music"
        property QtObject localProvider: QtObject {
            id: localMusicProvider
            property string name: "local"
        }
        
        property variant providers: [
            localMusicProvider
        ]
    }

    property variant services: [
        music
    ]
}