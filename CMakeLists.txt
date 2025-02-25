# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/DFA
    ${PROJECT_SOURCE_DIR}/src/errorHandler
    ${PROJECT_SOURCE_DIR}/src/errors
    ${PROJECT_SOURCE_DIR}/src/lexer
    ${PROJECT_SOURCE_DIR}/src/nodes
    ${PROJECT_SOURCE_DIR}/src/parser
    ${PROJECT_SOURCE_DIR}/src/parser/grammerSymbol
    ${PROJECT_SOURCE_DIR}/src/parser/parseTable
    ${PROJECT_SOURCE_DIR}/src/parser/parseTable/gotoTable
)

# Add the source files
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/parser/*.cpp
    ${PROJECT_SOURCE_DIR}/src/parser/parseTable/*.cpp
    ${PROJECT_SOURCE_DIR}/src/parser/parseTable/gotoTable/*.cpp
)

# Add the executable (replace MyProjectExecutable with your desired name)
add_executable(MyProjectExecutable ${SOURCES})

# Optionally, add extra flags or dependencies if needed
# Example: link libraries (if you have them)
# target_link_libraries(MyProjectExecutable SomeLibrary)

# Set output directories for binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# Additional optional configurations for debugging and release
set(CMAKE_BUILD_TYPE Debug)  # Change to Release for optimized builds
