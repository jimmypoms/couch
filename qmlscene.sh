#!/bin/bash

FILE=./src/app/view/qtquickcontrols2.conf
STYLE=$(awk -F "=" '/Style/ {print $2}' $FILE)
THEME=$(awk -F "=" '/Theme/ {print $2}' $FILE)
ACCENT=$(awk -F "=" '/Accent/ {print $2}' $FILE)
PRIMARY=$(awk -F "=" '/Primary/ {print $2}' $FILE)
BACKGROUND=$(awk -F "=" '/Background/ {print $2}' $FILE)
FOREGROUND=$(awk -F "=" '/Foreground/ {print $2}' $FILE)

QT_QUICK_CONTROLS_MATERIAL_THEME=$THEME QT_QUICK_CONTROLS_MATERIAL_ACCENT=$ACCENT QT_QUICK_CONTROLS_MATERIAL_PRIMARY=$PRIMARY QT_QUICK_CONTROLS_MATERIAL_FOREGROUND=$FOREGROUND QT_QUICK_CONTROLS_MATERIAL_BACKGROUND=$BACKGROUND qmlscene -style $STYLE -I imports/ src/app/view/Application.qml "$@"
