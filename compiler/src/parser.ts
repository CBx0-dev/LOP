import {Lexer, lexer_init, lexer_next_token, Token, TokenType} from "./lexer";

export interface Parser {
    tokens: Token[];
    length: number;
    position: number;
}

export enum NodeType {
    COMPILATION_UNIT,

    EXTERN_TYPE_MEMBER,
    TYPE_MEMBER,
    EXTERN_FUNCTION_MEMBER,
    FUNCTION_MEMBER,
    ENUM_MEMBER,

    BLOCK_STATEMENT,
    VARIABLE_STATEMENT,
    EXPRESSION_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,

    CTOR_EXPRESSION,
    ASSIGNMENT_EXPRESSION,
    UNARY_EXPRESSION,
    BINARY_EXPRESSION,
    CALL_EXPRESSION,
    MEMBER_EXPRESSION,
    IS_EXPRESSION,
    INTEGER_EXPRESSION,
    CHAR_EXPRESSION,
    STRING_EXPRESSION,
    BOOLEAN_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    PAREN_EXPRESSION,
    CAST_EXPRESSION,
    NULL_EXPRESSION,

    TYPE_CLAUSE,
    TYPE_SIGNATURE,
}

export interface UnknownNode {
    type: NodeType;
}

export interface CompilationUnit {
    type: NodeType.COMPILATION_UNIT;
    externTypes: ExternTypeMember[];
    types: TypeMember[];
    externFunctions: ExternFunctionMember[];
    functions: FunctionMember[];
    enums: EnumMember[];
    eof: Token;
}

export interface TypeMemberItem {
    identifier: Token;
    typeClause: TypeClauseNode;
    semicolons: Token[];
}

export interface ExternTypeMember {
    type: NodeType.EXTERN_TYPE_MEMBER;
    extern: Token;
    keyword: Token;
    identifier: Token;
    lBrace: Token;
    items: TypeMemberItem[];
    rBrace: Token;
    semicolons: Token[];
}

export interface TypeMember {
    type: NodeType.TYPE_MEMBER;
    keyword: Token;
    identifier: Token;
    lBrace: Token;
    items: TypeMemberItem[];
    rBrace: Token;
    semicolons: Token[];
}

export interface FunctionMemberParameter {
    identifier: Token;
    typeClause: TypeClauseNode;
    comma: Token | null;
}

export interface ExternFunctionMember {
    type: NodeType.EXTERN_FUNCTION_MEMBER;
    extern: Token;
    func: Token;
    identifier: Token;
    lParen: Token;
    parameters: FunctionMemberParameter[];
    rParen: Token;
    returnType: TypeClauseNode;
    semicolons: Token[];
}

export interface FunctionMember {
    type: NodeType.FUNCTION_MEMBER;
    keyword: Token;
    identifier: Token;
    lParen: Token;
    parameters: FunctionMemberParameter[];
    rParen: Token;
    returnType: TypeClauseNode;
    body: BlockStatement;
}

export interface EnumMemberItem {
    identifier: Token;
    comma: Token | null;
}

export interface EnumMember {
    type: NodeType.ENUM_MEMBER;
    keyword: Token;
    identifier: Token;
    lBrace: Token;
    items: EnumMemberItem[];
    rBrace: Token;
    semicolons: Token[];
}

export interface BlockStatement {
    type: NodeType.BLOCK_STATEMENT;
    lBrace: Token;

    statements: UnknownNode[];

    rBrace: Token;
    semicolons: Token[];
}

export interface VariableStatement {
    type: NodeType.VARIABLE_STATEMENT;
    keyword: Token;
    identifier: Token;
    typeClause: TypeClauseNode;
    equals: Token | null;
    initializer: UnknownNode | null;
    semicolons: Token[];
}

export interface ElseCase {
    keyword: Token;
    thenCase: UnknownNode;
}

export interface IfStatement {
    type: NodeType.IF_STATEMENT;
    keyword: Token;
    lParen: Token;
    condition: UnknownNode;
    rParen: Token;
    thenCase: UnknownNode;
    elseCase: ElseCase | null;
}

export interface WhileStatement {
    type: NodeType.WHILE_STATEMENT;
    keyword: Token;
    lParen: Token;
    condition: UnknownNode;
    rParen: Token;
    body: UnknownNode;
}

export interface ReturnStatement {
    type: NodeType.RETURN_STATEMENT;
    keyword: Token;
    value: UnknownNode | null;
    semicolons: Token[];
}

export interface BreakStatement {
    type: NodeType.BREAK_STATEMENT;
    keyword: Token;
    semicolons: Token[];
}

export interface ContinueStatement {
    type: NodeType.CONTINUE_STATEMENT;
    keyword: Token;
    semicolons: Token[];
}

export interface ExpressionStatement {
    type: NodeType.EXPRESSION_STATEMENT;
    expression: UnknownNode;
    semicolons: Token[];
}

export interface CtorExpression {
    type: NodeType.CTOR_EXPRESSION;
    keyword: Token;
    signature: TypeSignatureNode;
    lParen: Token;
    rParen: Token;
}

export interface AssignmentExpression {
    type: NodeType.ASSIGNMENT_EXPRESSION,
    left: UnknownNode;
    operator: Token;
    right: UnknownNode;
}

export interface UnaryExpression {
    type: NodeType.UNARY_EXPRESSION;
    operator: Token,
    right: UnknownNode;
}

export interface BinaryExpression {
    type: NodeType.BINARY_EXPRESSION;
    left: UnknownNode;
    operator: Token,
    right: UnknownNode;
}

export interface CallExpressionArgument {
    argument: UnknownNode;
    comma: Token | null;
}

export interface CallExpression {
    type: NodeType.CALL_EXPRESSION;
    callee: UnknownNode;
    lParen: Token;
    arguments: CallExpressionArgument[];
    rParen: Token;
}

export interface MemberExpression {
    type: NodeType.MEMBER_EXPRESSION;
    object: UnknownNode;
    dot: Token;
    identifier: Token;
}

export interface IsExpression {
    type: NodeType.IS_EXPRESSION;
    left: UnknownNode;
    keyword: Token;
    typeSignature: TypeSignatureNode;
}

export interface IntegerExpression {
    type: NodeType.INTEGER_EXPRESSION;
    value: Token;
}

export interface CharExpression {
    type: NodeType.CHAR_EXPRESSION;
    value: Token;
}

export interface StringExpression {
    type: NodeType.STRING_EXPRESSION;
    value: Token;
}

export interface BooleanExpression {
    type: NodeType.BOOLEAN_EXPRESSION;
    value: Token;
}

export interface IdentifierExpression {
    type: NodeType.IDENTIFIER_EXPRESSION;
    value: Token;
}

export interface ParenExpression {
    type: NodeType.PAREN_EXPRESSION;
    lParen: Token;
    expression: UnknownNode;
    rParen: Token;
}

export interface CastExpression {
    type: NodeType.CAST_EXPRESSION;
    lAngle: Token;
    typeSignature: TypeSignatureNode;
    rAngle: Token;
    expression: UnknownNode;
}

export interface NullExpression {
    type: NodeType.NULL_EXPRESSION;
    nil: Token;
}

export interface TypeClauseNode {
    type: NodeType.TYPE_CLAUSE;
    colon: Token;
    signature: TypeSignatureNode;
}

export interface TypeSignatureNodeDynamicGeneric {
    typeSignature: TypeSignatureNode;
    comma: Token | null;
}

export interface TypeSignatureNodeDynamic {
    lAngle: Token;

    generics: TypeSignatureNodeDynamicGeneric[];

    rAngle: Token;
}

export interface TypeSignatureNode {
    type: NodeType.TYPE_SIGNATURE;
    identifier: Token;
    dynamic: TypeSignatureNodeDynamic | null;
}

export function parser_init(filename: string, content: string, length: number): Parser {
    const lexer: Lexer = lexer_init(filename, content, length);
    const tokens: Token[] = [];
    let token: Token;
    do {
        token = lexer_next_token(lexer);
        if (token.type != TokenType.ERROR &&
            token.type != TokenType.WHITESPACE &&
            token.type != TokenType.SINGLE_COMMENT &&
            token.type != TokenType.MULTI_COMMENT) {
            tokens.push(token);
        }
    } while (token.type != TokenType.EOF);

    return {
        tokens,
        length: tokens.length,
        position: 0
    };
}

function current_token(parser: Parser): Token {
    if (parser.position >= parser.length) {
        return parser.tokens[parser.length - 1];
    }

    return parser.tokens[parser.position];
}

function peek_token(parser: Parser): Token {
    if (parser.position + 1 >= parser.length) {
        return parser.tokens[parser.length - 1];
    }

    return parser.tokens[parser.position + 1];
}

function next_token(parser: Parser): Token {
    const token: Token = current_token(parser);
    parser.position++;
    return token;
}

function match_token(parser: Parser, type: TokenType): Token {
    const current: Token = current_token(parser);
    if (current.type != type) {
        // TODO report diagnostic
        throw "Expect token";
    }

    parser.position++;
    return current;
}

function match_token2(parser: Parser, type1: TokenType, type2: TokenType): Token {
    const current: Token = current_token(parser);
    if (current.type != type1 && current.type != type2) {
        // TODO report diagnostic
        throw "Expect token";
    }

    parser.position++;
    return current;
}

function is_eof(parser: Parser): boolean {
    return parser.position >= parser.length;
}

function unary_operator_precedence(operator: TokenType): number {
    switch (operator) {
        case TokenType.BANG:
        case TokenType.PLUS:
        case TokenType.MINUS:
            return 6;
        default:
            return 0;
    }
}

function binary_operator_precedence(operator: TokenType): number {
    switch (operator) {
        case TokenType.STAR:
        case TokenType.SLASH:
            return 5;
        case TokenType.PLUS:
        case TokenType.MINUS:
            return 4;
        case TokenType.EQUALS_EQUALS:
        case TokenType.BANG_EQUALS:
        case TokenType.LANGLE:
        case TokenType.LANGLE_EQUALS:
        case TokenType.RANGLE:
        case TokenType.RANGLE_EQUALS:
            return 3;
        case TokenType.AND_AND:
            return 2;
        case TokenType.OR_OR:
            return 1;
        default:
            return 0;
    }

}

function parse_semicolon_block(parser: Parser, expectAtLeastOne: boolean): Token[] {
    const tokens: Token[] = [];

    if (expectAtLeastOne) {
        tokens.push(match_token(parser, TokenType.SEMICOLON));
    }

    while (current_token(parser).type == TokenType.SEMICOLON && !is_eof(parser)) {
        tokens.push(next_token(parser));
    }

    return tokens;
}

function parse_type_signature(parser: Parser): TypeSignatureNode {
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    let dynamic: TypeSignatureNodeDynamic | null = null;

    if (current_token(parser).type == TokenType.LANGLE) {
        const lAngle: Token = next_token(parser);
        const generics: TypeSignatureNodeDynamicGeneric[] = [];

        while (current_token(parser).type != TokenType.RANGLE && !is_eof(parser)) {
            const typeSignature: TypeSignatureNode = parse_type_signature(parser);
            let comma: Token | null = null;
            if (current_token(parser).type == TokenType.COMMA) {
                comma = next_token(parser);
            }

            generics.push({
                typeSignature,
                comma
            });
        }

        if (generics.length == 0) {
            // TODO replace with diagnostic
            throw "Generic count cannot be zero";
        }

        const rAngle: Token = match_token(parser, TokenType.RANGLE);

        dynamic = {
            lAngle,
            generics,
            rAngle
        };
    }

    return {
        type: NodeType.TYPE_SIGNATURE,
        identifier,
        dynamic
    };
}

function parse_type_clause(parser: Parser): TypeClauseNode {
    const colon: Token = match_token(parser, TokenType.COLON);
    const sig: TypeSignatureNode = parse_type_signature(parser);

    return {
        type: NodeType.TYPE_CLAUSE,
        colon,
        signature: sig
    };
}

function parse_ctor_expression(parser: Parser): CtorExpression {
    const keyword: Token = match_token(parser, TokenType.NEW_KEYWORD);
    const signature: TypeSignatureNode = parse_type_signature(parser);

    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const rParen: Token = match_token(parser, TokenType.RPAREN);

    return {
        type: NodeType.CTOR_EXPRESSION,
        keyword,
        signature,
        lParen,
        rParen
    }
}

function parse_integer_expression(parser: Parser): IntegerExpression {
    const value: Token = match_token(parser, TokenType.INTEGER_LITERAL);
    return {
        type: NodeType.INTEGER_EXPRESSION,
        value
    };
}

function parse_char_expression(parser: Parser): CharExpression {
    const value: Token = match_token(parser, TokenType.CHAR_LITERAL);
    return {
        type: NodeType.CHAR_EXPRESSION,
        value
    };
}

function parse_string_expression(parser: Parser): StringExpression {
    const value: Token = match_token(parser, TokenType.STRING_LITERAL);
    return {
        type: NodeType.STRING_EXPRESSION,
        value
    };
}

function parse_boolean_expression(parser: Parser): BooleanExpression {
    const value: Token = match_token2(parser, TokenType.FALSE_KEYWORD, TokenType.TRUE_KEYWORD);
    return {
        type: NodeType.BOOLEAN_EXPRESSION,
        value
    };
}

function parse_identifier_expression(parser: Parser): IdentifierExpression {
    const value: Token = match_token(parser, TokenType.IDENTIFIER);
    return {
        type: NodeType.IDENTIFIER_EXPRESSION,
        value
    };
}

function parse_paren_expression(parser: Parser): ParenExpression {
    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const expression: UnknownNode = parse_expression(parser);
    const rParen: Token = match_token(parser, TokenType.RPAREN);
    return {
        type: NodeType.PAREN_EXPRESSION,
        lParen,
        expression,
        rParen
    };
}

function parse_cast_expression(parser: Parser): CastExpression {
    const lAngle: Token = match_token(parser, TokenType.LANGLE);
    const typeSignature: TypeSignatureNode = parse_type_signature(parser);
    const rAngle: Token = match_token(parser, TokenType.RANGLE);
    const expression: UnknownNode = parse_expression(parser);

    return {
        type: NodeType.CAST_EXPRESSION,
        lAngle,
        typeSignature,
        rAngle,
        expression
    };
}

function parse_null_expression(parser: Parser): NullExpression {
    const nil: Token = match_token(parser, TokenType.NULL_KEYWORD);
    return {
        type: NodeType.NULL_EXPRESSION,
        nil
    };
}

function parse_base_expression(parser: Parser): UnknownNode {
    switch (current_token(parser).type) {
        case TokenType.INTEGER_LITERAL:
            return parse_integer_expression(parser);
        case TokenType.CHAR_LITERAL:
            return parse_char_expression(parser);
        case TokenType.STRING_LITERAL:
            return parse_string_expression(parser);
        case TokenType.TRUE_KEYWORD:
        case TokenType.FALSE_KEYWORD:
            return parse_boolean_expression(parser);
        case TokenType.IDENTIFIER:
            return parse_identifier_expression(parser);
        case TokenType.LPAREN:
            return parse_paren_expression(parser);
        case TokenType.LANGLE:
            return parse_cast_expression(parser);
        case TokenType.NULL_KEYWORD:
            return parse_null_expression(parser);
    }

    // TODO use diagnostic
    throw "(parser) Unknown expression";
}


function parse_wrapper_expression(parser: Parser): UnknownNode {
    let left: UnknownNode = parse_base_expression(parser);

    while (true) {
        if (current_token(parser).type == TokenType.LPAREN) {
            const lParen: Token = next_token(parser);
            const args: CallExpressionArgument[] = [];
            while (current_token(parser).type != TokenType.RPAREN && !is_eof(parser)) {
                const argument: UnknownNode = parse_expression(parser);
                let comma: Token | null = null;
                if (current_token(parser).type == TokenType.COMMA) {
                    comma = next_token(parser);
                }

                args.push({
                    argument,
                    comma
                });
            }

            const rParen: Token = match_token(parser, TokenType.RPAREN);
            left = (<CallExpression>{
                type: NodeType.CALL_EXPRESSION,
                callee: left,
                lParen,
                arguments: args,
                rParen
            });
            continue;
        } else if (current_token(parser).type == TokenType.DOT) {
            const dot: Token = next_token(parser);
            const identifier: Token = match_token(parser, TokenType.IDENTIFIER);

            left = (<MemberExpression>{
                type: NodeType.MEMBER_EXPRESSION,
                object: left,
                dot,
                identifier
            });
            continue;
        } else if (current_token(parser).type == TokenType.IS_KEYWORD) {
            const keyword: Token = next_token(parser);
            const typeSignature: TypeSignatureNode = parse_type_signature(parser);

            left = (<IsExpression>{
                type: NodeType.IS_EXPRESSION,
                left,
                keyword,
                typeSignature
            });
            continue;
        }

        break;
    }

    return left;
}


function parse_binary_expression(parser: Parser, parentPrecedence: number): UnknownNode {
    let left: UnknownNode;
    let unaryIndex: number = unary_operator_precedence(current_token(parser).type);
    if (unaryIndex != 0 && unaryIndex >= parentPrecedence) {
        let operator: Token = next_token(parser);
        let right: UnknownNode = parse_binary_expression(parser, unaryIndex);
        left = (<UnaryExpression>{
            type: NodeType.UNARY_EXPRESSION,
            operator,
            right
        });
    } else {
        left = parse_wrapper_expression(parser);
    }

    while (true) {
        let index: number = binary_operator_precedence(current_token(parser).type);
        if (index == 0 || index <= parentPrecedence) {
            break;
        }

        let operator: Token = next_token(parser);
        let right: UnknownNode = parse_binary_expression(parser, index);
        left = (<BinaryExpression>{
            type: NodeType.BINARY_EXPRESSION,
            left,
            operator,
            right
        });
    }

    return left;
}

function parse_assignment_expression(parser: Parser): UnknownNode {
    const left: UnknownNode = parse_binary_expression(parser, 0);
    if (current_token(parser).type == TokenType.EQUALS) {
        const operator: Token = next_token(parser);
        const right: UnknownNode = parse_expression(parser);
        return (<AssignmentExpression>{
            type: NodeType.ASSIGNMENT_EXPRESSION,
            left,
            operator,
            right
        });
    }

    return left;
}

function parse_expression(parser: Parser): UnknownNode {
    if (current_token(parser).type == TokenType.NEW_KEYWORD) {
        return parse_ctor_expression(parser);
    }

    return parse_assignment_expression(parser);
}

function parse_block_statement(parser: Parser): BlockStatement {
    const lBrace: Token = match_token(parser, TokenType.LBRACE);
    const statements: UnknownNode[] = [];

    while (current_token(parser).type != TokenType.RBRACE && !is_eof(parser)) {
        statements.push(parse_statement(parser));
    }

    const rBrace: Token = match_token(parser, TokenType.RBRACE);
    const semicolons: Token[] = parse_semicolon_block(parser, false);

    return {
        type: NodeType.BLOCK_STATEMENT,
        lBrace,
        statements,
        rBrace,
        semicolons
    };
}

function parse_variable_statement(parser: Parser): VariableStatement {
    const keyword: Token = match_token(parser, TokenType.LET_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const typeClause: TypeClauseNode = parse_type_clause(parser);

    let equals: Token | null = null;
    let initializer: UnknownNode | null;

    if (current_token(parser).type == TokenType.EQUALS) {
        equals = next_token(parser);
        initializer = parse_expression(parser);
    }

    const semicolons: Token[] = parse_semicolon_block(parser, true);

    return {
        type: NodeType.VARIABLE_STATEMENT,
        keyword,
        identifier,
        typeClause,
        equals,
        initializer,
        semicolons
    };
}

function parse_if_statement(parser: Parser): IfStatement {
    const keyword: Token = match_token(parser, TokenType.IF_KEYWORD);
    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const condition: UnknownNode = parse_expression(parser);
    const rParen: Token = match_token(parser, TokenType.RPAREN);
    const thenCase: UnknownNode = parse_statement(parser);

    let elseCase: ElseCase | null = null;
    if (current_token(parser).type == TokenType.ELSE_KEYWORD) {
        const keyword: Token = match_token(parser, TokenType.ELSE_KEYWORD);
        const thenCase: UnknownNode = parse_statement(parser);
        elseCase = {
            keyword,
            thenCase
        }
    }

    return {
        type: NodeType.IF_STATEMENT,
        keyword,
        lParen,
        condition,
        rParen,
        thenCase,
        elseCase
    };
}

function parse_while_statement(parser: Parser): WhileStatement {
    const keyword: Token = match_token(parser, TokenType.WHILE_KEYWORD);
    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const condition: UnknownNode = parse_expression(parser);
    const rParen: Token = match_token(parser, TokenType.RPAREN);
    const body: UnknownNode = parse_statement(parser);

    return {
        type: NodeType.WHILE_STATEMENT,
        keyword,
        lParen,
        condition,
        rParen,
        body
    };
}

function parse_return_statement(parser: Parser): ReturnStatement {
    const keyword: Token = match_token(parser, TokenType.RETURN_KEYWORD);

    let value: UnknownNode | null = null;
    if (current_token(parser).type != TokenType.SEMICOLON) {
        value = parse_expression(parser);
    }

    const semicolons: Token[] = parse_semicolon_block(parser, true);
    return {
        type: NodeType.RETURN_STATEMENT,
        keyword,
        value,
        semicolons
    };
}

function parse_break_statement(parser: Parser): BreakStatement {
    const keyword: Token = match_token(parser, TokenType.BREAK_KEYWORD);
    const semicolons: Token[] = parse_semicolon_block(parser, true);

    return {
        type: NodeType.BREAK_STATEMENT,
        keyword,
        semicolons
    };
}

function parse_continue_statement(parser: Parser): ContinueStatement {
    const keyword: Token = match_token(parser, TokenType.CONTINUE_KEYWORD);
    const semicolons: Token[] = parse_semicolon_block(parser, true);

    return {
        type: NodeType.CONTINUE_STATEMENT,
        keyword,
        semicolons
    };
}

function parse_expression_statement(parser: Parser): ExpressionStatement {
    const expression: UnknownNode = parse_expression(parser);
    const semicolons: Token[] = parse_semicolon_block(parser, true);

    return {
        type: NodeType.EXPRESSION_STATEMENT,
        expression,
        semicolons
    }
}

function parse_statement(parser: Parser): UnknownNode {
    switch (current_token(parser).type) {
        case TokenType.LBRACE:
            return parse_block_statement(parser);
        case TokenType.LET_KEYWORD:
            return parse_variable_statement(parser);
        case TokenType.IF_KEYWORD:
            return parse_if_statement(parser);
        case TokenType.WHILE_KEYWORD:
            return parse_while_statement(parser);
        case TokenType.RETURN_KEYWORD:
            return parse_return_statement(parser);
        case TokenType.BREAK_KEYWORD:
            return parse_break_statement(parser);
        case TokenType.CONTINUE_KEYWORD:
            return parse_continue_statement(parser);
    }

    return parse_expression_statement(parser);
}

function parse_extern_function_member(parser: Parser): ExternFunctionMember {
    const extern: Token = match_token(parser, TokenType.EXTERN_KEYWORD);
    const func: Token = match_token(parser, TokenType.FUNCTION_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const parameters: FunctionMemberParameter[] = [];

    while (current_token(parser).type != TokenType.RPAREN && !is_eof(parser)) {
        const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
        const typeClause: TypeClauseNode = parse_type_clause(parser);
        let comma: Token | null = null;
        if (current_token(parser).type == TokenType.COMMA) {
            comma = next_token(parser);
        }

        parameters.push({
            identifier,
            typeClause,
            comma
        });
    }

    const rParen: Token = match_token(parser, TokenType.RPAREN);
    const returnType: TypeClauseNode = parse_type_clause(parser);
    const semicolons: Token[] = parse_semicolon_block(parser, true);

    return {
        type: NodeType.EXTERN_FUNCTION_MEMBER,
        extern,
        func,
        identifier,
        lParen,
        parameters,
        rParen,
        returnType,
        semicolons
    };
}

function parse_extern_type_member(parser: Parser): ExternTypeMember {
    const extern: Token = match_token(parser, TokenType.EXTERN_KEYWORD);
    const keyword: Token = match_token(parser, TokenType.TYPE_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const lBrace: Token = match_token(parser, TokenType.LBRACE);
    const items: TypeMemberItem[] = [];

    while (current_token(parser).type != TokenType.RBRACE && !is_eof(parser)) {
        const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
        const typeClause: TypeClauseNode = parse_type_clause(parser);
        const semicolons: Token[] = parse_semicolon_block(parser, true);

        items.push({
            identifier,
            typeClause,
            semicolons
        });
    }

    const rBrace: Token = match_token(parser, TokenType.RBRACE);
    const semicolons: Token[] = parse_semicolon_block(parser, false);

    return {
        type: NodeType.EXTERN_TYPE_MEMBER,
        extern,
        keyword,
        identifier,
        lBrace,
        rBrace,
        items,
        semicolons
    }
}

function parse_function_member(parser: Parser): FunctionMember {
    const keyword: Token = match_token(parser, TokenType.FUNCTION_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const lParen: Token = match_token(parser, TokenType.LPAREN);
    const parameters: FunctionMemberParameter[] = [];

    while (current_token(parser).type != TokenType.RPAREN && !is_eof(parser)) {
        const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
        const typeClause: TypeClauseNode = parse_type_clause(parser);
        let comma: Token | null = null;
        if (current_token(parser).type == TokenType.COMMA) {
            comma = next_token(parser);
        }

        parameters.push({
            identifier,
            typeClause,
            comma
        });
    }

    const rParen: Token = match_token(parser, TokenType.RPAREN);
    const returnType: TypeClauseNode = parse_type_clause(parser);
    const body: BlockStatement = parse_block_statement(parser);

    return {
        type: NodeType.FUNCTION_MEMBER,
        keyword,
        identifier,
        lParen,
        parameters,
        rParen,
        returnType,
        body
    };
}

function parse_type_member(parser: Parser): TypeMember {
    const keyword: Token = match_token(parser, TokenType.TYPE_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const lBrace: Token = match_token(parser, TokenType.LBRACE);
    const items: TypeMemberItem[] = [];

    while (current_token(parser).type != TokenType.RBRACE && !is_eof(parser)) {
        const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
        const typeClause: TypeClauseNode = parse_type_clause(parser);
        const semicolons: Token[] = parse_semicolon_block(parser, true);

        items.push({
            identifier,
            typeClause,
            semicolons
        });
    }

    const rBrace: Token = match_token(parser, TokenType.RBRACE);
    const semicolons: Token[] = parse_semicolon_block(parser, false);

    return {
        type: NodeType.TYPE_MEMBER,
        keyword,
        identifier,
        lBrace,
        rBrace,
        items,
        semicolons
    }
}

function parse_enum_member(parser: Parser): EnumMember {
    const keyword: Token = match_token(parser, TokenType.ENUM_KEYWORD);
    const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
    const lBrace: Token = match_token(parser, TokenType.LBRACE);
    const items: EnumMemberItem[] = [];

    while (current_token(parser).type != TokenType.RBRACE && !is_eof(parser)) {
        const identifier: Token = match_token(parser, TokenType.IDENTIFIER);
        let comma: Token | null = null;
        if (current_token(parser).type == TokenType.COMMA) {
            comma = next_token(parser);
        }

        items.push({
            identifier,
            comma
        });
    }

    const rBrace: Token = match_token(parser, TokenType.RBRACE);
    const semicolons: Token[] = parse_semicolon_block(parser, false);

    return {
        type: NodeType.ENUM_MEMBER,
        keyword,
        identifier,
        lBrace,
        items,
        rBrace,
        semicolons
    };
}

export function parse_compilation_unit(parser: Parser): CompilationUnit {
    const externFunctions: ExternFunctionMember[] = [];
    const externTypes: ExternTypeMember[] = [];
    const functions: FunctionMember[] = [];
    const types: TypeMember[] = [];
    const enums: EnumMember[] = [];

    while (current_token(parser).type != TokenType.EOF && !is_eof(parser)) {
        switch (current_token(parser).type) {
            case TokenType.EXTERN_KEYWORD:
                if (peek_token(parser).type == TokenType.FUNCTION_KEYWORD) {
                    externFunctions.push(parse_extern_function_member(parser));
                    break;
                }
                if (peek_token(parser).type == TokenType.TYPE_KEYWORD) {
                    externTypes.push(parse_extern_type_member(parser));
                    break;
                }
                break;
            case TokenType.FUNCTION_KEYWORD:
                functions.push(parse_function_member(parser));
                break;
            case TokenType.TYPE_KEYWORD:
                types.push(parse_type_member(parser));
                break;
            case TokenType.ENUM_KEYWORD:
                enums.push(parse_enum_member(parser));
                break;
        }
    }

    const eof: Token = match_token(parser, TokenType.EOF);

    return {
        type: NodeType.COMPILATION_UNIT,
        externTypes,
        types,
        externFunctions,
        functions,
        enums,
        eof
    }
}
