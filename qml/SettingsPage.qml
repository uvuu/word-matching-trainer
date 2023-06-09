import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import Qt.labs.settings 1.0

import "components"

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
            id: dataFile

            text: DefaultSettings.dataFile
            color: "#60ABF6"

            MouseArea {
                anchors.fill: parent
                onClicked: console.log(parent.text)
            }

            Binding {
                target: DefaultSettings
                property: "dataFile"
                value: dataFile.text
            }
        }

        Label {
            text: "Use maximum gap:"
            Layout.fillWidth: true
        }

        CheckBox {
            id: maximumGap

            checked: DefaultSettings.useMaximumGap

            Binding {
                target: DefaultSettings
                property: "useMaximumGap"
                value: maximumGap.checked
            }
        }

        Label {
            text: "Answer color:"
            Layout.fillWidth: true
        }

        ColorTextInput {
            id: answerColor

            color: DefaultSettings.answerColor

            Binding {
                target: DefaultSettings
                property: "answerColor"
                value: answerColor.color
            }
        }
    }
}
