import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: button

    property alias text: label.text
    property alias textColor: label.color
    property alias contentWidth: label.contentWidth
    property alias contentSpacing: label.font.pixelSize

    signal clicked()

    implicitWidth: parent ? parent.width : 0
    implicitHeight: contentSpacing * 3
    border.color: label.color
    border.width: 1
    color: "transparent"
    radius: 5

    Label {
        id: label

        text: ""
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent

        onClicked: button.clicked()
    }
}
