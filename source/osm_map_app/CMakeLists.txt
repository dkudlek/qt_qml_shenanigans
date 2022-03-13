find_package(Qt5 REQUIRED Qml Quick Gui QuickWidgets Widgets Positioning Core)

IF (NOT Qt5_FOUND)
    message("Qt5 NOT FOUND!")
ENDIF ()
set(CMAKE_AUTOMOC ON)

qt5_add_resources(QML_QRC ${CMAKE_CURRENT_LIST_DIR}/main.qrc)
IF (WIN32)

    add_executable(osm_map_app WIN32
                   place_qt.h place_qt.cpp
                   places_qt.h places_qt.cpp
                   main.cpp)
    target_link_libraries(osm_map_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core)
    target_sources(osm_map_app PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app PRIVATE cxx_std_17)
    install(TARGETS osm_map_app DESTINATION bin)

    add_executable(osm_map_app_cmd
                   place_qt.h place_qt.cpp
                   places_qt.h places_qt.cpp
                   main.cpp)
    target_link_libraries(osm_map_app_cmd
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core)
    target_sources(osm_map_app_cmd PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app_cmd PRIVATE cxx_std_17)
    install(TARGETS osm_map_app_cmd DESTINATION bin)

ELSE ()
    add_executable(osm_map_app
                   place_qt.h place_qt.cpp
                   places_qt.h places_qt.cpp
                   main.cpp)
    target_link_libraries(osm_map_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core)
    target_sources(osm_map_app PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app PRIVATE cxx_std_17)
    install(TARGETS osm_map_app DESTINATION bin)
ENDIF ()