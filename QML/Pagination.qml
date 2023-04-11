import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    property int currentPage: 1
    property int pageCount: 1

    FlatButton {
        text: "<"
        enabled: currentPage > 1
        implicitHeight: contentSpacing * 1.5
        implicitWidth: contentSpacing * 1.5
        Layout.alignment: Qt.AlignRight

        onClicked: --currentPage
    }

    // TODO: keep the positions of arrows disregarding to the label size
    Label {
        id: name
        text: currentPage + " / " + pageCount
        Layout.alignment: Qt.AlignCenter
    }

    FlatButton {
        text: ">"
        enabled: currentPage < pageCount
        implicitHeight: contentSpacing * 1.5
        implicitWidth: contentSpacing * 1.5
        Layout.alignment: Qt.AlignLeft

        onClicked: ++currentPage
    }
}
