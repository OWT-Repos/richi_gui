import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15

InputPanel {
    id: inputPanel
    z: 99
    y: 500
    width: 880

    states: [
        State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: 500 - inputPanel.height
            }
        }
    ]

    transitions: [
        Transition {
            id: inputPanelTransition
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]
    Binding {
        target: InputContext
        property: "animating"
        value: inputPanelTransition.running
    }
}