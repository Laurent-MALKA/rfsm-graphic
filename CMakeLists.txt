cmake_minimum_required(VERSION 3.12)

project(RFSM_Graphic)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
#find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG
        PATHS C:/Qt/5.11.2/mingw53_32/lib/cmake/Qt5Widgets
        NO_DEFAULT_PATH)

# Populate a CMake variable with the sources
set(SOURCES
        src/main.cpp
        src/MainWindow.cpp src/MainWindow.hpp)
# Tell CMake to create the helloworld executable
add_executable(RFSM_Graphic ${SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(RFSM_Graphic
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui)