# Type System

The LOP type system is designed to be simple yet flexible, supporting primitives, objects, and structs. It includes
support for generics and is being expanded to handle nullability and memory-safe abstractions.

## Type Kinds

The LOP compiler classifies types into three main categories:

1. **PRIMITIVE**: Basic types like `i32`, `bool`, `char`, and `void`. These are typically passed by value and do not
   require garbage collection. Also at the current state these types fit into the size of a pointer (`size <= sizeof(
   void*)`).
2. **OBJECT**: GC-managed heap-allocated types. Objects include a type header for runtime metadata and GC tracing.

## Generics

LOP supports generics for both functions and complex types.

### Generic Types

Types can be declared with generic parameters. For example, `Span<T>` or `Func<Return, Arg1>`.
The compiler handles generics through "dynamic type signatures." When a generic type is encountered, the binder:

1. Binds the generic arguments.
2. Generates a unique `cName` for the specialization (e.g., `Func_Return_Arg1`).
3. Registers the specialized type in the scope.

### Function Generics

Functions are represented through a generic Type. The `Func<...>` type represents a function signature.
This behavior allows for type-safe dynamic function pointers, where without any barriers functions can be passed around
in variables.

## Nullability

Only Types of kind OBJECT are planned to be nullable. At the current implementation every type is implicit nullable.
It is planned to change this behavior in the future, so that types need to be explicitly declared as nullable e.g.
`Type?`.