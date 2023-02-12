find_package(Qt5 REQUIRED Qml Quick Gui QuickWidgets Widgets Positioning Core Xml)

IF (NOT Qt5_FOUND)
    message("Qt5 NOT FOUND!")
ENDIF ()
set(CMAKE_AUTOMOC ON)

qt5_add_resources(QML_QRC ${CMAKE_CURRENT_LIST_DIR}/main.qrc)
IF (WIN32)

    add_executable(osm_map_app WIN32
                   point_of_interest_qt.h
                   point_of_interest_qt_model.h
                   app_backend_qt.h
                   main.cpp)
    target_link_libraries(osm_map_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core
                          Qt5::Xml)
    target_sources(osm_map_app PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app PRIVATE cxx_std_17)
    install(TARGETS osm_map_app DESTINATION bin)

    add_executable(osm_map_app_cmd
                   point_of_interest_qt.h
                   point_of_interest_qt_model.h
                   app_backend_qt.h
                   main.cpp)
    target_link_libraries(osm_map_app_cmd
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core
                          Qt5::Xml)
    target_sources(osm_map_app_cmd PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app_cmd PRIVATE cxx_std_17)
    install(TARGETS osm_map_app_cmd DESTINATION bin)

ELSE ()
	find_package(Threads REQUIRED)
    add_executable(osm_map_app
                   point_of_interest_qt.h
                   point_of_interest_qt_model.h
                   app_backend_qt.h
                   main.cpp)
    target_link_libraries(osm_map_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Positioning
                          Qt5::Core
                          Qt5::Xml
						  Threads::Threads)
    target_sources(osm_map_app PRIVATE ${QML_QRC})
    target_compile_features(osm_map_app PRIVATE cxx_std_17)
    install(TARGETS osm_map_app DESTINATION bin)
ENDIF ()
