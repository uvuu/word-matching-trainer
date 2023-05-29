import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    width: childrenRect.width
    height: childrenRect.height

    Label {
        id: rgbText

        text: "#" + colorToHex(color.r) + colorToHex(color.g) + colorToHex(color.b)
        font.capitalization: Font.AllUppercase

        MouseArea {
            anchors.fill: parent
            onClicked: rgbText.visible = false
        }

        function colorToHex(color)
        {
            const hex = (Math.round(color * 255)).toString(16)
            return (hex.length < 2) ? "0" + hex : hex
        }
    }

    TextInput {
        color: rgbText.color
        font: rgbText.font
        visible: !rgbText.visible

        validator: RegularExpressionValidator {
            regularExpression: /^#(?:[0-9a-fA-F]{6}){1}$/
        }

        Keys.onEscapePressed: editingFinished()

        onTextChanged: {
            if (acceptableInput) {
                color = text
            }
        }

        onEditingFinished: {
            focus = false

            if (acceptableInput) {
                rgbText.color = text
            } else {
                text = rgbText.text
            }

            rgbText.visible = true
        }

        onFocusChanged: {
            if (!focus) {
                editingFinished()
            }
        }

        onVisibleChanged: {
            if (visible) {
                forceActiveFocus()
            }
        }

        Component.onCompleted: text = rgbText.text
    }
}
