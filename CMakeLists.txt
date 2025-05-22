cmake_minimum_required(VERSION 3.16)
project(NeuroSim VERSION 0.1 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# -------------------------
# Find dependencies
# -------------------------
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    OpenGLWidgets
    Test
)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# pybind11 as submodule
add_subdirectory(extern/pybind11)

# -------------------------
# Core simulation library
# -------------------------
add_library(neuro_core
    src/IntegrateAndFireNeuron.cpp
    src/Synapse.cpp
    src/Simulation.cpp
)

set_target_properties(neuro_core PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(neuro_core
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

# -------------------------
# GUI + visualization library
# -------------------------
add_library(neuro_gui
    src/ControlPanelWidget.cpp
    src/HeatmapWidget.cpp
    src/MainWindow.cpp
    src/RasterPlotWidget.cpp
    src/TraceViewWidget.cpp
)

target_include_directories(neuro_gui
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(neuro_gui
    PUBLIC
        Qt6::Widgets
        Qt6::OpenGLWidgets
        neuro_core
)

# -------------------------
# Main Qt Application
# -------------------------
add_executable(NeuroSim
    src/main.cpp
)

target_link_libraries(NeuroSim
    PRIVATE
        neuro_gui
)

# -------------------------
# Python Module (pybind11)
# -------------------------
pybind11_add_module(neurosim
    src/bindings.cpp
)

target_include_directories(neurosim
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(neurosim
    PRIVATE neuro_core
)

# -------------------------
# Unit Testing (Catch2)
# -------------------------
add_subdirectory(extern/Catch2)
enable_testing()

add_executable(NeuroSimTests
    tests/test_neuron.cpp
    tests/test_simulation.cpp
    tests/test_synapse.cpp
)

target_link_libraries(NeuroSimTests
    PRIVATE
        neuro_core
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(NeuroSimTests)

# -------------------------
# Unit Testing (QtTest)
# -------------------------
set(QT_GUI_TEST_FILES
    test_controlpanelwidget
    test_heatmapwidget
    test_rasterplotwidget
    test_traceviewwidget
    test_mainwindow
)

foreach(test_file IN LISTS QT_GUI_TEST_FILES)
    add_executable(${test_file} tests/${test_file}.cpp)
    target_link_libraries(${test_file}
        PRIVATE
            Qt6::Test
            Qt6::Widgets
            Qt6::OpenGLWidgets
            neuro_gui
    )
    add_test(NAME ${test_file} COMMAND ${test_file})
endforeach()

# -------------------------
# Doxygen Documentation
# -------------------------
find_package(Doxygen QUIET)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Doxygen not found. 'doc_doxygen' target will not be available.")
endif()
