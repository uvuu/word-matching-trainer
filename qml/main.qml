import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window

    minimumWidth: 350
    minimumHeight: 300
    width: 640
    height: 480
    visible: true
    title: qsTr("Word Matching Trainer")

    StackView {
        id: stackView

        initialItem: "Options.qml"
        anchors.fill: parent
        anchors.margins: (parent.width < parent.height ? parent.width : parent.height) * 0.05
    }

    // Save the window state between sessions
    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
