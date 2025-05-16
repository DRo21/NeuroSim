cmake_minimum_required(VERSION 3.16)
project(NeuroSim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    OpenGLWidgets
)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(NeuroSim ${SOURCES})

# Link Qt modules
target_link_libraries(NeuroSim PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

# Include path
target_include_directories(NeuroSim PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)
