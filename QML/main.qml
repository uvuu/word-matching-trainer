import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window

    minimumWidth: 350
    minimumHeight: 300
    width: 640
    height: 480
    visible: true
    title: qsTr("Matching Trainer")

    StackView {
        id: stackView

        initialItem: "Options.qml"
        anchors.fill: parent
        anchors.margins: (parent.width < parent.height ? parent.width : parent.height) * 0.05
    }
}
