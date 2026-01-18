# Generalized Operation Handling

This document describes a generalized mechanism for handling unary and binary operations. The goal is to validate
operations against operand types without explicitly declaring every possible combination of types, by leveraging a type
conversion system.

## Core Concepts

The system relies on a set of predefined operator rules and a type conversion engine to resolve expressions.

### Operator Definitions

An operator is defined by its symbol (token), its required operand type(s), and its result type.

#### Unary Rule

A unary operator rule consists of:

- **Symbol**: The operator token (e.g., `+`, `-`, `!`).
- **Operand Type**: The required type of the operand.
- **Result Type**: The type of the expression after the operation.

#### Binary Rule

A binary operator rule consists of:

- **Symbol**: The operator token (e.g., `+`, `-`, `*`, `/`).
- **Left Operand Type**: The required type of the left operand.
- **Right Operand Type**: The required type of the right operand.
- **Result Type**: The type of the expression after the operation.

## Resolution Logic

When an operation is encountered, the system follows a structured lookup process to find a matching operator rule.

1. **Exact Match**: The system first looks for an operator rule that exactly matches the symbol and the operand(s) type.
2. **Implicit Conversion**: If no exact match is found, the system checks if the operand(s) can be implicitly converted
   to a type for which an operator rule exists for that symbol.

## Theoretical Example: Mixed Type Addition

Consider a language with `i8` and `i32` types, where an implicit conversion exists from `i8` to `i32`.
If an addition `a + b` is encountered where `a` is `i8` and `b` is `i32`:

1. The system searches for a `+` operator rule for `(i8, i32)`.
2. Assuming none is found, it looks for other `+` rules.
3. It finds a `+` rule for `(i32, i32)`.
4. It checks if `a (i8)` can be implicitly converted to `i32` (Yes).
5. It checks if `b (i32)` can be implicitly converted to `i32` (Yes, trivial).
6. The operation is resolved using the `(i32, i32)` rule, with `a` being promoted to `i32`.

## Advantages of this Approach

Through this approach, we don't need to define $N^2$ rules for $N$ numeric types, or mixed types e.g. integers and
booleans. Additionally, new types are automatically included into existing rules if an implicit cast way exists.

## Future improvements

Currently, the resolution logic takes the first rule that reaches the result. Therefore, we have no prioritizing and
optimization check.

When in the future the conversion system has a cost system, we could use it to prioritize the best conversion path.
Where all operands are included in the cost table.