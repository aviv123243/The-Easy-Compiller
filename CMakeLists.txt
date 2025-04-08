cmake_minimum_required(VERSION 3.10)
project(The-Easy-Compiller)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/DFA
    ${CMAKE_SOURCE_DIR}/src/errorHandler
    ${CMAKE_SOURCE_DIR}/src/errors
    ${CMAKE_SOURCE_DIR}/src/lexer
    ${CMAKE_SOURCE_DIR}/src/nodes
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/parser/grammerSymbol
    ${CMAKE_SOURCE_DIR}/src/parser/parseTable
    ${CMAKE_SOURCE_DIR}/src/parser/parseTable/action
    ${CMAKE_SOURCE_DIR}/src/parser/parseTable/actionTable
    ${CMAKE_SOURCE_DIR}/src/parser/parseTable/gotoTable
    ${CMAKE_SOURCE_DIR}/src/parser/productionRule
    ${CMAKE_SOURCE_DIR}/src/parser/stackItem
    ${CMAKE_SOURCE_DIR}/src/symbolTable
    ${CMAKE_SOURCE_DIR}/src/symbolTable/scope
    ${CMAKE_SOURCE_DIR}/src/symbolTable/tableEntry
    ${CMAKE_SOURCE_DIR}/src/token
)

# Find all source files
file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Main executable
add_executable(tec ${SOURCES})

# Set output directories
set_target_properties(tec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
)