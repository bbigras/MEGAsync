// System
import QtQuick 2.15

// Local
import Components.Texts 1.0 as MegaTexts

QtObject {

    // Medium sizes
    property int padding: 8
    property int height: 36
    property int titleBottomMargin: 4
    property int iconMargin: 13
    property int iconWidth: 16
    property size iconSize: Qt.size(iconWidth, iconWidth)
    property int iconTextSeparation: 6
    property int focusBorderRadius: 11
    property int focusBorderWidth: 3
    property int borderRadius: 8
    property int borderWidth: 1
    property int hintTextSize: MegaTexts.Text.Size.Normal
    property int titleSpacing: 1

}
