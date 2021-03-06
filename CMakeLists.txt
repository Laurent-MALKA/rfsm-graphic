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

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options (-fcolor-diagnostics)
endif ()

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(COMMON_SOURCES
        src/engine/InputVariable.cpp
        src/engine/State.cpp
        src/engine/StateChart.cpp
        src/engine/Transition.cpp
        src/engine/Variable.cpp
        )

set(TARGET_SOURCE
        src/gui/AddStateTool.cpp
        src/gui/AddTransitionTool.cpp
        src/gui/Canvas.cpp
        src/gui/DeletionTool.cpp
        src/gui/MainWindow.cpp
        src/gui/PropertiesPanel.cpp
        src/gui/SelectTool.cpp
        src/gui/SetInitialStateTool.cpp
        src/gui/StateUI.cpp
        src/gui/Tool.cpp
        src/gui/TransitionUI.cpp
        src/main.cpp
        )

set(TEST_SOURCES
        test/stateChartTest.cpp
        test/stateTest.cpp
        test/tests.cpp
        test/transitionTest.cpp
        test/variableTest.cpp
        )

#Executables
add_executable(app ${COMMON_SOURCES} ${TARGET_SOURCE})
add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})

# Use the Widgets module from Qt 5
target_link_libraries(app
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )

target_link_libraries(tests
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )
