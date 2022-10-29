import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ApplicationWindow{
    id: root
    visibility: Window.Windowed
    visible: true
    minimumWidth: 800
    minimumHeight: 640
    Rectangle{
        id: back
        color: "white"
        anchors.fill: parent
        ListView{
            id: elementListView
            anchors.fill: parent
            model: backend.elements
            delegate: Item{
                width: root.width
                height: root.height / 20.0
                Label{
                    id: displayNameLabel
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                        rightMargin: parent.width / 2.0
                    }
                    text: backend.elements[index].displayName
                }
                Label{
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        left: displayNameLabel.right
                        right: parent.right
                        rightMargin: parent.width
                    }
                    text: backend.elements[index].velocity
                }
            }

        }
    }

}
