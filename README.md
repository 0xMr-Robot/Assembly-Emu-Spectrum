# Assembly Emulator (Spectrum)

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Supported Instructions](#supported-instructions)
4. [Custom Instructions](#custom-instructions)
5. [Examples](#examples)
6. [Getting Started](#getting-started)
7. [Contributing](#contributing)
8. [License](#license)

---

## Introduction

The **Assembly Emulator (Spectrum)** is a comprehensive emulator designed to simulate a simplified x86-like assembly environment. It supports a wide range of standard assembly instructions, including data movement, arithmetic operations, logical operations, control flow, and more. Additionally, the emulator introduces custom instructions to extend its functionality, making it a versatile tool for learning, testing, and experimenting with assembly language.

This project is ideal for developers, students, and enthusiasts who want to understand how assembly language works or need a sandbox environment to test their assembly code.

---

## Features

- **Comprehensive Instruction Set**: Supports a wide range of standard assembly instructions, including data movement, arithmetic, logical operations, and control flow.
- **Custom Instructions**: Introduces custom instructions for advanced operations like power, root, average, modulus, mirroring, prime checking, and more.
- **Memory and Stack Management**: Implements a memory and stack system to handle data movement and operations.
- **Flag Management**: Tracks and updates flags (e.g., Zero, Sign, Carry, Overflow) for conditional operations.
- **Interrupt Handling**: Supports custom interrupt handlers for system-level operations (e.g., displaying messages, reading/writing to the console).
- **Dynamic Resizing**: Dynamically resizes instruction and label arrays to handle large programs.
- **Tracing and Debugging**: Enables tracing to log emulator state before and after instruction execution.

---

## Supported Instructions

The emulator supports the following categories of instructions:

### 1. **Data Movement Instructions**
- `MOV`: Move data between registers, memory, and immediate values.
- `PUSH`: Push data onto the stack.
- `POP`: Pop data from the stack.
- `XCHG`: Exchange values between registers or memory.

### 2. **Arithmetic Instructions**
- `ADD`: Add two values.
- `SUB`: Subtract two values.
- `MUL`: Multiply two values.
- `DIV`: Divide two values.
- `INC`: Increment a value.
- `DEC`: Decrement a value.
- `NEG`: Negate a value.
- `CMP`: Compare two values and set flags.

### 3. **Logical Instructions**
- `AND`: Bitwise AND operation.
- `OR`: Bitwise OR operation.
- `XOR`: Bitwise XOR operation.
- `NOT`: Bitwise NOT operation.

### 4. **Shift and Rotate Instructions**
- `SHL`: Shift left.
- `SHR`: Shift right.
- `ROL`: Rotate left.
- `ROR`: Rotate right.

### 5. **Control Flow Instructions**
- `JMP`: Unconditional jump.
- `JE`: Jump if equal (based on Zero flag).
- `JNE`: Jump if not equal.
- `JG`: Jump if greater.
- `JGE`: Jump if greater or equal.
- `JL`: Jump if less.
- `JLE`: Jump if less or equal.
- `JA`: Jump if above (unsigned greater).
- `JAE`: Jump if above or equal (unsigned greater or equal).
- `JB`: Jump if below (unsigned less).
- `JBE`: Jump if below or equal (unsigned less or equal).
- `JO`: Jump if overflow.
- `JNO`: Jump if no overflow.
- `JS`: Jump if sign (negative).
- `JNS`: Jump if no sign (non-negative).
- `JP`: Jump if parity even.
- `JNP`: Jump if no parity (parity odd).

### 6. **Custom Instructions**
- `POW`: Calculate the power of a number.
- `ROOT`: Calculate the root of a number.
- `AVG`: Calculate the average of three numbers.
- `MOD`: Calculate the modulus of two numbers.
- `MIRROR`: Mirror the bits of a number.
- `ISPRIME`: Check if a number is prime.
- `MAX`: Find the maximum of three numbers.
- `MIN`: Find the minimum of three numbers.

### 7. **Miscellaneous Instructions**
- `INT`: Trigger an interrupt (e.g., display a message, read/write to the console).
- `NOP`: No operation.
- `LABEL`: Define a label for jumps.
- `COMMENT`: Ignore lines starting with `;`.

---

## Custom Instructions

The emulator introduces several custom instructions to extend its functionality:

- **`POW`**: Calculates the power of a base value raised to an exponent.
- **`ROOT`**: Calculates the nth root of a number.
- **`AVG`**: Computes the average of three numbers.
- **`MOD`**: Computes the modulus of two numbers.
- **`MIRROR`**: Mirrors the bits of a number.
- **`ISPRIME`**: Checks if a number is prime.
- **`MAX`**: Finds the maximum of three numbers.
- **`MIN`**: Finds the minimum of three numbers.

These instructions are designed to provide additional functionality beyond standard arithmetic and logical operations.

---

## Examples

### Example 1: Basic Arithmetic
```assembly
MOV RAX, 10       ; Load 10 into RAX
MOV RBX, 5        ; Load 5 into RBX
ADD RAX, RBX      ; RAX = RAX + RBX
```

### Example 2: Conditional Jump
```assembly
MOV RAX, 10       ; Load 10 into RAX
MOV RBX, 5        ; Load 5 into RBX
CMP RAX, RBX      ; Compare RAX and RBX
JG greater        ; Jump to 'greater' if RAX > RBX
; Code for RAX <= RBX
greater:
; Code for RAX > RBX
```

### Example 3: Custom Instruction (Power)
```assembly
MOV RAX, 2        ; Load 2 into RAX
MOV RBX, 3        ; Load 3 into RBX
POW RAX, RBX      ; RAX = RAX^RBX (2^3 = 8)
```

### Example 4: Interrupt Handling
```assembly
MOV RAX, message  ; Load address of message into RAX
INT 21h           ; Display message using interrupt 21h
message: db "Hello, World!", 0
```


# Getting Started

This guide will help you set up and run the **Assembly Emulator (Spectrum)** on your local machine.

---

## Prerequisites

Before you begin, ensure you have the following installed:

- **C Compiler**: A C compiler such as [GCC](https://gcc.gnu.org/) is required to compile the emulator.
- **Operating System**: The emulator is compatible with modern operating systems, including:
  - Windows
  - Linux
  - macOS

---

## Installation

Follow these steps to install and set up the emulator:

1. **Clone the Repository**:
   Clone the project repository to your local machine using Git:
   ```bash
   git clone https://github.com/yourusername/assembly-emulator.git
  ```

2. **Navigate to the Project Directory**:
Move into the project directory:
```bash
cd assembly-emulator
```

3. **Compile the Emulator**:
Use a C compiler (e.g., GCC) to compile the emulator:
```bash
gcc -o emulator AssemblyEmuSpectrum.c
```

4. **Run the Emulator**:
After compilation, execute the emulator:
```bash
./emulator
```


# Usage

Once the emulator is set up, you can start writing and running assembly programs.

1. **Write Your Assembly Code**:
Create an assembly file (e.g., program.asm) with your desired instructions. For example:
```assembly
MOV RAX, 10       ; Load 10 into RAX
MOV RBX, 5        ; Load 5 into RBX
ADD RAX, RBX      ; RAX = RAX + RBX
```

2.**Run the Emulator with Your Program**:
Execute the emulator and provide your assembly file as input:
```bash
./emulator program.asm
```
Or Pass The "program.asm" Into The Program After Execute The Emulator

3. **View the Output**:
The emulator will execute the instructions and display the results or emulator state as configured.