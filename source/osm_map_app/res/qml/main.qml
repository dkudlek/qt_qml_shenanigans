import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import QtLocation 5.6
import QtPositioning 5.6
import Tracker 1.0

ApplicationWindow {
    id: firstWindow
    minimumWidth: 800
    minimumHeight: 640
    visibility: "Windowed" //Window.Windowed
    visible: true
    screen: Qt.application.screens[0]
    Rectangle {
        anchors.fill: parent
        color: "black"
        focus: true
        Keys.onPressed: {
            if (event.modifiers === Qt.AltModifier) {
                if (event.key === Qt.Key_Q) {
                    firstWindow.close()
                } else if (event.key === Qt.Key_Return) {
                    if (firstWindow.visibility === Qt.WindowMaximized) {
                        firstWindow.visibility = "FullScreen"
                    } else {
                        firstWindow.visibility = "Windowed"
                    }
                }
                event.accepted = true
            }
        }
        Text {
            anchors.fill: parent
            color: "grey"
            text: "Loading..."
            font.pixelSize: 0.25 * parent.height
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Component {
            id: theMap
            Item {
                anchors.fill: parent
                Plugin {
                    id: mapPlugin
                    name: "osm"
                    PluginParameter {
                        name: "osm.mapping.providersrepository.disabled"
                        value: true
                    }
                    PluginParameter {
                        name: "osm.mapping.highdpi_tiles"
                        value: true
                    }
                    PluginParameter {
                        name: "osm.mapping.providersrepository.address"
                        value: "http://maps_redirect.qt.io/osm/5.6/street"
                    }
                }

                Map {
                    id: map
                    anchors.fill: parent
                    zoomLevel: 12.0
                    tilt: 0
                    plugin: mapPlugin
                    center: appBackend.coordinate
                    CoordinateAnimation {
                      duration: 100
                      easing.type: Easing.InOutQuad
                     }
                    property bool acceptChange: false
                    Component.onCompleted: {
                        acceptChange: true
                    }

                    function update() {
                        appBackend.update()
                    }

                    onHeightChanged: {
                        if (acceptChange) {
                            update()
                        }
                    }
                    onWidthChanged: {
                        if (acceptChange) {
                            update()
                        }
                    }
                    onMapReadyChanged: {
                        update()
                    }

                    MapPolyline {
                        Component.onCompleted: {
                            console.log(path)
                        }

                        visible: true
                        id: placesPolyline
                        line.width: 5
                        line.color: "red"
                        path: appBackend.path.path
                        opacity: 0.85
                    }

                    Rectangle{
                        color: "grey"
                        width: 125
                        anchors{
                            top: faster.top
                            bottom: faster.bottom
                            right: faster.left
                            rightMargin: parent.height * 1 / 40
                        }

                        Text{
                            id: speedVal
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.bottom:parent.bottom
                            width: 25
                            text: Math.floor(1000 / appBackend.updateInterval)
                            fontSizeMode: Text.Fit
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        Text{
                            id: speedDesc
                            anchors.left: speedVal.right
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom:parent.bottom
                            text: " Updates per second"
                            fontSizeMode: Text.Fit
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button{
                        id: faster
                        height: 40
                        width: 40
                        anchors{
                            top: parent.top
                            topMargin: parent.height * 1 / 40
                            right: parent.right
                            rightMargin: parent.height * 1 / 40

                        }
                        background: Rectangle{
                            color:{
                                if(faster.pressed){
                                    return "white"
                                }
                                return "grey"
                            }

                        }
                        icon.source: "qrc:///res/icons/plus.png"

                        onClicked: {
                            appBackend.faster()
                        }
                    }



                    Button{
                        id: slower
                        height: 40
                        width: 40
                        anchors{
                            top: faster.bottom
                            right: faster.right

                        }
                        background: Rectangle{
                            color:{
                                if(slower.pressed){
                                    return "white"
                                }
                                return "grey"
                            }

                        }
                        icon.source: "qrc:///res/icons/minus.png"

                        onClicked: {
                            appBackend.slower()
                        }

                    }



                    MapQuickItem {
                        visible: true
                        coordinate: appBackend.coordinate
                        sourceItem: Image {
                            anchors.bottom: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 40
                            height: width
                            source: "qrc:///res/icons/bike.png"
                        }
                    }

                    MapItemView {
                        visible: true
                        model: PointOfInterestModel {
                            backend: appBackend
                        }
                        delegate: Component {
                            MapQuickItem {
                                visible: true
                                coordinate: poi.coordinate
                                sourceItem: Item {
                                    id: location
                                    anchors.bottom: parent.top
                                    Image {
                                        id: locationImage
                                        height: 40
                                        width: height
                                        anchors.bottom: parent.bottom
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        source: "qrc:///res/icons/location.png"
                                    }
                                    Rectangle {
                                        color: "black"
                                        opacity: 0.8
                                        anchors.top: parent.bottom
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        width: 100
                                        height: 20

                                        Text {
                                            anchors.fill: parent
                                            text: poi.name
                                            color: "white"
                                            fontSizeMode: Text.Fit
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Loader {
            anchors.fill: parent
            visible: status === Loader.Ready
            asynchronous: true
            sourceComponent: theMap
        }
    }
}
