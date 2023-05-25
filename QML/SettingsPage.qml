import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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

    ColumnLayout {
        anchors.top: back.bottom
        anchors.topMargin: 20
        //width: parent.width

        RowLayout {
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
        }
    }
}
