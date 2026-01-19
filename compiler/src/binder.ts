import {
    AssignmentExpression,
    BinaryExpression,
    BlockStatement,
    BooleanExpression, BreakStatement,
    CallExpression,
    CastExpression,
    CharExpression,
    CompilationUnit, ContinueStatement,
    CtorExpression,
    EnumMember,
    ExpressionStatement,
    ExternFunctionMember,
    ExternTypeMember,
    FunctionMember,
    IdentifierExpression,
    IfStatement,
    IntegerExpression, IsExpression,
    MemberExpression,
    NodeType,
    NullExpression,
    ParenExpression,
    ReturnStatement,
    StringExpression,
    TypeClauseNode,
    TypeMember,
    TypeSignatureNode,
    TypeSignatureNodeDynamic,
    TypeSignatureNodeDynamicGeneric,
    UnaryExpression,
    UnknownNode,
    VariableStatement,
    WhileStatement
} from "./parser";
import {
    Scope,
    scope_declare_function,
    scope_declare_type,
    scope_declare_variable,
    scope_init,
    scope_lookup_function,
    scope_lookup_type,
    scope_lookup_variable,
    scope_pop_scope,
    scope_push_scope
} from "./scope";
import {Conversion, conversion_classify, conversion_init, ConversionRules} from "./conversion";
import {TokenType} from "./lexer";

export interface Binder {
    units: CompilationUnit[];
    trackedTypes: Type[];
    rootScope: Scope;
    currentScope: Scope;
    currentFunction: BoundFunctionMember | null;
    conversion: Conversion;

    // Core types
    voidType: Type;
    objectType: Type;
    boolType: Type;
    charType: Type;
    u8Type: Type;
    u16Type: Type;
    u32Type: Type;
    u64Type: Type;
    i8Type: Type;
    i16Type: Type;
    i32Type: Type;
    i64Type: Type;

    unaryOperators: BoundUnaryOperator[];
    binaryOperators: BoundBinaryOperator[];

    flags: {
        allowEnumIdentifiers: boolean;
        allowBreakStatement: boolean;
        allowContinueStatement: boolean;
    }
}

export enum BoundNode {
    PROGRAM,

    TYPE_MEMBER,
    FUNCTION_MEMBER,
    ENUM_MEMBER,

    BLOCK_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,
    EXPRESSION_STATEMENT,

    EMPTY_EXPRESSION,
    CAST_EXPRESSION,
    PAREN_EXPRESSION,
    ASSIGNMENT_EXPRESSION,
    CTOR_EXPRESSION,
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,
    VARIABLE_EXPRESSION,
    FUNCTION_EXPRESSION,
    ENUM_EXPRESSION,
    INTEGER_EXPRESSION,
    CHAR_EXPRESSION,
    STRING_EXPRESSION,
    BOOLEAN_EXPRESSION,
    CALL_EXPRESSION,
    MEMBER_EXPRESSION,
    IS_EXPRESSION,
    ENUM_FIELD_EXPRESSION,
    NULL_EXPRESSION,
}

export interface BoundUnknownNode {
    type: BoundNode;
}

export interface BoundUnknownExpression {
    type: BoundNode;
    returnType: Type;
}

export interface BoundProgram {
    type: BoundNode.PROGRAM;
    enums: BoundEnumMember[];
    externTypes: BoundTypeMember[];
    types: BoundTypeMember[];
    externFunctions: BoundFunctionMember[];
    functions: BoundFunctionMember[];
    trackedTypes: Type[];
}

export interface BoundEnumMemberItem {
    name: string;
}

export interface BoundEnumMember {
    type: BoundNode.ENUM_MEMBER;
    name: string;
    items: BoundEnumMemberItem[];
}

export interface BoundTypeMemberItem {
    name: string;
    type: Type;
}

export interface BoundTypeMemberMeta {
    generateTrace: boolean;
    traceName: string;
}

export interface BoundTypeMember {
    type: BoundNode.TYPE_MEMBER;
    name: string;
    items: BoundTypeMemberItem[];
    meta: BoundTypeMemberMeta
}

export interface BoundFunctionMember {
    type: BoundNode.FUNCTION_MEMBER;
    name: string;
    requiresGC: boolean;
    parameters: Variable[];
    variables: Variable[];
    body: BoundBlockStatement | null;
    returnType: Type;
    functionSignature: Type;
}

export interface BoundBlockStatement {
    type: BoundNode.BLOCK_STATEMENT;
    statements: BoundUnknownNode[];
}

export interface BoundIfStatement {
    type: BoundNode.IF_STATEMENT;
    condition: BoundUnknownExpression;
    thenCase: BoundUnknownNode;
    elseCase: BoundUnknownNode | null;
}

export interface BoundWhileStatement {
    type: BoundNode.WHILE_STATEMENT;
    condition: BoundUnknownExpression;
    body: BoundUnknownNode;
}

export interface BoundReturnStatement {
    type: BoundNode.RETURN_STATEMENT;
    value: BoundUnknownExpression | null;
}

export interface BoundBreakStatement {
    type: BoundNode.BREAK_STATEMENT;
}

export interface BoundContinueStatement {
    type: BoundNode.CONTINUE_STATEMENT;
}

export interface BoundExpressionStatement {
    type: BoundNode.EXPRESSION_STATEMENT;
    expression: BoundUnknownNode;
}

export interface BoundEmptyExpression {
    type: BoundNode.EMPTY_EXPRESSION;
}

export interface BoundCastExpression {
    type: BoundNode.CAST_EXPRESSION;
    returnType: Type;
    expression: BoundUnknownExpression;
    rule: ConversionRules;
}

export interface BoundNullExpression {
    type: BoundNode.NULL_EXPRESSION;
    returnType: Type;
}

export interface BoundParenExpression {
    type: BoundNode.PAREN_EXPRESSION;
    returnType: Type;
    expression: BoundUnknownExpression;
}

export interface BoundAssignmentExpression {
    type: BoundNode.ASSIGNMENT_EXPRESSION;
    returnType: Type;
    left: BoundUnknownExpression;
    right: BoundUnknownExpression;
}

export interface BoundUnaryExpression {
    type: BoundNode.UNARY_EXPRESSION;
    returnType: Type;
    operator: BoundUnaryOperator;
    right: BoundUnknownExpression;
}

export interface BoundBinaryExpression {
    type: BoundNode.BINARY_EXPRESSION;
    returnType: Type;
    left: BoundUnknownExpression;
    operator: BoundBinaryOperator;
    right: BoundUnknownExpression;
}

export interface BoundUnaryOperator {
    returnType: Type;
    tokenType: TokenType;
    right: Type;
}

export interface BoundBinaryOperator {
    returnType: Type;
    left: Type;
    tokenType: TokenType;
    right: Type;
}

export interface BoundCallExpression {
    type: BoundNode.CALL_EXPRESSION;
    returnType: Type;
    callee: BoundUnknownExpression;
    arguments: BoundUnknownExpression[];
}

export interface BoundMemberExpression {
    type: BoundNode.MEMBER_EXPRESSION;
    returnType: Type;
    object: BoundUnknownExpression;
    identifier: string;
}

export interface BoundIsExpression {
    type: BoundNode.IS_EXPRESSION;
    returnType: Type;
    left: BoundUnknownExpression;
    targetType: Type;
}

export interface BoundEnumFieldExpression {
    type: BoundNode.ENUM_FIELD_EXPRESSION;
    returnType: Type;
    name: string;
    item: string;
}

export interface BoundCtorExpression {
    type: BoundNode.CTOR_EXPRESSION;
    returnType: Type;
}

export interface BoundIntegerExpression {
    type: BoundNode.INTEGER_EXPRESSION;
    returnType: Type;
    value: string;
}

export interface BoundCharExpression {
    type: BoundNode.CHAR_EXPRESSION;
    returnType: Type;
    value: string;
}

export interface BoundStringExpression {
    type: BoundNode.STRING_EXPRESSION;
    returnType: Type;
    value: string;
}

export interface BoundBooleanExpression {
    type: BoundNode.BOOLEAN_EXPRESSION,
    returnType: Type;
    value: TokenType;
}

export interface BoundVariableExpression {
    type: BoundNode.VARIABLE_EXPRESSION;
    returnType: Type;
    variable: Variable;
}

export interface BoundFunctionExpression {
    type: BoundNode.FUNCTION_EXPRESSION;
    returnType: Type;
    func: BoundFunctionMember;
}

export interface BoundEnumExpression {
    type: BoundNode.ENUM_EXPRESSION;
    returnType: Type;
    enumMember: BoundEnumMember;
}

export enum TypeKind {
    PRIMITIVE,
    OBJECT,
    STRUCT
}

export interface Type {
    kind: TypeKind;
    name: string;
    generics: Type[] | null;
    cName: string;
    definition: BoundUnknownNode | null;
}

export enum VariableKind {
    PARAMETER,
    LOCAL,
    GLOBAL
}

export interface Variable {
    kind: VariableKind;
    name: string;
    id: number;
    type: Type;
}

export function type_init_simple(kind: TypeKind, name: string, cName: string): Type {
    return {
        kind,
        name,
        generics: null,
        cName,
        definition: null,
    };
}

export function type_init_complex(kind: TypeKind, name: string, cName: string, definition: BoundUnknownNode): Type {
    return {
        kind,
        name,
        generics: null,
        cName,
        definition
    }
}

export function type_init_dynamic(kind: TypeKind, name: string, cName: string, generics: Type[]): Type {
    return {
        kind,
        name,
        generics,
        cName,
        definition: null,
    }
}

export function type_eq_type(left: Type, right: Type): boolean {
    if (left.name != right.name) {
        return false;
    }

    if (!left.generics && right.generics ||
        left.generics && !right.generics) {
        return false;
    }

    if (!left.generics && !right.generics) {
        return true;
    }

    if (left.generics.length != right.generics.length) {
        return false;
    }

    for (let i: number = 0; i < left.generics.length; i++) {
        const leftGeneric: Type = left.generics[i];
        const rightGeneric: Type = right.generics[i];

        if (!type_eq_type(leftGeneric, rightGeneric)) {
            return false;
        }
    }

    return true;
}

export function type_eq_def(left: Type, name: string, generics: Type[] | null): boolean {
    if (left.name != name) {
        return false;
    }

    if (!left.generics && generics ||
        left.generics && !generics) {
        return false;
    }

    if (!left.generics && !generics) {
        return true;
    }

    if (left.generics.length != generics.length) {
        return false;
    }

    for (let i: number = 0; i < left.generics.length; i++) {
        const leftGeneric: Type = left.generics[i];
        const generic: Type = generics[i];

        if (!type_eq_type(leftGeneric, generic)) {
            return false;
        }
    }

    return true;
}

export function variable_init(func: BoundFunctionMember, kind: VariableKind, name: string, type: Type): Variable {
    const variable: Variable = {
        kind,
        name,
        id: func.variables.length + 1,
        type
    };

    if (type.kind == TypeKind.OBJECT) {
        func.requiresGC = true;
    }

    func.variables.push(variable);
    return variable;
}

export function parameter_init(name: string, type: Type): Variable {
    return {
        kind: VariableKind.PARAMETER,
        name: name,
        id: 0,
        type,
    };
}

function unary_operator_init(tokenType: TokenType, operandType: Type, returnType: Type): BoundUnaryOperator {
    return {
        tokenType,
        right: operandType,
        returnType
    };
}

function binary_operator_init(tokenType: TokenType, leftType: Type, rightType: Type, returnType: Type): BoundBinaryOperator {
    return {
        tokenType,
        left: leftType,
        right: rightType,
        returnType
    };
}

export function binder_init(units: CompilationUnit[]): Binder {
    const scope: Scope = scope_init(null);

    const voidType: Type = type_init_simple(TypeKind.PRIMITIVE, "void", "void");
    const objectType: Type = type_init_simple(TypeKind.OBJECT, "Object", "Object");
    const boolType: Type = type_init_simple(TypeKind.PRIMITIVE, "bool", "bool");
    const charType: Type = type_init_simple(TypeKind.PRIMITIVE, "char", "uchar");

    const u8Type: Type = type_init_simple(TypeKind.PRIMITIVE, "u8", "u8");
    const u16Type: Type = type_init_simple(TypeKind.PRIMITIVE, "u16", "u16");
    const u32Type: Type = type_init_simple(TypeKind.PRIMITIVE, "u32", "u32");
    const u64Type: Type = type_init_simple(TypeKind.PRIMITIVE, "u64", "u64");
    const i8Type: Type = type_init_simple(TypeKind.PRIMITIVE, "i8", "i8");
    const i16Type: Type = type_init_simple(TypeKind.PRIMITIVE, "i16", "i16");
    const i32Type: Type = type_init_simple(TypeKind.PRIMITIVE, "i32", "i32");
    const i64Type: Type = type_init_simple(TypeKind.PRIMITIVE, "i64", "i64");

    scope_declare_type(scope, objectType);
    scope_declare_type(scope, boolType);
    scope_declare_type(scope, charType);

    scope_declare_type(scope, u8Type);
    scope_declare_type(scope, u16Type);
    scope_declare_type(scope, u32Type);
    scope_declare_type(scope, u64Type);
    scope_declare_type(scope, i8Type);
    scope_declare_type(scope, i16Type);
    scope_declare_type(scope, i32Type);
    scope_declare_type(scope, i64Type);

    const conversion: Conversion = conversion_init(i8Type,
        i16Type,
        i32Type,
        i64Type,
        u8Type,
        u16Type,
        u32Type,
        u64Type,
        boolType,
        charType);

    const unaryOperators: BoundUnaryOperator[] = [
        unary_operator_init(TokenType.PLUS, i8Type, i8Type),
        unary_operator_init(TokenType.PLUS, i16Type, i16Type),
        unary_operator_init(TokenType.PLUS, i32Type, i32Type),
        unary_operator_init(TokenType.PLUS, i64Type, i64Type),

        unary_operator_init(TokenType.MINUS, i8Type, i8Type),
        unary_operator_init(TokenType.MINUS, i16Type, i16Type),
        unary_operator_init(TokenType.MINUS, i32Type, i32Type),
        unary_operator_init(TokenType.MINUS, i64Type, i64Type),

        unary_operator_init(TokenType.BANG, boolType, boolType),
    ];

    const binaryOperators: BoundBinaryOperator[] = [
        binary_operator_init(TokenType.PLUS, i8Type, i8Type, i8Type),
        binary_operator_init(TokenType.PLUS, i16Type, i16Type, i16Type),
        binary_operator_init(TokenType.PLUS, i32Type, i32Type, i32Type),
        binary_operator_init(TokenType.PLUS, i64Type, i64Type, i64Type),

        binary_operator_init(TokenType.MINUS, i8Type, i8Type, i8Type),
        binary_operator_init(TokenType.MINUS, i16Type, i16Type, i16Type),
        binary_operator_init(TokenType.MINUS, i32Type, i32Type, i32Type),
        binary_operator_init(TokenType.MINUS, i64Type, i64Type, i64Type),

        binary_operator_init(TokenType.STAR, i8Type, i8Type, i8Type),
        binary_operator_init(TokenType.STAR, i16Type, i16Type, i16Type),
        binary_operator_init(TokenType.STAR, i32Type, i32Type, i32Type),
        binary_operator_init(TokenType.STAR, i64Type, i64Type, i64Type),

        binary_operator_init(TokenType.SLASH, i8Type, i8Type, i8Type),
        binary_operator_init(TokenType.SLASH, i16Type, i16Type, i16Type),
        binary_operator_init(TokenType.SLASH, i32Type, i32Type, i32Type),
        binary_operator_init(TokenType.SLASH, i64Type, i64Type, i64Type),

        binary_operator_init(TokenType.EQUALS_EQUALS, boolType, boolType, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, charType, charType, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, objectType, objectType, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.EQUALS_EQUALS, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.BANG_EQUALS, boolType, boolType, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, charType, charType, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, objectType, objectType, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.BANG_EQUALS, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.LANGLE, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.LANGLE, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.LANGLE, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.LANGLE, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.LANGLE_EQUALS, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.LANGLE_EQUALS, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.LANGLE_EQUALS, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.LANGLE_EQUALS, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.RANGLE, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.RANGLE, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.RANGLE, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.RANGLE, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.RANGLE_EQUALS, i8Type, i8Type, boolType),
        binary_operator_init(TokenType.RANGLE_EQUALS, i16Type, i16Type, boolType),
        binary_operator_init(TokenType.RANGLE_EQUALS, i32Type, i32Type, boolType),
        binary_operator_init(TokenType.RANGLE_EQUALS, i64Type, i64Type, boolType),

        binary_operator_init(TokenType.AND_AND, boolType, boolType, boolType),
        binary_operator_init(TokenType.OR_OR, boolType, boolType, boolType),
    ];

    return {
        units,
        trackedTypes: [],
        rootScope: scope,
        currentScope: scope,
        currentFunction: null,
        conversion,

        voidType,
        objectType,
        boolType,
        charType,
        u8Type,
        u16Type,
        u32Type,
        u64Type,
        i8Type,
        i16Type,
        i32Type,
        i64Type,

        unaryOperators,
        binaryOperators,

        flags: {
            allowEnumIdentifiers: false,
            allowBreakStatement: false,
            allowContinueStatement: false
        }
    }
}

function generate_func_cName(generics: Type[]): string {
    let cName: string = "Func";
    for (const generic of generics) {
        cName += "_";
        cName += generic.cName;
    }

    return cName;
}

function bind_type_signature_dynamic_func(binder: Binder, dynamic: TypeSignatureNodeDynamic): Type {
    if (dynamic.generics.length < 1) {
        // TODO replace with diagnostics
        throw "Function type signature must have at least one generic type";
    }

    const generics: Type[] = [];
    for (let i: number = 0; i < dynamic.generics.length; i++) {
        const generic: TypeSignatureNodeDynamicGeneric = dynamic.generics[i];
        generics.push(bind_type_signature(binder, generic.typeSignature, i == 0));
    }

    let type: Type | null = scope_lookup_type(binder.currentScope, "Func", generics);
    if (!type) {
        const cName: string = generate_func_cName(generics);
        type = type_init_dynamic(TypeKind.PRIMITIVE, "Func", cName, generics);
        binder.trackedTypes.push(type);
        scope_declare_type(binder.rootScope, type);
    }

    return type;
}

function bind_type_signature_dynamic_span(binder: Binder, dynamic: TypeSignatureNodeDynamic): Type {
    if (dynamic.generics.length != 1) {
        // TODO replace with diagnostics
        throw "Span type signature must have one generic type";
    }

    const generics: Type[] = [bind_type_signature(binder, dynamic.generics[0].typeSignature, false)];

    let type: Type | null = scope_lookup_type(binder.currentScope, "Span", generics);
    if (!type) {
        let cName: string = "Span_";
        cName += generics[0].cName;
        type = type_init_dynamic(TypeKind.OBJECT, "Span", cName, generics);
        scope_declare_type(binder.rootScope, type);
    }

    return type;
}

function bind_type_signature_dynamic(binder: Binder, signature: TypeSignatureNode, dynamic: TypeSignatureNodeDynamic): Type {
    if (signature.identifier.value == "Func") {
        return bind_type_signature_dynamic_func(binder, dynamic);
    } else if (signature.identifier.value == "Span") {
        return bind_type_signature_dynamic_span(binder, dynamic);
    }

    throw "Unknown dynamic type signature";
}

function bind_type_signature(binder: Binder, signature: TypeSignatureNode, allowVoid: boolean): Type {
    if (signature.dynamic) {
        return bind_type_signature_dynamic(binder, signature, signature.dynamic);
    }
    if (signature.identifier.value == "void" && allowVoid) {
        return binder.voidType;
    }

    const type: Type | null = scope_lookup_type(binder.currentScope, signature.identifier.value, null);

    if (!type) {
        // TODO replace with diagnostics
        throw "Unknown type";
    }

    return type;
}

function bind_type_clause(binder: Binder, clause: TypeClauseNode, allowVoid: boolean): Type {
    return bind_type_signature(binder, clause.signature, allowVoid);
}

function bind_ctor_expression(binder: Binder, ctorExpression: CtorExpression): BoundCtorExpression {
    const type: Type = bind_type_signature(binder, ctorExpression.signature, false);
    if (type.kind != TypeKind.OBJECT) {
        // TODO replace with diagnostics
        throw "Can only use new with objects";
    }

    return {
        type: BoundNode.CTOR_EXPRESSION,
        returnType: type
    };
}

function is_node_assignable(node: BoundUnknownExpression): boolean {
    if (node.type == BoundNode.PAREN_EXPRESSION) {
        const parenExpression: BoundParenExpression = <BoundParenExpression>node;
        return is_node_assignable(parenExpression.expression);
    }

    return node.type == BoundNode.VARIABLE_EXPRESSION ||
        node.type == BoundNode.MEMBER_EXPRESSION;
}

function bind_assignment_expression(binder: Binder, assignmentExpression: AssignmentExpression): BoundAssignmentExpression {
    const left: BoundUnknownExpression = bind_expression(binder, assignmentExpression.left, null);
    if (!is_node_assignable(left)) {
        // TODO replace with diagnostics
        throw "Expression is not assignable";
    }

    const right: BoundUnknownExpression = bind_expression(binder, assignmentExpression.right, left.returnType);

    // TODO transform += to = ... + ...

    return {
        type: BoundNode.ASSIGNMENT_EXPRESSION,
        returnType: right.returnType,
        left,
        right
    };
}

function bind_unary_expression(binder: Binder, unaryExpression: UnaryExpression): BoundUnaryExpression {
    let right: BoundUnknownExpression = bind_expression(binder, unaryExpression.right, null);
    const operator: BoundUnaryOperator | null = lookup_unary_operator(binder, unaryExpression.operator.type, right.returnType);

    if (operator) {
        return {
            type: BoundNode.UNARY_EXPRESSION,
            returnType: operator.returnType,
            operator,
            right
        };
    }

    // Try to find an operator by converting operand
    for (const operator of binder.unaryOperators) {
        if (operator.tokenType != unaryExpression.operator.type) {
            continue;
        }

        const rightConversions: ConversionRules[] | null = conversion_classify(binder, right.returnType, operator.right, false);

        if (rightConversions != null) {
            right = bind_conversion(right, rightConversions);

            return {
                type: BoundNode.UNARY_EXPRESSION,
                returnType: operator.returnType,
                operator,
                right,
            };
        }
    }

    // TODO replace with diagnostics
    throw `Unary operator ${unaryExpression.operator.value} is not defined for type ${right.returnType.name}`;
}

function lookup_unary_operator(binder: Binder, tokenType: TokenType, operandType: Type): BoundUnaryOperator | null {
    for (const operator of binder.unaryOperators) {
        if (operator.tokenType == tokenType && operator.right == operandType) {
            return operator;
        }
    }

    return null;
}

function bind_binary_expression(binder: Binder, binaryExpression: BinaryExpression): BoundBinaryExpression {
    let left: BoundUnknownExpression = bind_expression(binder, binaryExpression.left, null);
    let right: BoundUnknownExpression = bind_expression(binder, binaryExpression.right, null);

    if (binaryExpression.operator.type == TokenType.EQUALS_EQUALS ||
        binaryExpression.operator.type == TokenType.BANG_EQUALS) {
        if (left.type == BoundNode.NULL_EXPRESSION && right.type != BoundNode.NULL_EXPRESSION) {
            left = bind_expression(binder, binaryExpression.left, right.returnType);
        } else if (right.type == BoundNode.NULL_EXPRESSION && left.type != BoundNode.NULL_EXPRESSION) {
            right = bind_expression(binder, binaryExpression.right, left.returnType);
        }
    }

    const operator: BoundBinaryOperator | null = lookup_binary_operator(binder, binaryExpression.operator.type, left.returnType, right.returnType);

    if (operator) {
        return {
            type: BoundNode.BINARY_EXPRESSION,
            returnType: operator.returnType,
            left,
            operator,
            right
        };
    }

    // Try to find an operator by converting operands
    for (const operator of binder.binaryOperators) {
        if (operator.tokenType != binaryExpression.operator.type) {
            continue;
        }

        const leftConversions: ConversionRules[] | null = conversion_classify(binder, left.returnType, operator.left, false);
        const rightConversions: ConversionRules[] | null = conversion_classify(binder, right.returnType, operator.right, false);

        if (leftConversions != null && rightConversions != null) {
            left = bind_conversion(left, leftConversions);
            right = bind_conversion(right, rightConversions);

            return {
                type: BoundNode.BINARY_EXPRESSION,
                returnType: operator.returnType,
                left,
                operator,
                right
            };
        }
    }

    // TODO replace with diagnostics
    throw `Binary operator ${binaryExpression.operator.value} is not defined for types ${left.returnType.name} and ${right.returnType.name}`;
}

function lookup_binary_operator(binder: Binder, tokenType: TokenType, leftType: Type, rightType: Type): BoundBinaryOperator | null {
    for (const operator of binder.binaryOperators) {
        if (operator.tokenType == tokenType && operator.left == leftType && operator.right == rightType) {
            return operator;
        }
    }

    return null;
}

function bind_call_expression(binder: Binder, callExpression: CallExpression): BoundCallExpression {
    const callee: BoundUnknownExpression = bind_expression(binder, callExpression.callee, null);
    if (callee.returnType.name != "Func") {
        // TODO replace with diagnostic
        throw "Expression is not callable";
    }
    if (!callee.returnType.generics) {
        throw "Function requires generics";
    }

    if (callee.returnType.generics.length - 1 != callExpression.arguments.length) {
        // TODO replace with diagnostic
        throw "Function argument count mismatch";
    }

    const args: BoundUnknownExpression[] = [];
    for (let i: number = 0; i < callExpression.arguments.length; i++) {
        const expectedType: Type = callee.returnType.generics[i + 1];
        const argument: BoundUnknownExpression = bind_expression(binder, callExpression.arguments[i].argument, expectedType);
        args.push(argument);
    }

    return {
        type: BoundNode.CALL_EXPRESSION,
        returnType: callee.returnType.generics[0],
        arguments: args,
        callee
    };
}

function bind_member_expression(binder: Binder, memberExpression: MemberExpression): BoundUnknownExpression {
    let oldEnumIdentifiers: boolean = binder.flags.allowEnumIdentifiers;
    binder.flags.allowEnumIdentifiers = true;
    const object: BoundUnknownExpression = bind_expression(binder, memberExpression.object, null);
    binder.flags.allowEnumIdentifiers = oldEnumIdentifiers;

    if (!object.returnType.definition) {
        // TODO replace with diagnostic
        throw "Cannot access this expression";
    }
    const identifier: string = memberExpression.identifier.value;

    if (object.returnType.definition.type == BoundNode.TYPE_MEMBER) {
        const definition: BoundTypeMember = <BoundTypeMember>object.returnType.definition;
        for (const item of definition.items) {
            if (item.name == identifier) {
                return (<BoundMemberExpression>{
                    type: BoundNode.MEMBER_EXPRESSION,
                    returnType: item.type,
                    object,
                    identifier
                });
            }
        }
    } else if (object.returnType.definition.type == BoundNode.ENUM_MEMBER) {
        const definition: BoundEnumMember = <BoundEnumMember>object.returnType.definition;
        for (const item of definition.items) {
            if (item.name == identifier) {
                return (<BoundEnumFieldExpression>{
                    type: BoundNode.ENUM_FIELD_EXPRESSION,
                    returnType: object.returnType,
                    name: object.returnType.name,
                    item: item.name
                });
            }
        }
    }

    // TODO replace with diagnostic
    throw "Cannot access this expression";
}

function bind_is_expression(binder: Binder, isExpression: IsExpression): BoundIsExpression {
    const left: BoundUnknownExpression = bind_expression(binder, isExpression.left, null);
    if (left.returnType.kind != TypeKind.OBJECT) {
        throw "Cannot use 'is' with non-object type";
    }
    const targetType: Type = bind_type_signature(binder, isExpression.typeSignature, false);
    if (targetType.kind != TypeKind.OBJECT) {
        throw "Cannot target non-object type in 'is'";
    }

    return {
        type: BoundNode.IS_EXPRESSION,
        returnType: binder.boolType,
        left,
        targetType,
    };
}

function bind_integer_expression(binder: Binder, integerExpression: IntegerExpression): BoundIntegerExpression {
    return {
        type: BoundNode.INTEGER_EXPRESSION,
        returnType: binder.i32Type,
        value: integerExpression.value.value
    };
}

function bind_char_expression(binder: Binder, charExpression: CharExpression): BoundCharExpression {
    return {
        type: BoundNode.CHAR_EXPRESSION,
        returnType: binder.charType,
        value: charExpression.value.value
    };
}

function bind_string_expression(binder: Binder, stringExpression: StringExpression): BoundStringExpression {
    const type: Type | null = scope_lookup_type(binder.currentScope, "String", null);
    if (!type) {
        throw "Cannot find string type";
    }

    return {
        type: BoundNode.STRING_EXPRESSION,
        returnType: type,
        value: stringExpression.value.value
    };
}

function bind_boolean_expression(binder: Binder, booleanExpression: BooleanExpression): BoundBooleanExpression {
    return {
        type: BoundNode.BOOLEAN_EXPRESSION,
        returnType: binder.boolType,
        value: booleanExpression.value.type
    };
}

function bind_identifier_expression(binder: Binder, identifierExpression: IdentifierExpression): BoundUnknownExpression {
    {
        const variable: Variable | null = scope_lookup_variable(binder.currentScope, identifierExpression.value.value);
        if (variable) {
            return (<BoundVariableExpression>{
                type: BoundNode.VARIABLE_EXPRESSION,
                returnType: variable.type,
                variable
            });
        }
    }

    {
        const func: BoundFunctionMember | null = scope_lookup_function(binder.currentScope, identifierExpression.value.value);
        if (func) {
            return (<BoundFunctionExpression>{
                type: BoundNode.FUNCTION_EXPRESSION,
                returnType: func.functionSignature,
                func
            });
        }
    }

    if (binder.flags.allowEnumIdentifiers) {
        const type: Type | null = scope_lookup_type(binder.currentScope, identifierExpression.value.value, null);
        if (type && type.definition && type.definition.type == BoundNode.ENUM_MEMBER) {
            return (<BoundEnumExpression>{
                type: BoundNode.ENUM_EXPRESSION,
                returnType: type,
                enumMember: type.definition
            });
        }
    }

    // TODO replace with diagnostics
    throw "Symbol not found";
}

function bind_paren_expression(binder: Binder, parenExpression: ParenExpression): BoundParenExpression {
    const expression: BoundUnknownExpression = bind_expression(binder, parenExpression.expression, null);

    return {
        type: BoundNode.PAREN_EXPRESSION,
        expression,
        returnType: expression.returnType
    };
}

function bind_cast_expression(binder: Binder, castExpression: CastExpression): BoundUnknownExpression {
    const targetType: Type = bind_type_signature(binder, castExpression.typeSignature, false);
    const expression: BoundUnknownExpression = bind_expression(binder, castExpression.expression, null);

    const conversions: ConversionRules[] | null = conversion_classify(binder, expression.returnType, targetType, true);
    if (!conversions) {
        throw "Expression not castable";
    }

    return bind_conversion(expression, conversions);
}

function bind_null_expression(binder: Binder, nullExpression: NullExpression): BoundUnknownExpression {
    return {
        type: BoundNode.NULL_EXPRESSION,
        returnType: binder.objectType
    };
}

function bind_conversion(boundExpression: BoundUnknownExpression, conversions: ConversionRules[]): BoundUnknownExpression {
    let innerExpression: BoundUnknownExpression = boundExpression;
    for (const conversion of conversions) {
        innerExpression = (<BoundCastExpression>{
            type: BoundNode.CAST_EXPRESSION,
            returnType: conversion.to,
            expression: innerExpression,
            rule: conversion
        });
    }

    return (<BoundParenExpression>{
        type: BoundNode.PAREN_EXPRESSION,
        expression: innerExpression,
        returnType: innerExpression.returnType
    });
}

function bind_expression_internal(binder: Binder, expression: UnknownNode): BoundUnknownExpression {
    switch (expression.type) {
        case NodeType.CTOR_EXPRESSION:
            return bind_ctor_expression(binder, expression as CtorExpression);
        case NodeType.ASSIGNMENT_EXPRESSION:
            return bind_assignment_expression(binder, expression as AssignmentExpression);
        case NodeType.UNARY_EXPRESSION:
            return bind_unary_expression(binder, expression as UnaryExpression);
        case NodeType.BINARY_EXPRESSION:
            return bind_binary_expression(binder, expression as BinaryExpression);
        case NodeType.CALL_EXPRESSION:
            return bind_call_expression(binder, expression as CallExpression);
        case NodeType.MEMBER_EXPRESSION:
            return bind_member_expression(binder, expression as MemberExpression);
        case NodeType.IS_EXPRESSION:
            return bind_is_expression(binder, expression as IsExpression);
        case NodeType.INTEGER_EXPRESSION:
            return bind_integer_expression(binder, expression as IntegerExpression);
        case NodeType.CHAR_EXPRESSION:
            return bind_char_expression(binder, expression as CharExpression);
        case NodeType.STRING_EXPRESSION:
            return bind_string_expression(binder, expression as StringExpression);
        case NodeType.BOOLEAN_EXPRESSION:
            return bind_boolean_expression(binder, expression as BooleanExpression);
        case NodeType.IDENTIFIER_EXPRESSION:
            return bind_identifier_expression(binder, expression as IdentifierExpression);
        case NodeType.PAREN_EXPRESSION:
            return bind_paren_expression(binder, expression as ParenExpression);
        case NodeType.CAST_EXPRESSION:
            return bind_cast_expression(binder, expression as CastExpression);
        case NodeType.NULL_EXPRESSION:
            return bind_null_expression(binder, expression as NullExpression);
    }

    // TODO do something other then throwing an exception
    throw "(binder) Unknown expression";
}

function bind_expression(binder: Binder, expression: UnknownNode, expectedType: Type | null): BoundUnknownExpression {
    const boundExpression: BoundUnknownExpression = bind_expression_internal(binder, expression);

    if (boundExpression.type == BoundNode.NULL_EXPRESSION) {
        if (expectedType == null) {
            return boundExpression;
        }

        if (expectedType.kind != TypeKind.OBJECT) {
            throw "(binder) Cannot assign null to unexpected expression";
        }
        boundExpression.returnType = expectedType;
    }

    if (expectedType && !type_eq_type(boundExpression.returnType, expectedType)) {
        const conversions: ConversionRules[] | null = conversion_classify(binder, boundExpression.returnType, expectedType, false);
        if (!conversions || conversions.length == 0) {
            throw "Not compatible expression";
        }

        return bind_conversion(boundExpression, conversions);
    }

    return boundExpression;
}

function bind_block_statement(binder: Binder, blockStatement: BlockStatement): BoundBlockStatement {
    scope_push_scope(binder)
    const statements: BoundUnknownNode[] = [];

    for (const statement of blockStatement.statements) {
        statements.push(bind_statement(binder, statement));
    }

    scope_pop_scope(binder);
    return {
        type: BoundNode.BLOCK_STATEMENT,
        statements
    }
}

function bind_variable_statement(binder: Binder, variableStatement: VariableStatement): BoundUnknownNode {
    if (!binder.currentFunction) {
        throw "Missing function";
    }

    const type: Type = bind_type_clause(binder, variableStatement.typeClause, false);

    const variable: Variable = variable_init(binder.currentFunction, VariableKind.LOCAL, variableStatement.identifier.value, type);
    scope_declare_variable(binder.currentScope, variable);

    let initializer: BoundUnknownNode;

    if (variableStatement.initializer) {
        const right: BoundUnknownExpression = bind_expression(binder, variableStatement.initializer, type);

        initializer = (<BoundAssignmentExpression>{
            type: BoundNode.ASSIGNMENT_EXPRESSION,
            returnType: variable.type,
            left: (<BoundVariableExpression>{
                type: BoundNode.VARIABLE_EXPRESSION,
                returnType: variable.type,
                variable
            }),
            right: right
        });
    } else {
        initializer = (<BoundEmptyExpression>{
            type: BoundNode.EMPTY_EXPRESSION
        });
    }

    return {
        type: BoundNode.EXPRESSION_STATEMENT,
        expression: initializer
    } as BoundExpressionStatement;
}

function bind_if_statement(binder: Binder, ifStatement: IfStatement): BoundIfStatement {
    const condition: BoundUnknownExpression = bind_expression(binder, ifStatement.condition, binder.boolType);
    const thenCase: BoundUnknownNode = bind_statement(binder, ifStatement.thenCase);

    let elseCase: BoundUnknownNode | null = null;
    if (ifStatement.elseCase) {
        elseCase = bind_statement(binder, ifStatement.elseCase.thenCase);
    }

    return {
        type: BoundNode.IF_STATEMENT,
        condition,
        thenCase,
        elseCase
    };
}

function bind_while_statement(binder: Binder, whileStatement: WhileStatement): BoundWhileStatement {
    const condition: BoundUnknownExpression = bind_expression(binder, whileStatement.condition, binder.boolType);

    let oldBreakStatement: boolean = binder.flags.allowBreakStatement;
    let oldContinueStatement: boolean = binder.flags.allowContinueStatement;
    binder.flags.allowBreakStatement = true;
    binder.flags.allowContinueStatement = true;
    const body: BoundUnknownNode = bind_statement(binder, whileStatement.body);
    binder.flags.allowBreakStatement = oldBreakStatement;
    binder.flags.allowContinueStatement = oldContinueStatement;

    return {
        type: BoundNode.WHILE_STATEMENT,
        condition,
        body
    };
}

function bind_return_statement(binder: Binder, returnStatement: ReturnStatement): BoundReturnStatement {
    if (!binder.currentFunction) {
        throw "Not in function";
    }

    if (binder.currentFunction.returnType == binder.voidType && returnStatement.value) {
        // TODO replace with diagnostics
        throw "Cannot return value from void function";
    }

    if (binder.currentFunction.returnType != binder.voidType && !returnStatement.value) {
        // TODO replace with diagnostics
        throw "Must return value from non-void function";
    }

    let value: BoundUnknownExpression | null = null;
    if (returnStatement.value) {
        value = bind_expression(binder, returnStatement.value, binder.currentFunction.returnType);
    }

    return {
        type: BoundNode.RETURN_STATEMENT,
        value
    };
}

function bind_break_statement(binder: Binder, breakStatement: BreakStatement): BoundBreakStatement {
    if (!binder.flags.allowBreakStatement) {
        throw "Break statements are not allowed here";
    }

    return {
        type: BoundNode.BREAK_STATEMENT
    };
}

function bind_continue_statement(binder: Binder, continueStatement: ContinueStatement): BoundContinueStatement {
    if (!binder.flags.allowContinueStatement) {
        throw "Continue statements are not allowed here";
    }

    return {
        type: BoundNode.CONTINUE_STATEMENT
    };
}

function bind_expression_statement(binder: Binder, expressionStatement: ExpressionStatement): BoundExpressionStatement {
    const expression: BoundUnknownNode = bind_expression(binder, expressionStatement.expression, null);

    return {
        type: BoundNode.EXPRESSION_STATEMENT,
        expression
    }
}

function bind_statement(binder: Binder, statement: UnknownNode): BoundUnknownNode {
    switch (statement.type) {
        case NodeType.BLOCK_STATEMENT:
            return bind_block_statement(binder, statement as BlockStatement);
        case NodeType.VARIABLE_STATEMENT:
            return bind_variable_statement(binder, statement as VariableStatement);
        case NodeType.IF_STATEMENT:
            return bind_if_statement(binder, statement as IfStatement);
        case NodeType.WHILE_STATEMENT:
            return bind_while_statement(binder, statement as WhileStatement);
        case NodeType.RETURN_STATEMENT:
            return bind_return_statement(binder, statement as ReturnStatement);
        case NodeType.BREAK_STATEMENT:
            return bind_break_statement(binder, statement as BreakStatement);
        case NodeType.CONTINUE_STATEMENT:
            return bind_continue_statement(binder, statement as ContinueStatement);
        case NodeType.EXPRESSION_STATEMENT:
            return bind_expression_statement(binder, statement as ExpressionStatement);
    }

    // TODO do something other then throwing an exception
    throw "Unknown statement";
}

function bind_enum_member(binder: Binder, enumMember: EnumMember): BoundEnumMember {
    const items: BoundEnumMemberItem[] = [];

    for (const item of enumMember.items) {
        // TODO detect duplicating names in items
        items.push({
            name: item.identifier.value
        });
    }

    const node: BoundEnumMember = {
        type: BoundNode.ENUM_MEMBER,
        name: enumMember.identifier.value,
        items
    };

    const type: Type = type_init_complex(TypeKind.PRIMITIVE, node.name, node.name, node);
    scope_declare_type(binder.currentScope, type);

    return node;
}

function bind_extern_type_member(binder: Binder, externTypeMember: ExternTypeMember): BoundTypeMember {
    const items: BoundTypeMemberItem[] = [];

    for (const item of externTypeMember.items) {
        // TODO detect duplicating names in items
        const type: Type = bind_type_clause(binder, item.typeClause, false);
        items.push({
            name: item.identifier.value,
            type
        });
    }

    const boundTypeMember: BoundTypeMember = {
        type: BoundNode.TYPE_MEMBER,
        name: externTypeMember.identifier.value,
        items,
        meta: {
            generateTrace: false,
            traceName: "ShouldNotAppear"
        }
    };

    const type: Type = type_init_complex(TypeKind.OBJECT, boundTypeMember.name, boundTypeMember.name, boundTypeMember);
    scope_declare_type(binder.currentScope, type);

    return boundTypeMember;
}

function bind_type_member_signature(binder: Binder, typeMember: TypeMember): void {
    const node: BoundTypeMember = {
        type: BoundNode.TYPE_MEMBER,
        name: typeMember.identifier.value,
        items: [],
        meta: {
            generateTrace: false,
            traceName: "object_empty_trace"
        }
    }

    const type: Type = type_init_complex(TypeKind.OBJECT, node.name, node.name, node);
    scope_declare_type(binder.currentScope, type);
}

function bind_type_member(binder: Binder, typeMember: TypeMember): BoundTypeMember {
    const type: Type = scope_lookup_type(binder.currentScope, typeMember.identifier.value, null);
    if (!type.definition || type.definition.type != BoundNode.TYPE_MEMBER) {
        throw "Cannot find type";
    }
    const definition: BoundTypeMember = <BoundTypeMember>type.definition;

    for (const item of typeMember.items) {
        // TODO detect duplicating names in items
        const type: Type = bind_type_clause(binder, item.typeClause, false);
        if (type.kind == TypeKind.OBJECT) {
            definition.meta.generateTrace = true;
            definition.meta.traceName = typeMember.identifier.value + "_trace";
        }

        definition.items.push({
            name: item.identifier.value,
            type
        });
    }

    return definition;
}

function bind_extern_function_member(binder: Binder, externFunctionMember: ExternFunctionMember): BoundFunctionMember {
    const generics: Type[] = [];
    const returnType: Type = bind_type_clause(binder, externFunctionMember.returnType, true);
    generics.push(returnType);
    scope_push_scope(binder);

    let requiresGC: boolean = false;
    const parameters: Variable[] = [];

    // TODO check for name duplicates
    for (const parameter of externFunctionMember.parameters) {
        const type: Type = bind_type_clause(binder, parameter.typeClause, false);
        const variable: Variable = parameter_init(parameter.identifier.value, type);

        if (variable.type.kind == TypeKind.OBJECT) {
            requiresGC = true;
        }

        parameters.push(variable);
        generics.push(type);
        scope_declare_variable(binder.currentScope, variable);
    }

    const cName: string = generate_func_cName(generics);
    const functionSignature: Type = type_init_dynamic(TypeKind.PRIMITIVE, "Func", cName, generics);

    const node: BoundFunctionMember = {
        type: BoundNode.FUNCTION_MEMBER,
        name: externFunctionMember.identifier.value,
        returnType,
        requiresGC,
        parameters,
        variables: [],
        body: null,
        functionSignature
    };

    scope_pop_scope(binder);
    scope_declare_function(binder.rootScope, node);
    return node;
}

function bind_function_member_signature(binder: Binder, functionMember: FunctionMember): void {
    const generics: Type[] = [];
    const returnType: Type = bind_type_clause(binder, functionMember.returnType, true);
    generics.push(returnType);

    let requiresGC: boolean = false;
    const parameters: Variable[] = [];

    // TODO check for name duplicates
    for (const parameter of functionMember.parameters) {
        const type: Type = bind_type_clause(binder, parameter.typeClause, false);
        const variable: Variable = parameter_init(parameter.identifier.value, type);

        if (variable.type.kind == TypeKind.OBJECT) {
            requiresGC = true;
        }

        parameters.push(variable);
        generics.push(type);
    }

    const cName: string = generate_func_cName(generics);
    const functionSignature: Type = type_init_dynamic(TypeKind.PRIMITIVE, "Func", cName, generics);

    const node: BoundFunctionMember = {
        type: BoundNode.FUNCTION_MEMBER,
        name: functionMember.identifier.value,
        returnType,
        requiresGC,
        parameters,
        variables: [],
        body: null,
        functionSignature
    };

    scope_declare_function(binder.rootScope, node);
}

function bind_function_member(binder: Binder, functionMember: FunctionMember): BoundFunctionMember {
    const func: BoundFunctionMember | null = scope_lookup_function(binder.currentScope, functionMember.identifier.value);
    if (!func) {
        throw "Cannot find function";
    }

    scope_push_scope(binder);
    binder.currentFunction = func;

    for (const parameter of func.parameters) {
        scope_declare_variable(binder.currentScope, parameter);
    }

    func.body = bind_block_statement(binder, functionMember.body);
    scope_pop_scope(binder);

    return func;
}

export function binder_bind(binder: Binder): BoundProgram {
    const enums: BoundEnumMember[] = [];
    const externTypes: BoundTypeMember[] = [];
    const types: BoundTypeMember[] = [];
    const externFunctions: BoundFunctionMember[] = [];
    const functions: BoundFunctionMember[] = [];

    // Bind enums
    for (const unit of binder.units) {
        for (const enumMember of unit.enums) {
            enums.push(bind_enum_member(binder, enumMember));
        }
    }

    // Bind extern types
    for (const unit of binder.units) {
        for (const externType of unit.externTypes) {
            externTypes.push(bind_extern_type_member(binder, externType));
        }
    }

    // Bind type signatures
    for (const unit of binder.units) {
        for (const type of unit.types) {
            bind_type_member_signature(binder, type);
        }
    }

    // Bind types
    for (const unit of binder.units) {
        for (const type of unit.types) {
            types.push(bind_type_member(binder, type));
        }
    }

    // Bind extern functions
    for (const unit of binder.units) {
        for (const func of unit.externFunctions) {
            externFunctions.push(bind_extern_function_member(binder, func));
        }
    }

    // Bind function signatures
    for (const unit of binder.units) {
        for (const func of unit.functions) {
            bind_function_member_signature(binder, func);
        }
    }

    // Bind functions
    for (const unit of binder.units) {
        for (const func of unit.functions) {
            functions.push(bind_function_member(binder, func));
        }
    }

    return {
        type: BoundNode.PROGRAM,
        enums,
        externTypes,
        types,
        externFunctions,
        functions,
        trackedTypes: binder.trackedTypes
    }
}