# Persistent Text Editor

A command-line based text editor implemented in C++ that leverages a **persistent rope** data structure to support efficient text editing with built-in undo/redo functionality.

## Overview

This project demonstrates advanced data structure techniques by implementing a **persistent rope**. Unlike conventional text editors that use gap buffers or piece tables, this editor uses a persistent approach to maintain previous versions of the text. This means every update creates a new version by reusing most of the unchanged structure, enabling O(log N) undo/redo operations and efficient memory sharing.

### Key Features

- **Persistent Rope Data Structure:**  
  Implements a binary tree where each leaf holds a segment of text. Updates are made via path copying, ensuring that previous versions remain accessible.

- **Efficient Editing Operations:**  
  Supports fast insertions and deletions by combining split and concatenation operations on the rope.

- **Undo/Redo Functionality:**  
  Maintains a history of versions, allowing users to easily revert or reapply changes.

- **Command-Line Interface (CLI):**  
  Provides simple commands to insert text, delete text, print the current document, and navigate through versions using undo and redo.

## Project Structure
Persistent-Text-Editor/ ├── Makefile ├── main.cpp ├── Rope.h └── Rope.cpp

- **Rope.h / Rope.cpp:**  
  Contains the implementation of the persistent rope data structure, including functions for building, splitting, concatenating, inserting, deleting, and converting the rope back into a string.

- **main.cpp:**  
  Implements the CLI for the text editor and version management for undo/redo functionality.

- **Makefile:**  
  Provides build instructions to compile the project using `g++`.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++ with C++11 support)
- GNU Make

### Build Instructions

1. Open a terminal in the project directory.
2. Run the following command to compile the project:
   ```bash
   make
3. This will generate an executable named editor.

### Running the Editor
Run the following command to launch the editor:
   ```bash
   ./editor
