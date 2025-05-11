# The Easy Compiler

A complete compiler for the **EZ programming language**, designed to simplify learning and implementing compiler theory. This repository contains all components required for lexical analysis, parsing, semantic analysis, and code generation targeting x86-64 assembly.

## Features

* **Lexical Analyzer:** DFA-based lexer for efficient tokenization.
* **Parser:** Custom parser utilizing structured grammar rules.
* **Semantic Analyzer:** Type checking, scope management, and error handling.
* **Code Generator:** Produces MASM-compatible x86-64 assembly.
* **Comprehensive Testing:** Demonstration programs for various algorithms.
* **VS Code Integration:** Syntax highlighting extension.
* **Automated Scripts:** Build and run scripts for Windows.

## Project Structure

* `src/`: Compiler source code.

  * `lexer/`, `parser/`, `semantic/`, `codeGenerator/`, and related components.
* `demos/`: Example EZ programs.
* `scripts/`: Utility scripts for project setup.
* `non-code resources/`: Documentation and diagrams.
* `vscode-extension/`: EZ language syntax highlighting for VS Code.
* `CFG/`: Grammar specification files.

## Getting Started

### Prerequisites

* Windows OS (recommended)
* Visual Studio with C++ support
* CMake (version 3.20 or higher)
* MASM assembler (ML64.exe)

### Building the Compiler

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Compiler

Use provided batch scripts or execute directly:

```sh
# Example
tec_build_exe.bat <source-file>.ez
tec_run.bat <source-file>.exe
```

## VS Code Extension

To install EZ syntax highlighting in VS Code:

```sh
cd vscode-extension/ez
code --install-extension ez-0.0.1.vsix
```

## Documentation

Detailed documentation, UML diagrams, and DFA visualizations are available under `non-code resources/`.

## License

Distributed under the MIT License. See `LICENSE` for details.

---

Developed by Aviv Esh ([GitHub](https://github.com/aviv123243)).
