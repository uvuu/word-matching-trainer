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

        onWidthChanged: rep.update()

        Repeater {
            id: rep
            model: performer.task

            Label {
                text: modelData //+ " "
                wrapMode: Label.Wrap
                horizontalAlignment: Label.AlignHCenter
                color: getColor()

                function getColor()
                {
                    let color = "white";
                    if (modelData[0] === "[")
                    {
                        color = (performer.remainingTime != 0) ? "transparent" : "yellow";
                    }

                    return color;
                }

                Component.onCompleted: {
                    // Set the gap width
                    if (modelData[0] === "[")
                    {
                        width = performer.getAnswerLength()
                    }


                    text = text.replace('[', '').replace(']', '')
                    rep.update()
                }

                Rectangle {
                    id: gapUnderscore
                    visible: modelData[0] === '['

                    //anchors.leftMargin: parent.leftPadding
                    //anchors.bottomMargin: -2 // underscore height
                    //anchors.topMargin: parent.height
                    //anchors.fill: parent

                    anchors.top: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 2

                    z: parent.z - 1
                }
            }

            function update() {
                let arr = [];

                for (var i = 0; i < rep.count; i++)
                {
                    var item = rep.itemAt(i)
                    if (item)
                    {
                        item.leftPadding = 0
                    }
                    task.forceLayout()
                }

                for (var i = 0; i < rep.count; i++)
                {
                    var item = rep.itemAt(i)
                    if (!item)
                        continue

                    var row = item.y / item.height

                    if (arr[row] == null)
                        arr[row] = { "length" : item.width, "first" : i }
                    else
                        arr[row]["length"] += item.width
                }

                for (const r of arr)
                {
                    rep.itemAt(r.first).leftPadding = (task.width - r.length) / 2
                }
            }
        }
    }
}
