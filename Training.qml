import QtQuick 2.12
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

    Label {
        text: performer.exerciseName
        anchors.right: parent.right
        anchors.verticalCenter: back.verticalCenter
    }

    Label {
        text: (performer.remainingTime / 1000).toFixed(1) // We want to see ms here
        anchors.horizontalCenter: task.horizontalCenter
        anchors.bottom: task.top
        anchors.bottomMargin: 30
    }

//    Label {
//        id: task

//        text: performer.task
//        // Split a row into multiple and center them
//        wrapMode: Label.Wrap
//        horizontalAlignment: Label.AlignHCenter
//        anchors.centerIn: parent
//        width: parent.width
//    }

    Flow {
//            anchors.fill: parent
//            anchors.margins: 4
//            spacing: 10
        id: task
        anchors.centerIn: parent
        width: parent.width
//        property var p: mapToGlobal(x, y)


        Repeater {
            id: rep
            model: performer.task
            //anchors.centerIn: parent

            Label {
                text: modelData //+ " "
                wrapMode: Label.Wrap
                horizontalAlignment: Label.AlignHCenter
                color: getColor()
                //property var row: 0
                //textFormat: Text.RichText
                //width: performer.getAnswerLength()
                //clip: true
                //anchors.centerIn: parent

                function getColor()
                {
                    if (modelData[0] === "[")
                    {
                        if (performer.remainingTime != 0) {
                            return "transparent";
                        }
                        else {
                            return "yellow";
                        }
                    }
                    else
                    {
                        return "white";
                    }
                }

                Component.onCompleted: {
                    //console.log(y)
//                    var p = mapToGlobal(x, y)
//                    var r = (p.y - task.p.y) / height
//                    console.log(p)
                    //console.log(text)

                    // New
                    if (modelData[0] === "[")
                    {
                        width = performer.getAnswerLength()
                    }


                    text = text.replace('[', '').replace(']', '')
                    rep.update()
                }

//                onYChanged: {
////                    console.log(y)
//                    row = y / height
//                    //rep.logRepeaterItems(rep)
//                    leftPadding = rep.offset(row)
//                }
//Border{}
                Rectangle {
                    visible: modelData[0] === '['
                    //color: parent.color
                    anchors.leftMargin: parent.leftPadding
                    anchors.bottomMargin: -2 // underscore height
                    anchors.topMargin: parent.height
                    anchors.fill: parent
                    z: parent.z - 1
                }
            }

//            function offset(row) {
//                var offsets = [];

//                var len = 0;
//                for (var i = 0; i < rep.count; i++) {
//                    var item = rep.itemAt(i)
//                    item.leftPadding = 0

//                    //offsets[item.y / item.height] += (rep.itemAt(i).width - len) / 2

//                    if (rep.itemAt(i).row === row)
//                    {
//                        len += rep.itemAt(i).width;
//                    }
//                }

//                return (task.width - len) / 2;
//            }

            function update() {
//                var offsets = [];
//                var firsts = [];
                var arr = [];
                //console.log("fuuuuuck")

                for (var i = 0; i < rep.count; i++) {
                    var item = rep.itemAt(i)
                    if (item) {
                        item.leftPadding = 0
                    }
                    task.forceLayout()
                }

                for (var i = 0; i < rep.count; i++) {
                    var item = rep.itemAt(i)
                    if (!item)
                        continue

                    //item.leftPadding = 0


                    var row = item.y / item.height
//                    console.log(row)
//                    console.log(item.leftPadding)

                    if (arr[row] == null)
                        arr[row] = { "length" : item.width, "first" : i }
                    else
                        arr[row]["length"] += item.width

//                    if (offsets[row] === null)
//                        offsets[row] = 0
//                    offsets[row] += item.width
//                    console.log(item.width)

//                    if (firsts[row] === null)
//                        firsts[row] = i
//                    console.log(firsts[row])
                }

                for (const r of arr) {
                    rep.itemAt(r.first).leftPadding = (task.width - r.length) / 2
                }

//                console.log(arr)

//                for (const [key, value] of Object.entries(offsets)) {
//                    console.log(key, value);
//                }

                //console.log(offsets)
                //return (task.width - len) / 2;
            }

//            function logRepeaterItems(repeaterItem) {
//                console.log("asfdas " + repeaterItem.count)
//                    for (var i = 0; i < repeaterItem.count; i++) {
//                        console.log("y: " + repeaterItem.itemAt(i).y)
//                        console.log("row: " + repeaterItem.itemAt(i).row)
//                    }
//                }

//            Component.onCompleted: {
//                var item = rep.itemAt(0);
//                if (item) {
//                    rep.itemAt(0).leftPadding = rep.offset(0);
//                }
//            }
        }

        onWidthChanged: {
//            for (var i = 0; i < rep.count; i++) {
//                rep.itemAt(i).leftPadding = 0;
//            }
//            var item = rep.itemAt(0);
//            if (item) {
//                rep.itemAt(0).leftPadding = rep.offset(0);
//            }

            rep.update()
        }
    }

    Component.onCompleted: {
        performer.run()
    }
}
