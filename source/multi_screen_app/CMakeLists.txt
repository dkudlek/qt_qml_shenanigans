find_package(Qt5 REQUIRED Qml Quick Gui QuickWidgets Widgets Core)

IF (NOT Qt5_FOUND)
    message("Qt5 NOT FOUND!")
ENDIF ()
set(CMAKE_AUTOMOC ON)

qt5_add_resources(QML_QRC ${CMAKE_CURRENT_LIST_DIR}/main.qrc)
IF (WIN32)

    add_executable(multi_screen_app WIN32
                   argparse.hpp
                   main.cpp)
    target_link_libraries(multi_screen_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Core)
    target_sources(multi_screen_app PRIVATE ${QML_QRC})
    target_compile_features(multi_screen_app PRIVATE cxx_std_17)
    install(TARGETS multi_screen_app DESTINATION bin)

    add_executable(multi_screen_app_cmd
                   argparse.hpp
                   main.cpp)
    target_link_libraries(multi_screen_app_cmd
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Core)
    target_sources(multi_screen_app_cmd PRIVATE ${QML_QRC})
    target_compile_features(multi_screen_app_cmd PRIVATE cxx_std_17)
    install(TARGETS multi_screen_app_cmd DESTINATION bin)

ELSE ()
    add_executable(multi_screen_app
                   argparse.hpp
                   main.cpp)
    target_link_libraries(multi_screen_app
                          Qt5::Qml
                          Qt5::Quick
                          Qt5::Gui
                          Qt5::QuickWidgets
                          Qt5::Widgets
                          Qt5::Core)
    target_sources(multi_screen_app PRIVATE ${QML_QRC})
    target_compile_features(multi_screen_app PRIVATE cxx_std_17)
    install(TARGETS multi_screen_app DESTINATION bin)
ENDIF ()