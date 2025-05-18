cmake_minimum_required(VERSION 3.16)
project(NeuroSim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# -------------------------
# Qt6 Packages
# -------------------------
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    OpenGLWidgets
)

# -------------------------
# Python & pybind11 for Python API
# -------------------------
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# pybind11 as submodule
add_subdirectory(extern/pybind11)

# -------------------------
# Include paths
# -------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${Python3_INCLUDE_DIRS}
)

# -------------------------
# Main Qt Application
# -------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(NeuroSim ${SOURCES})

target_link_libraries(NeuroSim PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Python3::Python
)

# -------------------------
# Python Module (bindings)
# -------------------------
pybind11_add_module(neurosim
    src/bindings.cpp
    src/Simulation.cpp
    src/Neuron.cpp
)

target_include_directories(neurosim PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${Python3_INCLUDE_DIRS}
)

target_link_libraries(neurosim PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

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
    message(STATUS "Doxygen not found. Documentation target will not be available.")
endif()
