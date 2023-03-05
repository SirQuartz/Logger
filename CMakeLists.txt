cmake_minimum_required(VERSION 3.5)

project(logger VERSION 1.0.0 LANGUAGES CXX)

# Get all source files in the src directory
file(GLOB SOURCES "src/*.cpp" "src/*.hpp")

# Create the library target and add the source files
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET logger PROPERTY PROJECT_LABEL "Logger")
