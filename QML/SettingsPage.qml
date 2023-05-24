import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    FlatButton {
        id: back

        width: contentWidth + contentSpacing * 2
        text: "Back"

        onClicked: {
            performer.stop()
            stackView.pop()
        }
    }

    Label {
        text: "Settings page"
        anchors.centerIn: parent
    }
}
