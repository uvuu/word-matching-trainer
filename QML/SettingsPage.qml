import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

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

    GridLayout {
        columns: 2
        anchors.top: back.bottom
        anchors.topMargin: 20
        //width: parent.width

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

        Rectangle {
            color: "yellow"
            height: 20
            width: height

            MouseArea {
                anchors.fill: parent
                onClicked: colorDialog.open()
            }

            //TODO: This dialog is available without additional actions only for a few platforms:
            // Linux, Windows, and MacOS. For other platforms(e.g. Android), there is no native dialog and
            // we have to use the Qt implementations from Widgets. To do that, it is necessary
            // to add Widgets module via CMake and use QApplication instead of QGuiApplication.
            // For further information, refer to https://doc.qt.io/qt-6/qml-qt-labs-platform-colordialog.html.
            ColorDialog {
                id: colorDialog

                title: "Please choose a color"
                onAccepted: {
                    console.log("You chose: " + colorDialog.color)
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
        }
    }
}
