import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    Component.onCompleted: performer.run()

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
        text: performer.exerciseName
        anchors.right: parent.right
        anchors.verticalCenter: back.verticalCenter
    }

    Label {
        text: (performer.remainingTime / 1000).toFixed(1) // Show only one digit after point
        anchors.horizontalCenter: task.horizontalCenter
        anchors.bottom: task.top
        anchors.bottomMargin: 30
    }

    Flow {
        id: task

        anchors.centerIn: parent
        width: parent.width

        onWidthChanged: wordsSet.alignWords()

        Repeater {
            id: wordsSet

            model: performer.task

            function alignWords() {
                let rowsData = [];
                for (var i = 0; i < wordsSet.count; i++) {
                    let item = wordsSet.itemAt(i)
                    if (!item) {
                        continue
                    }

                    item.leftPadding = 0
                    task.forceLayout()

                    const row = item.y / item.height
                    if (rowsData[row] === undefined) {
                        rowsData[row] = { "length" : item.width, "first" : i }
                    } else {
                        rowsData[row].length += item.width
                    }
                }

                for (const rowData of rowsData) {
                    wordsSet.itemAt(rowData.first).leftPadding = (task.width - rowData.length) / 2
                }
            }

            Label {
                property bool isExercisedWord: modelData[0] === "["

                text: modelData
                wrapMode: Label.Wrap
                horizontalAlignment: Label.AlignHCenter
                color: {
                    if (isExercisedWord) {
                        (performer.remainingTime != 0) ? "transparent" : "yellow"
                    } else {
                        "white"
                    }
                }

                Component.onCompleted: {
                    text = text.replace('[', '').replace(']', '')
                    // Set the gap width
                    if (isExercisedWord) {
                        width = performer.getMaxAnswerLength()
                    }
                    wordsSet.alignWords()
                }

                Rectangle {
                    visible: parent.isExercisedWord
                    anchors.top: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 2
                    z: parent.z - 1
                }
            }
        }
    }
}
