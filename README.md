# Merkle Tree-Based File Integrity Checker

## Overview
The **Merkle Tree-Based File Integrity Checker** is a C++ application that uses the Merkle Tree data structure to ensure the integrity of files and directories. By calculating hashes for each file and organizing them into a Merkle Tree, this tool allows you to detect any modifications to the file system.

This tool is useful for:
- Checking if files or directories have been tampered with or corrupted.
- Monitoring file changes in sensitive or critical systems.
- Validating data integrity without requiring full file comparisons.

## Features
- **File Integrity Check**: Compares the hash of files to detect modifications.
- **Directory Monitoring**: Checks the integrity of an entire directory.
- **Efficient**: Uses the Merkle Tree to minimize the number of comparisons.
- **C++ Implementation**: Written in modern C++ with modular components.

## Project Structure
The project consists of three main modules:
- **FileHandler**: Handles file operations such as reading and hashing files.
- **MerkleTree**: Implements the Merkle Tree logic for organizing hashes and checking integrity.
- **Main**: The entry point of the application, where the user interacts with the program.

## Installation

### Prerequisites
- A C++ compiler (e.g., GCC, Clang)
- CMake (for building the project)

### Steps to Build
1. Clone the repository:
   git clone https://github.com/RajvBundela/Merkle-Tree-Based-File-Integrity-Checker.git
   cd Merkle-Tree-Based-File-Integrity-Checker

2. Create a build directory:
    mkdir build
    cd build

3. Run CMake to configure the project:
    cmake ..

4. Build the project:
    make

5. Run the Program:
    ./FileIntegrityChecker <file-path>
