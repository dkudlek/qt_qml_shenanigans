import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Item{
    Component.onCompleted:{
        switch(appFirstWindowDisplaySize){
            case "fullscreen":
                firstWindow.visibility = Window.FullScreen        
                firstWindow.visible = true
                console.log("First Window: fullscreen")
                break
            case "off":
                firstWindow.visibility = Window.Hidden        
                firstWindow.visible = false
                console.log("First Window: off")
                break
            default:
                firstWindow.visibility = Window.Windowed        
                firstWindow.visible = true
                console.log("First Window: windowed")

        }
        switch(appSecondWindowDisplaySize){
            case "fullscreen":
                secondWindow.visibility = Window.FullScreen        
                secondWindow.visible = true
                console.log("Second Window: fullscreen")
                break
            case "off":
                secondWindow.visibility = Window.Hidden        
                secondWindow.visible = false
                console.log("Second Window: off")
                break
            default:
                secondWindow.visibility = Window.Windowed        
                secondWindow.visible = true
                console.log("Second Window: windowed")

        }
        switch(appThirdWindowDisplaySize){
            case "fullscreen":
                thirdWindow.visibility = Window.FullScreen        
                thirdWindow.visible = true
                console.log("Third Window: fullscreen")
                break
            case "off":
                thirdWindow.visibility = Window.Hidden        
                thirdWindow.visible = false
                console.log("Third Window: off")
                break
            default:
                thirdWindow.visibility = Window.Windowed        
                thirdWindow.visible = true
                console.log("Third Window: windowed")

        }
    }
    ApplicationWindow{
        id: firstWindow
        minimumWidth: 800
        minimumHeight: 640
        screen:{
            var screenMax = Qt.application.screens.length
            var screenId = appFirstWindowDisplayId
            if(0 <= screenId && screenId < screenMax){
                return Qt.application.screens[screenId]
            }else{
                return Qt.application.screens[0]
            }
        }

        Rectangle{
            anchors.fill: parent
            color: "red"
            focus: true
            Keys.onPressed:{
                if(event.modifiers === Qt.AltModifier){
                    if(event.key == Qt.Key_Q){
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
    }
    ApplicationWindow{
        id: secondWindow
        minimumWidth: 800
        minimumHeight: 640
        screen:{
            var screenMax = Qt.application.screens.length
            var screenId = appSecondWindowDisplayId
            if(0 <= screenId && screenId < screenMax){
                return Qt.application.screens[screenId]
            }else{
                return Qt.application.screens[0]
            }
        }
        Rectangle{
            anchors.fill: parent
            color: "green"
            focus: true
            Keys.onPressed:{
                if(event.modifiers === Qt.AltModifier){
                    if(event.key == Qt.Key_Q){
                        secondWindow.close()
                    }else if(event.key === Qt.Key_Return){
                        if(secondWindow.visibility === Qt.WindowMaximized){
                            secondWindow.visibility = "FullScreen"
                        }else{
                            secondWindow.visibility = "Windowed"
                        }
                    }
                    event.accepted = true
                }
            }
        }
    }
    ApplicationWindow{
        id: thirdWindow
        minimumWidth: 800
        minimumHeight: 640
        screen:{
            var screenMax = Qt.application.screens.length
            var screenId = appThirdWindowDisplayId
            if(0 <= screenId && screenId < screenMax){
                return Qt.application.screens[screenId]
            }else{
                return Qt.application.screens[0]
            }
        }
        Rectangle{
            anchors.fill: parent
            color: "blue"
            focus: true
            Keys.onPressed:{
                if(event.modifiers === Qt.AltModifier){
                    if(event.key == Qt.Key_Q){
                        thirdWindow.close()
                    }else if(event.key === Qt.Key_Return){
                        if(thirdWindow.visibility === Qt.WindowMaximized){
                            thirdWindow.visibility = "FullScreen"
                        }else{
                            thirdWindow.visibility = "Windowed"
                        }
                    }
                    event.accepted = true
                }
            }
        }
    }
}