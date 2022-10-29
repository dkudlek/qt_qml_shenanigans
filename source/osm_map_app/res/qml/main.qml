import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import QtLocation 5.6
import QtPositioning 5.6



ApplicationWindow{
    id: firstWindow
    minimumWidth: 800
    minimumHeight: 640
    visibility: "Windowed" //Window.Windowed
    visible: true
    screen: Qt.application.screens[0]
    Rectangle{
        anchors.fill: parent
        color: "red"
        focus: true
        Keys.onPressed:{
            if(event.modifiers === Qt.AltModifier){
                if(event.key === Qt.Key_Q){
                    firstWindow.close()
                }else if(event.key === Qt.Key_Return){
                    if(firstWindow.visibility === Qt.WindowMaximized){
                        firstWindow.visibility = "FullScreen"
                    }else{
                        firstWindow.visibility = "Windowed"
                    }
                }
                event.accepted = true
            }
        }
    }
    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter{
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }
        PluginParameter{
            name: "osm.mapping.highdpi_tiles"
            value: true
        }
        PluginParameter{
            name: "osm.mapping.providersrepository.address"
            value: "http://maps_redirect.qt.io/osm/5.6/street"
        }
    }

    Map{
        id: map
        anchors.fill: parent
        zoomLevel: 10
        tilt: 0
        plugin: mapPlugin
        center: QtPositioning.coordinate(50.232271671574345, 11.320323103928855)

        MapPolyline{
            id: placesPolyline
            line.width: 2
            line.color: "red"
            path: placesPolyline.setPath(appPlaces.path)
            opacity: 0.85
        }

        Repeater{
            id: placesRepeater
            property var myPlaces: appPlaces.places
            model: myPlaces
            MapQuickItem{
                id: placeMarker
                coordinate: placesRepeater.myPlaces[index].placeCoordinate
                sourceItem: Item{
                    Image{
                        id: placeIcon
                        width: 24
                        height: 24
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        source:"qrc:///res/icons/outline_my_location_black_24dp.png"
                    }
                    Label{
                        height: 24
                        anchors{
                            top: placeIcon.bottom
                            horizontalCenter: placeIcon.horizontalCenter
                        }

                        text: placesRepeater.myPlaces[index].placeName
                        color: "black"
                        wrapMode: Text.WordWrap
                        font.capitalization: Font.AllUppercase
                        font.bold: true
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        background: Rectangle {
                            color: "#aaaaaa"
                        }
                    }
                }
            }
        }


    }
}


