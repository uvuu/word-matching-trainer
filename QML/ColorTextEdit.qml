import QtQuick 2.15
import QtQuick.Controls 2.12


Item {
    width: childrenRect.width
    height: childrenRect.height

    Label {
        id: rgbText

        text: "#" + (color.r * 255).toString(16) + (color.g * 255).toString(16) + (color.b * 255).toString(16)
        font.capitalization: Font.AllUppercase

        MouseArea {
            anchors.fill: parent
            onClicked: rgbText.visible = false
        }
    }

    TextInput {
        color: rgbText.color
        font: rgbText.font
        text: rgbText.text
        visible: !rgbText.visible

        Keys.onEscapePressed: editingFinished()

        onEditingFinished: {
            focus = false
            rgbText.visible = true
        }

        onVisibleChanged: {
            if (visible) {
                forceActiveFocus()
            }
        }
    }
}
