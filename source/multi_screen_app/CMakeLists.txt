find_package(Qt5 REQUIRED Qml Quick Gui QuickWidgets Widgets Core)

IF(WIN32)
add_executable(multi_screen_app
               argparse.hpp
			   WIN32
			   main.cpp)

add_executable(multi_screen_app_cmd
               argparse.hpp
               main.cpp)
ELSE()
add_executable(multi_screen_app
			   argparse.hpp
               main.cpp)
ENDIF()

qt5_add_resources(QML_QRC ${CMAKE_CURRENT_LIST_DIR}/main.qrc)
target_sources(multi_screen_app PRIVATE ${QML_QRC})

target_link_libraries(multi_screen_app
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Gui
                      Qt5::QuickWidgets
                      Qt5::Widgets
                      Qt5::Core)
# target_include_directories(test_states PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS multi_screen_app DESTINATION bin)