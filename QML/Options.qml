import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Item {
    property var lastClickedButton : null

    StackView.onActivating: {
        lastClickedButton.color = Material.backgroundColor
        lastClickedButton.textColor = Material.foreground
    }

    ColumnLayout {
        id: options

        width: parent.width

        // TODO: Simplify TimeOptions
        TimeOption {
            id: questionTime

            text: "Question Time"
            value: performer.options.questionTime

            onValueChanged: performer.options.questionTime = value
        }

        TimeOption {
            id: answerTime

            text: "Answer Time"
            value: performer.options.answerTime

            onValueChanged: performer.options.answerTime = value
        }
    }

    ListView
    {
        id:list

        anchors.topMargin: 20
        anchors.bottomMargin: 10
        anchors.top: options.bottom
        anchors.bottom: pagination.top
        width: parent.width
        spacing: 5
        boundsBehavior: Flickable.StopAtBounds
        model: performer.exercisesNames

        delegate: FlatButton {
            id: option

            text: modelData

            onClicked: {
                option.color = Material.foreground
                option.textColor = Material.backgroundColor
                lastClickedButton = option

                performer.options.exerciseIndex = index

                stackView.push(training)
            }
        }
    }

    Component {
        id: training

        Training {}
    }

    Pagination {
        id: pagination
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
