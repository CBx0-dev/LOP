import {char_is_alpha, char_is_alpha_numeric, char_is_numeric, char_is_whitespace} from "./char";

export interface Lexer {
    filename: string;
    content: string;
    position: number;
    length: number;
}

export enum TokenType {
    ERROR,
    EOF,
    WHITESPACE,
    SINGLE_COMMENT,
    MULTI_COMMENT,

    IDENTIFIER,
    INTEGER_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,

    TYPE_KEYWORD,
    FUNCTION_KEYWORD,
    ENUM_KEYWORD,
    LET_KEYWORD,
    NEW_KEYWORD,
    IF_KEYWORD,
    ELSE_KEYWORD,
    WHILE_KEYWORD,
    RETURN_KEYWORD,
    TRUE_KEYWORD,
    FALSE_KEYWORD,
    EXTERN_KEYWORD,
    NULL_KEYWORD,
    BREAK_KEYWORD,
    CONTINUE_KEYWORD,
    IS_KEYWORD,

    COLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,
    EQUALS,
    EQUALS_EQUALS,
    BANG,
    BANG_EQUALS,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    AND,
    AND_AND,
    OR,
    OR_OR,
    LANGLE,
    LANGLE_EQUALS,
    RANGLE,
    RANGLE_EQUALS,
    COMMA,
    DOT,
}

export interface Token {
    type: TokenType;
    value: string;
}

export function lexer_init(filename: string, content: string, length: number): Lexer {
    return {
        filename,
        content,
        position: 0,
        length
    }
}

export function token_init(type: TokenType, value: string): Token {
    return {
        type,
        value
    };
}

function current_char(lexer: Lexer): string {
    if (is_eof(lexer)) {
        return '\0';
    }

    return lexer.content[lexer.position];
}


function peek_char(lexer: Lexer): string {
    if (lexer.position + 1 >= lexer.length) {
        return '\0';
    }

    return lexer.content[lexer.position + 1];
}


function next_char(lexer: Lexer): string {
    const c: string = current_char(lexer);
    lexer.position++;
    return c;
}

function is_eof(lexer: Lexer): boolean {
    return lexer.position >= lexer.length;
}

function lex_whitespace(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    while (char_is_whitespace(current_char(lexer)) && !is_eof(lexer)) {
        value += next_char(lexer);
    }

    return token_init(TokenType.WHITESPACE, value);
}

function lex_identifier(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    while ((char_is_alpha_numeric(current_char(lexer)) || current_char(lexer) == "_") && !is_eof(lexer)) {
        value += next_char(lexer);
    }

    let type: TokenType = TokenType.IDENTIFIER;

    switch (value) {
        case "type":
            type = TokenType.TYPE_KEYWORD;
            break;
        case "func":
            type = TokenType.FUNCTION_KEYWORD;
            break;
        case "enum":
            type = TokenType.ENUM_KEYWORD;
            break;
        case "let":
            type = TokenType.LET_KEYWORD;
            break;
        case "new":
            type = TokenType.NEW_KEYWORD;
            break;
        case "if":
            type = TokenType.IF_KEYWORD;
            break;
        case "else":
            type = TokenType.ELSE_KEYWORD;
            break;
        case "while":
            type = TokenType.WHILE_KEYWORD;
            break;
        case "return":
            type = TokenType.RETURN_KEYWORD;
            break;
        case "true":
            type = TokenType.TRUE_KEYWORD;
            break;
        case "false":
            type = TokenType.FALSE_KEYWORD;
            break;
        case "extern":
            type = TokenType.EXTERN_KEYWORD;
            break;
        case "null":
            type = TokenType.NULL_KEYWORD
            break;
        case "break":
            type = TokenType.BREAK_KEYWORD;
            break;
        case "continue":
            type = TokenType.CONTINUE_KEYWORD;
            break;
        case "is":
            type = TokenType.IS_KEYWORD
            break;
    }

    return token_init(type, value);
}

function lex_numeric(lexer: Lexer): Token {
    // TODO parse floating point literals
    let value: string = next_char(lexer);
    while (char_is_numeric(current_char(lexer)) && !is_eof(lexer)) {
        value += next_char(lexer);
    }

    return token_init(TokenType.INTEGER_LITERAL, value);
}

function lex_char(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    const c: string = next_char(lexer);
    value += c;
    if (c == "\\") {
        // TODO validate escape sequence
        value += next_char(lexer);
    }

    if (current_char(lexer) != "'") {
        throw "Missing char close";
    }

    value += next_char(lexer);
    return token_init(TokenType.CHAR_LITERAL, value);
}

function lex_string(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    while (current_char(lexer) != "\"" && !is_eof(lexer)) {
        if (current_char(lexer) == "\\") {
            value += next_char(lexer);
        }
        value += next_char(lexer);
    }

    if (current_char(lexer) != "\"") {
        throw "Missing string close";
    }
    value += next_char(lexer);
    return token_init(TokenType.STRING_LITERAL, value);
}

function lex_single_line_comment(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    while (current_char(lexer) != "\n" && !is_eof(lexer)) {
        value += next_char(lexer);
    }
    return token_init(TokenType.SINGLE_COMMENT, value);
}

function lex_multi_line_comment(lexer: Lexer): Token {
    let value: string = next_char(lexer);
    while ((current_char(lexer) != "*" || peek_char(lexer) != "/") && !is_eof(lexer)) {
        value += next_char(lexer);
    }
    next_char(lexer);
    next_char(lexer);
    return token_init(TokenType.MULTI_COMMENT, value);
}

export function lexer_next_token(lexer: Lexer): Token {
    if (is_eof(lexer)) {
        return token_init(TokenType.EOF, "");
    }

    if (char_is_whitespace(current_char(lexer))) {
        return lex_whitespace(lexer);
    }

    if (char_is_alpha(current_char(lexer)) || current_char(lexer) == "_") {
        return lex_identifier(lexer);
    }

    if (char_is_numeric(current_char(lexer))) {
        return lex_numeric(lexer);
    }

    if (current_char(lexer) == "'") {
        return lex_char(lexer);
    }

    if (current_char(lexer) == "\"") {
        return lex_string(lexer);
    }

    if (current_char(lexer) == "/" && peek_char(lexer) == "/") {
        return lex_single_line_comment(lexer);
    }
    if (current_char(lexer) == "/" && peek_char(lexer) == "*") {
        return lex_multi_line_comment(lexer);
    }

    const curr: string = next_char(lexer);

    switch (curr) {
        case "(":
            return token_init(TokenType.LPAREN, curr);
        case ")":
            return token_init(TokenType.RPAREN, curr);
        case "{":
            return token_init(TokenType.LBRACE, curr);
        case "}":
            return token_init(TokenType.RBRACE, curr);
        case ";":
            return token_init(TokenType.SEMICOLON, curr);
        case ":":
            return token_init(TokenType.COLON, curr);
        case "=":
            if (current_char(lexer) == "=") {
                next_char(lexer);
                return token_init(TokenType.EQUALS_EQUALS, "==");
            }
            return token_init(TokenType.EQUALS, curr);
        case "!":
            if (current_char(lexer) == "=") {
                next_char(lexer);
                return token_init(TokenType.BANG_EQUALS, "!=");
            }
            return token_init(TokenType.BANG, curr);
        case "+":
            return token_init(TokenType.PLUS, curr);
        case "-":
            return token_init(TokenType.MINUS, curr);
        case "*":
            return token_init(TokenType.STAR, curr);
        case "/":
            return token_init(TokenType.SLASH, curr);
        case "&":
            if (current_char(lexer) == "&") {
                next_char(lexer);
                return token_init(TokenType.AND_AND, "&&");
            }
            return token_init(TokenType.AND, curr);
        case "|":
            if (current_char(lexer) == "|") {
                next_char(lexer);
                return token_init(TokenType.OR_OR, "||");
            }
            return token_init(TokenType.OR, curr);
        case "<":
            if (current_char(lexer) == "=") {
                next_char(lexer);
                return token_init(TokenType.LANGLE_EQUALS, "<=");
            }
            return token_init(TokenType.LANGLE, curr);
        case ">":
            if (current_char(lexer) == "=") {
                next_char(lexer);
                return token_init(TokenType.RANGLE_EQUALS, ">=");
            }
            return token_init(TokenType.RANGLE, curr);
        case ",":
            return token_init(TokenType.COMMA, curr);
        case ".":
            return token_init(TokenType.DOT, curr);
    }

    return token_init(TokenType.ERROR, curr);
}