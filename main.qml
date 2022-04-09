import QtQuick 2.15
import QtQuick.Window 2.15

import com.demo.classes 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Example")
    SerialPortTool {
        id: serialPort
    }
    StateProvider {
        id: stateProvider
    }

    SerialPortPlate {
//        anchors.top: parent.top
        anchors.fill: parent
        id: ser
        availablePortsModel: serialPort.availablePorts
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}D{i:1}
}
##^##*/
