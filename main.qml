import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window

    width: 640
    height: 480
    visible: true
    title: qsTr("Matching Trainer")

    // This is unnecessary if you put the same option to a qtquickcontrols2.conf
    //Material.theme: Material.Dark

    StackView {
        id: stackView

        initialItem: "Options.qml"
        anchors.fill: parent
        anchors.margins: (parent.width < parent.height ? parent.width : parent.height) * 0.05
    }
}
