import * as fs from "fs";

import {
    BoundAssignmentExpression,
    BoundBinaryExpression,
    BoundBlockStatement,
    BoundBooleanExpression, BoundBreakStatement,
    BoundCallExpression,
    BoundCastExpression,
    BoundCharExpression, BoundContinueStatement,
    BoundCtorExpression,
    BoundEnumFieldExpression,
    BoundEnumMember,
    BoundExpressionStatement,
    BoundFunctionExpression,
    BoundFunctionMember,
    BoundIfStatement,
    BoundIntegerExpression, BoundIsExpression,
    BoundMemberExpression,
    BoundNode,
    BoundNullExpression,
    BoundParenExpression,
    BoundProgram,
    BoundReturnStatement,
    BoundStringExpression,
    BoundTypeMember,
    BoundUnaryExpression,
    BoundUnknownNode,
    BoundVariableExpression,
    BoundWhileStatement,
    Type,
    TypeKind,
    Variable
} from "./binder";
import {TokenType} from "./lexer";

export interface Emitter {
    stream: fs.WriteStream;
    intention: number;
    currentFunction: BoundFunctionMember | null;
}

export function emitter_init(stream: fs.WriteStream): Emitter {
    return {
        stream,
        intention: 0,
        currentFunction: null
    };
}

function write(emitter: Emitter, content: string): void {
    for (let i: number = 0; i < emitter.intention; i++) {
        emitter.stream.write(" ");
    }

    emitter.stream.write(content);
}

function write_nit(emitter: Emitter, content: string): void {
    emitter.stream.write(content);
}

function writeln_nit(emitter: Emitter, content: string): void {
    emitter.stream.write(content);
    emitter.stream.write("\n");
}

function writeln(emitter: Emitter, content: string): void {
    write(emitter, content);
    emitter.stream.write("\n");
}

function inc_intention(emitter: Emitter): void {
    emitter.intention += 4;
}

function dec_intention(emitter: Emitter): void {
    emitter.intention -= 4;
}

function emit_header(emitter: Emitter): void {
    writeln(emitter, "#include \"gc.h\"");
    writeln(emitter, "#include \"primitive.h\"");
    writeln(emitter, "#include \"object.h\"");
    writeln(emitter, "#include \"string_obj.h\"");
    writeln(emitter, "");
}

function emit_type(emitter: Emitter, type: Type): void {
    if (type.name == "Span") {
        if (!type.generics) {
            throw "Missing generic type";
        }
        emit_type(emitter, type.generics[0]);
        write_nit(emitter, "*");
        return;
    }
    write_nit(emitter, type.cName);
}

function emit_variable_name(emitter: Emitter, variable: Variable): void {
    write_nit(emitter, variable.name);
    write_nit(emitter, variable.id.toString());
}

function emit_cast_expression(emitter: Emitter, castExpression: BoundCastExpression): void {
    write_nit(emitter, "(");
    emit_type(emitter, castExpression.returnType);
    write_nit(emitter, ")");
    write_nit(emitter, "(");
    emit_expression(emitter, castExpression.expression);
    write_nit(emitter, ")");
}

function emit_null_expression(emitter: Emitter, nullExpression: BoundNullExpression): void {
    write_nit(emitter, "NULL");
}

function emit_paren_expression(emitter: Emitter, parenExpression: BoundParenExpression): void {
    write_nit(emitter, "(");
    emit_expression(emitter, parenExpression.expression);
    write_nit(emitter, ")");
}

function emit_ctor_expression(emitter: Emitter, ctorExpression: BoundCtorExpression): void {
    if (!ctorExpression.returnType.definition || ctorExpression.returnType.definition.type != BoundNode.TYPE_MEMBER) {
        throw "Definition must be set";
    }

    const definition: BoundTypeMember = ctorExpression.returnType.definition as BoundTypeMember;

    write_nit(emitter, "OBJECT_CTOR(");
    write_nit(emitter, definition.name);
    write_nit(emitter, "_impl, ");
    write_nit(emitter, definition.name);
    write_nit(emitter, "_type");
    write_nit(emitter, ")");
}

function emit_assignment_expression(emitter: Emitter, assignmentExpression: BoundAssignmentExpression): void {
    emit_expression(emitter, assignmentExpression.left);
    write_nit(emitter, " = ");
    emit_expression(emitter, assignmentExpression.right);
}

function emit_unary_expression(emitter: Emitter, unaryExpression: BoundUnaryExpression): void {
    switch (unaryExpression.operator.tokenType) {
        case TokenType.MINUS:
            write_nit(emitter, "-");
            break;
        case TokenType.PLUS:
            write_nit(emitter, "+");
            break;
        case TokenType.BANG:
            write_nit(emitter, "!");
            break;
    }
    emit_expression(emitter, unaryExpression.right);
}

function emit_binary_expression(emitter: Emitter, binaryExpression: BoundBinaryExpression): void {
    emit_expression(emitter, binaryExpression.left);
    write_nit(emitter, " ");
    switch (binaryExpression.operator.tokenType) {
        case TokenType.MINUS:
            write_nit(emitter, "-");
            break;
        case TokenType.PLUS:
            write_nit(emitter, "+");
            break;
        case TokenType.STAR:
            write_nit(emitter, "*");
            break;
        case TokenType.SLASH:
            write_nit(emitter, "/");
            break;
        case TokenType.EQUALS_EQUALS:
            write_nit(emitter, "==");
            break;
        case TokenType.BANG_EQUALS:
            write_nit(emitter, "!=");
            break;
        case TokenType.LANGLE:
            write_nit(emitter, "<");
            break;
        case TokenType.LANGLE_EQUALS:
            write_nit(emitter, "<=");
            break;
        case TokenType.RANGLE:
            write_nit(emitter, ">");
            break;
        case TokenType.RANGLE_EQUALS:
            write_nit(emitter, ">=");
            break;
        case TokenType.AND_AND:
            write_nit(emitter, "&&");
            break;
        case TokenType.OR_OR:
            write_nit(emitter, "||");
            break;
    }
    write_nit(emitter, " ");
    emit_expression(emitter, binaryExpression.right);
}

function emit_call_expression(emitter: Emitter, callExpression: BoundCallExpression): void {
    write_nit(emitter, "(");
    emit_expression(emitter, callExpression.callee);
    write_nit(emitter, ")");
    write_nit(emitter, "(");

    for (let i: number = 0; i < callExpression.arguments.length; i++) {
        if (i > 0) {
            write_nit(emitter, ", ");
        }

        emit_expression(emitter, callExpression.arguments[i]);
    }

    write_nit(emitter, ")");
}

function emit_member_expression(emitter: Emitter, memberExpression: BoundMemberExpression): void {
    write_nit(emitter, "(");
    emit_expression(emitter, memberExpression.object);
    write_nit(emitter, ")");
    write_nit(emitter, "->");
    write_nit(emitter, memberExpression.identifier);
}

function emit_is_expression(emitter: Emitter, isExpression: BoundIsExpression): void {
    write_nit(emitter, "OBJECT_TYPEOF(");
    emit_expression(emitter, isExpression.left);
    write_nit(emitter, ") == &");
    write_nit(emitter, isExpression.targetType.name);
    write_nit(emitter, "_type");
}

function emit_enum_field_expression(emitter: Emitter, enumFieldExpression: BoundEnumFieldExpression): void {
    write_nit(emitter, enumFieldExpression.name);
    write_nit(emitter, "_");
    write_nit(emitter, enumFieldExpression.item);
}

function emit_integer_expression(emitter: Emitter, integerExpression: BoundIntegerExpression): void {
    write_nit(emitter, integerExpression.value);
}

function emit_char_expression(emitter: Emitter, charExpression: BoundCharExpression): void {
    write_nit(emitter, charExpression.value);
}

function emit_string_expression(emitter: Emitter, stringExpression: BoundStringExpression): void {
    write_nit(emitter, "STRING_CTOR(String_impl, String_type, (uchar*)");
    write_nit(emitter, stringExpression.value);
    write_nit(emitter, ", ");
    // TODO cannot count raw value length because of escape sequences
    write_nit(emitter, (stringExpression.value.length - 2).toString());
    write_nit(emitter, ")");
}

function emit_boolean_expression(emitter: Emitter, booleanExpression: BoundBooleanExpression): void {
    if (booleanExpression.value == TokenType.TRUE_KEYWORD) {
        write_nit(emitter, "1");
    } else {
        write_nit(emitter, "0");
    }
}

function emit_variable_expression(emitter: Emitter, variableExpression: BoundVariableExpression): void {
    write_nit(emitter, variableExpression.variable.name);
    write_nit(emitter, variableExpression.variable.id.toString());
}

function emit_function_expression(emitter: Emitter, functionExpression: BoundFunctionExpression): void {
    write_nit(emitter, functionExpression.func.name);
}

function emit_expression(emitter: Emitter, expression: BoundUnknownNode): void {
    switch (expression.type) {
        case BoundNode.CAST_EXPRESSION:
            emit_cast_expression(emitter, expression as BoundCastExpression);
            break;
        case BoundNode.NULL_EXPRESSION:
            emit_null_expression(emitter, expression as BoundNullExpression);
            break;
        case BoundNode.PAREN_EXPRESSION:
            emit_paren_expression(emitter, expression as BoundParenExpression);
            break;
        case BoundNode.CTOR_EXPRESSION:
            emit_ctor_expression(emitter, expression as BoundCtorExpression);
            break;
        case BoundNode.ASSIGNMENT_EXPRESSION:
            emit_assignment_expression(emitter, expression as BoundAssignmentExpression);
            break;
        case BoundNode.UNARY_EXPRESSION:
            emit_unary_expression(emitter, expression as BoundUnaryExpression);
            break;
        case BoundNode.BINARY_EXPRESSION:
            emit_binary_expression(emitter, expression as BoundBinaryExpression);
            break;
        case BoundNode.CALL_EXPRESSION:
            emit_call_expression(emitter, expression as BoundCallExpression);
            break;
        case BoundNode.MEMBER_EXPRESSION:
            emit_member_expression(emitter, expression as BoundMemberExpression);
            break;
        case BoundNode.IS_EXPRESSION:
            emit_is_expression(emitter, expression as BoundIsExpression);
            break;
        case BoundNode.ENUM_FIELD_EXPRESSION:
            emit_enum_field_expression(emitter, expression as BoundEnumFieldExpression);
            break;
        case BoundNode.INTEGER_EXPRESSION:
            emit_integer_expression(emitter, expression as BoundIntegerExpression);
            break;
        case BoundNode.CHAR_EXPRESSION:
            emit_char_expression(emitter, expression as BoundCharExpression);
            break;
        case BoundNode.STRING_EXPRESSION:
            emit_string_expression(emitter, expression as BoundStringExpression);
            break;
        case BoundNode.BOOLEAN_EXPRESSION:
            emit_boolean_expression(emitter, expression as BoundBooleanExpression);
            break;
        case BoundNode.VARIABLE_EXPRESSION:
            emit_variable_expression(emitter, expression as BoundVariableExpression);
            break;
        case BoundNode.FUNCTION_EXPRESSION:
            emit_function_expression(emitter, expression as BoundFunctionExpression);
            break;
    }
}

function emit_block_statement(emitter: Emitter, blockStatement: BoundBlockStatement): void {
    writeln(emitter, "{")
    inc_intention(emitter);

    for (const statement of blockStatement.statements) {
        emit_statement(emitter, statement);
    }

    dec_intention(emitter);
    writeln(emitter, "}");
}

function emit_if_statement(emitter: Emitter, ifStatement: BoundIfStatement): void {
    write(emitter, "if (");
    emit_expression(emitter, ifStatement.condition);
    writeln_nit(emitter, ")");
    emit_statement(emitter, ifStatement.thenCase);

    if (ifStatement.elseCase) {
        writeln(emitter, "else");
        emit_statement(emitter, ifStatement.elseCase);
    }
}

function emit_while_statement(emitter: Emitter, whileStatement: BoundWhileStatement): void {
    write(emitter, "while (");
    emit_expression(emitter, whileStatement.condition);
    writeln_nit(emitter, ")");

    emit_statement(emitter, whileStatement.body);
}

function emit_return_statement(emitter: Emitter, returnStatement: BoundReturnStatement): void {
    if (!emitter.currentFunction) {
        throw "Requires current function";
    }
    if (emitter.currentFunction.requiresGC) {
        writeln(emitter, "GC_FRAME_DESTROY;");
    }

    write(emitter, "return");
    if (returnStatement.value) {
        write_nit(emitter, " ");
        emit_expression(emitter, returnStatement.value);
    }

    writeln_nit(emitter, ";");
}

function emit_break_statement(emitter: Emitter, breakStatement: BoundBreakStatement): void {
    writeln(emitter, "break;");
}

function emit_continue_statement(emitter: Emitter, continueStatement: BoundContinueStatement): void {
    writeln(emitter, "continue;");
}

function emit_expression_statement(emitter: Emitter, expressionStatement: BoundExpressionStatement): void {
    if (expressionStatement.expression.type == BoundNode.EMPTY_EXPRESSION) {
        return;
    }
    write(emitter, "");
    emit_expression(emitter, expressionStatement.expression);
    writeln_nit(emitter, ";");
}

function emit_statement(emitter: Emitter, statement: BoundUnknownNode): void {
    switch (statement.type) {
        case BoundNode.BLOCK_STATEMENT:
            emit_block_statement(emitter, statement as BoundBlockStatement);
            break;
        case BoundNode.IF_STATEMENT:
            emit_if_statement(emitter, statement as BoundIfStatement);
            break;
        case BoundNode.WHILE_STATEMENT:
            emit_while_statement(emitter, statement as BoundWhileStatement);
            break;
        case BoundNode.RETURN_STATEMENT:
            emit_return_statement(emitter, statement as BoundReturnStatement);
            break;
        case BoundNode.BREAK_STATEMENT:
            emit_break_statement(emitter, statement as BoundBreakStatement);
            break;
        case BoundNode.CONTINUE_STATEMENT:
            emit_continue_statement(emitter, statement as BoundContinueStatement);
            break;
        case BoundNode.EXPRESSION_STATEMENT:
            emit_expression_statement(emitter, statement as BoundExpressionStatement);
            break;
    }
}

function emit_track_func_type(emitter: Emitter, type: Type): void {
    if (!type.generics) {
        throw "Func type must have generic parameters"
    }
    write(emitter, "typedef ");
    emit_type(emitter, type.generics[0]);
    write_nit(emitter, " (*");
    write_nit(emitter, type.cName);
    write_nit(emitter, ")(");

    for (let i: number = 1; i < type.generics.length; i++) {
        if (i > 1) {
            write_nit(emitter, ", ");
        }

        emit_type(emitter, type.generics[i]);
    }

    writeln_nit(emitter, ");");
}

function emit_enum_member(emitter: Emitter, enumMember: BoundEnumMember): void {
    writeln(emitter, "typedef enum");
    writeln(emitter, "{");
    inc_intention(emitter);

    for (const item of enumMember.items) {
        write(emitter, enumMember.name);
        write_nit(emitter, "_");
        write_nit(emitter, item.name);
        writeln_nit(emitter, ",");
    }

    dec_intention(emitter);
    write(emitter, "} ");
    write_nit(emitter, enumMember.name);
    writeln_nit(emitter, ";");
}

function emit_type_member_header(emitter: Emitter, typeMember: BoundTypeMember): void {
    write(emitter, "typedef struct ");
    write_nit(emitter, typeMember.name);
    write_nit(emitter, "_impl* ");
    write_nit(emitter, typeMember.name);
    writeln_nit(emitter, ";");
}

function emit_type_member(emitter: Emitter, typeMember: BoundTypeMember): void {
    write(emitter, "struct ");
    write_nit(emitter, typeMember.name);
    writeln_nit(emitter, "_impl");
    writeln(emitter, "{");

    inc_intention(emitter);

    writeln(emitter, "ObjectType* __type_header__;");

    for (const item of typeMember.items) {
        write(emitter, "");
        emit_type(emitter, item.type);
        write_nit(emitter, " ");
        write_nit(emitter, item.name);
        writeln_nit(emitter, ";");
    }

    dec_intention(emitter);
    writeln(emitter, "};");
}

function emit_type_member_trace(emitter: Emitter, typeMember: BoundTypeMember): void {
    write(emitter, "static void ");
    write_nit(emitter, typeMember.meta.traceName);
    writeln_nit(emitter, "(const void* _obj, gc_mark_fn mark)");
    writeln(emitter, "{");

    inc_intention(emitter);
    write(emitter, "const ");
    write_nit(emitter, typeMember.name);
    write_nit(emitter, " obj = (");
    write_nit(emitter, typeMember.name);
    writeln_nit(emitter, ")_obj;");

    for (const item of typeMember.items) {
        if (item.type.kind != TypeKind.OBJECT) {
            continue;
        }

        write(emitter, "mark(obj->");
        write_nit(emitter, item.name)
        writeln_nit(emitter, ");");
    }
    dec_intention(emitter);

    writeln(emitter, "}");
}

function emit_type_member_type(emitter: Emitter, typeMember: BoundTypeMember): void {
    write(emitter, "ObjectType ");
    write_nit(emitter, typeMember.name);
    writeln_nit(emitter, "_type = {");

    inc_intention(emitter);
    write(emitter, ".trace = ");
    writeln_nit(emitter, typeMember.meta.traceName);

    dec_intention(emitter);

    writeln(emitter, "};");
}

function emit_extern_type_member_type(emitter: Emitter, typeMember: BoundTypeMember): void {
    write(emitter, "extern ObjectType ");
    write_nit(emitter, typeMember.name);
    writeln_nit(emitter, "_type;");
}

function emit_extern_function_member(emitter: Emitter, functionMember: BoundFunctionMember): void {
    write_nit(emitter, "extern ");
    emit_function_member_header(emitter, functionMember);
}

function emit_function_member_header(emitter: Emitter, functionMember: BoundFunctionMember): void {
    emit_type(emitter, functionMember.returnType);
    write_nit(emitter, " ");
    write_nit(emitter, functionMember.name);
    write_nit(emitter, "(");

    for (let i: number = 0; i < functionMember.parameters.length; i++) {
        if (i > 0) {
            write_nit(emitter, ", ");
        }
        const parameter: Variable = functionMember.parameters[i];
        emit_type(emitter, parameter.type);
        write_nit(emitter, " ");
        emit_variable_name(emitter, parameter);
    }

    writeln_nit(emitter, ");");
}

function emit_function_member(emitter: Emitter, functionMember: BoundFunctionMember): void {
    emitter.currentFunction = functionMember;

    emit_type(emitter, functionMember.returnType);
    write_nit(emitter, " ");
    write_nit(emitter, functionMember.name);
    write_nit(emitter, "(");

    let gcObjects: number = 0;

    for (let i: number = 0; i < functionMember.parameters.length; i++) {
        if (i > 0) {
            write_nit(emitter, ", ");
        }
        const parameter: Variable = functionMember.parameters[i];

        if (parameter.type.kind == TypeKind.OBJECT) {
            gcObjects++;
        }

        emit_type(emitter, parameter.type);
        write_nit(emitter, " ");
        emit_variable_name(emitter, parameter);
    }

    writeln_nit(emitter, ")");
    writeln_nit(emitter, "{");
    inc_intention(emitter);

    for (const variable of functionMember.variables) {
        write(emitter, "");
        emit_type(emitter, variable.type);
        write_nit(emitter, " ");
        emit_variable_name(emitter, variable);

        if (variable.type.kind == TypeKind.OBJECT) {
            gcObjects++;
            write_nit(emitter, " = NULL");
        }

        writeln_nit(emitter, ";");
    }

    if (gcObjects > 0) {
        write(emitter, "GC_FRAME_INIT(");
        write_nit(emitter, gcObjects.toString());

        for (const parameter of functionMember.parameters) {
            if (parameter.type.kind != TypeKind.OBJECT) {
                continue;
            }

            write_nit(emitter, ", GC_LOCAL(");
            emit_variable_name(emitter, parameter);
            write_nit(emitter, ")");
        }

        for (const variable of functionMember.variables) {
            if (variable.type.kind != TypeKind.OBJECT) {
                continue;
            }

            write_nit(emitter, ", GC_LOCAL(");
            emit_variable_name(emitter, variable);
            write_nit(emitter, ")");
        }

        writeln_nit(emitter, ");");
    }

    emit_block_statement(emitter, functionMember.body);

    if (gcObjects > 0) {
        writeln(emitter, "GC_FRAME_DESTROY;");
    }

    dec_intention(emitter);
    writeln_nit(emitter, "}");
    writeln_nit(emitter, "");
}

export function emit_program(emitter: Emitter, program: BoundProgram): void {
    emit_header(emitter);

    // Emit enum
    for (const enumMember of program.enums) {
        emit_enum_member(emitter, enumMember);
    }

    // Emit type header
    for (const type of program.types) {
        emit_type_member_header(emitter, type);
    }

    // Emit extern type header
    for (const type of program.externTypes) {
        emit_type_member_header(emitter, type);
    }

    writeln(emitter, "");

    // Emit dynamic Func types
    for (const type of program.trackedTypes) {
        if (type.name == "Func") {
            emit_track_func_type(emitter, type);
        }
    }

    writeln(emitter, "");

    // Emit type
    for (const type of program.types) {
        emit_type_member(emitter, type);
        writeln_nit(emitter, "");

        if (type.meta.generateTrace) {
            emit_type_member_trace(emitter, type);
            writeln_nit(emitter, "");
        }

        emit_type_member_type(emitter, type);
    }

    // Emit extern type
    for (const type of program.externTypes) {
        emit_type_member(emitter, type);
        emit_extern_type_member_type(emitter, type);
        writeln_nit(emitter, "");
    }

    writeln(emitter, "");
    writeln(emitter, "");

    // Emit extern function signatures
    for (const func of program.externFunctions) {
        emit_extern_function_member(emitter, func);
    }

    writeln(emitter, "");

    // Emit function signatures
    for (const func of program.functions) {
        emit_function_member_header(emitter, func);
    }

    writeln(emitter, "");

    // Emit function implementations
    for (const func of program.functions) {
        emit_function_member(emitter, func);
    }
}