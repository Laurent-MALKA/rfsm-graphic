cmake_minimum_required(VERSION 3.1)

project(RFSM_Graphic)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Require C++ version
set(CMAKE_CXX_STANDARD 11)

#
set(CMAKE_BUILD_TYPE Debug)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(COMMON_SOURCES
        src/Config.cpp  
        src/engine/State.cpp
        src/engine/StateChart.cpp
        src/engine/Transition.cpp
        src/engine/Variable.cpp
        src/engine/InputVariable.cpp
        )

set(TARGET_SOURCE
        src/main.cpp
        src/gui/MainWindow.cpp
        src/gui/Canvas.cpp
        src/gui/StateUI.cpp
        src/gui/Tool.cpp
        src/gui/SelectTool.cpp
        src/gui/AddStateTool.cpp
        src/gui/DeletionTool.cpp
        )

set(TEST_SOURCES
        test/stateTest.cpp  
        test/stateChartTest.cpp  
        test/tests.cpp  
        test/transitionTest.cpp  
        test/variableTest.cpp)

# Tell CMake to create the helloworld executable
add_executable(app ${COMMON_SOURCES} ${TARGET_SOURCE})
add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(app
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui)

target_link_libraries(tests
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui)
