# Proof of Concept: Self-Implementing Language

This PoC focuses on the roadmap for re-implementing this language in itself. The current compiler is written in
TypeScript and targets C. To achieve self-hosting, we need to implement all necessary language features to support
Lexer, Parser, Binder, and Emitter.

## Self-Implementation Strategy

1. **Core Data Structures**: Implement support for objects/structs and basic types.
2. **Control Flow**: Add `if`, `while`, and `return` statements.
3. **Array/String Support**: Necessary for handling source code.
4. **File I/O**: Ability to read source files and write generated code. For now, we use extern C functions.
5. **Bootstrapping**: Use the TypeScript compiler to compile the first version of the self-hosted compiler.

## Feature Checklist

### 1. Declarations

- [x] **Object Declarations**
    - [x] Type declaration
- [ ] **Enum Declaration**
- [x] **Function Declarations**
    - [x] parameters
    - [x] return types
- [x] **Variable Declarations**
    - [x] explicit typing

### 2. Statements

- [x] **Block Statements** (`{ ... }`)
- [x] **Expression Statements**
- [ ] **Control Flow**
    - [x] `if` / `else`
    - [x] `while` loop
    - [ ] `for` loop
    - [ ] `switch` / `case`
    - [x] `return` statement
    - [ ] `break` / `continue`

### 3. Expressions

- [x] **Assignments**
- [x] **Constructor Expressions** (`new Type()`)
- [ ] **Accessors**
    - [x] Member access (`obj.field`)
    - [ ] Array indexing (`arr[i]`)
- [x] **Operators**
    - [x] Arithmetic (`+`, `-`, `*`, `/`)
    - [x] Comparison (`==`, `!=`, `<`, `>`)
    - [x] Logical (`&&`, `||`, `!`)
- [x] **Literals**
    - [x] Integer literals
    - [x] String literals
    - [x] Char literals
    - [x] Boolean literals
- [x] **Function Calls**
- [ ] **Casting System**
    - [x] Casting rules
    - [x] Explicit casting
    - [x] Implicit casting
    - [ ] Object casting `myObj is MyType myCastedVariable`

### 4. Types

- [x] **Built-in Types**
    - [x] `i32`
    - [x] `void`
- [ ] **Complex Types**
    - [x] Functions `Func<Return, Arg1, Arg2, ArgN>`
    - [ ] Arrays
    - [x] Strings
    - [ ] Nullable

### 5. Compiler Infrastructure (for self-hosting)

- [x] **Standard Library**
    - [x] Extern function declaration for C function import
- [x] **Comments**
    - [x] Single line
    - [x] Multiline

## Transpilation status

- [x] binder.ts
- [ ] c_emitter.ts
- [x] char.ts
- [x] conversion.ts
- [x] lexer.ts
- [ ] main.ts
- [x] parser.ts
- [x] scope.ts