# Proof of Concept (PoC)

This directory contains theoretical proof-of-concept (PoC) documents and design specifications for the LOP (Low Object
Language) project. It serves as a repository for formal proofs, architectural decisions, and future improvement ideas.

## Overview

The "Proof of Concept" documents are intended to bridge the gap between abstract design goals and concrete
implementation in the runtime or compiler. They document the rationale behind specific features and provide a roadmap
for their development.

## Documents

Currently, the following documents are available:

- [Garbage Collector (GC)](GC.md): Detailed explanation of the mark-and-sweep garbage collector, shadow stack
  implementation, and root tracking.
- [Objects](Object.md): Specification for GC-aware complex structs, their memory layout, type metadata, and
  instantiation mechanisms.
- [Conversion](Conversion.md): Type conversion system (implicit/explicit) using BFS for path resolution.
- [Operations](Operations.md): Generalized handling of unary and binary operations using type conversion.
- [Self-Implementation](SelfImplementation.md): Roadmap and status for re-implementing the language in itself.

## Goals

- **Documentation**: Record design decisions and the reasoning behind them.
- **Verification**: Provide a theoretical basis that can be verified through small-scale PoCs.
- **Future Planning**: Outline features that are planned but not yet fully implemented (e.g., custom user-implemented GC
  hooks or object constructors).
- **Onboarding**: Help contributors understand the core internals of the language and its runtime.

## Contributing

When introducing a new major feature or making significant changes to the language internals, it is recommended to first
create a PoC document here to discuss the design and theoretical implications.
