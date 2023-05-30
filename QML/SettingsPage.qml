import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

Item {

    Pane {
          anchors.fill: parent
          focusPolicy: Qt.ClickFocus
    }

    FlatButton {
        id: back

        width: contentWidth + contentSpacing * 2
        text: "Back"

        onClicked: {
            performer.stop()
            stackView.pop()
        }
    }

    GridLayout {
        columns: 2
        anchors.top: back.bottom
        anchors.topMargin: 20

        Label {
            text: "Data file:"
            Layout.fillWidth: true
        }

        Label {
            text: "data.txt"
            color: "#60ABF6"

            MouseArea {
                anchors.fill: parent
                onClicked: console.log(parent.text)
            }
        }

        Label {
            text: "Maximum gap:"
            Layout.fillWidth: true
        }

        CheckBox {
            checked: true
        }

        Label {
            text: "Answer color:"
            Layout.fillWidth: true
        }

        ColorTextInput {}
    }
}
