pragma Singleton

import QtQuick 2.0
import Qt.labs.settings 1.0

Settings {
    property string dataFile: "data.txt"
    property bool maximumGap: true
    property color answerColor: "yellow"
}
