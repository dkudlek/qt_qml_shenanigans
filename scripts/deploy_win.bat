SET QML_MULTI_SCREEN_DIR=..\source\multi_screen_app\res\qml
SET QML_CUSTOM_OBJECT_DIR=..\source\custom_objects_app\res\qml
SET QML_OSM_MAP_DIR=..\source\osm_map_app\res\qml
SET QT_PATH=C:\Qt\Qt5.12.0\5.12.0\msvc2017_64

%QT_PATH%\bin\windeployqt.exe --qmldir %QML_MULTI_SCREEN_DIR% ..\install\bin\multi_screen_app_cmd.exe
%QT_PATH%\bin\windeployqt.exe --qmldir %QML_CUSTOM_OBJECT_DIR% ..\install\bin\custom_objects_app_cmd.exe
%QT_PATH%\bin\windeployqt.exe --qmldir %QML_OSM_MAP_DIR% ..\install\bin\osm_map_app_cmd.exe


