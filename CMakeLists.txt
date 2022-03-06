cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(qt_qml_shenanigans)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# Setup basic install PATHs for lib, bin, include and CMake
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")


add_subdirectory(source)
