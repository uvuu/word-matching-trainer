import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import Qt.labs.settings 1.0

import com.uvuu.qml 1.0 // Here we acquire the PagingProxyModel type

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

    PagingProxyModel {
        id: pagedExercisesModel
        sourceModel: performer.exercisesNames
    }

    ListView
    {
        id: list

        anchors.topMargin: 20
        anchors.top: options.bottom
        anchors.bottom: pagination.top
        width: parent.width
        spacing: 5
        boundsBehavior: Flickable.StopAtBounds
        model: pagedExercisesModel

        delegate: FlatButton {
            id: option

            text: model.display

            onClicked: {
                option.color = Material.foreground
                option.textColor = Material.backgroundColor
                lastClickedButton = option

                performer.options.exerciseIndex = model.sourceIndex

                stackView.push(training)
            }
        }

        onHeightChanged: {
            if (count <= 0 || list.itemAtIndex(0) === null) {
                return
            }

            const pageSize = height / (list.itemAtIndex(0).height + spacing)
            pagedExercisesModel.pageSize = pageSize > 0 ? pageSize : 1
        }
    }

    Pagination {
        id: pagination

        pageCount: pagedExercisesModel.pageCount
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        visible: pageCount > 1

        // The two bindings below allow to change the page in both directions,
        // i.e. from the pagination and the model accordingly.
        // This is a bidirectional/two-ways binding.
        Binding on currentPage {
            value: pagedExercisesModel.page
        }

        Binding {
            target: pagedExercisesModel
            property: "page"
            value: pagination.currentPage
        }
    }

    Settings {
        id: settings

        property alias page: pagination.currentPage
        property alias questionTime: questionTime.value
        property alias answerTime: answerTime.value
    }

    Component {
        id: training

        Training {}
    }
}
