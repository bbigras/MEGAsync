// System
import QtQuick 2.15

// Local
import Common 1.0
import Components.Texts 1.0 as MegaTexts

MegaTexts.Text {
    id: control

    function updateLinkColor() {
        var color = Styles.linkPrimary;
        if(!enabled) {
            color = Styles.notificationInfo;
        } else if(visited) {
            color = Styles.linkVisited;
        }
        control.text = control.text.replace("color:" + urlColor, "color:" + color);
        urlColor = color;
    }

    readonly property url defaultUrl: "default"

    property url url: defaultUrl
    property bool manageMouse: false
    property bool hovered: false
    property bool manageHover: false
    property bool visited: false
    property color urlColor: Styles.linkPrimary
    property string rawText: ""

    color: enabled ? Styles.textPrimary : Styles.textDisabled
    textFormat: Text.RichText

    // We are using rawText to avoid breaking internal connections in the text property.
    // If we assign a string directly to the RichText text property and we use the replace
    // javascript function (we modify the text), then when the text is updated, it is not
    // refreshed internally. We cannot assign other varaible and change it here at the
    // same time. For more info, please see SNC-3917.
    onRawTextChanged: {
        var copyText = rawText;
        copyText = copyText.replace("[B]","<b>");
        copyText = copyText.replace("[/B]","</b>");
        copyText = copyText.replace("[A]", "<a style=\"text-decoration:none\"
                                            style=\"color:" + urlColor + ";\" href=\"" + url + "\">");
        copyText = copyText.replace("[/A]","</a>");
        control.text = copyText;
    }

    onLinkActivated: {
        if(url != defaultUrl) {
            Qt.openUrlExternally(url);
            visited = true;
            updateLinkColor();
        }
    }

    onLinkHovered: {
        hovered = link.length;
    }

    onEnabledChanged: {
        updateLinkColor();
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        cursorShape: hovered ? Qt.PointingHandCursor : Qt.ArrowCursor
        onPressed: mouse.accepted = false;
        enabled: control.manageMouse
        hoverEnabled: control.manageHover
    }
}
