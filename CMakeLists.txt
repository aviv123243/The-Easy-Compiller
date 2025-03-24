cmake_minimum_required(VERSION 3.10)
project(TECProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify g++ as the compiler
set(CMAKE_CXX_COMPILER "g++")

# Collect all .cpp files from src directory and subdirectories
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Exclude any unwanted files if needed (optional)
# list(FILTER SOURCES EXCLUDE REGEX "bison.*")

# Add executable
add_executable(tec ${SOURCES})

# Include directories
target_include_directories(tec PRIVATE
    "src"
    "src/DFA"
    "src/errorHandler"
    "src/errors"
    "src/lexer"
    "src/main"
    "src/nodes"
    "src/parser"
    "src/parser/grammerSymbol"
    "src/parser/parseTable"
    "src/parser/parseTable/action"
    "src/parser/parseTable/actionTable"
    "src/parser/parseTable/gotoTable"
    "src/parser/productionRule"
    "src/parser/stackItem"
    "src/symbolTable"
    "src/symbolTable/tableEntery"
    "src/token"
)