import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    property alias text: label.text
    property alias value: spinBox.value
    signal valueModified()

    Label {
        id: label

        text: "Time"
        Layout.alignment: Qt.AlignLeft
        Layout.fillWidth: true
    }

    SpinBox {
        id: spinBox

        // All values here are ms
        from: 100
        to: 10000
        stepSize: 100
        value: 0
        textFromValue: function() { return Number(value / 1000).toString() }

        Layout.alignment: Qt.AlignRight
    }

    Component.onCompleted: {
        spinBox.valueModified.connect(valueModified)
    }
}
