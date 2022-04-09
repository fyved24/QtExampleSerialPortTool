import QtQuick 2.4

SerialPortPlateForm {
    Connections {
        target: serialPort
        function onReceived(content) {
            console.log(content)
            receivedTextArea.append(content)
        }
    }

    Connections {
        target: serialPortComboBox
        function onActivated(index) {
            console.log(serialPortComboBox.currentValue)
            serialPort.serialPortName = serialPortComboBox.currentValue
            stateProvider.setState("port",  serialPortComboBox.currentValue)
        }
    }
    Connections {
        target: baudComboBox
        function onActivated(index) {
            console.log(baudComboBox.currentValue)
            serialPort.baudRate = baudComboBox.currentValue
            stateProvider.setState("baud",  baudComboBox.currentValue)
        }
    }
    Connections {
        target: openSerialButton
        function onClicked() {
            serialPort.start()
            console.log('buttonOpenSerial')

        }
    }
    Connections {
        target: sendButton
        function onClicked() {
            let text = sendTextField.text
            serialPort.send(text)
            console.log('buttonSend')
        }
    }
    Connections {
        target: stateProvider
        function onStateChanged() {
            console.log('stateChanged', JSON.stringify(stateProvider.settings))

        }
    }
    function init() {
        if (stateProvider.settings.hasOwnProperty("port")) {
            let port = stateProvider.settings["port"]
            serialPortComboBox.model.forEach(function(item, index) {
                if(item === port) {
                    serialPortComboBox.currentIndex = index
                }
            })
        }
        if (stateProvider.settings.hasOwnProperty("baud")) {
            let baud = stateProvider.settings["baud"]
            baudComboBox.model.forEach(function(item, index) {
                if(item === baud) {
                    baudComboBox.currentIndex = index
                }
            })
        }
    }

    Component.onCompleted: {
        serialPort.serialPortName = serialPortComboBox.currentValue
        serialPort.baudRate = baudComboBox.currentValue
        init();
    }
}
