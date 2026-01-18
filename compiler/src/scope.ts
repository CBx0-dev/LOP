import {Binder, BoundFunctionMember, Type, type_eq_def, Variable} from "./binder";

export interface Scope {
    parent: Scope | null;
    types: Type[];
    variables: Variable[];
    functions: BoundFunctionMember[];
}

export function scope_init(parent: Scope | null): Scope {
    return {
        parent,
        types: [],
        variables: [],
        functions: []
    };
}

export function scope_push_scope(binder: Binder): void {
    binder.currentScope = scope_init(binder.currentScope);
}

export function scope_pop_scope(binder: Binder): void {
    binder.currentScope = binder.currentScope.parent;
}

export function scope_declare_type(scope: Scope, type: Type): void {
    // TODO check for a symbol with already the name
    scope.types.push(type);
}

export function scope_lookup_type(scope: Scope, name: string, generics: Type[] | null): Type | null {
    for (const type of scope.types) {
        if (type_eq_def(type, name, generics)) {
            return type;
        }
    }

    if (scope.parent) {
        return scope_lookup_type(scope.parent, name, generics);
    }

    return null;
}

export function scope_declare_variable(scope: Scope, variable: Variable): void {
    // TODO check for a symbol with already the name in the same scope
    scope.variables.push(variable);
}

export function scope_lookup_variable(scope: Scope, name: string): Variable | null {
    for (const variable of scope.variables) {
        if (variable.name == name) {
            return variable;
        }
    }

    if (scope.parent) {
        return scope_lookup_variable(scope.parent, name);
    }

    return null;
}

export function scope_declare_function(scope: Scope, func: BoundFunctionMember): void {
    // TODO check for a symbol with already the name in the same scope
    scope.functions.push(func);
}

export function scope_lookup_function(scope: Scope, name: string): BoundFunctionMember | null {
    for (const func of scope.functions) {
        if (func.name == name) {
            return func;
        }
    }

    if (scope.parent) {
        return scope_lookup_function(scope.parent, name);
    }

    return null;
}