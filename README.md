# 🔢 Arbitrary Precision Calculator (APC)

Perform arithmetic on numbers of **any size** using C and doubly linked lists.


## 📖 Overview

This project implements an **Arbitrary Precision Calculator (APC)** in C that can handle numbers larger than built-in data types (`int`, `long`, etc.).
It uses **doubly linked lists** to store and process each digit efficiently.


## ✨ Features

* 🚀 Supports very large integers (no overflow issues)
* ➕ Addition
* ➖ Subtraction
* ✖️ Multiplication
* ➗ Division
* 🔍 Input validation for operands & operators
* 🔗 Digit-wise computation using linked lists
* ⚡ Handles both positive and negative numbers


## 🛠️ Tech Stack

* **Language:** C
* **Concepts Used:**

  * Doubly Linked List
  * Dynamic Memory Allocation
  * String Processing


## 📂 Project Structure

```bash
.
├── main.c          # Entry point
├── main.h          # Structure & function declarations
├── *.c             # Core logic (operations & helpers)
```


## ▶️ Getting Started

### 🔧 Compile

```bash
gcc *.c -o apc
```

### ▶️ Run

```bash
./apc <operand1> <operator> <operand2>
```

### ✅ Example

```bash
./apc 999999999999 + 1
```

### 💡 Output

```bash
The value is:
1000000000000
```


## ⚙️ How It Works

1. Inputs are taken via command-line arguments
2. Each number is converted into a **doubly linked list**
3. Arithmetic is performed digit-by-digit (like manual calculation)
4. Result is stored and printed as a linked list


## 🧠 Key Highlights

* Overcomes limitations of standard data types
* Efficient digit-wise computation
* Clean modular design using functions
