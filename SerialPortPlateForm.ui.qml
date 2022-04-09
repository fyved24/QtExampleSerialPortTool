import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridLayout {
    property alias availablePortsModel: serialPortComboBox.model
    property alias serialPortComboBox: serialPortComboBox
    property alias baudComboBox: baudComboBox
    property alias receivedTextArea: receivedTextArea
    property alias sendTextField: sendTextField
    property alias openSerialButton: openSerialButton
    property alias sendButton: sendButton
    rows: 6
    columns: 5
    Label {
        Layout.columnSpan: 1
        text: qsTr("可用串口")
    }

    ComboBox {
        Layout.columnSpan: 2
        id: serialPortComboBox
        model: ["COM1", "COM2"]
    }
    ComboBox {
        Layout.columnSpan: 2
        id: baudComboBox
        model: [9600, 115200]
    }

    Rectangle {
        id: textRect
        //        width: 500
        //        height: 200
        Layout.columnSpan: 5
        Layout.rowSpan: 2
        Layout.fillHeight: true
        Layout.fillWidth: true
        border {
            color: "#333333"
        }

        ScrollView {
            id: view
            anchors.fill: parent
            TextArea {
                id: receivedTextArea
                wrapMode: TextArea.Wrap //换行
                font.pixelSize: 15
                font.weight: Font.Light
                textFormat: TextArea.AutoText
                readOnly: true
            }
        }
    }
    TextField {
        id: sendTextField
        Layout.columnSpan: 5
        Layout.fillWidth: true
        placeholderText: qsTr("待发送内容")
        selectByMouse: true
    }
    Button {
        id: openSerialButton
        text: qsTr("打开串口")
    }

    Button {
        id: sendButton
        text: qsTr("发送")
    }
}
