#include "gc.h"
#include "primitive.h"
#include "object.h"
#include "string_obj.h"

typedef enum
{
    DataTypeKind_PRIMITIVE,
    DataTypeKind_OBJECT,
    DataTypeKind_STRUCT,
} DataTypeKind;
typedef enum
{
    VariableKind_PARAMETER,
    VariableKind_LOCAL,
    VariableKind_GLOBAL,
} VariableKind;
typedef enum
{
    ConversionKind_IMPLICIT,
    ConversionKind_EXPLICIT,
} ConversionKind;
typedef enum
{
    DiagnosticCode_UNEXPECTED_CHAR,
    DiagnosticCode_UNCLOSED_STRING,
    DiagnosticCode_UNCLOSED_CHAR,
    DiagnosticCode_EXPECTED_TOKEN,
    DiagnosticCode_UNEXPECTED_TOKEN,
} DiagnosticCode;
typedef enum
{
    TokenKind_ERROR,
    TokenKind_EOF,
    TokenKind_WHITESPACE,
    TokenKind_SINGLE_COMMENT,
    TokenKind_MULTI_COMMENT,
    TokenKind_IDENTIFIER,
    TokenKind_INTEGER_LITERAL,
    TokenKind_CHAR_LITERAL,
    TokenKind_STRING_LITERAL,
    TokenKind_TYPE_KEYWORD,
    TokenKind_FUNCTION_KEYWORD,
    TokenKind_ENUM_KEYWORD,
    TokenKind_LET_KEYWORD,
    TokenKind_NEW_KEYWORD,
    TokenKind_IF_KEYWORD,
    TokenKind_ELSE_KEYWORD,
    TokenKind_WHILE_KEYWORD,
    TokenKind_RETURN_KEYWORD,
    TokenKind_TRUE_KEYWORD,
    TokenKind_FALSE_KEYWORD,
    TokenKind_EXTERN_KEYWORD,
    TokenKind_NULL_KEYWORD,
    TokenKind_BREAK_KEYWORD,
    TokenKind_CONTINUE_KEYWORD,
    TokenKind_IS_KEYWORD,
    TokenKind_COLON,
    TokenKind_LPAREN,
    TokenKind_RPAREN,
    TokenKind_LBRACE,
    TokenKind_RBRACE,
    TokenKind_SEMICOLON,
    TokenKind_EQUALS,
    TokenKind_EQUALS_EQUALS,
    TokenKind_BANG,
    TokenKind_BANG_EQUALS,
    TokenKind_PLUS,
    TokenKind_MINUS,
    TokenKind_STAR,
    TokenKind_SLASH,
    TokenKind_AND,
    TokenKind_AND_AND,
    TokenKind_OR,
    TokenKind_OR_OR,
    TokenKind_LANGLE,
    TokenKind_LANGLE_EQUALS,
    TokenKind_RANGLE,
    TokenKind_RANGLE_EQUALS,
    TokenKind_COMMA,
    TokenKind_DOT,
} TokenKind;
typedef struct BinderFlags_impl* BinderFlags;
typedef struct Binder_impl* Binder;
typedef struct BoundProgram_impl* BoundProgram;
typedef struct BoundEnumMemberItem_impl* BoundEnumMemberItem;
typedef struct BoundEnumMember_impl* BoundEnumMember;
typedef struct BoundTypeMemberItem_impl* BoundTypeMemberItem;
typedef struct BoundTypeMemberMeta_impl* BoundTypeMemberMeta;
typedef struct BoundTypeMember_impl* BoundTypeMember;
typedef struct BoundFunctionMember_impl* BoundFunctionMember;
typedef struct BoundBlockStatement_impl* BoundBlockStatement;
typedef struct BoundIfStatement_impl* BoundIfStatement;
typedef struct BoundWhileStatement_impl* BoundWhileStatement;
typedef struct BoundReturnStatement_impl* BoundReturnStatement;
typedef struct BoundBreakStatement_impl* BoundBreakStatement;
typedef struct BoundContinueStatement_impl* BoundContinueStatement;
typedef struct BoundExpressionStatement_impl* BoundExpressionStatement;
typedef struct BoundUnkownExpression_impl* BoundUnkownExpression;
typedef struct BoundEmptyExpression_impl* BoundEmptyExpression;
typedef struct BoundCastExpression_impl* BoundCastExpression;
typedef struct BoundNullExpression_impl* BoundNullExpression;
typedef struct BoundParenExpression_impl* BoundParenExpression;
typedef struct BoundAssignmentExpression_impl* BoundAssignmentExpression;
typedef struct BoundUnaryExpression_impl* BoundUnaryExpression;
typedef struct BoundBinaryExpression_impl* BoundBinaryExpression;
typedef struct BoundUnaryOperator_impl* BoundUnaryOperator;
typedef struct BoundBinaryOperator_impl* BoundBinaryOperator;
typedef struct BoundCallExpression_impl* BoundCallExpression;
typedef struct BoundMemberExpression_impl* BoundMemberExpression;
typedef struct BoundIsExpression_impl* BoundIsExpression;
typedef struct BoundEnumFieldExpression_impl* BoundEnumFieldExpression;
typedef struct BoundCtorExpression_impl* BoundCtorExpression;
typedef struct BoundIntegerExpression_impl* BoundIntegerExpression;
typedef struct BoundCharExpression_impl* BoundCharExpression;
typedef struct BoundStringExpression_impl* BoundStringExpression;
typedef struct BoundBooleanExpression_impl* BoundBooleanExpression;
typedef struct BoundVariableExpression_impl* BoundVariableExpression;
typedef struct BoundFunctionExpression_impl* BoundFunctionExpression;
typedef struct BoundEnumExpression_impl* BoundEnumExpression;
typedef struct DataType_impl* DataType;
typedef struct Variable_impl* Variable;
typedef struct I32_impl* I32;
typedef struct Emitter_impl* Emitter;
typedef struct ConversionRule_impl* ConversionRule;
typedef struct DiagnosticBag_impl* DiagnosticBag;
typedef struct Diagnostic_impl* Diagnostic;
typedef struct Lexer_impl* Lexer;
typedef struct LocationSpan_impl* LocationSpan;
typedef struct Token_impl* Token;
typedef struct ObjectListItem_impl* ObjectListItem;
typedef struct ObjectList_impl* ObjectList;
typedef struct ObjectListIterator_impl* ObjectListIterator;
typedef struct Parser_impl* Parser;
typedef struct CompilationUnit_impl* CompilationUnit;
typedef struct TypeMemberItem_impl* TypeMemberItem;
typedef struct ExternTypeMember_impl* ExternTypeMember;
typedef struct TypeMember_impl* TypeMember;
typedef struct FunctionMemberParameter_impl* FunctionMemberParameter;
typedef struct ExternFunctionMember_impl* ExternFunctionMember;
typedef struct FunctionMember_impl* FunctionMember;
typedef struct EnumMemberItem_impl* EnumMemberItem;
typedef struct EnumMember_impl* EnumMember;
typedef struct BlockStatement_impl* BlockStatement;
typedef struct VariableStatement_impl* VariableStatement;
typedef struct ElseCase_impl* ElseCase;
typedef struct IfStatement_impl* IfStatement;
typedef struct WhileStatement_impl* WhileStatement;
typedef struct ReturnStatement_impl* ReturnStatement;
typedef struct BreakStatement_impl* BreakStatement;
typedef struct ContinueStatement_impl* ContinueStatement;
typedef struct ExpressionStatement_impl* ExpressionStatement;
typedef struct CtorExpression_impl* CtorExpression;
typedef struct AssignmentExpression_impl* AssignmentExpression;
typedef struct UnaryExpression_impl* UnaryExpression;
typedef struct BinaryExpression_impl* BinaryExpression;
typedef struct CallExpressionArgument_impl* CallExpressionArgument;
typedef struct CallExpression_impl* CallExpression;
typedef struct MemberExpression_impl* MemberExpression;
typedef struct IsExpression_impl* IsExpression;
typedef struct LiteralExpression_impl* LiteralExpression;
typedef struct ParenExpression_impl* ParenExpression;
typedef struct CastExpression_impl* CastExpression;
typedef struct TypeClause_impl* TypeClause;
typedef struct TypeSignatureDynamicGeneric_impl* TypeSignatureDynamicGeneric;
typedef struct TypeSignatureDynamic_impl* TypeSignatureDynamic;
typedef struct TypeSignature_impl* TypeSignature;
typedef struct Scope_impl* Scope;
typedef struct String_impl* String;


struct BinderFlags_impl
{
    ObjectType* __type_header__;
    bool allowEnumIdentifiers;
    bool allowBreakStatement;
    bool allowContinueStatement;
};

ObjectType BinderFlags_type = {
    .trace = object_empty_trace
};
struct Binder_impl
{
    ObjectType* __type_header__;
    ObjectList units;
    ObjectList trackedTypes;
    Scope rootScope;
    Scope currentScope;
    BoundFunctionMember currentFunction;
    ObjectList conversionRules;
    DataType voidType;
    DataType objectType;
    DataType boolType;
    DataType charType;
    DataType u8Type;
    DataType u16Type;
    DataType u32Type;
    DataType u64Type;
    DataType i8Type;
    DataType i16Type;
    DataType i32Type;
    DataType i64Type;
    ObjectList unaryOperators;
    ObjectList binaryOperators;
    BinderFlags flags;
};

static void Binder_trace(const void* _obj, gc_mark_fn mark)
{
    const Binder obj = (Binder)_obj;
    mark(obj->units);
    mark(obj->trackedTypes);
    mark(obj->rootScope);
    mark(obj->currentScope);
    mark(obj->currentFunction);
    mark(obj->conversionRules);
    mark(obj->voidType);
    mark(obj->objectType);
    mark(obj->boolType);
    mark(obj->charType);
    mark(obj->u8Type);
    mark(obj->u16Type);
    mark(obj->u32Type);
    mark(obj->u64Type);
    mark(obj->i8Type);
    mark(obj->i16Type);
    mark(obj->i32Type);
    mark(obj->i64Type);
    mark(obj->unaryOperators);
    mark(obj->binaryOperators);
    mark(obj->flags);
}

ObjectType Binder_type = {
    .trace = Binder_trace
};
struct BoundProgram_impl
{
    ObjectType* __type_header__;
    ObjectList enums;
    ObjectList externTypes;
    ObjectList types;
    ObjectList externFunctions;
    ObjectList functions;
    ObjectList trackedTypes;
};

static void BoundProgram_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundProgram obj = (BoundProgram)_obj;
    mark(obj->enums);
    mark(obj->externTypes);
    mark(obj->types);
    mark(obj->externFunctions);
    mark(obj->functions);
    mark(obj->trackedTypes);
}

ObjectType BoundProgram_type = {
    .trace = BoundProgram_trace
};
struct BoundEnumMemberItem_impl
{
    ObjectType* __type_header__;
    String name;
};

static void BoundEnumMemberItem_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundEnumMemberItem obj = (BoundEnumMemberItem)_obj;
    mark(obj->name);
}

ObjectType BoundEnumMemberItem_type = {
    .trace = BoundEnumMemberItem_trace
};
struct BoundEnumMember_impl
{
    ObjectType* __type_header__;
    String name;
    ObjectList items;
};

static void BoundEnumMember_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundEnumMember obj = (BoundEnumMember)_obj;
    mark(obj->name);
    mark(obj->items);
}

ObjectType BoundEnumMember_type = {
    .trace = BoundEnumMember_trace
};
struct BoundTypeMemberItem_impl
{
    ObjectType* __type_header__;
    String name;
    DataType dataType;
};

static void BoundTypeMemberItem_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundTypeMemberItem obj = (BoundTypeMemberItem)_obj;
    mark(obj->name);
    mark(obj->dataType);
}

ObjectType BoundTypeMemberItem_type = {
    .trace = BoundTypeMemberItem_trace
};
struct BoundTypeMemberMeta_impl
{
    ObjectType* __type_header__;
    bool generateTrace;
    String traceName;
};

static void BoundTypeMemberMeta_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundTypeMemberMeta obj = (BoundTypeMemberMeta)_obj;
    mark(obj->traceName);
}

ObjectType BoundTypeMemberMeta_type = {
    .trace = BoundTypeMemberMeta_trace
};
struct BoundTypeMember_impl
{
    ObjectType* __type_header__;
    String name;
    ObjectList items;
    BoundTypeMemberMeta meta;
};

static void BoundTypeMember_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundTypeMember obj = (BoundTypeMember)_obj;
    mark(obj->name);
    mark(obj->items);
    mark(obj->meta);
}

ObjectType BoundTypeMember_type = {
    .trace = BoundTypeMember_trace
};
struct BoundFunctionMember_impl
{
    ObjectType* __type_header__;
    String name;
    bool requiresGC;
    ObjectList parameters;
    ObjectList variables;
    Object body;
    DataType returnType;
    DataType functionSignature;
};

static void BoundFunctionMember_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundFunctionMember obj = (BoundFunctionMember)_obj;
    mark(obj->name);
    mark(obj->parameters);
    mark(obj->variables);
    mark(obj->body);
    mark(obj->returnType);
    mark(obj->functionSignature);
}

ObjectType BoundFunctionMember_type = {
    .trace = BoundFunctionMember_trace
};
struct BoundBlockStatement_impl
{
    ObjectType* __type_header__;
    ObjectList statements;
};

static void BoundBlockStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundBlockStatement obj = (BoundBlockStatement)_obj;
    mark(obj->statements);
}

ObjectType BoundBlockStatement_type = {
    .trace = BoundBlockStatement_trace
};
struct BoundIfStatement_impl
{
    ObjectType* __type_header__;
    Object condition;
    Object thenCase;
    Object elseCase;
};

static void BoundIfStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundIfStatement obj = (BoundIfStatement)_obj;
    mark(obj->condition);
    mark(obj->thenCase);
    mark(obj->elseCase);
}

ObjectType BoundIfStatement_type = {
    .trace = BoundIfStatement_trace
};
struct BoundWhileStatement_impl
{
    ObjectType* __type_header__;
    Object condition;
    Object body;
};

static void BoundWhileStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundWhileStatement obj = (BoundWhileStatement)_obj;
    mark(obj->condition);
    mark(obj->body);
}

ObjectType BoundWhileStatement_type = {
    .trace = BoundWhileStatement_trace
};
struct BoundReturnStatement_impl
{
    ObjectType* __type_header__;
    Object value;
};

static void BoundReturnStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundReturnStatement obj = (BoundReturnStatement)_obj;
    mark(obj->value);
}

ObjectType BoundReturnStatement_type = {
    .trace = BoundReturnStatement_trace
};
struct BoundBreakStatement_impl
{
    ObjectType* __type_header__;
};

ObjectType BoundBreakStatement_type = {
    .trace = object_empty_trace
};
struct BoundContinueStatement_impl
{
    ObjectType* __type_header__;
};

ObjectType BoundContinueStatement_type = {
    .trace = object_empty_trace
};
struct BoundExpressionStatement_impl
{
    ObjectType* __type_header__;
    Object expression;
};

static void BoundExpressionStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundExpressionStatement obj = (BoundExpressionStatement)_obj;
    mark(obj->expression);
}

ObjectType BoundExpressionStatement_type = {
    .trace = BoundExpressionStatement_trace
};
struct BoundUnkownExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
};

static void BoundUnkownExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundUnkownExpression obj = (BoundUnkownExpression)_obj;
    mark(obj->returnType);
}

ObjectType BoundUnkownExpression_type = {
    .trace = BoundUnkownExpression_trace
};
struct BoundEmptyExpression_impl
{
    ObjectType* __type_header__;
};

ObjectType BoundEmptyExpression_type = {
    .trace = object_empty_trace
};
struct BoundCastExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object expression;
    ConversionRule rule;
};

static void BoundCastExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundCastExpression obj = (BoundCastExpression)_obj;
    mark(obj->returnType);
    mark(obj->expression);
    mark(obj->rule);
}

ObjectType BoundCastExpression_type = {
    .trace = BoundCastExpression_trace
};
struct BoundNullExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
};

static void BoundNullExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundNullExpression obj = (BoundNullExpression)_obj;
    mark(obj->returnType);
}

ObjectType BoundNullExpression_type = {
    .trace = BoundNullExpression_trace
};
struct BoundParenExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object expression;
};

static void BoundParenExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundParenExpression obj = (BoundParenExpression)_obj;
    mark(obj->returnType);
    mark(obj->expression);
}

ObjectType BoundParenExpression_type = {
    .trace = BoundParenExpression_trace
};
struct BoundAssignmentExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object left;
    Object right;
};

static void BoundAssignmentExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundAssignmentExpression obj = (BoundAssignmentExpression)_obj;
    mark(obj->returnType);
    mark(obj->left);
    mark(obj->right);
}

ObjectType BoundAssignmentExpression_type = {
    .trace = BoundAssignmentExpression_trace
};
struct BoundUnaryExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    BoundUnaryOperator operator;
    Object right;
};

static void BoundUnaryExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundUnaryExpression obj = (BoundUnaryExpression)_obj;
    mark(obj->returnType);
    mark(obj->operator);
    mark(obj->right);
}

ObjectType BoundUnaryExpression_type = {
    .trace = BoundUnaryExpression_trace
};
struct BoundBinaryExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object left;
    BoundBinaryOperator operator;
    Object right;
};

static void BoundBinaryExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundBinaryExpression obj = (BoundBinaryExpression)_obj;
    mark(obj->returnType);
    mark(obj->left);
    mark(obj->operator);
    mark(obj->right);
}

ObjectType BoundBinaryExpression_type = {
    .trace = BoundBinaryExpression_trace
};
struct BoundUnaryOperator_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    TokenKind tokenKind;
    DataType right;
};

static void BoundUnaryOperator_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundUnaryOperator obj = (BoundUnaryOperator)_obj;
    mark(obj->returnType);
    mark(obj->right);
}

ObjectType BoundUnaryOperator_type = {
    .trace = BoundUnaryOperator_trace
};
struct BoundBinaryOperator_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    DataType left;
    TokenKind tokenKind;
    DataType right;
};

static void BoundBinaryOperator_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundBinaryOperator obj = (BoundBinaryOperator)_obj;
    mark(obj->returnType);
    mark(obj->left);
    mark(obj->right);
}

ObjectType BoundBinaryOperator_type = {
    .trace = BoundBinaryOperator_trace
};
struct BoundCallExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object callee;
    ObjectList arguments;
};

static void BoundCallExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundCallExpression obj = (BoundCallExpression)_obj;
    mark(obj->returnType);
    mark(obj->callee);
    mark(obj->arguments);
}

ObjectType BoundCallExpression_type = {
    .trace = BoundCallExpression_trace
};
struct BoundMemberExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object object;
    String identifier;
};

static void BoundMemberExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundMemberExpression obj = (BoundMemberExpression)_obj;
    mark(obj->returnType);
    mark(obj->object);
    mark(obj->identifier);
}

ObjectType BoundMemberExpression_type = {
    .trace = BoundMemberExpression_trace
};
struct BoundIsExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Object left;
    DataType targetType;
};

static void BoundIsExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundIsExpression obj = (BoundIsExpression)_obj;
    mark(obj->returnType);
    mark(obj->left);
    mark(obj->targetType);
}

ObjectType BoundIsExpression_type = {
    .trace = BoundIsExpression_trace
};
struct BoundEnumFieldExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    String name;
    String item;
};

static void BoundEnumFieldExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundEnumFieldExpression obj = (BoundEnumFieldExpression)_obj;
    mark(obj->returnType);
    mark(obj->name);
    mark(obj->item);
}

ObjectType BoundEnumFieldExpression_type = {
    .trace = BoundEnumFieldExpression_trace
};
struct BoundCtorExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
};

static void BoundCtorExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundCtorExpression obj = (BoundCtorExpression)_obj;
    mark(obj->returnType);
}

ObjectType BoundCtorExpression_type = {
    .trace = BoundCtorExpression_trace
};
struct BoundIntegerExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    String value;
};

static void BoundIntegerExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundIntegerExpression obj = (BoundIntegerExpression)_obj;
    mark(obj->returnType);
    mark(obj->value);
}

ObjectType BoundIntegerExpression_type = {
    .trace = BoundIntegerExpression_trace
};
struct BoundCharExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    String value;
};

static void BoundCharExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundCharExpression obj = (BoundCharExpression)_obj;
    mark(obj->returnType);
    mark(obj->value);
}

ObjectType BoundCharExpression_type = {
    .trace = BoundCharExpression_trace
};
struct BoundStringExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    String value;
};

static void BoundStringExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundStringExpression obj = (BoundStringExpression)_obj;
    mark(obj->returnType);
    mark(obj->value);
}

ObjectType BoundStringExpression_type = {
    .trace = BoundStringExpression_trace
};
struct BoundBooleanExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    TokenKind value;
};

static void BoundBooleanExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundBooleanExpression obj = (BoundBooleanExpression)_obj;
    mark(obj->returnType);
}

ObjectType BoundBooleanExpression_type = {
    .trace = BoundBooleanExpression_trace
};
struct BoundVariableExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    Variable variable;
};

static void BoundVariableExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundVariableExpression obj = (BoundVariableExpression)_obj;
    mark(obj->returnType);
    mark(obj->variable);
}

ObjectType BoundVariableExpression_type = {
    .trace = BoundVariableExpression_trace
};
struct BoundFunctionExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    BoundFunctionMember function;
};

static void BoundFunctionExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundFunctionExpression obj = (BoundFunctionExpression)_obj;
    mark(obj->returnType);
    mark(obj->function);
}

ObjectType BoundFunctionExpression_type = {
    .trace = BoundFunctionExpression_trace
};
struct BoundEnumExpression_impl
{
    ObjectType* __type_header__;
    DataType returnType;
    BoundEnumMember enumMember;
};

static void BoundEnumExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BoundEnumExpression obj = (BoundEnumExpression)_obj;
    mark(obj->returnType);
    mark(obj->enumMember);
}

ObjectType BoundEnumExpression_type = {
    .trace = BoundEnumExpression_trace
};
struct DataType_impl
{
    ObjectType* __type_header__;
    DataTypeKind kind;
    String name;
    ObjectList generics;
    String cName;
    Object definition;
};

static void DataType_trace(const void* _obj, gc_mark_fn mark)
{
    const DataType obj = (DataType)_obj;
    mark(obj->name);
    mark(obj->generics);
    mark(obj->cName);
    mark(obj->definition);
}

ObjectType DataType_type = {
    .trace = DataType_trace
};
struct Variable_impl
{
    ObjectType* __type_header__;
    VariableKind kind;
    String name;
    i32 id;
    DataType dataType;
};

static void Variable_trace(const void* _obj, gc_mark_fn mark)
{
    const Variable obj = (Variable)_obj;
    mark(obj->name);
    mark(obj->dataType);
}

ObjectType Variable_type = {
    .trace = Variable_trace
};
struct I32_impl
{
    ObjectType* __type_header__;
    i32 value;
};

ObjectType I32_type = {
    .trace = object_empty_trace
};
struct Emitter_impl
{
    ObjectType* __type_header__;
    Object file;
    i32 intention;
    BoundFunctionMember currentFunction;
};

static void Emitter_trace(const void* _obj, gc_mark_fn mark)
{
    const Emitter obj = (Emitter)_obj;
    mark(obj->file);
    mark(obj->currentFunction);
}

ObjectType Emitter_type = {
    .trace = Emitter_trace
};
struct ConversionRule_impl
{
    ObjectType* __type_header__;
    DataType from;
    DataType to;
    ConversionKind kind;
};

static void ConversionRule_trace(const void* _obj, gc_mark_fn mark)
{
    const ConversionRule obj = (ConversionRule)_obj;
    mark(obj->from);
    mark(obj->to);
}

ObjectType ConversionRule_type = {
    .trace = ConversionRule_trace
};
struct DiagnosticBag_impl
{
    ObjectType* __type_header__;
    ObjectList list;
};

static void DiagnosticBag_trace(const void* _obj, gc_mark_fn mark)
{
    const DiagnosticBag obj = (DiagnosticBag)_obj;
    mark(obj->list);
}

ObjectType DiagnosticBag_type = {
    .trace = DiagnosticBag_trace
};
struct Diagnostic_impl
{
    ObjectType* __type_header__;
    DiagnosticCode code;
    LocationSpan span;
    ObjectList args;
};

static void Diagnostic_trace(const void* _obj, gc_mark_fn mark)
{
    const Diagnostic obj = (Diagnostic)_obj;
    mark(obj->span);
    mark(obj->args);
}

ObjectType Diagnostic_type = {
    .trace = Diagnostic_trace
};
struct Lexer_impl
{
    ObjectType* __type_header__;
    DiagnosticBag diagnostics;
    String filename;
    String content;
    i32 position;
    i32 currentLine;
    i32 currentCol;
};

static void Lexer_trace(const void* _obj, gc_mark_fn mark)
{
    const Lexer obj = (Lexer)_obj;
    mark(obj->diagnostics);
    mark(obj->filename);
    mark(obj->content);
}

ObjectType Lexer_type = {
    .trace = Lexer_trace
};
struct LocationSpan_impl
{
    ObjectType* __type_header__;
    String filename;
    i32 startPos;
    i32 endPos;
    i32 startLine;
    i32 endLine;
    i32 startCol;
    i32 endCol;
};

static void LocationSpan_trace(const void* _obj, gc_mark_fn mark)
{
    const LocationSpan obj = (LocationSpan)_obj;
    mark(obj->filename);
}

ObjectType LocationSpan_type = {
    .trace = LocationSpan_trace
};
struct Token_impl
{
    ObjectType* __type_header__;
    TokenKind kind;
    String value;
    LocationSpan span;
};

static void Token_trace(const void* _obj, gc_mark_fn mark)
{
    const Token obj = (Token)_obj;
    mark(obj->value);
    mark(obj->span);
}

ObjectType Token_type = {
    .trace = Token_trace
};
struct ObjectListItem_impl
{
    ObjectType* __type_header__;
    Object value;
    ObjectListItem next;
    ObjectListItem prev;
};

static void ObjectListItem_trace(const void* _obj, gc_mark_fn mark)
{
    const ObjectListItem obj = (ObjectListItem)_obj;
    mark(obj->value);
    mark(obj->next);
    mark(obj->prev);
}

ObjectType ObjectListItem_type = {
    .trace = ObjectListItem_trace
};
struct ObjectList_impl
{
    ObjectType* __type_header__;
    ObjectListItem first;
    ObjectListItem last;
    i32 length;
};

static void ObjectList_trace(const void* _obj, gc_mark_fn mark)
{
    const ObjectList obj = (ObjectList)_obj;
    mark(obj->first);
    mark(obj->last);
}

ObjectType ObjectList_type = {
    .trace = ObjectList_trace
};
struct ObjectListIterator_impl
{
    ObjectType* __type_header__;
    ObjectListItem current;
    i32 index;
    i32 length;
};

static void ObjectListIterator_trace(const void* _obj, gc_mark_fn mark)
{
    const ObjectListIterator obj = (ObjectListIterator)_obj;
    mark(obj->current);
}

ObjectType ObjectListIterator_type = {
    .trace = ObjectListIterator_trace
};
struct Parser_impl
{
    ObjectType* __type_header__;
    DiagnosticBag diagnostics;
    ObjectList tokens;
    i32 position;
};

static void Parser_trace(const void* _obj, gc_mark_fn mark)
{
    const Parser obj = (Parser)_obj;
    mark(obj->diagnostics);
    mark(obj->tokens);
}

ObjectType Parser_type = {
    .trace = Parser_trace
};
struct CompilationUnit_impl
{
    ObjectType* __type_header__;
    ObjectList externTypes;
    ObjectList types;
    ObjectList externFunctions;
    ObjectList functions;
    ObjectList enums;
    Token eof;
};

static void CompilationUnit_trace(const void* _obj, gc_mark_fn mark)
{
    const CompilationUnit obj = (CompilationUnit)_obj;
    mark(obj->externTypes);
    mark(obj->types);
    mark(obj->externFunctions);
    mark(obj->functions);
    mark(obj->enums);
    mark(obj->eof);
}

ObjectType CompilationUnit_type = {
    .trace = CompilationUnit_trace
};
struct TypeMemberItem_impl
{
    ObjectType* __type_header__;
    Token identifier;
    TypeClause typeClause;
    ObjectList semicolons;
};

static void TypeMemberItem_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeMemberItem obj = (TypeMemberItem)_obj;
    mark(obj->identifier);
    mark(obj->typeClause);
    mark(obj->semicolons);
}

ObjectType TypeMemberItem_type = {
    .trace = TypeMemberItem_trace
};
struct ExternTypeMember_impl
{
    ObjectType* __type_header__;
    Token extern_;
    Token keyword;
    Token identifier;
    Token lBrace;
    ObjectList items;
    Token rBrace;
    ObjectList semicolons;
};

static void ExternTypeMember_trace(const void* _obj, gc_mark_fn mark)
{
    const ExternTypeMember obj = (ExternTypeMember)_obj;
    mark(obj->extern_);
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->lBrace);
    mark(obj->items);
    mark(obj->rBrace);
    mark(obj->semicolons);
}

ObjectType ExternTypeMember_type = {
    .trace = ExternTypeMember_trace
};
struct TypeMember_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token identifier;
    Token lBrace;
    ObjectList items;
    Token rBrace;
    ObjectList semicolons;
};

static void TypeMember_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeMember obj = (TypeMember)_obj;
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->lBrace);
    mark(obj->items);
    mark(obj->rBrace);
    mark(obj->semicolons);
}

ObjectType TypeMember_type = {
    .trace = TypeMember_trace
};
struct FunctionMemberParameter_impl
{
    ObjectType* __type_header__;
    Token identifier;
    TypeClause typeClause;
    Token comma;
};

static void FunctionMemberParameter_trace(const void* _obj, gc_mark_fn mark)
{
    const FunctionMemberParameter obj = (FunctionMemberParameter)_obj;
    mark(obj->identifier);
    mark(obj->typeClause);
    mark(obj->comma);
}

ObjectType FunctionMemberParameter_type = {
    .trace = FunctionMemberParameter_trace
};
struct ExternFunctionMember_impl
{
    ObjectType* __type_header__;
    Token extern_;
    Token keyword;
    Token identifier;
    Token lParen;
    ObjectList parameters;
    Token rParen;
    TypeClause returnType;
    ObjectList semicolons;
};

static void ExternFunctionMember_trace(const void* _obj, gc_mark_fn mark)
{
    const ExternFunctionMember obj = (ExternFunctionMember)_obj;
    mark(obj->extern_);
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->lParen);
    mark(obj->parameters);
    mark(obj->rParen);
    mark(obj->returnType);
    mark(obj->semicolons);
}

ObjectType ExternFunctionMember_type = {
    .trace = ExternFunctionMember_trace
};
struct FunctionMember_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token identifier;
    Token lParen;
    ObjectList parameters;
    Token rParen;
    TypeClause returnType;
    BlockStatement body;
};

static void FunctionMember_trace(const void* _obj, gc_mark_fn mark)
{
    const FunctionMember obj = (FunctionMember)_obj;
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->lParen);
    mark(obj->parameters);
    mark(obj->rParen);
    mark(obj->returnType);
    mark(obj->body);
}

ObjectType FunctionMember_type = {
    .trace = FunctionMember_trace
};
struct EnumMemberItem_impl
{
    ObjectType* __type_header__;
    Token identifier;
    Token comma;
};

static void EnumMemberItem_trace(const void* _obj, gc_mark_fn mark)
{
    const EnumMemberItem obj = (EnumMemberItem)_obj;
    mark(obj->identifier);
    mark(obj->comma);
}

ObjectType EnumMemberItem_type = {
    .trace = EnumMemberItem_trace
};
struct EnumMember_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token identifier;
    Token lBrace;
    ObjectList items;
    Token rBrace;
    ObjectList semicolons;
};

static void EnumMember_trace(const void* _obj, gc_mark_fn mark)
{
    const EnumMember obj = (EnumMember)_obj;
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->lBrace);
    mark(obj->items);
    mark(obj->rBrace);
    mark(obj->semicolons);
}

ObjectType EnumMember_type = {
    .trace = EnumMember_trace
};
struct BlockStatement_impl
{
    ObjectType* __type_header__;
    Token lBrace;
    ObjectList statements;
    Token rBrace;
    ObjectList semicolons;
};

static void BlockStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BlockStatement obj = (BlockStatement)_obj;
    mark(obj->lBrace);
    mark(obj->statements);
    mark(obj->rBrace);
    mark(obj->semicolons);
}

ObjectType BlockStatement_type = {
    .trace = BlockStatement_trace
};
struct VariableStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token identifier;
    TypeClause typeClause;
    Token equals;
    Object initializer;
    ObjectList semicolons;
};

static void VariableStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const VariableStatement obj = (VariableStatement)_obj;
    mark(obj->keyword);
    mark(obj->identifier);
    mark(obj->typeClause);
    mark(obj->equals);
    mark(obj->initializer);
    mark(obj->semicolons);
}

ObjectType VariableStatement_type = {
    .trace = VariableStatement_trace
};
struct ElseCase_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Object thenCase;
};

static void ElseCase_trace(const void* _obj, gc_mark_fn mark)
{
    const ElseCase obj = (ElseCase)_obj;
    mark(obj->keyword);
    mark(obj->thenCase);
}

ObjectType ElseCase_type = {
    .trace = ElseCase_trace
};
struct IfStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token lParen;
    Object condition;
    Token rParen;
    Object thenCase;
    ElseCase elseCase;
};

static void IfStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const IfStatement obj = (IfStatement)_obj;
    mark(obj->keyword);
    mark(obj->lParen);
    mark(obj->condition);
    mark(obj->rParen);
    mark(obj->thenCase);
    mark(obj->elseCase);
}

ObjectType IfStatement_type = {
    .trace = IfStatement_trace
};
struct WhileStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Token lParen;
    Object condition;
    Object rParen;
    Object body;
};

static void WhileStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const WhileStatement obj = (WhileStatement)_obj;
    mark(obj->keyword);
    mark(obj->lParen);
    mark(obj->condition);
    mark(obj->rParen);
    mark(obj->body);
}

ObjectType WhileStatement_type = {
    .trace = WhileStatement_trace
};
struct ReturnStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    Object value;
    ObjectList semicolons;
};

static void ReturnStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const ReturnStatement obj = (ReturnStatement)_obj;
    mark(obj->keyword);
    mark(obj->value);
    mark(obj->semicolons);
}

ObjectType ReturnStatement_type = {
    .trace = ReturnStatement_trace
};
struct BreakStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    ObjectList semicolons;
};

static void BreakStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const BreakStatement obj = (BreakStatement)_obj;
    mark(obj->keyword);
    mark(obj->semicolons);
}

ObjectType BreakStatement_type = {
    .trace = BreakStatement_trace
};
struct ContinueStatement_impl
{
    ObjectType* __type_header__;
    Token keyword;
    ObjectList semicolons;
};

static void ContinueStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const ContinueStatement obj = (ContinueStatement)_obj;
    mark(obj->keyword);
    mark(obj->semicolons);
}

ObjectType ContinueStatement_type = {
    .trace = ContinueStatement_trace
};
struct ExpressionStatement_impl
{
    ObjectType* __type_header__;
    Object expression;
    ObjectList semicolons;
};

static void ExpressionStatement_trace(const void* _obj, gc_mark_fn mark)
{
    const ExpressionStatement obj = (ExpressionStatement)_obj;
    mark(obj->expression);
    mark(obj->semicolons);
}

ObjectType ExpressionStatement_type = {
    .trace = ExpressionStatement_trace
};
struct CtorExpression_impl
{
    ObjectType* __type_header__;
    Token keyword;
    TypeSignature typeSignature;
    Token lParen;
    Token rParen;
};

static void CtorExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const CtorExpression obj = (CtorExpression)_obj;
    mark(obj->keyword);
    mark(obj->typeSignature);
    mark(obj->lParen);
    mark(obj->rParen);
}

ObjectType CtorExpression_type = {
    .trace = CtorExpression_trace
};
struct AssignmentExpression_impl
{
    ObjectType* __type_header__;
    Object left;
    Token operator;
    Object right;
};

static void AssignmentExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const AssignmentExpression obj = (AssignmentExpression)_obj;
    mark(obj->left);
    mark(obj->operator);
    mark(obj->right);
}

ObjectType AssignmentExpression_type = {
    .trace = AssignmentExpression_trace
};
struct UnaryExpression_impl
{
    ObjectType* __type_header__;
    Token operator;
    Object right;
};

static void UnaryExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const UnaryExpression obj = (UnaryExpression)_obj;
    mark(obj->operator);
    mark(obj->right);
}

ObjectType UnaryExpression_type = {
    .trace = UnaryExpression_trace
};
struct BinaryExpression_impl
{
    ObjectType* __type_header__;
    Object left;
    Token operator;
    Object right;
};

static void BinaryExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const BinaryExpression obj = (BinaryExpression)_obj;
    mark(obj->left);
    mark(obj->operator);
    mark(obj->right);
}

ObjectType BinaryExpression_type = {
    .trace = BinaryExpression_trace
};
struct CallExpressionArgument_impl
{
    ObjectType* __type_header__;
    Object expression;
    Token comma;
};

static void CallExpressionArgument_trace(const void* _obj, gc_mark_fn mark)
{
    const CallExpressionArgument obj = (CallExpressionArgument)_obj;
    mark(obj->expression);
    mark(obj->comma);
}

ObjectType CallExpressionArgument_type = {
    .trace = CallExpressionArgument_trace
};
struct CallExpression_impl
{
    ObjectType* __type_header__;
    Object callee;
    Token lParen;
    ObjectList arguments;
    Token rParen;
};

static void CallExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const CallExpression obj = (CallExpression)_obj;
    mark(obj->callee);
    mark(obj->lParen);
    mark(obj->arguments);
    mark(obj->rParen);
}

ObjectType CallExpression_type = {
    .trace = CallExpression_trace
};
struct MemberExpression_impl
{
    ObjectType* __type_header__;
    Object object;
    Token dot;
    Token identifier;
};

static void MemberExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const MemberExpression obj = (MemberExpression)_obj;
    mark(obj->object);
    mark(obj->dot);
    mark(obj->identifier);
}

ObjectType MemberExpression_type = {
    .trace = MemberExpression_trace
};
struct IsExpression_impl
{
    ObjectType* __type_header__;
    Object left;
    Token keyword;
    TypeSignature typeSignature;
};

static void IsExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const IsExpression obj = (IsExpression)_obj;
    mark(obj->left);
    mark(obj->keyword);
    mark(obj->typeSignature);
}

ObjectType IsExpression_type = {
    .trace = IsExpression_trace
};
struct LiteralExpression_impl
{
    ObjectType* __type_header__;
    Token value;
};

static void LiteralExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const LiteralExpression obj = (LiteralExpression)_obj;
    mark(obj->value);
}

ObjectType LiteralExpression_type = {
    .trace = LiteralExpression_trace
};
struct ParenExpression_impl
{
    ObjectType* __type_header__;
    Token lParen;
    Object expression;
    Token rParen;
};

static void ParenExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const ParenExpression obj = (ParenExpression)_obj;
    mark(obj->lParen);
    mark(obj->expression);
    mark(obj->rParen);
}

ObjectType ParenExpression_type = {
    .trace = ParenExpression_trace
};
struct CastExpression_impl
{
    ObjectType* __type_header__;
    Token lAngle;
    TypeSignature typeSignature;
    Token rAngle;
    Object expression;
};

static void CastExpression_trace(const void* _obj, gc_mark_fn mark)
{
    const CastExpression obj = (CastExpression)_obj;
    mark(obj->lAngle);
    mark(obj->typeSignature);
    mark(obj->rAngle);
    mark(obj->expression);
}

ObjectType CastExpression_type = {
    .trace = CastExpression_trace
};
struct TypeClause_impl
{
    ObjectType* __type_header__;
    Token colon;
    TypeSignature typeSignature;
};

static void TypeClause_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeClause obj = (TypeClause)_obj;
    mark(obj->colon);
    mark(obj->typeSignature);
}

ObjectType TypeClause_type = {
    .trace = TypeClause_trace
};
struct TypeSignatureDynamicGeneric_impl
{
    ObjectType* __type_header__;
    TypeSignature typeSignature;
    Token comma;
};

static void TypeSignatureDynamicGeneric_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeSignatureDynamicGeneric obj = (TypeSignatureDynamicGeneric)_obj;
    mark(obj->typeSignature);
    mark(obj->comma);
}

ObjectType TypeSignatureDynamicGeneric_type = {
    .trace = TypeSignatureDynamicGeneric_trace
};
struct TypeSignatureDynamic_impl
{
    ObjectType* __type_header__;
    Token lAngle;
    ObjectList generics;
    Token rAngle;
};

static void TypeSignatureDynamic_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeSignatureDynamic obj = (TypeSignatureDynamic)_obj;
    mark(obj->lAngle);
    mark(obj->generics);
    mark(obj->rAngle);
}

ObjectType TypeSignatureDynamic_type = {
    .trace = TypeSignatureDynamic_trace
};
struct TypeSignature_impl
{
    ObjectType* __type_header__;
    Token identifier;
    TypeSignatureDynamic dynamic;
};

static void TypeSignature_trace(const void* _obj, gc_mark_fn mark)
{
    const TypeSignature obj = (TypeSignature)_obj;
    mark(obj->identifier);
    mark(obj->dynamic);
}

ObjectType TypeSignature_type = {
    .trace = TypeSignature_trace
};
struct Scope_impl
{
    ObjectType* __type_header__;
    Scope parent;
    ObjectList dataTypes;
    ObjectList variables;
    ObjectList functions;
};

static void Scope_trace(const void* _obj, gc_mark_fn mark)
{
    const Scope obj = (Scope)_obj;
    mark(obj->parent);
    mark(obj->dataTypes);
    mark(obj->variables);
    mark(obj->functions);
}

ObjectType Scope_type = {
    .trace = Scope_trace
};
struct String_impl
{
    ObjectType* __type_header__;
    uchar* buff;
    i32 length;
};
extern ObjectType String_type;



extern Object fs_open_file(String path0);
extern void fs_write_string(Object file0, String value0);
extern void fs_write_char(Object file0, uchar value0);
extern void fs_write_int(Object file0, i32 value0);
extern void fs_close_file(Object file0);
extern Object fs_get_stderr();
extern void gc_mark();
extern void gc_sweep();
extern void gc_mark_sweep();
extern void string_dump(String str0);
extern String string_concat(String left0, String right0);
extern String string_substring(String left0, i32 start0, i32 end0);
extern uchar string_char_at(String left0, i32 index0);
extern bool string_equals(String left0, String right0);
extern String fs_read_file(String path0);
extern void exit(i32 code0);

DataType type_init_simple(DataTypeKind kind0, String name0, String cName0);
DataType type_init_complex(DataTypeKind kind0, String name0, String cName0, Object definition0);
DataType type_init_dynamic(DataTypeKind kind0, String name0, String cName0, ObjectList generics0);
bool type_eq_type(DataType left0, DataType right0);
bool type_eq_def(DataType left0, String name0, ObjectList generics0);
Variable variable_init(BoundFunctionMember function0, VariableKind kind0, String name0, DataType dataType0);
Variable parameter_init(String name0, DataType dataType0);
BoundUnaryOperator unary_operator_init(TokenKind tokenKind0, DataType operandType0, DataType returnType0);
BoundBinaryOperator binary_operator_init(TokenKind tokenKind0, DataType leftType0, DataType rightType0, DataType returnType0);
Binder binder_init(ObjectList units0);
DataType RETURN_TYPE(Object object0);
void SET_RETURN_TYPE(Object object0, DataType dataType0);
String generate_func_cName(ObjectList generics0);
DataType bind_type_signature_dynamic_func(Binder binder0, TypeSignatureDynamic dynamic0);
DataType bind_type_signature_dynamic_span(Binder binder0, TypeSignatureDynamic dynamic0);
DataType bind_type_signature_dynamic(Binder binder0, TypeSignature signature0, TypeSignatureDynamic dynamic0);
DataType bind_type_signature(Binder binder0, TypeSignature signature0, bool allowVoid0);
DataType bind_type_clause(Binder binder0, TypeClause typeClause0, bool allowVoid0);
BoundCtorExpression bind_ctor_expression(Binder binder0, CtorExpression ctorExpression0);
bool is_node_assignable(Object node0);
BoundAssignmentExpression bind_assignment_expression(Binder binder0, AssignmentExpression assignmentExpression0);
BoundUnaryOperator lookup_unary_operator(Binder binder0, TokenKind tokenKind0, DataType operandType0);
BoundUnaryExpression bind_unary_expression(Binder binder0, UnaryExpression unaryExpression0);
BoundBinaryOperator lookup_binary_operator(Binder binder0, TokenKind tokenKind0, DataType leftType0, DataType rightType0);
BoundBinaryExpression bind_binary_expression(Binder binder0, BinaryExpression binaryExpression0);
BoundCallExpression bind_call_expression(Binder binder0, CallExpression callExpression0);
Object bind_member_expression(Binder binder0, MemberExpression memberExpression0);
BoundIsExpression bind_is_expression(Binder binder0, IsExpression isExpression0);
Object bind_literal_expression(Binder binder0, LiteralExpression literalExpression0);
Object bind_identifier_expression(Binder binder0, LiteralExpression literalExpression0);
BoundParenExpression bind_paren_expression(Binder binder0, ParenExpression parenExpression0);
Object bind_cast_expression(Binder binder0, CastExpression castExpression0);
Object bind_conversion(Object boundExpression0, ObjectList conversions0);
Object bind_expression_internal(Binder binder0, Object expression0);
Object bind_expression(Binder binder0, Object expression0, DataType expectedType0);
BoundBlockStatement bind_block_statement(Binder binder0, BlockStatement blockStatement0);
Object bind_variable_statement(Binder binder0, VariableStatement variableStatement0);
BoundIfStatement bind_if_statement(Binder binder0, IfStatement ifStatement0);
BoundWhileStatement bind_while_statement(Binder binder0, WhileStatement whileStatement0);
BoundReturnStatement bind_return_statement(Binder binder0, ReturnStatement returnStatement0);
BoundBreakStatement bind_break_statement(Binder binder0, BreakStatement breakStatement0);
BoundContinueStatement bind_continue_statement(Binder binder0, ContinueStatement continueStatement0);
BoundExpressionStatement bind_expression_statement(Binder binder0, ExpressionStatement expressionStatement0);
Object bind_statement(Binder binder0, Object statement0);
BoundEnumMember bind_enum_member(Binder binder0, EnumMember enumMember0);
BoundTypeMember bind_extern_type_member(Binder binder0, ExternTypeMember externTypeMember0);
void bind_type_member_signature(Binder binder0, TypeMember typeMember0);
BoundTypeMember bind_type_member(Binder binder0, TypeMember typeMember0);
BoundFunctionMember bind_extern_function_member(Binder binder0, ExternFunctionMember externFunctionMember0);
void bind_function_member_signature(Binder binder0, FunctionMember functionMember0);
BoundFunctionMember bind_function_member(Binder binder0, FunctionMember functionMember0);
BoundProgram binder_bind(Binder binder0);
I32 box_i32(i32 value0);
Emitter emitter_init(Object file0);
void write_intended(Emitter emitter0, String content0);
void writeln_intended(Emitter emitter0, String content0);
void write(Emitter emitter0, String content0);
void writeln(Emitter emitter0, String content0);
void inc_intention(Emitter emitter0);
void dec_intention(Emitter emitter0);
void emit_header(Emitter emitter0);
void emit_type(Emitter emitter0, DataType dataType0);
void emit_variable_name(Emitter emitter0, Variable variable0);
void emit_cast_expression(Emitter emitter0, BoundCastExpression castExpression0);
void emit_null_expression(Emitter emitter0, BoundNullExpression nullExpression0);
void emit_paren_expression(Emitter emitter0, BoundParenExpression parenExpression0);
void emit_ctor_expression(Emitter emitter0, BoundCtorExpression ctorExpression0);
void emit_assignment_expression(Emitter emitter0, BoundAssignmentExpression assignment_expression0);
void emit_unary_expression(Emitter emitter0, BoundUnaryExpression unaryExpression0);
void emit_binary_expression(Emitter emitter0, BoundBinaryExpression binaryExpression0);
void emit_call_expression(Emitter emitter0, BoundCallExpression callExpression0);
void emit_member_expression(Emitter emitter0, BoundMemberExpression memberExpression0);
void emit_is_expression(Emitter emitter0, BoundIsExpression isExpression0);
void emit_enum_field_expression(Emitter emitter0, BoundEnumFieldExpression enumFieldExpression0);
void emit_integer_expression(Emitter emitter0, BoundIntegerExpression integerExpression0);
void emit_char_expression(Emitter emitter0, BoundCharExpression charExpression0);
void emit_string_expression(Emitter emitter0, BoundStringExpression stringExpression0);
void emit_boolean_expression(Emitter emitter0, BoundBooleanExpression booleanExpression0);
void emit_variable_expression(Emitter emitter0, BoundVariableExpression variableExpression0);
void emit_function_expression(Emitter emitter0, BoundFunctionExpression functionExpression0);
void emit_expression(Emitter emitter0, Object expression0);
void emit_block_statement(Emitter emitter0, BoundBlockStatement blockStatement0);
void emit_if_statement(Emitter emitter0, BoundIfStatement ifStatement0);
void emit_while_statement(Emitter emitter0, BoundWhileStatement whileStatement0);
void emit_return_statement(Emitter emitter0, BoundReturnStatement returnStatement0);
void emit_break_statement(Emitter emitter0, BoundBreakStatement breakStatement0);
void emit_continue_statement(Emitter emitter0, BoundContinueStatement continueStatement0);
void emit_expression_statement(Emitter emitter0, BoundExpressionStatement expressionStatement0);
void emit_statement(Emitter emitter0, Object statement0);
void emit_track_func_type(Emitter emitter0, DataType dataType0);
void emit_enum_member(Emitter emitter0, BoundEnumMember enumMember0);
void emit_type_member_header(Emitter emitter0, BoundTypeMember typeMember0);
void emit_type_member(Emitter emitter0, BoundTypeMember typeMember0);
void emit_type_member_trace(Emitter emitter0, BoundTypeMember typeMember0);
void emit_type_member_type(Emitter emitter0, BoundTypeMember typeMember0);
void emit_extern_type_member_type(Emitter emitter0, BoundTypeMember typeMember0);
void emit_extern_function_member(Emitter emitter0, BoundFunctionMember functionMember0);
void emit_function_member_header(Emitter emitter0, BoundFunctionMember functionMember0);
void emit_function_member(Emitter emitter0, BoundFunctionMember functionMember0);
void emit_program(Emitter emitter0, BoundProgram program0);
bool char_is_alpha(uchar c0);
bool char_is_numeric(uchar c0);
bool char_is_alpha_numeric(uchar c0);
bool char_is_whitespace(uchar c0);
ConversionRule rule_init(DataType from0, DataType to0, ConversionKind kind0);
ObjectList conversion_init(DataType i8Type0, DataType i16Type0, DataType i32Type0, DataType i64Type0, DataType u8Type0, DataType u16Type0, DataType u32Type0, DataType u64Type0, DataType boolType0, DataType charType0);
ObjectList conversion_classify(Binder binder0, DataType from0, DataType to0, bool explicit0);
DiagnosticBag diagnosticBag_init();
Diagnostic diagnostic_init(DiagnosticCode code0, LocationSpan span0, ObjectList args0);
void report_unexpected_char(DiagnosticBag bag0, LocationSpan span0, String value0);
void report_unclosed_string(DiagnosticBag bag0, LocationSpan span0);
void report_unclosed_char(DiagnosticBag bag0, LocationSpan span0);
void report_expected_token(DiagnosticBag bag0, LocationSpan span0, TokenKind got0, TokenKind expected0);
void report_expected_token2(DiagnosticBag bag0, LocationSpan span0, TokenKind got0, TokenKind expected10, TokenKind expected20);
void diagnostic_print_code_message(Object fd0, DiagnosticCode code0, ObjectList args0);
void diagnostic_print_single(Object fd0, Diagnostic diagnostic0);
void diagnostic_print(DiagnosticBag diagnostics0);
Lexer lexer_init(DiagnosticBag diagnostics0, String filename0, String content0);
LocationSpan locationSpan_init(String filename0, i32 startPos0, i32 endPos0, i32 startLine0, i32 endLine0, i32 startCol0, i32 endCol0);
Token token_init(TokenKind kind0, String value0, LocationSpan span0);
bool lexer_is_eof(Lexer lexer0);
uchar current_char(Lexer lexer0);
uchar peek_char(Lexer lexer0);
uchar next_char(Lexer lexer0);
Token lex_whitespace(Lexer lexer0);
Token lex_identifier(Lexer lexer0);
Token lex_numeric(Lexer lexer0);
Token lex_char(Lexer lexer0);
Token lex_string(Lexer lexer0);
Token lex_single_line_comment(Lexer lexer0);
Token lex_multi_line_comment(Lexer lexer0);
Token lexer_next_token(Lexer lexer0);
ObjectList list_init();
void list_push(ObjectList list0, Object value0);
void list_unshift(ObjectList list0, Object value0);
Object list_pop(ObjectList list0);
Object list_shift(ObjectList list0);
Object list_get_value(ObjectList list0, i32 index0);
ObjectList list_concat(ObjectList left0, ObjectList right0);
ObjectList list_dup(ObjectList list0);
ObjectListIterator list_iterator(ObjectList list0);
bool list_iterator_has_next(ObjectListIterator iterator0);
Object list_iterator_next(ObjectListIterator iterator0);
i32 entry(ObjectList args0);
void PANIC(String message0);
Parser parser_init(DiagnosticBag diagnostics0, String filename0, String content0);
Token current_token(Parser parser0);
Token peek_token(Parser parser0);
Token next_token(Parser parser0);
Token match_token(Parser parser0, TokenKind kind0);
Token match_token2(Parser parser0, TokenKind kind10, TokenKind kind20);
bool parser_is_eof(Parser parser0);
i32 unary_operator_precedence(TokenKind operator0);
i32 binary_operator_precedence(TokenKind operator0);
ObjectList parse_semicolon_block(Parser parser0, bool expectAtLeastOne0);
TypeSignature parse_type_signature(Parser parser0);
TypeClause parse_type_clause(Parser parser0);
CtorExpression parse_ctor_expression(Parser parser0);
LiteralExpression parse_integer_expression(Parser parser0);
LiteralExpression parse_char_expression(Parser parser0);
LiteralExpression parse_string_expression(Parser parser0);
LiteralExpression parse_boolean_expression(Parser parser0);
LiteralExpression parse_identifier_expression(Parser parser0);
ParenExpression parse_paren_expression(Parser parser0);
CastExpression parse_cast_expression(Parser parser0);
LiteralExpression parse_null_expression(Parser parser0);
Object parse_base_expression(Parser parser0);
Object parse_wrapper_expression(Parser parser0);
Object parse_binary_expression(Parser parser0, i32 parentPrecedence0);
Object parse_assignment_expression(Parser parser0);
Object parse_expression(Parser parser0);
BlockStatement parse_block_statement(Parser parser0);
VariableStatement parse_variable_statement(Parser parser0);
IfStatement parse_if_statement(Parser parser0);
WhileStatement parse_while_statement(Parser parser0);
ReturnStatement parse_return_statement(Parser parser0);
BreakStatement parse_break_statement(Parser parser0);
ContinueStatement parse_continue_statement(Parser parser0);
ExpressionStatement parse_expression_statement(Parser parser0);
Object parse_statement(Parser parser0);
ExternFunctionMember parse_extern_function_member(Parser parser0);
ExternTypeMember parse_extern_type_member(Parser parser0);
FunctionMember parse_function_member(Parser parser0);
TypeMember parse_type_member(Parser parser0);
EnumMember parse_enum_member(Parser parser0);
CompilationUnit parse_compilation_unit(Parser parser0);
Scope scope_init(Scope parent0);
void scope_push_scope(Binder binder0);
void scope_pop_scope(Binder binder0);
void scope_declare_type(Scope scope0, DataType dataType0);
DataType scope_lookup_type(Scope scope0, String name0, ObjectList generics0);
void scope_declare_variable(Scope scope0, Variable variable0);
Variable scope_lookup_variable(Scope scope0, String name0);
void scope_declare_function(Scope scope0, BoundFunctionMember function0);
BoundFunctionMember scope_lookup_function(Scope scope0, String name0);

DataType type_init_simple(DataTypeKind kind0, String name0, String cName0)
{
    DataType dataType1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(name0), GC_LOCAL(cName0), GC_LOCAL(dataType1));
    {
        dataType1 = OBJECT_CTOR(DataType_impl, DataType_type);
        (dataType1)->kind = kind0;
        (dataType1)->name = name0;
        (dataType1)->generics = NULL;
        (dataType1)->cName = cName0;
        (dataType1)->definition = NULL;
        GC_FRAME_DESTROY;
        return dataType1;
    }
    GC_FRAME_DESTROY;
}

DataType type_init_complex(DataTypeKind kind0, String name0, String cName0, Object definition0)
{
    DataType dataType1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(name0), GC_LOCAL(cName0), GC_LOCAL(definition0), GC_LOCAL(dataType1));
    {
        dataType1 = OBJECT_CTOR(DataType_impl, DataType_type);
        (dataType1)->kind = kind0;
        (dataType1)->name = name0;
        (dataType1)->generics = NULL;
        (dataType1)->cName = cName0;
        (dataType1)->definition = definition0;
        GC_FRAME_DESTROY;
        return dataType1;
    }
    GC_FRAME_DESTROY;
}

DataType type_init_dynamic(DataTypeKind kind0, String name0, String cName0, ObjectList generics0)
{
    DataType dataType1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(name0), GC_LOCAL(cName0), GC_LOCAL(generics0), GC_LOCAL(dataType1));
    {
        dataType1 = OBJECT_CTOR(DataType_impl, DataType_type);
        (dataType1)->kind = kind0;
        (dataType1)->name = name0;
        (dataType1)->generics = generics0;
        (dataType1)->cName = cName0;
        (dataType1)->definition = NULL;
        GC_FRAME_DESTROY;
        return dataType1;
    }
    GC_FRAME_DESTROY;
}

bool type_eq_type(DataType left0, DataType right0)
{
    i32 i1;
    DataType leftGeneric2 = NULL;
    DataType rightGeneric3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(left0), GC_LOCAL(right0), GC_LOCAL(leftGeneric2), GC_LOCAL(rightGeneric3));
    {
        if (!(string_equals)((left0)->name, (right0)->name))
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        if (((Object)((left0)->generics)) == ((Object)(NULL)) && ((Object)((right0)->generics)) != ((Object)(NULL)) || ((Object)((left0)->generics)) != ((Object)(NULL)) && ((Object)((right0)->generics)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        if (((Object)((left0)->generics)) == ((Object)(NULL)) && ((Object)((right0)->generics)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return 1;
        }
        if (((left0)->generics)->length != ((right0)->generics)->length)
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        i1 = 0;
        while (i1 < ((left0)->generics)->length)
        {
            leftGeneric2 = ((DataType)((list_get_value)((left0)->generics, i1)));
            rightGeneric3 = ((DataType)((list_get_value)((right0)->generics, i1)));
            i1 = i1 + 1;
            if (!(type_eq_type)(leftGeneric2, rightGeneric3))
            {
                GC_FRAME_DESTROY;
                return 0;
            }
        }
        GC_FRAME_DESTROY;
        return 1;
    }
    GC_FRAME_DESTROY;
}

bool type_eq_def(DataType left0, String name0, ObjectList generics0)
{
    i32 i1;
    DataType leftGeneric2 = NULL;
    DataType generic3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(left0), GC_LOCAL(name0), GC_LOCAL(generics0), GC_LOCAL(leftGeneric2), GC_LOCAL(generic3));
    {
        if (!(string_equals)((left0)->name, name0))
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        if (((Object)((left0)->generics)) == ((Object)(NULL)) && ((Object)(generics0)) != ((Object)(NULL)) || ((Object)((left0)->generics)) != ((Object)(NULL)) && ((Object)(generics0)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        if (((Object)((left0)->generics)) == ((Object)(NULL)) && ((Object)(generics0)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return 1;
        }
        if (((left0)->generics)->length != (generics0)->length)
        {
            GC_FRAME_DESTROY;
            return 0;
        }
        i1 = 0;
        while (i1 < (generics0)->length)
        {
            leftGeneric2 = ((DataType)((list_get_value)((left0)->generics, i1)));
            generic3 = ((DataType)((list_get_value)(generics0, i1)));
            i1 = i1 + 1;
            if (!(type_eq_type)(leftGeneric2, generic3))
            {
                GC_FRAME_DESTROY;
                return 0;
            }
        }
        GC_FRAME_DESTROY;
        return 1;
    }
    GC_FRAME_DESTROY;
}

Variable variable_init(BoundFunctionMember function0, VariableKind kind0, String name0, DataType dataType0)
{
    Variable variable1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(function0), GC_LOCAL(name0), GC_LOCAL(dataType0), GC_LOCAL(variable1));
    {
        variable1 = OBJECT_CTOR(Variable_impl, Variable_type);
        (variable1)->kind = kind0;
        (variable1)->name = name0;
        (variable1)->id = ((function0)->variables)->length + 1;
        (variable1)->dataType = dataType0;
        if (((i32)((dataType0)->kind)) == ((i32)(DataTypeKind_OBJECT)))
        {
            (function0)->requiresGC = 1;
        }
        (list_push)((function0)->variables, ((Object)(variable1)));
        GC_FRAME_DESTROY;
        return variable1;
    }
    GC_FRAME_DESTROY;
}

Variable parameter_init(String name0, DataType dataType0)
{
    Variable variable1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(name0), GC_LOCAL(dataType0), GC_LOCAL(variable1));
    {
        variable1 = OBJECT_CTOR(Variable_impl, Variable_type);
        (variable1)->kind = VariableKind_PARAMETER;
        (variable1)->name = name0;
        (variable1)->id = 0;
        (variable1)->dataType = dataType0;
        GC_FRAME_DESTROY;
        return variable1;
    }
    GC_FRAME_DESTROY;
}

BoundUnaryOperator unary_operator_init(TokenKind tokenKind0, DataType operandType0, DataType returnType0)
{
    BoundUnaryOperator operator1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(operandType0), GC_LOCAL(returnType0), GC_LOCAL(operator1));
    {
        operator1 = OBJECT_CTOR(BoundUnaryOperator_impl, BoundUnaryOperator_type);
        (operator1)->tokenKind = tokenKind0;
        (operator1)->right = operandType0;
        (operator1)->returnType = returnType0;
        GC_FRAME_DESTROY;
        return operator1;
    }
    GC_FRAME_DESTROY;
}

BoundBinaryOperator binary_operator_init(TokenKind tokenKind0, DataType leftType0, DataType rightType0, DataType returnType0)
{
    BoundBinaryOperator operator1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(leftType0), GC_LOCAL(rightType0), GC_LOCAL(returnType0), GC_LOCAL(operator1));
    {
        operator1 = OBJECT_CTOR(BoundBinaryOperator_impl, BoundBinaryOperator_type);
        (operator1)->tokenKind = tokenKind0;
        (operator1)->left = leftType0;
        (operator1)->right = rightType0;
        (operator1)->returnType = returnType0;
        GC_FRAME_DESTROY;
        return operator1;
    }
    GC_FRAME_DESTROY;
}

Binder binder_init(ObjectList units0)
{
    Scope scope1 = NULL;
    DataType voidType2 = NULL;
    DataType objectType3 = NULL;
    DataType boolType4 = NULL;
    DataType charType5 = NULL;
    DataType u8Type6 = NULL;
    DataType u16Type7 = NULL;
    DataType u32Type8 = NULL;
    DataType u64Type9 = NULL;
    DataType i8Type10 = NULL;
    DataType i16Type11 = NULL;
    DataType i32Type12 = NULL;
    DataType i64Type13 = NULL;
    ObjectList conversionRules14 = NULL;
    ObjectList unaryOperators15 = NULL;
    ObjectList binaryOperators16 = NULL;
    BinderFlags flags17 = NULL;
    Binder binder18 = NULL;
    GC_FRAME_INIT(19, GC_LOCAL(units0), GC_LOCAL(scope1), GC_LOCAL(voidType2), GC_LOCAL(objectType3), GC_LOCAL(boolType4), GC_LOCAL(charType5), GC_LOCAL(u8Type6), GC_LOCAL(u16Type7), GC_LOCAL(u32Type8), GC_LOCAL(u64Type9), GC_LOCAL(i8Type10), GC_LOCAL(i16Type11), GC_LOCAL(i32Type12), GC_LOCAL(i64Type13), GC_LOCAL(conversionRules14), GC_LOCAL(unaryOperators15), GC_LOCAL(binaryOperators16), GC_LOCAL(flags17), GC_LOCAL(binder18));
    {
        scope1 = (scope_init)(NULL);
        voidType2 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"void", 4), STRING_CTOR(String_impl, String_type, (uchar*)"void", 4));
        objectType3 = (type_init_simple)(DataTypeKind_OBJECT, STRING_CTOR(String_impl, String_type, (uchar*)"Object", 6), STRING_CTOR(String_impl, String_type, (uchar*)"Object", 6));
        boolType4 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"bool", 4), STRING_CTOR(String_impl, String_type, (uchar*)"bool", 4));
        charType5 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"char", 4), STRING_CTOR(String_impl, String_type, (uchar*)"uchar", 5));
        u8Type6 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"u8", 2), STRING_CTOR(String_impl, String_type, (uchar*)"u8", 2));
        u16Type7 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"u16", 3), STRING_CTOR(String_impl, String_type, (uchar*)"u16", 3));
        u32Type8 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"u32", 3), STRING_CTOR(String_impl, String_type, (uchar*)"u32", 3));
        u64Type9 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"u64", 3), STRING_CTOR(String_impl, String_type, (uchar*)"u64", 3));
        i8Type10 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"i8", 2), STRING_CTOR(String_impl, String_type, (uchar*)"i8", 2));
        i16Type11 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"i16", 3), STRING_CTOR(String_impl, String_type, (uchar*)"i16", 3));
        i32Type12 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"i32", 3), STRING_CTOR(String_impl, String_type, (uchar*)"i32", 3));
        i64Type13 = (type_init_simple)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"i64", 3), STRING_CTOR(String_impl, String_type, (uchar*)"i64", 3));
        (scope_declare_type)(scope1, objectType3);
        (scope_declare_type)(scope1, boolType4);
        (scope_declare_type)(scope1, charType5);
        (scope_declare_type)(scope1, u8Type6);
        (scope_declare_type)(scope1, u16Type7);
        (scope_declare_type)(scope1, u32Type8);
        (scope_declare_type)(scope1, u64Type9);
        (scope_declare_type)(scope1, i8Type10);
        (scope_declare_type)(scope1, i16Type11);
        (scope_declare_type)(scope1, i32Type12);
        (scope_declare_type)(scope1, i64Type13);
        conversionRules14 = (conversion_init)(i8Type10, i16Type11, i32Type12, i64Type13, u8Type6, u16Type7, u32Type8, u64Type9, boolType4, charType5);
        unaryOperators15 = (list_init)();
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_PLUS, i8Type10, i8Type10))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_PLUS, i16Type11, i16Type11))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_PLUS, i32Type12, i32Type12))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_PLUS, i64Type13, i64Type13))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_MINUS, i8Type10, i8Type10))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_MINUS, i16Type11, i16Type11))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_MINUS, i32Type12, i32Type12))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_MINUS, i64Type13, i64Type13))));
        (list_push)(unaryOperators15, ((Object)((unary_operator_init)(TokenKind_BANG, boolType4, boolType4))));
        binaryOperators16 = (list_init)();
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_PLUS, i8Type10, i8Type10, i8Type10))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_PLUS, i16Type11, i16Type11, i16Type11))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_PLUS, i32Type12, i32Type12, i32Type12))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_PLUS, i64Type13, i64Type13, i64Type13))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_MINUS, i8Type10, i8Type10, i8Type10))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_MINUS, i16Type11, i16Type11, i16Type11))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_MINUS, i32Type12, i32Type12, i32Type12))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_MINUS, i64Type13, i64Type13, i64Type13))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_STAR, i8Type10, i8Type10, i8Type10))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_STAR, i16Type11, i16Type11, i16Type11))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_STAR, i32Type12, i32Type12, i32Type12))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_STAR, i64Type13, i64Type13, i64Type13))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_SLASH, i8Type10, i8Type10, i8Type10))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_SLASH, i16Type11, i16Type11, i16Type11))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_SLASH, i32Type12, i32Type12, i32Type12))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_SLASH, i64Type13, i64Type13, i64Type13))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, boolType4, boolType4, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, charType5, charType5, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, objectType3, objectType3, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_EQUALS_EQUALS, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, boolType4, boolType4, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, charType5, charType5, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, objectType3, objectType3, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_BANG_EQUALS, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE_EQUALS, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE_EQUALS, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE_EQUALS, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_LANGLE_EQUALS, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE_EQUALS, i8Type10, i8Type10, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE_EQUALS, i16Type11, i16Type11, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE_EQUALS, i32Type12, i32Type12, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_RANGLE_EQUALS, i64Type13, i64Type13, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_AND_AND, boolType4, boolType4, boolType4))));
        (list_push)(binaryOperators16, ((Object)((binary_operator_init)(TokenKind_OR_OR, boolType4, boolType4, boolType4))));
        flags17 = OBJECT_CTOR(BinderFlags_impl, BinderFlags_type);
        (flags17)->allowEnumIdentifiers = 0;
        (flags17)->allowBreakStatement = 0;
        (flags17)->allowContinueStatement = 0;
        binder18 = OBJECT_CTOR(Binder_impl, Binder_type);
        (binder18)->units = units0;
        (binder18)->trackedTypes = (list_init)();
        (binder18)->rootScope = scope1;
        (binder18)->currentScope = scope1;
        (binder18)->currentFunction = NULL;
        (binder18)->conversionRules = conversionRules14;
        (binder18)->voidType = voidType2;
        (binder18)->objectType = objectType3;
        (binder18)->boolType = boolType4;
        (binder18)->charType = charType5;
        (binder18)->u8Type = u8Type6;
        (binder18)->u16Type = u16Type7;
        (binder18)->u32Type = u32Type8;
        (binder18)->u64Type = u64Type9;
        (binder18)->i8Type = i8Type10;
        (binder18)->i16Type = i16Type11;
        (binder18)->i32Type = i32Type12;
        (binder18)->i64Type = i64Type13;
        (binder18)->unaryOperators = unaryOperators15;
        (binder18)->binaryOperators = binaryOperators16;
        (binder18)->flags = flags17;
        GC_FRAME_DESTROY;
        return binder18;
    }
    GC_FRAME_DESTROY;
}

DataType RETURN_TYPE(Object object0)
{
    GC_FRAME_INIT(1, GC_LOCAL(object0));
    {
        GC_FRAME_DESTROY;
        return ((((BoundUnkownExpression)(object0))))->returnType;
    }
    GC_FRAME_DESTROY;
}

void SET_RETURN_TYPE(Object object0, DataType dataType0)
{
    GC_FRAME_INIT(2, GC_LOCAL(object0), GC_LOCAL(dataType0));
    {
        ((((BoundUnkownExpression)(object0))))->returnType = dataType0;
    }
    GC_FRAME_DESTROY;
}

String generate_func_cName(ObjectList generics0)
{
    String cName1 = NULL;
    ObjectListIterator iter2 = NULL;
    DataType generic3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(generics0), GC_LOCAL(cName1), GC_LOCAL(iter2), GC_LOCAL(generic3));
    {
        cName1 = STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4);
        iter2 = (list_iterator)(generics0);
        while ((list_iterator_has_next)(iter2))
        {
            generic3 = ((DataType)((list_iterator_next)(iter2)));
            cName1 = (string_concat)(cName1, STRING_CTOR(String_impl, String_type, (uchar*)"_", 1));
            cName1 = (string_concat)(cName1, (generic3)->cName);
        }
        GC_FRAME_DESTROY;
        return cName1;
    }
    GC_FRAME_DESTROY;
}

DataType bind_type_signature_dynamic_func(Binder binder0, TypeSignatureDynamic dynamic0)
{
    ObjectList generics1 = NULL;
    i32 i2;
    TypeSignatureDynamicGeneric generic3 = NULL;
    DataType dataType4 = NULL;
    String cName5 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(binder0), GC_LOCAL(dynamic0), GC_LOCAL(generics1), GC_LOCAL(generic3), GC_LOCAL(dataType4), GC_LOCAL(cName5));
    {
        if (((dynamic0)->generics)->length < 1)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Function type signature must have at least one generic type", 59));
        }
        generics1 = (list_init)();
        i2 = 0;
        while (i2 < ((dynamic0)->generics)->length)
        {
            generic3 = ((TypeSignatureDynamicGeneric)((list_get_value)((dynamic0)->generics, i2)));
            (list_push)(generics1, ((Object)((bind_type_signature)(binder0, (generic3)->typeSignature, i2 == 0))));
        }
        dataType4 = (scope_lookup_type)((binder0)->currentScope, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4), generics1);
        if (((Object)(dataType4)) == ((Object)(NULL)))
        {
            cName5 = (generate_func_cName)(generics1);
            dataType4 = (type_init_dynamic)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4), cName5, generics1);
            (list_push)((binder0)->trackedTypes, ((Object)(dataType4)));
            (scope_declare_type)((binder0)->rootScope, dataType4);
        }
        GC_FRAME_DESTROY;
        return dataType4;
    }
    GC_FRAME_DESTROY;
}

DataType bind_type_signature_dynamic_span(Binder binder0, TypeSignatureDynamic dynamic0)
{
    DataType generic1 = NULL;
    ObjectList generics2 = NULL;
    DataType dataType3 = NULL;
    String cName4 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(binder0), GC_LOCAL(dynamic0), GC_LOCAL(generic1), GC_LOCAL(generics2), GC_LOCAL(dataType3), GC_LOCAL(cName4));
    {
        if (((dynamic0)->generics)->length != 1)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Span type signature must have one generic type", 46));
        }
        generic1 = (bind_type_signature)(binder0, ((((TypeSignatureDynamicGeneric)((list_get_value)((dynamic0)->generics, 0)))))->typeSignature, 0);
        generics2 = (list_init)();
        (list_push)(generics2, ((Object)(generic1)));
        dataType3 = (scope_lookup_type)((binder0)->currentScope, STRING_CTOR(String_impl, String_type, (uchar*)"Span", 4), generics2);
        if (((Object)(dataType3)) == ((Object)(NULL)))
        {
            cName4 = (string_concat)(STRING_CTOR(String_impl, String_type, (uchar*)"Span_", 5), (generic1)->cName);
            dataType3 = (type_init_dynamic)(DataTypeKind_OBJECT, STRING_CTOR(String_impl, String_type, (uchar*)"Span", 4), cName4, generics2);
            (scope_declare_type)((binder0)->rootScope, dataType3);
        }
        GC_FRAME_DESTROY;
        return dataType3;
    }
    GC_FRAME_DESTROY;
}

DataType bind_type_signature_dynamic(Binder binder0, TypeSignature signature0, TypeSignatureDynamic dynamic0)
{
    String keyword1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(signature0), GC_LOCAL(dynamic0), GC_LOCAL(keyword1));
    {
        keyword1 = ((signature0)->identifier)->value;
        if ((string_equals)(keyword1, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4)))
        {
            GC_FRAME_DESTROY;
            return (bind_type_signature_dynamic_func)(binder0, dynamic0);
        }
        if ((string_equals)(keyword1, STRING_CTOR(String_impl, String_type, (uchar*)"Span", 4)))
        {
            GC_FRAME_DESTROY;
            return (bind_type_signature_dynamic_span)(binder0, dynamic0);
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unknown dynamic type signature", 30));
    }
    GC_FRAME_DESTROY;
}

DataType bind_type_signature(Binder binder0, TypeSignature signature0, bool allowVoid0)
{
    DataType dataType1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(binder0), GC_LOCAL(signature0), GC_LOCAL(dataType1));
    {
        if (((Object)((signature0)->dynamic)) != ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return (bind_type_signature_dynamic)(binder0, signature0, (signature0)->dynamic);
        }
        if ((string_equals)(((signature0)->identifier)->value, STRING_CTOR(String_impl, String_type, (uchar*)"void", 4)) && allowVoid0)
        {
            GC_FRAME_DESTROY;
            return (binder0)->voidType;
        }
        dataType1 = (scope_lookup_type)((binder0)->currentScope, ((signature0)->identifier)->value, NULL);
        if (((Object)(dataType1)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unkown type", 11));
        }
        GC_FRAME_DESTROY;
        return dataType1;
    }
    GC_FRAME_DESTROY;
}

DataType bind_type_clause(Binder binder0, TypeClause typeClause0, bool allowVoid0)
{
    GC_FRAME_INIT(2, GC_LOCAL(binder0), GC_LOCAL(typeClause0));
    {
        GC_FRAME_DESTROY;
        return (bind_type_signature)(binder0, (typeClause0)->typeSignature, allowVoid0);
    }
    GC_FRAME_DESTROY;
}

BoundCtorExpression bind_ctor_expression(Binder binder0, CtorExpression ctorExpression0)
{
    DataType dataType1 = NULL;
    BoundCtorExpression node2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(ctorExpression0), GC_LOCAL(dataType1), GC_LOCAL(node2));
    {
        dataType1 = (bind_type_signature)(binder0, (ctorExpression0)->typeSignature, 0);
        if (((i32)((dataType1)->kind)) != ((i32)(DataTypeKind_OBJECT)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Can only use with objects", 25));
        }
        node2 = OBJECT_CTOR(BoundCtorExpression_impl, BoundCtorExpression_type);
        (node2)->returnType = dataType1;
        GC_FRAME_DESTROY;
        return node2;
    }
    GC_FRAME_DESTROY;
}

bool is_node_assignable(Object node0)
{
    ParenExpression parenExpression1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(node0), GC_LOCAL(parenExpression1));
    {
        if (OBJECT_TYPEOF(node0) == &ParenExpression_type)
        {
            parenExpression1 = ((ParenExpression)(node0));
            GC_FRAME_DESTROY;
            return (is_node_assignable)((parenExpression1)->expression);
        }
        GC_FRAME_DESTROY;
        return OBJECT_TYPEOF(node0) == &BoundVariableExpression_type || OBJECT_TYPEOF(node0) == &BoundMemberExpression_type;
    }
    GC_FRAME_DESTROY;
}

BoundAssignmentExpression bind_assignment_expression(Binder binder0, AssignmentExpression assignmentExpression0)
{
    Object left1 = NULL;
    Object right2 = NULL;
    BoundAssignmentExpression node3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(assignmentExpression0), GC_LOCAL(left1), GC_LOCAL(right2), GC_LOCAL(node3));
    {
        left1 = (bind_expression)(binder0, (assignmentExpression0)->left, NULL);
        if (!(is_node_assignable)(left1))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Expression is not assignable", 28));
        }
        right2 = (bind_expression)(binder0, (assignmentExpression0)->right, (RETURN_TYPE)(left1));
        node3 = OBJECT_CTOR(BoundAssignmentExpression_impl, BoundAssignmentExpression_type);
        (node3)->returnType = (RETURN_TYPE)(right2);
        (node3)->left = left1;
        (node3)->right = right2;
        GC_FRAME_DESTROY;
        return node3;
    }
    GC_FRAME_DESTROY;
}

BoundUnaryOperator lookup_unary_operator(Binder binder0, TokenKind tokenKind0, DataType operandType0)
{
    ObjectListIterator iter1 = NULL;
    BoundUnaryOperator operator2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(operandType0), GC_LOCAL(iter1), GC_LOCAL(operator2));
    {
        iter1 = (list_iterator)((binder0)->unaryOperators);
        while ((list_iterator_has_next)(iter1))
        {
            operator2 = ((BoundUnaryOperator)((list_iterator_next)(iter1)));
            if (((i32)((operator2)->tokenKind)) == ((i32)(tokenKind0)) && (type_eq_type)((operator2)->right, operandType0))
            {
                GC_FRAME_DESTROY;
                return operator2;
            }
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

BoundUnaryExpression bind_unary_expression(Binder binder0, UnaryExpression unaryExpression0)
{
    Object right1 = NULL;
    BoundUnaryOperator operator2 = NULL;
    BoundUnaryExpression node3 = NULL;
    ObjectListIterator iter4 = NULL;
    BoundUnaryOperator operator5 = NULL;
    ObjectList rightConversion6 = NULL;
    BoundUnaryExpression node7 = NULL;
    GC_FRAME_INIT(9, GC_LOCAL(binder0), GC_LOCAL(unaryExpression0), GC_LOCAL(right1), GC_LOCAL(operator2), GC_LOCAL(node3), GC_LOCAL(iter4), GC_LOCAL(operator5), GC_LOCAL(rightConversion6), GC_LOCAL(node7));
    {
        right1 = (bind_expression)(binder0, (unaryExpression0)->right, NULL);
        operator2 = (lookup_unary_operator)(binder0, ((unaryExpression0)->operator)->kind, (RETURN_TYPE)(right1));
        if (((Object)(operator2)) != ((Object)(NULL)))
        {
            node3 = OBJECT_CTOR(BoundUnaryExpression_impl, BoundUnaryExpression_type);
            (node3)->returnType = (operator2)->returnType;
            (node3)->operator = operator2;
            (node3)->right = right1;
            GC_FRAME_DESTROY;
            return node3;
        }
        iter4 = (list_iterator)((binder0)->unaryOperators);
        while ((list_iterator_has_next)(iter4))
        {
            operator5 = ((BoundUnaryOperator)((list_iterator_next)(iter4)));
            rightConversion6 = (conversion_classify)(binder0, (RETURN_TYPE)(right1), (operator5)->right, 0);
            if (((Object)(rightConversion6)) != ((Object)(NULL)))
            {
                right1 = (bind_conversion)(right1, rightConversion6);
                node7 = OBJECT_CTOR(BoundUnaryExpression_impl, BoundUnaryExpression_type);
                (node7)->returnType = (operator5)->returnType;
                (node7)->operator = operator5;
                (node7)->right = right1;
                GC_FRAME_DESTROY;
                return node7;
            }
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unary operator is not defined for this type", 43));
    }
    GC_FRAME_DESTROY;
}

BoundBinaryOperator lookup_binary_operator(Binder binder0, TokenKind tokenKind0, DataType leftType0, DataType rightType0)
{
    ObjectListIterator iter1 = NULL;
    BoundBinaryOperator operator2 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(leftType0), GC_LOCAL(rightType0), GC_LOCAL(iter1), GC_LOCAL(operator2));
    {
        iter1 = (list_iterator)((binder0)->binaryOperators);
        while ((list_iterator_has_next)(iter1))
        {
            operator2 = ((BoundBinaryOperator)((list_iterator_next)(iter1)));
            if (((i32)((operator2)->tokenKind)) == ((i32)(tokenKind0)) && (type_eq_type)((operator2)->left, leftType0) && (type_eq_type)((operator2)->right, rightType0))
            {
                GC_FRAME_DESTROY;
                return operator2;
            }
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

BoundBinaryExpression bind_binary_expression(Binder binder0, BinaryExpression binaryExpression0)
{
    Object left1 = NULL;
    Object right2 = NULL;
    BoundBinaryOperator operator3 = NULL;
    BoundBinaryExpression node4 = NULL;
    ObjectListIterator iter5 = NULL;
    BoundBinaryOperator operator6 = NULL;
    ObjectList leftConversion7 = NULL;
    ObjectList rightConversion8 = NULL;
    BoundBinaryExpression node9 = NULL;
    GC_FRAME_INIT(11, GC_LOCAL(binder0), GC_LOCAL(binaryExpression0), GC_LOCAL(left1), GC_LOCAL(right2), GC_LOCAL(operator3), GC_LOCAL(node4), GC_LOCAL(iter5), GC_LOCAL(operator6), GC_LOCAL(leftConversion7), GC_LOCAL(rightConversion8), GC_LOCAL(node9));
    {
        left1 = (bind_expression)(binder0, (binaryExpression0)->left, NULL);
        right2 = (bind_expression)(binder0, (binaryExpression0)->right, NULL);
        if (((i32)(((binaryExpression0)->operator)->kind)) == ((i32)(TokenKind_EQUALS_EQUALS)) || ((i32)(((binaryExpression0)->operator)->kind)) == ((i32)(TokenKind_BANG_EQUALS)))
        {
            if (OBJECT_TYPEOF(left1) == &BoundNullExpression_type && OBJECT_TYPEOF(right2) == &BoundNullExpression_type)
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot compare null with null", 29));
            }
            if (OBJECT_TYPEOF(left1) == &BoundNullExpression_type && !(OBJECT_TYPEOF(right2) == &BoundNullExpression_type))
            {
                left1 = (bind_expression)(binder0, (binaryExpression0)->left, (RETURN_TYPE)(right2));
            }
            else
            if (OBJECT_TYPEOF(right2) == &BoundNullExpression_type && !(OBJECT_TYPEOF(left1) == &BoundNullExpression_type))
            {
                right2 = (bind_expression)(binder0, (binaryExpression0)->right, (RETURN_TYPE)(right2));
            }
        }
        operator3 = (lookup_binary_operator)(binder0, ((binaryExpression0)->operator)->kind, (RETURN_TYPE)(left1), (RETURN_TYPE)(right2));
        if (((Object)(operator3)) != ((Object)(NULL)))
        {
            node4 = OBJECT_CTOR(BoundBinaryExpression_impl, BoundBinaryExpression_type);
            (node4)->returnType = (operator3)->returnType;
            (node4)->left = left1;
            (node4)->operator = operator3;
            (node4)->right = right2;
            GC_FRAME_DESTROY;
            return node4;
        }
        iter5 = (list_iterator)((binder0)->binaryOperators);
        while ((list_iterator_has_next)(iter5))
        {
            operator6 = ((BoundBinaryOperator)((list_iterator_next)(iter5)));
            if (((i32)((operator6)->tokenKind)) != ((i32)(((binaryExpression0)->operator)->kind)))
            {
                continue;
            }
            leftConversion7 = (conversion_classify)(binder0, (RETURN_TYPE)(left1), (operator6)->left, 0);
            rightConversion8 = (conversion_classify)(binder0, (RETURN_TYPE)(right2), (operator6)->right, 0);
            if (((Object)(leftConversion7)) != ((Object)(NULL)) && ((Object)(rightConversion8)) != ((Object)(NULL)))
            {
                left1 = (bind_conversion)(left1, leftConversion7);
                right2 = (bind_conversion)(right2, leftConversion7);
                node9 = OBJECT_CTOR(BoundBinaryExpression_impl, BoundBinaryExpression_type);
                (node9)->returnType = (operator6)->returnType;
                (node9)->left = left1;
                (node9)->operator = operator6;
                (node9)->right = right2;
                GC_FRAME_DESTROY;
                return node9;
            }
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Binary operator is not defined for those types", 46));
    }
    GC_FRAME_DESTROY;
}

BoundCallExpression bind_call_expression(Binder binder0, CallExpression callExpression0)
{
    Object callee1 = NULL;
    DataType calleeReturnType2 = NULL;
    ObjectList arguments3 = NULL;
    i32 i4;
    DataType expectedType5 = NULL;
    Object argument6 = NULL;
    BoundCallExpression node7 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(binder0), GC_LOCAL(callExpression0), GC_LOCAL(callee1), GC_LOCAL(calleeReturnType2), GC_LOCAL(arguments3), GC_LOCAL(expectedType5), GC_LOCAL(argument6), GC_LOCAL(node7));
    {
        callee1 = (bind_expression)(binder0, (callExpression0)->callee, NULL);
        calleeReturnType2 = (RETURN_TYPE)(callee1);
        if (!(string_equals)((calleeReturnType2)->name, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Expression is not callable", 26));
        }
        if (((Object)((calleeReturnType2)->generics)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Function requires generics", 26));
        }
        if (((calleeReturnType2)->generics)->length - 1 != ((callExpression0)->arguments)->length)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Function argument count missmatch", 33));
        }
        arguments3 = (list_init)();
        i4 = 0;
        while (i4 < ((callExpression0)->arguments)->length)
        {
            expectedType5 = ((DataType)((list_get_value)((calleeReturnType2)->generics, i4 + 1)));
            argument6 = (bind_expression)(binder0, ((((CallExpressionArgument)((list_get_value)((callExpression0)->arguments, i4)))))->expression, expectedType5);
            i4 = i4 + 1;
            (list_push)(arguments3, argument6);
        }
        node7 = OBJECT_CTOR(BoundCallExpression_impl, BoundCallExpression_type);
        (node7)->returnType = ((DataType)((list_get_value)((calleeReturnType2)->generics, 0)));
        (node7)->arguments = arguments3;
        (node7)->callee = callee1;
        GC_FRAME_DESTROY;
        return node7;
    }
    GC_FRAME_DESTROY;
}

Object bind_member_expression(Binder binder0, MemberExpression memberExpression0)
{
    bool oldEnumIdentifier1;
    Object object2 = NULL;
    DataType objectReturnType3 = NULL;
    String identifier4 = NULL;
    BoundTypeMember definition5 = NULL;
    ObjectListIterator iter6 = NULL;
    BoundTypeMemberItem item7 = NULL;
    BoundMemberExpression node8 = NULL;
    BoundEnumMember definition9 = NULL;
    ObjectListIterator iter10 = NULL;
    BoundEnumMemberItem item11 = NULL;
    BoundEnumFieldExpression node12 = NULL;
    GC_FRAME_INIT(13, GC_LOCAL(binder0), GC_LOCAL(memberExpression0), GC_LOCAL(object2), GC_LOCAL(objectReturnType3), GC_LOCAL(identifier4), GC_LOCAL(definition5), GC_LOCAL(iter6), GC_LOCAL(item7), GC_LOCAL(node8), GC_LOCAL(definition9), GC_LOCAL(iter10), GC_LOCAL(item11), GC_LOCAL(node12));
    {
        oldEnumIdentifier1 = ((binder0)->flags)->allowEnumIdentifiers;
        ((binder0)->flags)->allowEnumIdentifiers = 1;
        object2 = (bind_expression)(binder0, (memberExpression0)->object, NULL);
        ((binder0)->flags)->allowEnumIdentifiers = oldEnumIdentifier1;
        objectReturnType3 = (RETURN_TYPE)(object2);
        if ((objectReturnType3)->definition == NULL)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot access this expression", 29));
        }
        identifier4 = ((memberExpression0)->identifier)->value;
        if (OBJECT_TYPEOF((objectReturnType3)->definition) == &BoundTypeMember_type)
        {
            definition5 = ((BoundTypeMember)((objectReturnType3)->definition));
            iter6 = (list_iterator)((definition5)->items);
            while ((list_iterator_has_next)(iter6))
            {
                item7 = ((BoundTypeMemberItem)((list_iterator_next)(iter6)));
                if ((string_equals)((item7)->name, identifier4))
                {
                    node8 = OBJECT_CTOR(BoundMemberExpression_impl, BoundMemberExpression_type);
                    (node8)->returnType = (item7)->dataType;
                    (node8)->object = object2;
                    (node8)->identifier = identifier4;
                    GC_FRAME_DESTROY;
                    return ((Object)(node8));
                }
            }
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Item not found in Type", 22));
        }
        if (OBJECT_TYPEOF((objectReturnType3)->definition) == &BoundEnumMember_type)
        {
            definition9 = ((BoundEnumMember)((objectReturnType3)->definition));
            iter10 = (list_iterator)((definition9)->items);
            while ((list_iterator_has_next)(iter10))
            {
                item11 = ((BoundEnumMemberItem)((list_iterator_next)(iter10)));
                if ((string_equals)((item11)->name, identifier4))
                {
                    node12 = OBJECT_CTOR(BoundEnumFieldExpression_impl, BoundEnumFieldExpression_type);
                    (node12)->returnType = objectReturnType3;
                    (node12)->name = (objectReturnType3)->name;
                    (node12)->item = (item11)->name;
                    GC_FRAME_DESTROY;
                    return ((Object)(node12));
                }
            }
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Item not found in Enum", 22));
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot access this expression", 29));
    }
    GC_FRAME_DESTROY;
}

BoundIsExpression bind_is_expression(Binder binder0, IsExpression isExpression0)
{
    Object left1 = NULL;
    DataType targetType2 = NULL;
    BoundIsExpression node3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(isExpression0), GC_LOCAL(left1), GC_LOCAL(targetType2), GC_LOCAL(node3));
    {
        left1 = (bind_expression)(binder0, (isExpression0)->left, NULL);
        if (((i32)(((RETURN_TYPE)(left1))->kind)) != ((i32)(DataTypeKind_OBJECT)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot use 'is' with non-object type", 36));
        }
        targetType2 = (bind_type_signature)(binder0, (isExpression0)->typeSignature, 0);
        if (((i32)((targetType2)->kind)) != ((i32)(DataTypeKind_OBJECT)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Target type in 'is' must be an object type", 42));
        }
        node3 = OBJECT_CTOR(BoundIsExpression_impl, BoundIsExpression_type);
        (node3)->returnType = (binder0)->boolType;
        (node3)->left = left1;
        (node3)->targetType = targetType2;
        GC_FRAME_DESTROY;
        return node3;
    }
    GC_FRAME_DESTROY;
}

Object bind_literal_expression(Binder binder0, LiteralExpression literalExpression0)
{
    BoundIntegerExpression node1 = NULL;
    BoundCharExpression node2 = NULL;
    DataType stringType3 = NULL;
    BoundStringExpression node4 = NULL;
    BoundBooleanExpression node5 = NULL;
    BoundNullExpression node6 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(binder0), GC_LOCAL(literalExpression0), GC_LOCAL(node1), GC_LOCAL(node2), GC_LOCAL(stringType3), GC_LOCAL(node4), GC_LOCAL(node5), GC_LOCAL(node6));
    {
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_INTEGER_LITERAL)))
        {
            node1 = OBJECT_CTOR(BoundIntegerExpression_impl, BoundIntegerExpression_type);
            (node1)->returnType = (binder0)->i32Type;
            (node1)->value = ((literalExpression0)->value)->value;
            GC_FRAME_DESTROY;
            return ((Object)(node1));
        }
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_CHAR_LITERAL)))
        {
            node2 = OBJECT_CTOR(BoundCharExpression_impl, BoundCharExpression_type);
            (node2)->returnType = (binder0)->charType;
            (node2)->value = ((literalExpression0)->value)->value;
            GC_FRAME_DESTROY;
            return ((Object)(node2));
        }
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_STRING_LITERAL)))
        {
            stringType3 = (scope_lookup_type)((binder0)->currentScope, STRING_CTOR(String_impl, String_type, (uchar*)"String", 6), NULL);
            if (((Object)(stringType3)) == ((Object)(NULL)))
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot find string type", 23));
            }
            node4 = OBJECT_CTOR(BoundStringExpression_impl, BoundStringExpression_type);
            (node4)->returnType = stringType3;
            (node4)->value = ((literalExpression0)->value)->value;
            GC_FRAME_DESTROY;
            return ((Object)(node4));
        }
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_TRUE_KEYWORD)) || ((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_FALSE_KEYWORD)))
        {
            node5 = OBJECT_CTOR(BoundBooleanExpression_impl, BoundBooleanExpression_type);
            (node5)->returnType = (binder0)->boolType;
            (node5)->value = ((literalExpression0)->value)->kind;
            GC_FRAME_DESTROY;
            return ((Object)(node5));
        }
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_IDENTIFIER)))
        {
            GC_FRAME_DESTROY;
            return (bind_identifier_expression)(binder0, literalExpression0);
        }
        if (((i32)(((literalExpression0)->value)->kind)) == ((i32)(TokenKind_NULL_KEYWORD)))
        {
            node6 = OBJECT_CTOR(BoundNullExpression_impl, BoundNullExpression_type);
            (node6)->returnType = (binder0)->objectType;
            GC_FRAME_DESTROY;
            return ((Object)(node6));
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unknown literal expression type", 31));
    }
    GC_FRAME_DESTROY;
}

Object bind_identifier_expression(Binder binder0, LiteralExpression literalExpression0)
{
    Variable variable1 = NULL;
    BoundVariableExpression node2 = NULL;
    BoundFunctionMember function3 = NULL;
    BoundFunctionExpression node4 = NULL;
    DataType dataType5 = NULL;
    BoundEnumExpression node6 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(binder0), GC_LOCAL(literalExpression0), GC_LOCAL(variable1), GC_LOCAL(node2), GC_LOCAL(function3), GC_LOCAL(node4), GC_LOCAL(dataType5), GC_LOCAL(node6));
    {
        {
            variable1 = (scope_lookup_variable)((binder0)->currentScope, ((literalExpression0)->value)->value);
            if (((Object)(variable1)) != ((Object)(NULL)))
            {
                node2 = OBJECT_CTOR(BoundVariableExpression_impl, BoundVariableExpression_type);
                (node2)->returnType = (variable1)->dataType;
                (node2)->variable = variable1;
                GC_FRAME_DESTROY;
                return ((Object)(node2));
            }
        }
        {
            function3 = (scope_lookup_function)((binder0)->currentScope, ((literalExpression0)->value)->value);
            if (((Object)(function3)) != ((Object)(NULL)))
            {
                node4 = OBJECT_CTOR(BoundFunctionExpression_impl, BoundFunctionExpression_type);
                (node4)->returnType = (function3)->functionSignature;
                (node4)->function = function3;
                GC_FRAME_DESTROY;
                return ((Object)(node4));
            }
        }
        if (((binder0)->flags)->allowEnumIdentifiers)
        {
            dataType5 = (scope_lookup_type)((binder0)->currentScope, ((literalExpression0)->value)->value, NULL);
            if (((Object)(dataType5)) != ((Object)(NULL)) && (dataType5)->definition != NULL && OBJECT_TYPEOF((dataType5)->definition) == &BoundEnumMember_type)
            {
                node6 = OBJECT_CTOR(BoundEnumExpression_impl, BoundEnumExpression_type);
                (node6)->returnType = dataType5;
                (node6)->enumMember = ((BoundEnumMember)((dataType5)->definition));
                GC_FRAME_DESTROY;
                return ((Object)(node6));
            }
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Symbol not found", 16));
    }
    GC_FRAME_DESTROY;
}

BoundParenExpression bind_paren_expression(Binder binder0, ParenExpression parenExpression0)
{
    Object expression1 = NULL;
    BoundParenExpression node2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(parenExpression0), GC_LOCAL(expression1), GC_LOCAL(node2));
    {
        expression1 = (bind_expression)(binder0, (parenExpression0)->expression, NULL);
        node2 = OBJECT_CTOR(BoundParenExpression_impl, BoundParenExpression_type);
        (node2)->expression = expression1;
        (node2)->returnType = (RETURN_TYPE)(expression1);
        GC_FRAME_DESTROY;
        return node2;
    }
    GC_FRAME_DESTROY;
}

Object bind_cast_expression(Binder binder0, CastExpression castExpression0)
{
    DataType targetType1 = NULL;
    Object expression2 = NULL;
    ObjectList conversions3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(castExpression0), GC_LOCAL(targetType1), GC_LOCAL(expression2), GC_LOCAL(conversions3));
    {
        targetType1 = (bind_type_signature)(binder0, (castExpression0)->typeSignature, 0);
        expression2 = (bind_expression)(binder0, (castExpression0)->expression, NULL);
        conversions3 = (conversion_classify)(binder0, (RETURN_TYPE)(expression2), targetType1, 1);
        if (((Object)(conversions3)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Expression is not castable", 26));
        }
        GC_FRAME_DESTROY;
        return (bind_conversion)(expression2, conversions3);
    }
    GC_FRAME_DESTROY;
}

Object bind_conversion(Object boundExpression0, ObjectList conversions0)
{
    Object innerExpression1 = NULL;
    ObjectListIterator iter2 = NULL;
    ConversionRule conversion3 = NULL;
    BoundCastExpression node4 = NULL;
    BoundParenExpression node5 = NULL;
    GC_FRAME_INIT(7, GC_LOCAL(boundExpression0), GC_LOCAL(conversions0), GC_LOCAL(innerExpression1), GC_LOCAL(iter2), GC_LOCAL(conversion3), GC_LOCAL(node4), GC_LOCAL(node5));
    {
        innerExpression1 = boundExpression0;
        iter2 = (list_iterator)(conversions0);
        while ((list_iterator_has_next)(iter2))
        {
            conversion3 = ((ConversionRule)((list_iterator_next)(iter2)));
            node4 = OBJECT_CTOR(BoundCastExpression_impl, BoundCastExpression_type);
            (node4)->returnType = (conversion3)->to;
            (node4)->expression = innerExpression1;
            (node4)->rule = conversion3;
            innerExpression1 = ((Object)(node4));
        }
        node5 = OBJECT_CTOR(BoundParenExpression_impl, BoundParenExpression_type);
        (node5)->expression = innerExpression1;
        (node5)->returnType = (RETURN_TYPE)(innerExpression1);
        GC_FRAME_DESTROY;
        return ((Object)(node5));
    }
    GC_FRAME_DESTROY;
}

Object bind_expression_internal(Binder binder0, Object expression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(binder0), GC_LOCAL(expression0));
    {
        if (OBJECT_TYPEOF(expression0) == &CtorExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_ctor_expression)(binder0, ((CtorExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &AssignmentExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_assignment_expression)(binder0, ((AssignmentExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &UnaryExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_unary_expression)(binder0, ((UnaryExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &BinaryExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_binary_expression)(binder0, ((BinaryExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &CallExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_call_expression)(binder0, ((CallExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &MemberExpression_type)
        {
            GC_FRAME_DESTROY;
            return (bind_member_expression)(binder0, ((MemberExpression)(expression0)));
        }
        if (OBJECT_TYPEOF(expression0) == &IsExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_is_expression)(binder0, ((IsExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &LiteralExpression_type)
        {
            GC_FRAME_DESTROY;
            return (bind_literal_expression)(binder0, ((LiteralExpression)(expression0)));
        }
        if (OBJECT_TYPEOF(expression0) == &ParenExpression_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_paren_expression)(binder0, ((ParenExpression)(expression0)))));
        }
        if (OBJECT_TYPEOF(expression0) == &CastExpression_type)
        {
            GC_FRAME_DESTROY;
            return (bind_cast_expression)(binder0, ((CastExpression)(expression0)));
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"(binder) Unknown expression", 27));
    }
    GC_FRAME_DESTROY;
}

Object bind_expression(Binder binder0, Object expression0, DataType expectedType0)
{
    Object boundExpression1 = NULL;
    ObjectList conversions2 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(expression0), GC_LOCAL(expectedType0), GC_LOCAL(boundExpression1), GC_LOCAL(conversions2));
    {
        boundExpression1 = (bind_expression_internal)(binder0, expression0);
        if (OBJECT_TYPEOF(boundExpression1) == &BoundNullExpression_type)
        {
            if (((Object)(expectedType0)) == ((Object)(NULL)))
            {
                GC_FRAME_DESTROY;
                return boundExpression1;
            }
            if (((i32)((expectedType0)->kind)) != ((i32)(DataTypeKind_OBJECT)))
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"(binder) Cannot assign null to unexpected expression", 52));
            }
            (SET_RETURN_TYPE)(boundExpression1, expectedType0);
        }
        if (((Object)(expectedType0)) != ((Object)(NULL)) && !(type_eq_type)((RETURN_TYPE)(boundExpression1), expectedType0))
        {
            conversions2 = (conversion_classify)(binder0, (RETURN_TYPE)(boundExpression1), expectedType0, 0);
            if (((Object)(conversions2)) == ((Object)(NULL)) || (conversions2)->length == 0)
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Not compatible expression", 25));
            }
            GC_FRAME_DESTROY;
            return (bind_conversion)(boundExpression1, conversions2);
        }
        GC_FRAME_DESTROY;
        return boundExpression1;
    }
    GC_FRAME_DESTROY;
}

BoundBlockStatement bind_block_statement(Binder binder0, BlockStatement blockStatement0)
{
    ObjectList statements1 = NULL;
    ObjectListIterator iter2 = NULL;
    Object statement3 = NULL;
    BoundBlockStatement node4 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(binder0), GC_LOCAL(blockStatement0), GC_LOCAL(statements1), GC_LOCAL(iter2), GC_LOCAL(statement3), GC_LOCAL(node4));
    {
        (scope_push_scope)(binder0);
        statements1 = (list_init)();
        iter2 = (list_iterator)((blockStatement0)->statements);
        while ((list_iterator_has_next)(iter2))
        {
            statement3 = (list_iterator_next)(iter2);
            (list_push)(statements1, (bind_statement)(binder0, statement3));
        }
        (scope_pop_scope)(binder0);
        node4 = OBJECT_CTOR(BoundBlockStatement_impl, BoundBlockStatement_type);
        (node4)->statements = statements1;
        GC_FRAME_DESTROY;
        return node4;
    }
    GC_FRAME_DESTROY;
}

Object bind_variable_statement(Binder binder0, VariableStatement variableStatement0)
{
    DataType dataType1 = NULL;
    Variable variable2 = NULL;
    Object initializer3 = NULL;
    Object right4 = NULL;
    BoundVariableExpression variableExpression5 = NULL;
    BoundAssignmentExpression assignmentExpression6 = NULL;
    BoundExpressionStatement node7 = NULL;
    GC_FRAME_INIT(9, GC_LOCAL(binder0), GC_LOCAL(variableStatement0), GC_LOCAL(dataType1), GC_LOCAL(variable2), GC_LOCAL(initializer3), GC_LOCAL(right4), GC_LOCAL(variableExpression5), GC_LOCAL(assignmentExpression6), GC_LOCAL(node7));
    {
        if (((Object)((binder0)->currentFunction)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Missing current function context", 32));
        }
        dataType1 = (bind_type_clause)(binder0, (variableStatement0)->typeClause, 0);
        variable2 = (variable_init)((binder0)->currentFunction, VariableKind_LOCAL, ((variableStatement0)->identifier)->value, dataType1);
        (scope_declare_variable)((binder0)->currentScope, variable2);
        initializer3 = NULL;
        if ((variableStatement0)->initializer != NULL)
        {
            right4 = (bind_expression)(binder0, (variableStatement0)->initializer, dataType1);
            variableExpression5 = OBJECT_CTOR(BoundVariableExpression_impl, BoundVariableExpression_type);
            (variableExpression5)->returnType = dataType1;
            (variableExpression5)->variable = variable2;
            assignmentExpression6 = OBJECT_CTOR(BoundAssignmentExpression_impl, BoundAssignmentExpression_type);
            (assignmentExpression6)->returnType = dataType1;
            (assignmentExpression6)->left = ((Object)(variableExpression5));
            (assignmentExpression6)->right = right4;
            initializer3 = ((Object)(assignmentExpression6));
        }
        else
        {
            initializer3 = ((Object)(OBJECT_CTOR(BoundEmptyExpression_impl, BoundEmptyExpression_type)));
        }
        node7 = OBJECT_CTOR(BoundExpressionStatement_impl, BoundExpressionStatement_type);
        (node7)->expression = initializer3;
        GC_FRAME_DESTROY;
        return ((Object)(node7));
    }
    GC_FRAME_DESTROY;
}

BoundIfStatement bind_if_statement(Binder binder0, IfStatement ifStatement0)
{
    Object condition1 = NULL;
    Object thenCase2 = NULL;
    Object elseCase3 = NULL;
    BoundIfStatement node4 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(binder0), GC_LOCAL(ifStatement0), GC_LOCAL(condition1), GC_LOCAL(thenCase2), GC_LOCAL(elseCase3), GC_LOCAL(node4));
    {
        condition1 = (bind_expression)(binder0, (ifStatement0)->condition, (binder0)->boolType);
        thenCase2 = (bind_statement)(binder0, (ifStatement0)->thenCase);
        elseCase3 = NULL;
        if (((Object)((ifStatement0)->elseCase)) != ((Object)(NULL)))
        {
            elseCase3 = (bind_statement)(binder0, ((ifStatement0)->elseCase)->thenCase);
        }
        node4 = OBJECT_CTOR(BoundIfStatement_impl, BoundIfStatement_type);
        (node4)->condition = condition1;
        (node4)->thenCase = thenCase2;
        (node4)->elseCase = elseCase3;
        GC_FRAME_DESTROY;
        return node4;
    }
    GC_FRAME_DESTROY;
}

BoundWhileStatement bind_while_statement(Binder binder0, WhileStatement whileStatement0)
{
    Object condition1 = NULL;
    bool oldBreakStatement2;
    bool oldContinueStatement3;
    Object body4 = NULL;
    BoundWhileStatement node5 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(whileStatement0), GC_LOCAL(condition1), GC_LOCAL(body4), GC_LOCAL(node5));
    {
        condition1 = (bind_expression)(binder0, (whileStatement0)->condition, (binder0)->boolType);
        oldBreakStatement2 = ((binder0)->flags)->allowBreakStatement;
        oldContinueStatement3 = ((binder0)->flags)->allowContinueStatement;
        ((binder0)->flags)->allowBreakStatement = 1;
        ((binder0)->flags)->allowContinueStatement = 1;
        body4 = (bind_statement)(binder0, (whileStatement0)->body);
        ((binder0)->flags)->allowBreakStatement = oldBreakStatement2;
        ((binder0)->flags)->allowContinueStatement = oldContinueStatement3;
        node5 = OBJECT_CTOR(BoundWhileStatement_impl, BoundWhileStatement_type);
        (node5)->condition = condition1;
        (node5)->body = body4;
        GC_FRAME_DESTROY;
        return node5;
    }
    GC_FRAME_DESTROY;
}

BoundReturnStatement bind_return_statement(Binder binder0, ReturnStatement returnStatement0)
{
    Object value1 = NULL;
    BoundReturnStatement node2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(returnStatement0), GC_LOCAL(value1), GC_LOCAL(node2));
    {
        if (((Object)((binder0)->currentFunction)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Missing current function context", 32));
        }
        if ((type_eq_type)(((binder0)->currentFunction)->returnType, (binder0)->voidType) && (returnStatement0)->value != NULL)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot return value from void function", 38));
        }
        if (!(type_eq_type)(((binder0)->currentFunction)->returnType, (binder0)->voidType) && (returnStatement0)->value == NULL)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Must return value from non-void function", 40));
        }
        value1 = NULL;
        if ((returnStatement0)->value != NULL)
        {
            value1 = (bind_expression)(binder0, (returnStatement0)->value, ((binder0)->currentFunction)->returnType);
        }
        node2 = OBJECT_CTOR(BoundReturnStatement_impl, BoundReturnStatement_type);
        (node2)->value = value1;
        GC_FRAME_DESTROY;
        return node2;
    }
    GC_FRAME_DESTROY;
}

BoundBreakStatement bind_break_statement(Binder binder0, BreakStatement breakStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(binder0), GC_LOCAL(breakStatement0));
    {
        if (!((binder0)->flags)->allowBreakStatement)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Break statements are not allowed here", 37));
        }
        GC_FRAME_DESTROY;
        return OBJECT_CTOR(BoundBreakStatement_impl, BoundBreakStatement_type);
    }
    GC_FRAME_DESTROY;
}

BoundContinueStatement bind_continue_statement(Binder binder0, ContinueStatement continueStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(binder0), GC_LOCAL(continueStatement0));
    {
        if (!((binder0)->flags)->allowContinueStatement)
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Continue statements are not allowed here", 40));
        }
        GC_FRAME_DESTROY;
        return OBJECT_CTOR(BoundContinueStatement_impl, BoundContinueStatement_type);
    }
    GC_FRAME_DESTROY;
}

BoundExpressionStatement bind_expression_statement(Binder binder0, ExpressionStatement expressionStatement0)
{
    Object expression1 = NULL;
    BoundExpressionStatement node2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(binder0), GC_LOCAL(expressionStatement0), GC_LOCAL(expression1), GC_LOCAL(node2));
    {
        expression1 = (bind_expression)(binder0, (expressionStatement0)->expression, NULL);
        node2 = OBJECT_CTOR(BoundExpressionStatement_impl, BoundExpressionStatement_type);
        (node2)->expression = expression1;
        GC_FRAME_DESTROY;
        return node2;
    }
    GC_FRAME_DESTROY;
}

Object bind_statement(Binder binder0, Object statement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(binder0), GC_LOCAL(statement0));
    {
        if (OBJECT_TYPEOF(statement0) == &BlockStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_block_statement)(binder0, ((BlockStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &VariableStatement_type)
        {
            GC_FRAME_DESTROY;
            return (bind_variable_statement)(binder0, ((VariableStatement)(statement0)));
        }
        if (OBJECT_TYPEOF(statement0) == &IfStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_if_statement)(binder0, ((IfStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &WhileStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_while_statement)(binder0, ((WhileStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &ReturnStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_return_statement)(binder0, ((ReturnStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &BreakStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_break_statement)(binder0, ((BreakStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &ContinueStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_continue_statement)(binder0, ((ContinueStatement)(statement0)))));
        }
        if (OBJECT_TYPEOF(statement0) == &ExpressionStatement_type)
        {
            GC_FRAME_DESTROY;
            return ((Object)((bind_expression_statement)(binder0, ((ExpressionStatement)(statement0)))));
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unknown statement", 17));
    }
    GC_FRAME_DESTROY;
}

BoundEnumMember bind_enum_member(Binder binder0, EnumMember enumMember0)
{
    ObjectList items1 = NULL;
    ObjectListIterator iter2 = NULL;
    EnumMemberItem item3 = NULL;
    BoundEnumMemberItem node4 = NULL;
    BoundEnumMember node5 = NULL;
    DataType dataType6 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(binder0), GC_LOCAL(enumMember0), GC_LOCAL(items1), GC_LOCAL(iter2), GC_LOCAL(item3), GC_LOCAL(node4), GC_LOCAL(node5), GC_LOCAL(dataType6));
    {
        items1 = (list_init)();
        iter2 = (list_iterator)((enumMember0)->items);
        while ((list_iterator_has_next)(iter2))
        {
            item3 = ((EnumMemberItem)((list_iterator_next)(iter2)));
            node4 = OBJECT_CTOR(BoundEnumMemberItem_impl, BoundEnumMemberItem_type);
            (node4)->name = ((item3)->identifier)->value;
            (list_push)(items1, ((Object)(node4)));
        }
        node5 = OBJECT_CTOR(BoundEnumMember_impl, BoundEnumMember_type);
        (node5)->name = ((enumMember0)->identifier)->value;
        (node5)->items = items1;
        dataType6 = (type_init_complex)(DataTypeKind_PRIMITIVE, (node5)->name, (node5)->name, ((Object)(node5)));
        (scope_declare_type)((binder0)->currentScope, dataType6);
        GC_FRAME_DESTROY;
        return node5;
    }
    GC_FRAME_DESTROY;
}

BoundTypeMember bind_extern_type_member(Binder binder0, ExternTypeMember externTypeMember0)
{
    ObjectList items1 = NULL;
    ObjectListIterator iter2 = NULL;
    TypeMemberItem item3 = NULL;
    DataType dataType4 = NULL;
    BoundTypeMemberItem node5 = NULL;
    BoundTypeMemberMeta meta6 = NULL;
    BoundTypeMember node7 = NULL;
    DataType dataType8 = NULL;
    GC_FRAME_INIT(10, GC_LOCAL(binder0), GC_LOCAL(externTypeMember0), GC_LOCAL(items1), GC_LOCAL(iter2), GC_LOCAL(item3), GC_LOCAL(dataType4), GC_LOCAL(node5), GC_LOCAL(meta6), GC_LOCAL(node7), GC_LOCAL(dataType8));
    {
        items1 = (list_init)();
        iter2 = (list_iterator)((externTypeMember0)->items);
        while ((list_iterator_has_next)(iter2))
        {
            item3 = ((TypeMemberItem)((list_iterator_next)(iter2)));
            dataType4 = (bind_type_clause)(binder0, (item3)->typeClause, 0);
            node5 = OBJECT_CTOR(BoundTypeMemberItem_impl, BoundTypeMemberItem_type);
            (node5)->name = ((item3)->identifier)->value;
            (node5)->dataType = dataType4;
            (list_push)(items1, ((Object)(node5)));
        }
        meta6 = OBJECT_CTOR(BoundTypeMemberMeta_impl, BoundTypeMemberMeta_type);
        (meta6)->generateTrace = 0;
        (meta6)->traceName = STRING_CTOR(String_impl, String_type, (uchar*)"ShouldNotAppear", 15);
        node7 = OBJECT_CTOR(BoundTypeMember_impl, BoundTypeMember_type);
        (node7)->name = ((externTypeMember0)->identifier)->value;
        (node7)->items = items1;
        (node7)->meta = meta6;
        dataType8 = (type_init_complex)(DataTypeKind_OBJECT, (node7)->name, (node7)->name, ((Object)(node7)));
        (scope_declare_type)((binder0)->currentScope, dataType8);
        GC_FRAME_DESTROY;
        return node7;
    }
    GC_FRAME_DESTROY;
}

void bind_type_member_signature(Binder binder0, TypeMember typeMember0)
{
    BoundTypeMemberMeta meta1 = NULL;
    BoundTypeMember node2 = NULL;
    DataType dataType3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(typeMember0), GC_LOCAL(meta1), GC_LOCAL(node2), GC_LOCAL(dataType3));
    {
        meta1 = OBJECT_CTOR(BoundTypeMemberMeta_impl, BoundTypeMemberMeta_type);
        (meta1)->generateTrace = 0;
        (meta1)->traceName = STRING_CTOR(String_impl, String_type, (uchar*)"object_empty_trace", 18);
        node2 = OBJECT_CTOR(BoundTypeMember_impl, BoundTypeMember_type);
        (node2)->name = ((typeMember0)->identifier)->value;
        (node2)->items = (list_init)();
        (node2)->meta = meta1;
        dataType3 = (type_init_complex)(DataTypeKind_OBJECT, (node2)->name, (node2)->name, ((Object)(node2)));
        (scope_declare_type)((binder0)->currentScope, dataType3);
    }
    GC_FRAME_DESTROY;
}

BoundTypeMember bind_type_member(Binder binder0, TypeMember typeMember0)
{
    DataType dataType1 = NULL;
    BoundTypeMember definition2 = NULL;
    ObjectListIterator iter3 = NULL;
    TypeMemberItem item4 = NULL;
    DataType dataType5 = NULL;
    BoundTypeMemberItem node6 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(binder0), GC_LOCAL(typeMember0), GC_LOCAL(dataType1), GC_LOCAL(definition2), GC_LOCAL(iter3), GC_LOCAL(item4), GC_LOCAL(dataType5), GC_LOCAL(node6));
    {
        dataType1 = (scope_lookup_type)((binder0)->currentScope, ((typeMember0)->identifier)->value, NULL);
        if ((dataType1)->definition == NULL || !(OBJECT_TYPEOF((dataType1)->definition) == &BoundTypeMember_type))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot find Type", 16));
        }
        definition2 = ((BoundTypeMember)((dataType1)->definition));
        iter3 = (list_iterator)((typeMember0)->items);
        while ((list_iterator_has_next)(iter3))
        {
            item4 = ((TypeMemberItem)((list_iterator_next)(iter3)));
            dataType5 = (bind_type_clause)(binder0, (item4)->typeClause, 0);
            if (((i32)((dataType5)->kind)) == ((i32)(DataTypeKind_OBJECT)))
            {
                ((definition2)->meta)->generateTrace = 1;
                ((definition2)->meta)->traceName = (string_concat)(((typeMember0)->identifier)->value, STRING_CTOR(String_impl, String_type, (uchar*)"_trace", 6));
            }
            node6 = OBJECT_CTOR(BoundTypeMemberItem_impl, BoundTypeMemberItem_type);
            (node6)->name = ((item4)->identifier)->value;
            (node6)->dataType = dataType5;
            (list_push)((definition2)->items, ((Object)(node6)));
        }
        GC_FRAME_DESTROY;
        return definition2;
    }
    GC_FRAME_DESTROY;
}

BoundFunctionMember bind_extern_function_member(Binder binder0, ExternFunctionMember externFunctionMember0)
{
    ObjectList generics1 = NULL;
    DataType returnType2 = NULL;
    bool requiresGC3;
    ObjectList parameters4 = NULL;
    ObjectListIterator iter5 = NULL;
    FunctionMemberParameter parameter6 = NULL;
    DataType dataType7 = NULL;
    Variable variable8 = NULL;
    String cName9 = NULL;
    DataType functionSignature10 = NULL;
    BoundFunctionMember node11 = NULL;
    GC_FRAME_INIT(12, GC_LOCAL(binder0), GC_LOCAL(externFunctionMember0), GC_LOCAL(generics1), GC_LOCAL(returnType2), GC_LOCAL(parameters4), GC_LOCAL(iter5), GC_LOCAL(parameter6), GC_LOCAL(dataType7), GC_LOCAL(variable8), GC_LOCAL(cName9), GC_LOCAL(functionSignature10), GC_LOCAL(node11));
    {
        generics1 = (list_init)();
        returnType2 = (bind_type_clause)(binder0, (externFunctionMember0)->returnType, 1);
        (list_push)(generics1, ((Object)(returnType2)));
        (scope_push_scope)(binder0);
        requiresGC3 = 0;
        parameters4 = (list_init)();
        iter5 = (list_iterator)((externFunctionMember0)->parameters);
        while ((list_iterator_has_next)(iter5))
        {
            parameter6 = ((FunctionMemberParameter)((list_iterator_next)(iter5)));
            dataType7 = (bind_type_clause)(binder0, (parameter6)->typeClause, 0);
            variable8 = (parameter_init)(((parameter6)->identifier)->value, dataType7);
            if (((i32)(((variable8)->dataType)->kind)) == ((i32)(DataTypeKind_OBJECT)))
            {
                requiresGC3 = 1;
            }
            (list_push)(parameters4, ((Object)(variable8)));
            (list_push)(generics1, ((Object)(dataType7)));
            (scope_declare_variable)((binder0)->currentScope, variable8);
        }
        cName9 = (generate_func_cName)(generics1);
        functionSignature10 = (type_init_dynamic)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4), cName9, generics1);
        node11 = OBJECT_CTOR(BoundFunctionMember_impl, BoundFunctionMember_type);
        (node11)->name = ((externFunctionMember0)->identifier)->value;
        (node11)->returnType = returnType2;
        (node11)->requiresGC = requiresGC3;
        (node11)->parameters = parameters4;
        (node11)->variables = (list_init)();
        (node11)->body = NULL;
        (node11)->functionSignature = functionSignature10;
        (scope_pop_scope)(binder0);
        (scope_declare_function)((binder0)->rootScope, node11);
        GC_FRAME_DESTROY;
        return node11;
    }
    GC_FRAME_DESTROY;
}

void bind_function_member_signature(Binder binder0, FunctionMember functionMember0)
{
    ObjectList generics1 = NULL;
    DataType returnType2 = NULL;
    bool requiresGC3;
    ObjectList parameters4 = NULL;
    ObjectListIterator iter5 = NULL;
    FunctionMemberParameter parameter6 = NULL;
    DataType dataType7 = NULL;
    Variable variable8 = NULL;
    String cName9 = NULL;
    DataType functionSignature10 = NULL;
    BoundFunctionMember node11 = NULL;
    GC_FRAME_INIT(12, GC_LOCAL(binder0), GC_LOCAL(functionMember0), GC_LOCAL(generics1), GC_LOCAL(returnType2), GC_LOCAL(parameters4), GC_LOCAL(iter5), GC_LOCAL(parameter6), GC_LOCAL(dataType7), GC_LOCAL(variable8), GC_LOCAL(cName9), GC_LOCAL(functionSignature10), GC_LOCAL(node11));
    {
        generics1 = (list_init)();
        returnType2 = (bind_type_clause)(binder0, (functionMember0)->returnType, 1);
        (list_push)(generics1, ((Object)(returnType2)));
        requiresGC3 = 0;
        parameters4 = (list_init)();
        iter5 = (list_iterator)((functionMember0)->parameters);
        while ((list_iterator_has_next)(iter5))
        {
            parameter6 = ((FunctionMemberParameter)((list_iterator_next)(iter5)));
            dataType7 = (bind_type_clause)(binder0, (parameter6)->typeClause, 0);
            variable8 = (parameter_init)(((parameter6)->identifier)->value, dataType7);
            if (((i32)(((variable8)->dataType)->kind)) == ((i32)(DataTypeKind_OBJECT)))
            {
                requiresGC3 = 1;
            }
            (list_push)(parameters4, ((Object)(variable8)));
            (list_push)(generics1, ((Object)(dataType7)));
        }
        cName9 = (generate_func_cName)(generics1);
        functionSignature10 = (type_init_dynamic)(DataTypeKind_PRIMITIVE, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4), cName9, generics1);
        node11 = OBJECT_CTOR(BoundFunctionMember_impl, BoundFunctionMember_type);
        (node11)->name = ((functionMember0)->identifier)->value;
        (node11)->returnType = returnType2;
        (node11)->requiresGC = requiresGC3;
        (node11)->parameters = parameters4;
        (node11)->variables = (list_init)();
        (node11)->body = NULL;
        (node11)->functionSignature = functionSignature10;
        (scope_declare_function)((binder0)->rootScope, node11);
    }
    GC_FRAME_DESTROY;
}

BoundFunctionMember bind_function_member(Binder binder0, FunctionMember functionMember0)
{
    BoundFunctionMember function1 = NULL;
    ObjectListIterator iter2 = NULL;
    Variable parameter3 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(binder0), GC_LOCAL(functionMember0), GC_LOCAL(function1), GC_LOCAL(iter2), GC_LOCAL(parameter3));
    {
        function1 = (scope_lookup_function)((binder0)->currentScope, ((functionMember0)->identifier)->value);
        if (((Object)(function1)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Cannot find function", 20));
        }
        (scope_push_scope)(binder0);
        (binder0)->currentFunction = function1;
        iter2 = (list_iterator)((function1)->parameters);
        while ((list_iterator_has_next)(iter2))
        {
            parameter3 = ((Variable)((list_iterator_next)(iter2)));
            (scope_declare_variable)((binder0)->currentScope, parameter3);
        }
        (function1)->body = ((Object)((bind_block_statement)(binder0, (functionMember0)->body)));
        (scope_pop_scope)(binder0);
        GC_FRAME_DESTROY;
        return function1;
    }
    GC_FRAME_DESTROY;
}

BoundProgram binder_bind(Binder binder0)
{
    ObjectList enums1 = NULL;
    ObjectList externTypes2 = NULL;
    ObjectList types3 = NULL;
    ObjectList externFunctions4 = NULL;
    ObjectList functions5 = NULL;
    ObjectListIterator iter6 = NULL;
    CompilationUnit unit7 = NULL;
    ObjectListIterator iter8 = NULL;
    EnumMember enumMember9 = NULL;
    ObjectListIterator iter10 = NULL;
    CompilationUnit unit11 = NULL;
    ObjectListIterator iter12 = NULL;
    ExternTypeMember externType13 = NULL;
    ObjectListIterator iter14 = NULL;
    CompilationUnit unit15 = NULL;
    ObjectListIterator iter16 = NULL;
    TypeMember typeMember17 = NULL;
    ObjectListIterator iter18 = NULL;
    CompilationUnit unit19 = NULL;
    ObjectListIterator iter20 = NULL;
    TypeMember typeMember21 = NULL;
    ObjectListIterator iter22 = NULL;
    CompilationUnit unit23 = NULL;
    ObjectListIterator iter24 = NULL;
    ExternFunctionMember externFunction25 = NULL;
    ObjectListIterator iter26 = NULL;
    CompilationUnit unit27 = NULL;
    ObjectListIterator iter28 = NULL;
    FunctionMember function29 = NULL;
    ObjectListIterator iter30 = NULL;
    CompilationUnit unit31 = NULL;
    ObjectListIterator iter32 = NULL;
    FunctionMember function33 = NULL;
    BoundProgram node34 = NULL;
    GC_FRAME_INIT(35, GC_LOCAL(binder0), GC_LOCAL(enums1), GC_LOCAL(externTypes2), GC_LOCAL(types3), GC_LOCAL(externFunctions4), GC_LOCAL(functions5), GC_LOCAL(iter6), GC_LOCAL(unit7), GC_LOCAL(iter8), GC_LOCAL(enumMember9), GC_LOCAL(iter10), GC_LOCAL(unit11), GC_LOCAL(iter12), GC_LOCAL(externType13), GC_LOCAL(iter14), GC_LOCAL(unit15), GC_LOCAL(iter16), GC_LOCAL(typeMember17), GC_LOCAL(iter18), GC_LOCAL(unit19), GC_LOCAL(iter20), GC_LOCAL(typeMember21), GC_LOCAL(iter22), GC_LOCAL(unit23), GC_LOCAL(iter24), GC_LOCAL(externFunction25), GC_LOCAL(iter26), GC_LOCAL(unit27), GC_LOCAL(iter28), GC_LOCAL(function29), GC_LOCAL(iter30), GC_LOCAL(unit31), GC_LOCAL(iter32), GC_LOCAL(function33), GC_LOCAL(node34));
    {
        enums1 = (list_init)();
        externTypes2 = (list_init)();
        types3 = (list_init)();
        externFunctions4 = (list_init)();
        functions5 = (list_init)();
        {
            iter6 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter6))
            {
                unit7 = ((CompilationUnit)((list_iterator_next)(iter6)));
                iter8 = (list_iterator)((unit7)->enums);
                while ((list_iterator_has_next)(iter8))
                {
                    enumMember9 = ((EnumMember)((list_iterator_next)(iter8)));
                    (list_push)(enums1, ((Object)((bind_enum_member)(binder0, enumMember9))));
                }
            }
        }
        {
            iter10 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter10))
            {
                unit11 = ((CompilationUnit)((list_iterator_next)(iter10)));
                iter12 = (list_iterator)((unit11)->externTypes);
                while ((list_iterator_has_next)(iter12))
                {
                    externType13 = ((ExternTypeMember)((list_iterator_next)(iter12)));
                    (list_push)(externTypes2, ((Object)((bind_extern_type_member)(binder0, externType13))));
                }
            }
        }
        {
            iter14 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter14))
            {
                unit15 = ((CompilationUnit)((list_iterator_next)(iter14)));
                iter16 = (list_iterator)((unit15)->types);
                while ((list_iterator_has_next)(iter16))
                {
                    typeMember17 = ((TypeMember)((list_iterator_next)(iter16)));
                    (bind_type_member_signature)(binder0, typeMember17);
                }
            }
        }
        {
            iter18 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter18))
            {
                unit19 = ((CompilationUnit)((list_iterator_next)(iter18)));
                iter20 = (list_iterator)((unit19)->types);
                while ((list_iterator_has_next)(iter20))
                {
                    typeMember21 = ((TypeMember)((list_iterator_next)(iter20)));
                    (list_push)(types3, ((Object)((bind_type_member)(binder0, typeMember21))));
                }
            }
        }
        {
            iter22 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter22))
            {
                unit23 = ((CompilationUnit)((list_iterator_next)(iter22)));
                iter24 = (list_iterator)((unit23)->externFunctions);
                while ((list_iterator_has_next)(iter24))
                {
                    externFunction25 = ((ExternFunctionMember)((list_iterator_next)(iter24)));
                    (list_push)(externFunctions4, ((Object)((bind_extern_function_member)(binder0, externFunction25))));
                }
            }
        }
        {
            iter26 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter26))
            {
                unit27 = ((CompilationUnit)((list_iterator_next)(iter26)));
                iter28 = (list_iterator)((unit27)->functions);
                while ((list_iterator_has_next)(iter28))
                {
                    function29 = ((FunctionMember)((list_iterator_next)(iter28)));
                    (bind_function_member_signature)(binder0, function29);
                }
            }
        }
        {
            iter30 = (list_iterator)((binder0)->units);
            while ((list_iterator_has_next)(iter30))
            {
                unit31 = ((CompilationUnit)((list_iterator_next)(iter30)));
                iter32 = (list_iterator)((unit31)->functions);
                while ((list_iterator_has_next)(iter32))
                {
                    function33 = ((FunctionMember)((list_iterator_next)(iter32)));
                    (list_push)(functions5, ((Object)((bind_function_member)(binder0, function33))));
                }
            }
        }
        node34 = OBJECT_CTOR(BoundProgram_impl, BoundProgram_type);
        (node34)->enums = enums1;
        (node34)->externTypes = externTypes2;
        (node34)->types = types3;
        (node34)->externFunctions = externFunctions4;
        (node34)->functions = functions5;
        (node34)->trackedTypes = (binder0)->trackedTypes;
        GC_FRAME_DESTROY;
        return node34;
    }
    GC_FRAME_DESTROY;
}

I32 box_i32(i32 value0)
{
    I32 box1 = NULL;
    GC_FRAME_INIT(1, GC_LOCAL(box1));
    {
        box1 = OBJECT_CTOR(I32_impl, I32_type);
        (box1)->value = value0;
        GC_FRAME_DESTROY;
        return box1;
    }
    GC_FRAME_DESTROY;
}

Emitter emitter_init(Object file0)
{
    Emitter emitter1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(file0), GC_LOCAL(emitter1));
    {
        emitter1 = OBJECT_CTOR(Emitter_impl, Emitter_type);
        (emitter1)->file = file0;
        (emitter1)->intention = 0;
        (emitter1)->currentFunction = NULL;
        GC_FRAME_DESTROY;
        return emitter1;
    }
    GC_FRAME_DESTROY;
}

void write_intended(Emitter emitter0, String content0)
{
    i32 i1;
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(content0));
    {
        i1 = 0;
        while (i1 < (emitter0)->intention)
        {
            i1 = i1 + 1;
            (fs_write_string)((emitter0)->file, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
        }
        (fs_write_string)((emitter0)->file, content0);
    }
    GC_FRAME_DESTROY;
}

void writeln_intended(Emitter emitter0, String content0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(content0));
    {
        (write_intended)(emitter0, content0);
        (fs_write_string)((emitter0)->file, STRING_CTOR(String_impl, String_type, (uchar*)"\n", 2));
    }
    GC_FRAME_DESTROY;
}

void write(Emitter emitter0, String content0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(content0));
    {
        (fs_write_string)((emitter0)->file, content0);
    }
    GC_FRAME_DESTROY;
}

void writeln(Emitter emitter0, String content0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(content0));
    {
        (write)(emitter0, content0);
        (fs_write_string)((emitter0)->file, STRING_CTOR(String_impl, String_type, (uchar*)"\n", 2));
    }
    GC_FRAME_DESTROY;
}

void inc_intention(Emitter emitter0)
{
    GC_FRAME_INIT(1, GC_LOCAL(emitter0));
    {
        (emitter0)->intention = (emitter0)->intention + 4;
    }
    GC_FRAME_DESTROY;
}

void dec_intention(Emitter emitter0)
{
    GC_FRAME_INIT(1, GC_LOCAL(emitter0));
    {
        (emitter0)->intention = (emitter0)->intention - 4;
    }
    GC_FRAME_DESTROY;
}

void emit_header(Emitter emitter0)
{
    GC_FRAME_INIT(1, GC_LOCAL(emitter0));
    {
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"#include \"gc.h\"", 17));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"#include \"primitive.h\"", 24));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"#include \"object.h\"", 21));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"#include \"string_obj.h\"", 25));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
    }
    GC_FRAME_DESTROY;
}

void emit_type(Emitter emitter0, DataType dataType0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(dataType0));
    {
        if ((string_equals)((dataType0)->name, STRING_CTOR(String_impl, String_type, (uchar*)"Span", 4)))
        {
            if (((Object)((dataType0)->generics)) == ((Object)(NULL)))
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Missing generic type", 20));
            }
            (emit_type)(emitter0, ((DataType)((list_get_value)((dataType0)->generics, 0))));
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"*", 1));
            GC_FRAME_DESTROY;
            return;
        }
        (write)(emitter0, (dataType0)->cName);
    }
    GC_FRAME_DESTROY;
}

void emit_variable_name(Emitter emitter0, Variable variable0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(variable0));
    {
        (write)(emitter0, (variable0)->name);
        (fs_write_int)((emitter0)->file, (variable0)->id);
    }
    GC_FRAME_DESTROY;
}

void emit_cast_expression(Emitter emitter0, BoundCastExpression castExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(castExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (emit_type)(emitter0, (RETURN_TYPE)(((Object)(castExpression0))));
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")(", 2));
        (emit_expression)(emitter0, (castExpression0)->expression);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_null_expression(Emitter emitter0, BoundNullExpression nullExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(nullExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"NULL", 4));
    }
    GC_FRAME_DESTROY;
}

void emit_paren_expression(Emitter emitter0, BoundParenExpression parenExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(parenExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (emit_expression)(emitter0, (parenExpression0)->expression);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_ctor_expression(Emitter emitter0, BoundCtorExpression ctorExpression0)
{
    DataType returnType1 = NULL;
    BoundTypeMember definition2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(emitter0), GC_LOCAL(ctorExpression0), GC_LOCAL(returnType1), GC_LOCAL(definition2));
    {
        returnType1 = (RETURN_TYPE)(((Object)(ctorExpression0)));
        if ((returnType1)->definition == NULL || !(OBJECT_TYPEOF((returnType1)->definition) == &BoundTypeMember_type))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Definition must be set", 22));
        }
        definition2 = ((BoundTypeMember)((returnType1)->definition));
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"OBJECT_CTOR(", 12));
        (write)(emitter0, (definition2)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_impl, ", 7));
        (write)(emitter0, (definition2)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_type", 5));
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_assignment_expression(Emitter emitter0, BoundAssignmentExpression assignment_expression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(assignment_expression0));
    {
        (emit_expression)(emitter0, (assignment_expression0)->left);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" = ", 3));
        (emit_expression)(emitter0, (assignment_expression0)->right);
    }
    GC_FRAME_DESTROY;
}

void emit_unary_expression(Emitter emitter0, BoundUnaryExpression unaryExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(unaryExpression0));
    {
        if (((i32)(((unaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_MINUS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"-", 1));
        }
        else
        if (((i32)(((unaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_PLUS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"+", 1));
        }
        else
        if (((i32)(((unaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_BANG)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"!", 1));
        }
        (emit_expression)(emitter0, (unaryExpression0)->right);
    }
    GC_FRAME_DESTROY;
}

void emit_binary_expression(Emitter emitter0, BoundBinaryExpression binaryExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(binaryExpression0));
    {
        (emit_expression)(emitter0, (binaryExpression0)->left);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_MINUS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"-", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_PLUS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"+", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_STAR)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"*", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_SLASH)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"/", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_EQUALS_EQUALS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"==", 2));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_BANG_EQUALS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"!=", 2));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_LANGLE)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"<", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_LANGLE_EQUALS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"<=", 2));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_RANGLE)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)">", 1));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_RANGLE_EQUALS)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)">=", 2));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_AND_AND)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"&&", 2));
        }
        else
        if (((i32)(((binaryExpression0)->operator)->tokenKind)) == ((i32)(TokenKind_OR_OR)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"||", 2));
        }
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
        (emit_expression)(emitter0, (binaryExpression0)->right);
    }
    GC_FRAME_DESTROY;
}

void emit_call_expression(Emitter emitter0, BoundCallExpression callExpression0)
{
    i32 i1;
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(callExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (emit_expression)(emitter0, (callExpression0)->callee);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")(", 2));
        i1 = 0;
        while (i1 < ((callExpression0)->arguments)->length)
        {
            if (i1 > 0)
            {
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", ", 2));
            }
            (emit_expression)(emitter0, (list_get_value)((callExpression0)->arguments, i1));
            i1 = i1 + 1;
        }
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_member_expression(Emitter emitter0, BoundMemberExpression memberExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(memberExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (emit_expression)(emitter0, (memberExpression0)->object);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")->", 3));
        (write)(emitter0, (memberExpression0)->identifier);
    }
    GC_FRAME_DESTROY;
}

void emit_is_expression(Emitter emitter0, BoundIsExpression isExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(isExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"OBJECT_TYPEOF(", 14));
        (emit_expression)(emitter0, (isExpression0)->left);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)") == &", 6));
        (write)(emitter0, ((isExpression0)->targetType)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_type", 5));
    }
    GC_FRAME_DESTROY;
}

void emit_enum_field_expression(Emitter emitter0, BoundEnumFieldExpression enumFieldExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(enumFieldExpression0));
    {
        (write)(emitter0, (enumFieldExpression0)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_", 1));
        (write)(emitter0, (enumFieldExpression0)->item);
    }
    GC_FRAME_DESTROY;
}

void emit_integer_expression(Emitter emitter0, BoundIntegerExpression integerExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(integerExpression0));
    {
        (write)(emitter0, (integerExpression0)->value);
    }
    GC_FRAME_DESTROY;
}

void emit_char_expression(Emitter emitter0, BoundCharExpression charExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(charExpression0));
    {
        (write)(emitter0, (charExpression0)->value);
    }
    GC_FRAME_DESTROY;
}

void emit_string_expression(Emitter emitter0, BoundStringExpression stringExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(stringExpression0));
    {
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"STRING_CTOR(String_impl, String_type, (uchar*)", 46));
        (write)(emitter0, (stringExpression0)->value);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", ", 2));
        (fs_write_int)((emitter0)->file, ((stringExpression0)->value)->length - 2);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_boolean_expression(Emitter emitter0, BoundBooleanExpression booleanExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(booleanExpression0));
    {
        if (((i32)((booleanExpression0)->value)) == ((i32)(TokenKind_TRUE_KEYWORD)))
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"1", 1));
            GC_FRAME_DESTROY;
            return;
        }
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"0", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_variable_expression(Emitter emitter0, BoundVariableExpression variableExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(variableExpression0));
    {
        (write)(emitter0, ((variableExpression0)->variable)->name);
        (fs_write_int)((emitter0)->file, ((variableExpression0)->variable)->id);
    }
    GC_FRAME_DESTROY;
}

void emit_function_expression(Emitter emitter0, BoundFunctionExpression functionExpression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(functionExpression0));
    {
        (write)(emitter0, ((functionExpression0)->function)->name);
    }
    GC_FRAME_DESTROY;
}

void emit_expression(Emitter emitter0, Object expression0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(expression0));
    {
        if (OBJECT_TYPEOF(expression0) == &BoundCastExpression_type)
        {
            (emit_cast_expression)(emitter0, ((BoundCastExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundNullExpression_type)
        {
            (emit_null_expression)(emitter0, ((BoundNullExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundParenExpression_type)
        {
            (emit_paren_expression)(emitter0, ((BoundParenExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundCtorExpression_type)
        {
            (emit_ctor_expression)(emitter0, ((BoundCtorExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundAssignmentExpression_type)
        {
            (emit_assignment_expression)(emitter0, ((BoundAssignmentExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundUnaryExpression_type)
        {
            (emit_unary_expression)(emitter0, ((BoundUnaryExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundBinaryExpression_type)
        {
            (emit_binary_expression)(emitter0, ((BoundBinaryExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundCallExpression_type)
        {
            (emit_call_expression)(emitter0, ((BoundCallExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundMemberExpression_type)
        {
            (emit_member_expression)(emitter0, ((BoundMemberExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundIsExpression_type)
        {
            (emit_is_expression)(emitter0, ((BoundIsExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundEnumFieldExpression_type)
        {
            (emit_enum_field_expression)(emitter0, ((BoundEnumFieldExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundIntegerExpression_type)
        {
            (emit_integer_expression)(emitter0, ((BoundIntegerExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundCharExpression_type)
        {
            (emit_char_expression)(emitter0, ((BoundCharExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundStringExpression_type)
        {
            (emit_string_expression)(emitter0, ((BoundStringExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundBooleanExpression_type)
        {
            (emit_boolean_expression)(emitter0, ((BoundBooleanExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundVariableExpression_type)
        {
            (emit_variable_expression)(emitter0, ((BoundVariableExpression)(expression0)));
        }
        else
        if (OBJECT_TYPEOF(expression0) == &BoundFunctionExpression_type)
        {
            (emit_function_expression)(emitter0, ((BoundFunctionExpression)(expression0)));
        }
    }
    GC_FRAME_DESTROY;
}

void emit_block_statement(Emitter emitter0, BoundBlockStatement blockStatement0)
{
    ObjectListIterator iter1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(emitter0), GC_LOCAL(blockStatement0), GC_LOCAL(iter1));
    {
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"{", 1));
        (inc_intention)(emitter0);
        iter1 = (list_iterator)((blockStatement0)->statements);
        while ((list_iterator_has_next)(iter1))
        {
            (emit_statement)(emitter0, (list_iterator_next)(iter1));
        }
        (dec_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"}", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_if_statement(Emitter emitter0, BoundIfStatement ifStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(ifStatement0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"if (", 4));
        (emit_expression)(emitter0, (ifStatement0)->condition);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
        (emit_statement)(emitter0, (ifStatement0)->thenCase);
        if ((ifStatement0)->elseCase != NULL)
        {
            (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"else", 4));
            (emit_statement)(emitter0, (ifStatement0)->elseCase);
        }
    }
    GC_FRAME_DESTROY;
}

void emit_while_statement(Emitter emitter0, BoundWhileStatement whileStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(whileStatement0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"while (", 7));
        (emit_expression)(emitter0, (whileStatement0)->condition);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
        (emit_statement)(emitter0, (whileStatement0)->body);
    }
    GC_FRAME_DESTROY;
}

void emit_return_statement(Emitter emitter0, BoundReturnStatement returnStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(returnStatement0));
    {
        if (((Object)((emitter0)->currentFunction)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Requires current function", 25));
        }
        if (((emitter0)->currentFunction)->requiresGC)
        {
            (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"GC_FRAME_DESTROY;", 17));
        }
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"return", 6));
        if ((returnStatement0)->value != NULL)
        {
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
            (emit_expression)(emitter0, (returnStatement0)->value);
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_break_statement(Emitter emitter0, BoundBreakStatement breakStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(breakStatement0));
    {
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"break;", 6));
    }
    GC_FRAME_DESTROY;
}

void emit_continue_statement(Emitter emitter0, BoundContinueStatement continueStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(continueStatement0));
    {
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"continue;", 9));
    }
    GC_FRAME_DESTROY;
}

void emit_expression_statement(Emitter emitter0, BoundExpressionStatement expressionStatement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(expressionStatement0));
    {
        if (OBJECT_TYPEOF((expressionStatement0)->expression) == &BoundEmptyExpression_type)
        {
            GC_FRAME_DESTROY;
            return;
        }
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        (emit_expression)(emitter0, (expressionStatement0)->expression);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_statement(Emitter emitter0, Object statement0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(statement0));
    {
        if (OBJECT_TYPEOF(statement0) == &BoundBlockStatement_type)
        {
            (emit_block_statement)(emitter0, ((BoundBlockStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundIfStatement_type)
        {
            (emit_if_statement)(emitter0, ((BoundIfStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundWhileStatement_type)
        {
            (emit_while_statement)(emitter0, ((BoundWhileStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundReturnStatement_type)
        {
            (emit_return_statement)(emitter0, ((BoundReturnStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundBreakStatement_type)
        {
            (emit_break_statement)(emitter0, ((BoundBreakStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundContinueStatement_type)
        {
            (emit_continue_statement)(emitter0, ((BoundContinueStatement)(statement0)));
        }
        else
        if (OBJECT_TYPEOF(statement0) == &BoundExpressionStatement_type)
        {
            (emit_expression_statement)(emitter0, ((BoundExpressionStatement)(statement0)));
        }
    }
    GC_FRAME_DESTROY;
}

void emit_track_func_type(Emitter emitter0, DataType dataType0)
{
    i32 i1;
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(dataType0));
    {
        if (((Object)((dataType0)->generics)) == ((Object)(NULL)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Func type must have generic parameters", 38));
        }
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"typedef ", 8));
        (emit_type)(emitter0, ((DataType)((list_get_value)((dataType0)->generics, 0))));
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (write)(emitter0, (dataType0)->cName);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")(", 2));
        i1 = 1;
        while (i1 < ((dataType0)->generics)->length)
        {
            if (i1 > 1)
            {
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", ", 2));
            }
            (emit_type)(emitter0, ((DataType)((list_get_value)((dataType0)->generics, i1))));
            i1 = i1 + 1;
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)");", 2));
    }
    GC_FRAME_DESTROY;
}

void emit_enum_member(Emitter emitter0, BoundEnumMember enumMember0)
{
    ObjectListIterator iter1 = NULL;
    BoundEnumMemberItem item2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(emitter0), GC_LOCAL(enumMember0), GC_LOCAL(iter1), GC_LOCAL(item2));
    {
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"typedef enum", 12));
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"{", 1));
        (inc_intention)(emitter0);
        iter1 = (list_iterator)((enumMember0)->items);
        while ((list_iterator_has_next)(iter1))
        {
            item2 = ((BoundEnumMemberItem)((list_iterator_next)(iter1)));
            (write_intended)(emitter0, (enumMember0)->name);
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_", 1));
            (write)(emitter0, (item2)->name);
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)",", 1));
        }
        (dec_intention)(emitter0);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"} ", 2));
        (write)(emitter0, (enumMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_type_member_header(Emitter emitter0, BoundTypeMember typeMember0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(typeMember0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"typedef struct ", 15));
        (write)(emitter0, (typeMember0)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_impl* ", 7));
        (write)(emitter0, (typeMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_type_member(Emitter emitter0, BoundTypeMember typeMember0)
{
    ObjectListIterator iter1 = NULL;
    BoundTypeMemberItem item2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(emitter0), GC_LOCAL(typeMember0), GC_LOCAL(iter1), GC_LOCAL(item2));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"struct ", 7));
        (write)(emitter0, (typeMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_impl", 5));
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"{", 1));
        (inc_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"ObjectType* __type_header__;", 28));
        iter1 = (list_iterator)((typeMember0)->items);
        while ((list_iterator_has_next)(iter1))
        {
            item2 = ((BoundTypeMemberItem)((list_iterator_next)(iter1)));
            (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
            (emit_type)(emitter0, (item2)->dataType);
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
            (write)(emitter0, (item2)->name);
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
        }
        (dec_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"};", 2));
    }
    GC_FRAME_DESTROY;
}

void emit_type_member_trace(Emitter emitter0, BoundTypeMember typeMember0)
{
    ObjectListIterator iter1 = NULL;
    BoundTypeMemberItem item2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(emitter0), GC_LOCAL(typeMember0), GC_LOCAL(iter1), GC_LOCAL(item2));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"static void ", 12));
        (write)(emitter0, ((typeMember0)->meta)->traceName);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(const void* _obj, gc_mark_fn mark)", 35));
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"{", 1));
        (inc_intention)(emitter0);
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"const ", 6));
        (write)(emitter0, (typeMember0)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" obj = (", 8));
        (write)(emitter0, (typeMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")_obj;", 6));
        iter1 = (list_iterator)((typeMember0)->items);
        while ((list_iterator_has_next)(iter1))
        {
            item2 = ((BoundTypeMemberItem)((list_iterator_next)(iter1)));
            if (((i32)(((item2)->dataType)->kind)) != ((i32)(DataTypeKind_OBJECT)))
            {
                continue;
            }
            (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"mark(obj->", 10));
            (write)(emitter0, (item2)->name);
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)");", 2));
        }
        (dec_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"}", 1));
    }
    GC_FRAME_DESTROY;
}

void emit_type_member_type(Emitter emitter0, BoundTypeMember typeMember0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(typeMember0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"ObjectType ", 11));
        (write)(emitter0, (typeMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_type = {", 9));
        (inc_intention)(emitter0);
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)".trace = ", 9));
        (writeln)(emitter0, ((typeMember0)->meta)->traceName);
        (dec_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"};", 2));
    }
    GC_FRAME_DESTROY;
}

void emit_extern_type_member_type(Emitter emitter0, BoundTypeMember typeMember0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(typeMember0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"extern ObjectType ", 18));
        (write)(emitter0, (typeMember0)->name);
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"_type;", 6));
    }
    GC_FRAME_DESTROY;
}

void emit_extern_function_member(Emitter emitter0, BoundFunctionMember functionMember0)
{
    GC_FRAME_INIT(2, GC_LOCAL(emitter0), GC_LOCAL(functionMember0));
    {
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"extern ", 7));
        (emit_function_member_header)(emitter0, functionMember0);
    }
    GC_FRAME_DESTROY;
}

void emit_function_member_header(Emitter emitter0, BoundFunctionMember functionMember0)
{
    i32 i1;
    Variable parameter2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(emitter0), GC_LOCAL(functionMember0), GC_LOCAL(parameter2));
    {
        (emit_type)(emitter0, (functionMember0)->returnType);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
        (write)(emitter0, (functionMember0)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        i1 = 0;
        while (i1 < ((functionMember0)->parameters)->length)
        {
            if (i1 > 0)
            {
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", ", 2));
            }
            parameter2 = ((Variable)((list_get_value)((functionMember0)->parameters, i1)));
            (emit_type)(emitter0, (parameter2)->dataType);
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
            (emit_variable_name)(emitter0, parameter2);
            i1 = i1 + 1;
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)");", 2));
    }
    GC_FRAME_DESTROY;
}

void emit_function_member(Emitter emitter0, BoundFunctionMember functionMember0)
{
    i32 gcObjects1;
    i32 i2;
    Variable parameter3 = NULL;
    ObjectListIterator iter4 = NULL;
    Variable variable5 = NULL;
    ObjectListIterator piter6 = NULL;
    Variable parameter7 = NULL;
    ObjectListIterator viter8 = NULL;
    Variable variable9 = NULL;
    GC_FRAME_INIT(9, GC_LOCAL(emitter0), GC_LOCAL(functionMember0), GC_LOCAL(parameter3), GC_LOCAL(iter4), GC_LOCAL(variable5), GC_LOCAL(piter6), GC_LOCAL(parameter7), GC_LOCAL(viter8), GC_LOCAL(variable9));
    {
        (emitter0)->currentFunction = functionMember0;
        (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        (emit_type)(emitter0, (functionMember0)->returnType);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
        (write)(emitter0, (functionMember0)->name);
        (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        gcObjects1 = 0;
        i2 = 0;
        while (i2 < ((functionMember0)->parameters)->length)
        {
            if (i2 > 0)
            {
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", ", 2));
            }
            parameter3 = ((Variable)((list_get_value)((functionMember0)->parameters, i2)));
            if (((i32)(((parameter3)->dataType)->kind)) == ((i32)(DataTypeKind_OBJECT)))
            {
                gcObjects1 = gcObjects1 + 1;
            }
            (emit_type)(emitter0, (parameter3)->dataType);
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
            (emit_variable_name)(emitter0, parameter3);
            i2 = i2 + 1;
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"{", 1));
        (inc_intention)(emitter0);
        iter4 = (list_iterator)((functionMember0)->variables);
        while ((list_iterator_has_next)(iter4))
        {
            variable5 = ((Variable)((list_iterator_next)(iter4)));
            (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
            (emit_type)(emitter0, (variable5)->dataType);
            (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" ", 1));
            (emit_variable_name)(emitter0, variable5);
            if (((i32)(((variable5)->dataType)->kind)) == ((i32)(DataTypeKind_OBJECT)))
            {
                gcObjects1 = gcObjects1 + 1;
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)" = NULL", 7));
            }
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)";", 1));
        }
        if (gcObjects1 > 0)
        {
            (write_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"GC_FRAME_INIT(", 14));
            (fs_write_int)((emitter0)->file, gcObjects1);
            piter6 = (list_iterator)((functionMember0)->parameters);
            while ((list_iterator_has_next)(piter6))
            {
                parameter7 = ((Variable)((list_iterator_next)(piter6)));
                if (((i32)(((parameter7)->dataType)->kind)) != ((i32)(DataTypeKind_OBJECT)))
                {
                    continue;
                }
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", GC_LOCAL(", 11));
                (emit_variable_name)(emitter0, parameter7);
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
            }
            viter8 = (list_iterator)((functionMember0)->variables);
            while ((list_iterator_has_next)(viter8))
            {
                variable9 = ((Variable)((list_iterator_next)(viter8)));
                if (((i32)(((variable9)->dataType)->kind)) != ((i32)(DataTypeKind_OBJECT)))
                {
                    continue;
                }
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)", GC_LOCAL(", 11));
                (emit_variable_name)(emitter0, variable9);
                (write)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)")", 1));
            }
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)");", 2));
        }
        (emit_block_statement)(emitter0, ((BoundBlockStatement)((functionMember0)->body)));
        if (gcObjects1 > 0)
        {
            (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"GC_FRAME_DESTROY;", 17));
        }
        (dec_intention)(emitter0);
        (writeln_intended)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"}", 1));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
    }
    GC_FRAME_DESTROY;
}

void emit_program(Emitter emitter0, BoundProgram program0)
{
    ObjectListIterator enumIter1 = NULL;
    ObjectListIterator typeHeaderIter2 = NULL;
    ObjectListIterator externTypeHeaderIter3 = NULL;
    ObjectListIterator trackedTypeIter4 = NULL;
    DataType dataType5 = NULL;
    ObjectListIterator typeIter6 = NULL;
    BoundTypeMember typeMember7 = NULL;
    ObjectListIterator externTypeIter8 = NULL;
    BoundTypeMember typeMember9 = NULL;
    ObjectListIterator externFuncIter10 = NULL;
    ObjectListIterator funcHeaderIter11 = NULL;
    ObjectListIterator funcIter12 = NULL;
    GC_FRAME_INIT(14, GC_LOCAL(emitter0), GC_LOCAL(program0), GC_LOCAL(enumIter1), GC_LOCAL(typeHeaderIter2), GC_LOCAL(externTypeHeaderIter3), GC_LOCAL(trackedTypeIter4), GC_LOCAL(dataType5), GC_LOCAL(typeIter6), GC_LOCAL(typeMember7), GC_LOCAL(externTypeIter8), GC_LOCAL(typeMember9), GC_LOCAL(externFuncIter10), GC_LOCAL(funcHeaderIter11), GC_LOCAL(funcIter12));
    {
        (emit_header)(emitter0);
        enumIter1 = (list_iterator)((program0)->enums);
        while ((list_iterator_has_next)(enumIter1))
        {
            (emit_enum_member)(emitter0, ((BoundEnumMember)((list_iterator_next)(enumIter1))));
        }
        typeHeaderIter2 = (list_iterator)((program0)->types);
        while ((list_iterator_has_next)(typeHeaderIter2))
        {
            (emit_type_member_header)(emitter0, ((BoundTypeMember)((list_iterator_next)(typeHeaderIter2))));
        }
        externTypeHeaderIter3 = (list_iterator)((program0)->externTypes);
        while ((list_iterator_has_next)(externTypeHeaderIter3))
        {
            (emit_type_member_header)(emitter0, ((BoundTypeMember)((list_iterator_next)(externTypeHeaderIter3))));
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        trackedTypeIter4 = (list_iterator)((program0)->trackedTypes);
        while ((list_iterator_has_next)(trackedTypeIter4))
        {
            dataType5 = ((DataType)((list_iterator_next)(trackedTypeIter4)));
            if ((string_equals)((dataType5)->name, STRING_CTOR(String_impl, String_type, (uchar*)"Func", 4)))
            {
                (emit_track_func_type)(emitter0, dataType5);
            }
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        typeIter6 = (list_iterator)((program0)->types);
        while ((list_iterator_has_next)(typeIter6))
        {
            typeMember7 = ((BoundTypeMember)((list_iterator_next)(typeIter6)));
            (emit_type_member)(emitter0, typeMember7);
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
            if (((typeMember7)->meta)->generateTrace)
            {
                (emit_type_member_trace)(emitter0, typeMember7);
                (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
            }
            (emit_type_member_type)(emitter0, typeMember7);
        }
        externTypeIter8 = (list_iterator)((program0)->externTypes);
        while ((list_iterator_has_next)(externTypeIter8))
        {
            typeMember9 = ((BoundTypeMember)((list_iterator_next)(externTypeIter8)));
            (emit_type_member)(emitter0, typeMember9);
            (emit_extern_type_member_type)(emitter0, typeMember9);
            (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        externFuncIter10 = (list_iterator)((program0)->externFunctions);
        while ((list_iterator_has_next)(externFuncIter10))
        {
            (emit_extern_function_member)(emitter0, ((BoundFunctionMember)((list_iterator_next)(externFuncIter10))));
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        funcHeaderIter11 = (list_iterator)((program0)->functions);
        while ((list_iterator_has_next)(funcHeaderIter11))
        {
            (emit_function_member_header)(emitter0, ((BoundFunctionMember)((list_iterator_next)(funcHeaderIter11))));
        }
        (writeln)(emitter0, STRING_CTOR(String_impl, String_type, (uchar*)"", 0));
        funcIter12 = (list_iterator)((program0)->functions);
        while ((list_iterator_has_next)(funcIter12))
        {
            (emit_function_member)(emitter0, ((BoundFunctionMember)((list_iterator_next)(funcIter12))));
        }
    }
    GC_FRAME_DESTROY;
}

bool char_is_alpha(uchar c0)
{
    {
        return ((i16)(c0)) >= ((i16)('a')) && ((i16)(c0)) <= ((i16)('z')) || ((i16)(c0)) >= ((i16)('A')) && ((i16)(c0)) <= ((i16)('Z'));
    }
}

bool char_is_numeric(uchar c0)
{
    {
        return ((i16)(c0)) >= ((i16)('0')) && ((i16)(c0)) <= ((i16)('9'));
    }
}

bool char_is_alpha_numeric(uchar c0)
{
    {
        return (char_is_alpha)(c0) || (char_is_numeric)(c0);
    }
}

bool char_is_whitespace(uchar c0)
{
    {
        return c0 == ' ' || c0 == '\t' || c0 == '\n' || c0 == '\r';
    }
}

ConversionRule rule_init(DataType from0, DataType to0, ConversionKind kind0)
{
    ConversionRule rule1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(from0), GC_LOCAL(to0), GC_LOCAL(rule1));
    {
        rule1 = OBJECT_CTOR(ConversionRule_impl, ConversionRule_type);
        (rule1)->from = from0;
        (rule1)->to = to0;
        (rule1)->kind = kind0;
        GC_FRAME_DESTROY;
        return rule1;
    }
    GC_FRAME_DESTROY;
}

ObjectList conversion_init(DataType i8Type0, DataType i16Type0, DataType i32Type0, DataType i64Type0, DataType u8Type0, DataType u16Type0, DataType u32Type0, DataType u64Type0, DataType boolType0, DataType charType0)
{
    ObjectList rules1 = NULL;
    GC_FRAME_INIT(11, GC_LOCAL(i8Type0), GC_LOCAL(i16Type0), GC_LOCAL(i32Type0), GC_LOCAL(i64Type0), GC_LOCAL(u8Type0), GC_LOCAL(u16Type0), GC_LOCAL(u32Type0), GC_LOCAL(u64Type0), GC_LOCAL(boolType0), GC_LOCAL(charType0), GC_LOCAL(rules1));
    {
        rules1 = (list_init)();
        (list_push)(rules1, ((Object)((rule_init)(i8Type0, i16Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i16Type0, i32Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i32Type0, i64Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i16Type0, i8Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i32Type0, i16Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i64Type0, i32Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u8Type0, u16Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u16Type0, u32Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u32Type0, u64Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u16Type0, u8Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u32Type0, u16Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u64Type0, u32Type0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(i64Type0, boolType0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(u64Type0, boolType0, ConversionKind_EXPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(boolType0, i8Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(boolType0, u8Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(charType0, u8Type0, ConversionKind_IMPLICIT))));
        (list_push)(rules1, ((Object)((rule_init)(charType0, i16Type0, ConversionKind_IMPLICIT))));
        GC_FRAME_DESTROY;
        return rules1;
    }
    GC_FRAME_DESTROY;
}

ObjectList conversion_classify(Binder binder0, DataType from0, DataType to0, bool explicit0)
{
    ObjectList list1 = NULL;
    ObjectList list2 = NULL;
    ObjectList list3 = NULL;
    ObjectList list4 = NULL;
    ObjectList frontierTypes5 = NULL;
    ObjectList frontierPaths6 = NULL;
    ObjectList nextTypes7 = NULL;
    ObjectList nextPaths8 = NULL;
    i32 i9;
    DataType currentType10 = NULL;
    ObjectList currentPath11 = NULL;
    ObjectListIterator iter12 = NULL;
    ConversionRule rule13 = NULL;
    bool seen14;
    ObjectListIterator iter15 = NULL;
    ConversionRule step16 = NULL;
    ObjectList newPath17 = NULL;
    GC_FRAME_INIT(18, GC_LOCAL(binder0), GC_LOCAL(from0), GC_LOCAL(to0), GC_LOCAL(list1), GC_LOCAL(list2), GC_LOCAL(list3), GC_LOCAL(list4), GC_LOCAL(frontierTypes5), GC_LOCAL(frontierPaths6), GC_LOCAL(nextTypes7), GC_LOCAL(nextPaths8), GC_LOCAL(currentType10), GC_LOCAL(currentPath11), GC_LOCAL(iter12), GC_LOCAL(rule13), GC_LOCAL(iter15), GC_LOCAL(step16), GC_LOCAL(newPath17));
    {
        if ((type_eq_type)(from0, to0))
        {
            GC_FRAME_DESTROY;
            return (list_init)();
        }
        if ((from0)->definition != NULL && OBJECT_TYPEOF((from0)->definition) == &BoundTypeMember_type && (type_eq_type)(to0, (binder0)->objectType))
        {
            list1 = (list_init)();
            (list_push)(list1, ((Object)((rule_init)(from0, to0, ConversionKind_IMPLICIT))));
            GC_FRAME_DESTROY;
            return list1;
        }
        if (explicit0 && (type_eq_type)(from0, (binder0)->objectType) && (to0)->definition != NULL && OBJECT_TYPEOF((to0)->definition) == &BoundTypeMember_type)
        {
            list2 = (list_init)();
            (list_push)(list2, ((Object)((rule_init)(from0, to0, ConversionKind_EXPLICIT))));
            GC_FRAME_DESTROY;
            return list2;
        }
        if ((from0)->definition != NULL && OBJECT_TYPEOF((from0)->definition) == &BoundEnumMember_type && (type_eq_type)(to0, (binder0)->i32Type))
        {
            list3 = (list_init)();
            (list_push)(list3, ((Object)((rule_init)(from0, to0, ConversionKind_IMPLICIT))));
            GC_FRAME_DESTROY;
            return list3;
        }
        if (explicit0 && (type_eq_type)(from0, (binder0)->i32Type) && (to0)->definition != NULL && OBJECT_TYPEOF((to0)->definition) == &BoundEnumMember_type)
        {
            list4 = (list_init)();
            (list_push)(list4, ((Object)((rule_init)(from0, to0, ConversionKind_EXPLICIT))));
            GC_FRAME_DESTROY;
            return list4;
        }
        frontierTypes5 = (list_init)();
        (list_push)(frontierTypes5, ((Object)(from0)));
        frontierPaths6 = (list_init)();
        (list_push)(frontierPaths6, ((Object)((list_init)())));
        while ((frontierTypes5)->length > 0)
        {
            nextTypes7 = (list_init)();
            nextPaths8 = (list_init)();
            i9 = 0;
            while (i9 < (frontierTypes5)->length)
            {
                currentType10 = ((DataType)((list_get_value)(frontierTypes5, i9)));
                currentPath11 = ((ObjectList)((list_get_value)(frontierPaths6, i9)));
                i9 = i9 + 1;
                iter12 = (list_iterator)((binder0)->conversionRules);
                while ((list_iterator_has_next)(iter12))
                {
                    rule13 = ((ConversionRule)((list_iterator_next)(iter12)));
                    if (!(type_eq_type)((rule13)->from, currentType10) || !explicit0 && ((i32)((rule13)->kind)) == ((i32)(ConversionKind_EXPLICIT)))
                    {
                        continue;
                    }
                    seen14 = 0;
                    iter15 = (list_iterator)(currentPath11);
                    while ((list_iterator_has_next)(iter15))
                    {
                        step16 = ((ConversionRule)((list_iterator_next)(iter15)));
                        if ((type_eq_type)((step16)->from, (rule13)->to))
                        {
                            seen14 = 1;
                            break;
                        }
                    }
                    if (seen14)
                    {
                        continue;
                    }
                    newPath17 = (list_dup)(currentPath11);
                    (list_push)(newPath17, ((Object)(rule13)));
                    if ((type_eq_type)((rule13)->to, to0))
                    {
                        GC_FRAME_DESTROY;
                        return newPath17;
                    }
                    (list_push)(nextTypes7, ((Object)((rule13)->to)));
                    (list_push)(nextPaths8, ((Object)(newPath17)));
                }
            }
            frontierTypes5 = nextTypes7;
            frontierPaths6 = nextPaths8;
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

DiagnosticBag diagnosticBag_init()
{
    DiagnosticBag diagnostics1 = NULL;
    GC_FRAME_INIT(1, GC_LOCAL(diagnostics1));
    {
        diagnostics1 = OBJECT_CTOR(DiagnosticBag_impl, DiagnosticBag_type);
        (diagnostics1)->list = (list_init)();
        GC_FRAME_DESTROY;
        return diagnostics1;
    }
    GC_FRAME_DESTROY;
}

Diagnostic diagnostic_init(DiagnosticCode code0, LocationSpan span0, ObjectList args0)
{
    Diagnostic diagnostic1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(span0), GC_LOCAL(args0), GC_LOCAL(diagnostic1));
    {
        diagnostic1 = OBJECT_CTOR(Diagnostic_impl, Diagnostic_type);
        (diagnostic1)->code = code0;
        (diagnostic1)->span = span0;
        (diagnostic1)->args = args0;
        GC_FRAME_DESTROY;
        return diagnostic1;
    }
    GC_FRAME_DESTROY;
}

void report_unexpected_char(DiagnosticBag bag0, LocationSpan span0, String value0)
{
    ObjectList args1 = NULL;
    Diagnostic diagnostic2 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(bag0), GC_LOCAL(span0), GC_LOCAL(value0), GC_LOCAL(args1), GC_LOCAL(diagnostic2));
    {
        args1 = (list_init)();
        (list_push)(args1, ((Object)(value0)));
        diagnostic2 = (diagnostic_init)(DiagnosticCode_UNEXPECTED_CHAR, span0, args1);
        (list_push)((bag0)->list, ((Object)(diagnostic2)));
    }
    GC_FRAME_DESTROY;
}

void report_unclosed_string(DiagnosticBag bag0, LocationSpan span0)
{
    Diagnostic diagnostic1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(bag0), GC_LOCAL(span0), GC_LOCAL(diagnostic1));
    {
        diagnostic1 = (diagnostic_init)(DiagnosticCode_UNCLOSED_STRING, span0, (list_init)());
        (list_push)((bag0)->list, ((Object)(diagnostic1)));
    }
    GC_FRAME_DESTROY;
}

void report_unclosed_char(DiagnosticBag bag0, LocationSpan span0)
{
    Diagnostic diagnostic1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(bag0), GC_LOCAL(span0), GC_LOCAL(diagnostic1));
    {
        diagnostic1 = (diagnostic_init)(DiagnosticCode_UNCLOSED_CHAR, span0, (list_init)());
        (list_push)((bag0)->list, ((Object)(diagnostic1)));
    }
    GC_FRAME_DESTROY;
}

void report_expected_token(DiagnosticBag bag0, LocationSpan span0, TokenKind got0, TokenKind expected0)
{
    ObjectList args1 = NULL;
    Diagnostic diagnostic2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(bag0), GC_LOCAL(span0), GC_LOCAL(args1), GC_LOCAL(diagnostic2));
    {
        args1 = (list_init)();
        (list_push)(args1, ((Object)((box_i32)(((i32)(got0))))));
        (list_push)(args1, ((Object)((box_i32)(((i32)(expected0))))));
        diagnostic2 = (diagnostic_init)(DiagnosticCode_EXPECTED_TOKEN, span0, args1);
    }
    GC_FRAME_DESTROY;
}

void report_expected_token2(DiagnosticBag bag0, LocationSpan span0, TokenKind got0, TokenKind expected10, TokenKind expected20)
{
    ObjectList args1 = NULL;
    Diagnostic diagnostic2 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(bag0), GC_LOCAL(span0), GC_LOCAL(args1), GC_LOCAL(diagnostic2));
    {
        args1 = (list_init)();
        (list_push)(args1, ((Object)((box_i32)(((i32)(got0))))));
        (list_push)(args1, ((Object)((box_i32)(((i32)(expected10))))));
        (list_push)(args1, ((Object)((box_i32)(((i32)(expected20))))));
        diagnostic2 = (diagnostic_init)(DiagnosticCode_EXPECTED_TOKEN, span0, args1);
    }
    GC_FRAME_DESTROY;
}

void diagnostic_print_code_message(Object fd0, DiagnosticCode code0, ObjectList args0)
{
    String c1 = NULL;
    i32 got2;
    i32 expected3;
    i32 expected4;
    i32 got5;
    GC_FRAME_INIT(3, GC_LOCAL(fd0), GC_LOCAL(args0), GC_LOCAL(c1));
    {
        if (((i32)(code0)) == ((i32)(DiagnosticCode_UNEXPECTED_CHAR)))
        {
            c1 = ((String)((list_get_value)(args0, 0)));
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"Unexpected character '", 22));
            (fs_write_string)(fd0, c1);
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"'", 1));
        }
        else
        if (((i32)(code0)) == ((i32)(DiagnosticCode_UNCLOSED_STRING)))
        {
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"Unterminated string literal", 27));
        }
        else
        if (((i32)(code0)) == ((i32)(DiagnosticCode_UNCLOSED_CHAR)))
        {
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"Unterminated char literal", 25));
        }
        else
        if (((i32)(code0)) == ((i32)(DiagnosticCode_EXPECTED_TOKEN)))
        {
            got2 = ((((I32)((list_get_value)(args0, 0)))))->value;
            expected3 = ((((I32)((list_get_value)(args0, 1)))))->value;
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"Expected token '", 16));
            (fs_write_int)(fd0, expected3);
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"'", 1));
            if ((args0)->length == 3)
            {
                expected4 = ((((I32)((list_get_value)(args0, 2)))))->value;
                (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)", or '", 6));
                (fs_write_int)(fd0, expected4);
                (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"'", 1));
            }
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)", but got '", 11));
            (fs_write_int)(fd0, got2);
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"'", 1));
        }
        else
        if (((i32)(code0)) == ((i32)(DiagnosticCode_UNEXPECTED_TOKEN)))
        {
            got5 = ((((I32)((list_get_value)(args0, 0)))))->value;
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"Unexpected token '", 18));
            (fs_write_int)(fd0, got5);
            (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"'", 1));
        }
    }
    GC_FRAME_DESTROY;
}

void diagnostic_print_single(Object fd0, Diagnostic diagnostic0)
{
    DiagnosticCode code1;
    LocationSpan span2 = NULL;
    ObjectList args3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(fd0), GC_LOCAL(diagnostic0), GC_LOCAL(span2), GC_LOCAL(args3));
    {
        code1 = (diagnostic0)->code;
        span2 = (diagnostic0)->span;
        args3 = (diagnostic0)->args;
        (fs_write_string)(fd0, (span2)->filename);
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"(", 1));
        (fs_write_int)(fd0, (span2)->startLine);
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)":", 1));
        (fs_write_int)(fd0, (span2)->startCol);
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)") [", 3));
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"LOP", 3));
        (fs_write_int)(fd0, ((i32)(code1)));
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"]: ", 3));
        (diagnostic_print_code_message)(fd0, code1, args3);
        (fs_write_string)(fd0, STRING_CTOR(String_impl, String_type, (uchar*)"\n", 2));
    }
    GC_FRAME_DESTROY;
}

void diagnostic_print(DiagnosticBag diagnostics0)
{
    Object fd1 = NULL;
    ObjectListIterator iter2 = NULL;
    Diagnostic diagnostic3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(diagnostics0), GC_LOCAL(fd1), GC_LOCAL(iter2), GC_LOCAL(diagnostic3));
    {
        fd1 = (fs_get_stderr)();
        iter2 = (list_iterator)((diagnostics0)->list);
        while ((list_iterator_has_next)(iter2))
        {
            diagnostic3 = ((Diagnostic)((list_iterator_next)(iter2)));
            (diagnostic_print_single)(fd1, diagnostic3);
        }
    }
    GC_FRAME_DESTROY;
}

Lexer lexer_init(DiagnosticBag diagnostics0, String filename0, String content0)
{
    Lexer lexer1 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(diagnostics0), GC_LOCAL(filename0), GC_LOCAL(content0), GC_LOCAL(lexer1));
    {
        lexer1 = OBJECT_CTOR(Lexer_impl, Lexer_type);
        (lexer1)->diagnostics = diagnostics0;
        (lexer1)->filename = filename0;
        (lexer1)->content = content0;
        (lexer1)->position = 0;
        (lexer1)->currentCol = 1;
        (lexer1)->currentLine = 1;
        GC_FRAME_DESTROY;
        return lexer1;
    }
    GC_FRAME_DESTROY;
}

LocationSpan locationSpan_init(String filename0, i32 startPos0, i32 endPos0, i32 startLine0, i32 endLine0, i32 startCol0, i32 endCol0)
{
    LocationSpan span1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(filename0), GC_LOCAL(span1));
    {
        span1 = OBJECT_CTOR(LocationSpan_impl, LocationSpan_type);
        (span1)->filename = filename0;
        (span1)->startPos = startPos0;
        (span1)->endPos = endPos0;
        (span1)->startLine = startLine0;
        (span1)->endLine = endLine0;
        (span1)->startCol = startCol0;
        (span1)->endCol = endCol0;
        GC_FRAME_DESTROY;
        return span1;
    }
    GC_FRAME_DESTROY;
}

Token token_init(TokenKind kind0, String value0, LocationSpan span0)
{
    Token token1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(value0), GC_LOCAL(span0), GC_LOCAL(token1));
    {
        token1 = OBJECT_CTOR(Token_impl, Token_type);
        (token1)->kind = kind0;
        (token1)->value = value0;
        (token1)->span = span0;
        GC_FRAME_DESTROY;
        return token1;
    }
    GC_FRAME_DESTROY;
}

bool lexer_is_eof(Lexer lexer0)
{
    GC_FRAME_INIT(1, GC_LOCAL(lexer0));
    {
        GC_FRAME_DESTROY;
        return (lexer0)->position >= ((lexer0)->content)->length;
    }
    GC_FRAME_DESTROY;
}

uchar current_char(Lexer lexer0)
{
    GC_FRAME_INIT(1, GC_LOCAL(lexer0));
    {
        if ((lexer_is_eof)(lexer0))
        {
            GC_FRAME_DESTROY;
            return '\0';
        }
        GC_FRAME_DESTROY;
        return (string_char_at)((lexer0)->content, (lexer0)->position);
    }
    GC_FRAME_DESTROY;
}

uchar peek_char(Lexer lexer0)
{
    GC_FRAME_INIT(1, GC_LOCAL(lexer0));
    {
        if ((lexer0)->position + 1 >= ((lexer0)->content)->length)
        {
            GC_FRAME_DESTROY;
            return '\0';
        }
        GC_FRAME_DESTROY;
        return (string_char_at)((lexer0)->content, (lexer0)->position + 1);
    }
    GC_FRAME_DESTROY;
}

uchar next_char(Lexer lexer0)
{
    uchar c1;
    GC_FRAME_INIT(1, GC_LOCAL(lexer0));
    {
        c1 = (current_char)(lexer0);
        if (c1 == '\n')
        {
            (lexer0)->currentLine = (lexer0)->currentLine + 1;
            (lexer0)->currentCol = 1;
        }
        else
        {
            (lexer0)->currentCol = (lexer0)->currentCol + 1;
        }
        (lexer0)->position = (lexer0)->position + 1;
        GC_FRAME_DESTROY;
        return c1;
    }
    GC_FRAME_DESTROY;
}

Token lex_whitespace(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    String value4 = NULL;
    LocationSpan span5 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value4), GC_LOCAL(span5));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        while ((char_is_whitespace)((current_char)(lexer0)) && !(lexer_is_eof)(lexer0))
        {
            (next_char)(lexer0);
        }
        value4 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span5 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_WHITESPACE, value4, span5);
    }
    GC_FRAME_DESTROY;
}

Token lex_identifier(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    TokenKind kind4;
    String value5 = NULL;
    LocationSpan span6 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value5), GC_LOCAL(span6));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        while (((char_is_alpha_numeric)((current_char)(lexer0)) || (current_char)(lexer0) == '_') && !(lexer_is_eof)(lexer0))
        {
            (next_char)(lexer0);
        }
        kind4 = TokenKind_IDENTIFIER;
        value5 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"type", 4)))
        {
            kind4 = TokenKind_TYPE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"func", 4)))
        {
            kind4 = TokenKind_FUNCTION_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"enum", 4)))
        {
            kind4 = TokenKind_ENUM_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"let", 3)))
        {
            kind4 = TokenKind_LET_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"new", 3)))
        {
            kind4 = TokenKind_NEW_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"if", 2)))
        {
            kind4 = TokenKind_IF_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"else", 4)))
        {
            kind4 = TokenKind_ELSE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"while", 5)))
        {
            kind4 = TokenKind_WHILE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"return", 6)))
        {
            kind4 = TokenKind_RETURN_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"true", 4)))
        {
            kind4 = TokenKind_TRUE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"false", 5)))
        {
            kind4 = TokenKind_FALSE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"extern", 6)))
        {
            kind4 = TokenKind_EXTERN_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"null", 4)))
        {
            kind4 = TokenKind_NULL_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"break", 5)))
        {
            kind4 = TokenKind_BREAK_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"continue", 8)))
        {
            kind4 = TokenKind_CONTINUE_KEYWORD;
        }
        else
        if ((string_equals)(value5, STRING_CTOR(String_impl, String_type, (uchar*)"is", 2)))
        {
            kind4 = TokenKind_IS_KEYWORD;
        }
        span6 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        GC_FRAME_DESTROY;
        return (token_init)(kind4, value5, span6);
    }
    GC_FRAME_DESTROY;
}

Token lex_numeric(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    String value4 = NULL;
    LocationSpan span5 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value4), GC_LOCAL(span5));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        while ((char_is_numeric)((current_char)(lexer0)) && !(lexer_is_eof)(lexer0))
        {
            (next_char)(lexer0);
        }
        value4 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span5 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_INTEGER_LITERAL, value4, span5);
    }
    GC_FRAME_DESTROY;
}

Token lex_char(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    uchar c4;
    bool missingClose5;
    String value6 = NULL;
    LocationSpan span7 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value6), GC_LOCAL(span7));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        (next_char)(lexer0);
        c4 = (next_char)(lexer0);
        if (c4 == '\\')
        {
            (next_char)(lexer0);
        }
        missingClose5 = 1;
        if ((current_char)(lexer0) == '\'')
        {
            missingClose5 = 0;
            (next_char)(lexer0);
        }
        value6 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span7 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        if (missingClose5)
        {
            (report_unclosed_char)((lexer0)->diagnostics, span7);
        }
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_CHAR_LITERAL, value6, span7);
    }
    GC_FRAME_DESTROY;
}

Token lex_string(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    bool missingClose4;
    String value5 = NULL;
    LocationSpan span6 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value5), GC_LOCAL(span6));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        (next_char)(lexer0);
        while ((current_char)(lexer0) != '"' && (current_char)(lexer0) != '\n' && !(lexer_is_eof)(lexer0))
        {
            if ((current_char)(lexer0) == '\\')
            {
                (next_char)(lexer0);
            }
            (next_char)(lexer0);
        }
        missingClose4 = 1;
        if ((current_char)(lexer0) == '"')
        {
            missingClose4 = 0;
            (next_char)(lexer0);
        }
        value5 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span6 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        if (missingClose4)
        {
            (report_unclosed_string)((lexer0)->diagnostics, span6);
        }
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_STRING_LITERAL, value5, span6);
    }
    GC_FRAME_DESTROY;
}

Token lex_single_line_comment(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    String value4 = NULL;
    LocationSpan span5 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value4), GC_LOCAL(span5));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        while ((current_char)(lexer0) != '\n' && !(lexer_is_eof)(lexer0))
        {
            (next_char)(lexer0);
        }
        value4 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span5 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_SINGLE_COMMENT, value4, span5);
    }
    GC_FRAME_DESTROY;
}

Token lex_multi_line_comment(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    String value4 = NULL;
    LocationSpan span5 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value4), GC_LOCAL(span5));
    {
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        while (((current_char)(lexer0) != '*' || (peek_char)(lexer0) != '/') && !(lexer_is_eof)(lexer0))
        {
            (next_char)(lexer0);
        }
        (next_char)(lexer0);
        (next_char)(lexer0);
        value4 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span5 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        GC_FRAME_DESTROY;
        return (token_init)(TokenKind_MULTI_COMMENT, value4, span5);
    }
    GC_FRAME_DESTROY;
}

Token lexer_next_token(Lexer lexer0)
{
    i32 startPos1;
    i32 startLine2;
    i32 startCol3;
    uchar curr4;
    TokenKind kind5;
    String value6 = NULL;
    LocationSpan span7 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(lexer0), GC_LOCAL(value6), GC_LOCAL(span7));
    {
        if ((lexer_is_eof)(lexer0))
        {
            GC_FRAME_DESTROY;
            return (token_init)(TokenKind_EOF, STRING_CTOR(String_impl, String_type, (uchar*)"", 0), (locationSpan_init)((lexer0)->filename, (lexer0)->position, (lexer0)->position, (lexer0)->currentLine, (lexer0)->currentLine, (lexer0)->currentCol, (lexer0)->currentCol));
        }
        if ((char_is_whitespace)((current_char)(lexer0)))
        {
            GC_FRAME_DESTROY;
            return (lex_whitespace)(lexer0);
        }
        if ((char_is_alpha)((current_char)(lexer0)) || (current_char)(lexer0) == '_')
        {
            GC_FRAME_DESTROY;
            return (lex_identifier)(lexer0);
        }
        if ((char_is_numeric)((current_char)(lexer0)))
        {
            GC_FRAME_DESTROY;
            return (lex_numeric)(lexer0);
        }
        if ((current_char)(lexer0) == '\'')
        {
            GC_FRAME_DESTROY;
            return (lex_char)(lexer0);
        }
        if ((current_char)(lexer0) == '"')
        {
            GC_FRAME_DESTROY;
            return (lex_string)(lexer0);
        }
        if ((current_char)(lexer0) == '/' && (peek_char)(lexer0) == '/')
        {
            GC_FRAME_DESTROY;
            return (lex_single_line_comment)(lexer0);
        }
        if ((current_char)(lexer0) == '/' && (peek_char)(lexer0) == '*')
        {
            GC_FRAME_DESTROY;
            return (lex_single_line_comment)(lexer0);
        }
        startPos1 = (lexer0)->position;
        startLine2 = (lexer0)->currentLine;
        startCol3 = (lexer0)->currentCol;
        curr4 = (next_char)(lexer0);
        if (curr4 == '(')
        {
            kind5 = TokenKind_LPAREN;
        }
        else
        if (curr4 == ')')
        {
            kind5 = TokenKind_RPAREN;
        }
        else
        if (curr4 == '{')
        {
            kind5 = TokenKind_LBRACE;
        }
        else
        if (curr4 == '}')
        {
            kind5 = TokenKind_RBRACE;
        }
        else
        if (curr4 == ';')
        {
            kind5 = TokenKind_SEMICOLON;
        }
        else
        if (curr4 == ':')
        {
            kind5 = TokenKind_COLON;
        }
        else
        if (curr4 == '=')
        {
            if ((current_char)(lexer0) == '=')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_EQUALS_EQUALS;
            }
            else
            {
                kind5 = TokenKind_EQUALS;
            }
        }
        else
        if (curr4 == '!')
        {
            if ((current_char)(lexer0) == '=')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_BANG_EQUALS;
            }
            else
            {
                kind5 = TokenKind_BANG;
            }
        }
        else
        if (curr4 == '+')
        {
            kind5 = TokenKind_PLUS;
        }
        else
        if (curr4 == '-')
        {
            kind5 = TokenKind_MINUS;
        }
        else
        if (curr4 == '*')
        {
            kind5 = TokenKind_STAR;
        }
        else
        if (curr4 == '/')
        {
            kind5 = TokenKind_SLASH;
        }
        else
        if (curr4 == '&')
        {
            if ((current_char)(lexer0) == '&')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_AND_AND;
            }
            else
            {
                kind5 = TokenKind_AND;
            }
        }
        else
        if (curr4 == '|')
        {
            if ((current_char)(lexer0) == '|')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_OR_OR;
            }
            else
            {
                kind5 = TokenKind_OR;
            }
        }
        else
        if (curr4 == '<')
        {
            if ((current_char)(lexer0) == '=')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_LANGLE_EQUALS;
            }
            else
            {
                kind5 = TokenKind_LANGLE;
            }
        }
        else
        if (curr4 == '>')
        {
            if ((current_char)(lexer0) == '=')
            {
                (next_char)(lexer0);
                kind5 = TokenKind_RANGLE_EQUALS;
            }
            else
            {
                kind5 = TokenKind_RANGLE;
            }
        }
        else
        if (curr4 == ',')
        {
            kind5 = TokenKind_COMMA;
        }
        else
        if (curr4 == '.')
        {
            kind5 = TokenKind_DOT;
        }
        else
        {
            kind5 = TokenKind_ERROR;
        }
        value6 = (string_substring)((lexer0)->content, startPos1, (lexer0)->position);
        span7 = (locationSpan_init)((lexer0)->filename, startPos1, (lexer0)->position, startLine2, (lexer0)->currentLine, startCol3, (lexer0)->currentCol);
        if (((i32)(kind5)) == ((i32)(TokenKind_ERROR)))
        {
            (report_unexpected_char)((lexer0)->diagnostics, span7, value6);
        }
        GC_FRAME_DESTROY;
        return (token_init)(kind5, value6, span7);
    }
    GC_FRAME_DESTROY;
}

ObjectList list_init()
{
    ObjectList list1 = NULL;
    GC_FRAME_INIT(1, GC_LOCAL(list1));
    {
        list1 = OBJECT_CTOR(ObjectList_impl, ObjectList_type);
        (list1)->length = 0;
        (list1)->first = NULL;
        (list1)->last = NULL;
        GC_FRAME_DESTROY;
        return list1;
    }
    GC_FRAME_DESTROY;
}

void list_push(ObjectList list0, Object value0)
{
    ObjectListItem item1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(list0), GC_LOCAL(value0), GC_LOCAL(item1));
    {
        item1 = OBJECT_CTOR(ObjectListItem_impl, ObjectListItem_type);
        (item1)->value = value0;
        (item1)->next = NULL;
        (item1)->prev = NULL;
        (list0)->length = (list0)->length + 1;
        if (((Object)((list0)->first)) == ((Object)(NULL)) && ((Object)((list0)->last)) == ((Object)(NULL)))
        {
            (list0)->first = item1;
            (list0)->last = item1;
            GC_FRAME_DESTROY;
            return;
        }
        ((list0)->last)->next = item1;
        (item1)->prev = (list0)->last;
        (list0)->last = item1;
    }
    GC_FRAME_DESTROY;
}

void list_unshift(ObjectList list0, Object value0)
{
    ObjectListItem item1 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(list0), GC_LOCAL(value0), GC_LOCAL(item1));
    {
        item1 = OBJECT_CTOR(ObjectListItem_impl, ObjectListItem_type);
        (item1)->value = value0;
        (item1)->next = NULL;
        (item1)->prev = NULL;
        (list0)->length = (list0)->length + 1;
        if (((Object)((list0)->first)) == ((Object)(NULL)) && ((Object)((list0)->last)) == ((Object)(NULL)))
        {
            (list0)->first = item1;
            (list0)->last = item1;
            GC_FRAME_DESTROY;
            return;
        }
        ((list0)->first)->prev = item1;
        (item1)->next = (list0)->first;
        (list0)->first = item1;
    }
    GC_FRAME_DESTROY;
}

Object list_pop(ObjectList list0)
{
    Object value1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(list0), GC_LOCAL(value1));
    {
        if (((Object)((list0)->last)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return NULL;
        }
        value1 = ((list0)->last)->value;
        (((list0)->last)->prev)->next = NULL;
        (list0)->last = ((list0)->last)->prev;
        (list0)->length = (list0)->length - 1;
        GC_FRAME_DESTROY;
        return value1;
    }
    GC_FRAME_DESTROY;
}

Object list_shift(ObjectList list0)
{
    Object value1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(list0), GC_LOCAL(value1));
    {
        if (((Object)((list0)->first)) == ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return NULL;
        }
        value1 = ((list0)->first)->value;
        (((list0)->first)->next)->prev = NULL;
        (list0)->first = ((list0)->first)->next;
        (list0)->length = (list0)->length - 1;
        GC_FRAME_DESTROY;
        return value1;
    }
    GC_FRAME_DESTROY;
}

Object list_get_value(ObjectList list0, i32 index0)
{
    i32 i1;
    ObjectListItem curr2 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(list0), GC_LOCAL(curr2));
    {
        if (index0 < 0 || index0 >= (list0)->length)
        {
            GC_FRAME_DESTROY;
            return NULL;
        }
        i1 = 0;
        curr2 = (list0)->first;
        while (i1 < index0)
        {
            curr2 = (curr2)->next;
            i1 = i1 + 1;
        }
        GC_FRAME_DESTROY;
        return (curr2)->value;
    }
    GC_FRAME_DESTROY;
}

ObjectList list_concat(ObjectList left0, ObjectList right0)
{
    ObjectList result1 = NULL;
    ObjectListIterator iter2 = NULL;
    Object value3 = NULL;
    Object value4 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(left0), GC_LOCAL(right0), GC_LOCAL(result1), GC_LOCAL(iter2), GC_LOCAL(value3), GC_LOCAL(value4));
    {
        result1 = (list_init)();
        iter2 = (list_iterator)(left0);
        while ((list_iterator_has_next)(iter2))
        {
            value3 = (list_iterator_next)(iter2);
            (list_push)(result1, value3);
        }
        iter2 = (list_iterator)(right0);
        while ((list_iterator_has_next)(iter2))
        {
            value4 = (list_iterator_next)(iter2);
            (list_push)(result1, value4);
        }
        GC_FRAME_DESTROY;
        return result1;
    }
    GC_FRAME_DESTROY;
}

ObjectList list_dup(ObjectList list0)
{
    ObjectList result1 = NULL;
    ObjectListIterator iter2 = NULL;
    Object value3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(list0), GC_LOCAL(result1), GC_LOCAL(iter2), GC_LOCAL(value3));
    {
        result1 = (list_init)();
        iter2 = (list_iterator)(list0);
        while ((list_iterator_has_next)(iter2))
        {
            value3 = (list_iterator_next)(iter2);
            (list_push)(result1, value3);
        }
        GC_FRAME_DESTROY;
        return result1;
    }
    GC_FRAME_DESTROY;
}

ObjectListIterator list_iterator(ObjectList list0)
{
    ObjectListIterator iterator1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(list0), GC_LOCAL(iterator1));
    {
        iterator1 = OBJECT_CTOR(ObjectListIterator_impl, ObjectListIterator_type);
        (iterator1)->current = (list0)->first;
        (iterator1)->index = 0;
        (iterator1)->length = (list0)->length;
        GC_FRAME_DESTROY;
        return iterator1;
    }
    GC_FRAME_DESTROY;
}

bool list_iterator_has_next(ObjectListIterator iterator0)
{
    GC_FRAME_INIT(1, GC_LOCAL(iterator0));
    {
        GC_FRAME_DESTROY;
        return (iterator0)->index < (iterator0)->length;
    }
    GC_FRAME_DESTROY;
}

Object list_iterator_next(ObjectListIterator iterator0)
{
    Object value1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(iterator0), GC_LOCAL(value1));
    {
        value1 = NULL;
        if (((Object)((iterator0)->current)) != ((Object)(NULL)))
        {
            value1 = ((iterator0)->current)->value;
            (iterator0)->current = ((iterator0)->current)->next;
        }
        (iterator0)->index = (iterator0)->index + 1;
        GC_FRAME_DESTROY;
        return value1;
    }
    GC_FRAME_DESTROY;
}

i32 entry(ObjectList args0)
{
    ObjectListIterator iter1 = NULL;
    String output2 = NULL;
    DiagnosticBag diagnostics3 = NULL;
    ObjectList units4 = NULL;
    String file5 = NULL;
    String content6 = NULL;
    i32 diagnosticCount7;
    Parser parser8 = NULL;
    CompilationUnit unit9 = NULL;
    Binder binder10 = NULL;
    BoundProgram program11 = NULL;
    Object outputFile12 = NULL;
    Emitter emitter13 = NULL;
    GC_FRAME_INIT(13, GC_LOCAL(args0), GC_LOCAL(iter1), GC_LOCAL(output2), GC_LOCAL(diagnostics3), GC_LOCAL(units4), GC_LOCAL(file5), GC_LOCAL(content6), GC_LOCAL(parser8), GC_LOCAL(unit9), GC_LOCAL(binder10), GC_LOCAL(program11), GC_LOCAL(outputFile12), GC_LOCAL(emitter13));
    {
        iter1 = (list_iterator)(args0);
        (list_iterator_next)(iter1);
        if (!(list_iterator_has_next)(iter1))
        {
            GC_FRAME_DESTROY;
            return 1;
        }
        output2 = ((String)((list_iterator_next)(iter1)));
        diagnostics3 = (diagnosticBag_init)();
        units4 = (list_init)();
        while ((list_iterator_has_next)(iter1))
        {
            file5 = ((String)((list_iterator_next)(iter1)));
            content6 = (fs_read_file)(file5);
            diagnosticCount7 = ((diagnostics3)->list)->length;
            parser8 = (parser_init)(diagnostics3, file5, content6);
            if (diagnosticCount7 != ((diagnostics3)->list)->length)
            {
                continue;
            }
            unit9 = (parse_compilation_unit)(parser8);
            (list_push)(units4, ((Object)(unit9)));
        }
        if (((diagnostics3)->list)->length > 0)
        {
            (diagnostic_print)(diagnostics3);
            GC_FRAME_DESTROY;
            return 1;
        }
        if ((units4)->length == 0)
        {
            GC_FRAME_DESTROY;
            return 1;
        }
        binder10 = (binder_init)(units4);
        program11 = (binder_bind)(binder10);
        if (((diagnostics3)->list)->length > 0)
        {
            (diagnostic_print)(diagnostics3);
            GC_FRAME_DESTROY;
            return 1;
        }
        outputFile12 = (fs_open_file)(output2);
        emitter13 = (emitter_init)(outputFile12);
        (emit_program)(emitter13, program11);
        (fs_close_file)(outputFile12);
        GC_FRAME_DESTROY;
        return 0;
    }
    GC_FRAME_DESTROY;
}

void PANIC(String message0)
{
    GC_FRAME_INIT(1, GC_LOCAL(message0));
    {
        (string_dump)(message0);
        (exit)(1);
    }
    GC_FRAME_DESTROY;
}

Parser parser_init(DiagnosticBag diagnostics0, String filename0, String content0)
{
    Lexer lexer1 = NULL;
    ObjectList tokens2 = NULL;
    Token token3 = NULL;
    Parser parser4 = NULL;
    GC_FRAME_INIT(7, GC_LOCAL(diagnostics0), GC_LOCAL(filename0), GC_LOCAL(content0), GC_LOCAL(lexer1), GC_LOCAL(tokens2), GC_LOCAL(token3), GC_LOCAL(parser4));
    {
        lexer1 = (lexer_init)(diagnostics0, filename0, content0);
        tokens2 = (list_init)();
        token3 = (lexer_next_token)(lexer1);
        while (((i32)((token3)->kind)) != ((i32)(TokenKind_EOF)))
        {
            if (((i32)((token3)->kind)) != ((i32)(TokenKind_ERROR)) && ((i32)((token3)->kind)) != ((i32)(TokenKind_WHITESPACE)) && ((i32)((token3)->kind)) != ((i32)(TokenKind_SINGLE_COMMENT)) && ((i32)((token3)->kind)) != ((i32)(TokenKind_MULTI_COMMENT)))
            {
                (list_push)(tokens2, ((Object)(token3)));
            }
            token3 = (lexer_next_token)(lexer1);
        }
        (list_push)(tokens2, ((Object)(token3)));
        lexer1 = NULL;
        parser4 = OBJECT_CTOR(Parser_impl, Parser_type);
        (parser4)->diagnostics = diagnostics0;
        (parser4)->tokens = tokens2;
        (parser4)->position = 0;
        GC_FRAME_DESTROY;
        return parser4;
    }
    GC_FRAME_DESTROY;
}

Token current_token(Parser parser0)
{
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        if ((parser0)->position >= ((parser0)->tokens)->length)
        {
            GC_FRAME_DESTROY;
            return ((Token)((list_get_value)((parser0)->tokens, ((parser0)->tokens)->length - 1)));
        }
        GC_FRAME_DESTROY;
        return ((Token)((list_get_value)((parser0)->tokens, (parser0)->position)));
    }
    GC_FRAME_DESTROY;
}

Token peek_token(Parser parser0)
{
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        if ((parser0)->position + 1 >= ((parser0)->tokens)->length)
        {
            GC_FRAME_DESTROY;
            return ((Token)((list_get_value)((parser0)->tokens, ((parser0)->tokens)->length - 1)));
        }
        GC_FRAME_DESTROY;
        return ((Token)((list_get_value)((parser0)->tokens, (parser0)->position + 1)));
    }
    GC_FRAME_DESTROY;
}

Token next_token(Parser parser0)
{
    Token curr1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(parser0), GC_LOCAL(curr1));
    {
        curr1 = (current_token)(parser0);
        (parser0)->position = (parser0)->position + 1;
        GC_FRAME_DESTROY;
        return curr1;
    }
    GC_FRAME_DESTROY;
}

Token match_token(Parser parser0, TokenKind kind0)
{
    Token curr1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(parser0), GC_LOCAL(curr1));
    {
        curr1 = (current_token)(parser0);
        if (((i32)((curr1)->kind)) != ((i32)(kind0)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Expected token, was not received", 32));
        }
        (parser0)->position = (parser0)->position + 1;
        GC_FRAME_DESTROY;
        return curr1;
    }
    GC_FRAME_DESTROY;
}

Token match_token2(Parser parser0, TokenKind kind10, TokenKind kind20)
{
    Token curr1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(parser0), GC_LOCAL(curr1));
    {
        curr1 = (current_token)(parser0);
        if (((i32)((curr1)->kind)) != ((i32)(kind10)) && ((i32)((curr1)->kind)) != ((i32)(kind20)))
        {
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Expected token, was not received", 32));
        }
        (parser0)->position = (parser0)->position + 1;
        GC_FRAME_DESTROY;
        return curr1;
    }
    GC_FRAME_DESTROY;
}

bool parser_is_eof(Parser parser0)
{
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        GC_FRAME_DESTROY;
        return (parser0)->position >= ((parser0)->tokens)->length;
    }
    GC_FRAME_DESTROY;
}

i32 unary_operator_precedence(TokenKind operator0)
{
    {
        if (((i32)(operator0)) == ((i32)(TokenKind_BANG)) || ((i32)(operator0)) == ((i32)(TokenKind_PLUS)) || ((i32)(operator0)) == ((i32)(TokenKind_MINUS)))
        {
            return 6;
        }
        return 0;
    }
}

i32 binary_operator_precedence(TokenKind operator0)
{
    {
        if (((i32)(operator0)) == ((i32)(TokenKind_STAR)) || ((i32)(operator0)) == ((i32)(TokenKind_SLASH)))
        {
            return 5;
        }
        if (((i32)(operator0)) == ((i32)(TokenKind_PLUS)) || ((i32)(operator0)) == ((i32)(TokenKind_MINUS)))
        {
            return 4;
        }
        if (((i32)(operator0)) == ((i32)(TokenKind_EQUALS_EQUALS)) || ((i32)(operator0)) == ((i32)(TokenKind_BANG_EQUALS)) || ((i32)(operator0)) == ((i32)(TokenKind_LANGLE)) || ((i32)(operator0)) == ((i32)(TokenKind_LANGLE_EQUALS)) || ((i32)(operator0)) == ((i32)(TokenKind_RANGLE)) || ((i32)(operator0)) == ((i32)(TokenKind_RANGLE_EQUALS)))
        {
            return 3;
        }
        if (((i32)(operator0)) == ((i32)(TokenKind_AND_AND)))
        {
            return 2;
        }
        if (((i32)(operator0)) == ((i32)(TokenKind_OR_OR)))
        {
            return 1;
        }
        return 0;
    }
}

ObjectList parse_semicolon_block(Parser parser0, bool expectAtLeastOne0)
{
    ObjectList list1 = NULL;
    Token token2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(list1), GC_LOCAL(token2));
    {
        list1 = (list_init)();
        if (expectAtLeastOne0)
        {
            token2 = (match_token)(parser0, TokenKind_SEMICOLON);
            (list_push)(list1, ((Object)(token2)));
        }
        while (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_SEMICOLON)) && !(parser_is_eof)(parser0))
        {
            (list_push)(list1, ((Object)((next_token)(parser0))));
        }
        GC_FRAME_DESTROY;
        return list1;
    }
    GC_FRAME_DESTROY;
}

TypeSignature parse_type_signature(Parser parser0)
{
    Token identifier1 = NULL;
    TypeSignatureDynamic dynamic2 = NULL;
    Token lAngle3 = NULL;
    ObjectList generics4 = NULL;
    TypeSignature typeSignature5 = NULL;
    Token comma6 = NULL;
    TypeSignatureDynamicGeneric generic7 = NULL;
    Token rAngle8 = NULL;
    TypeSignature typeSignature9 = NULL;
    GC_FRAME_INIT(10, GC_LOCAL(parser0), GC_LOCAL(identifier1), GC_LOCAL(dynamic2), GC_LOCAL(lAngle3), GC_LOCAL(generics4), GC_LOCAL(typeSignature5), GC_LOCAL(comma6), GC_LOCAL(generic7), GC_LOCAL(rAngle8), GC_LOCAL(typeSignature9));
    {
        identifier1 = (match_token)(parser0, TokenKind_IDENTIFIER);
        dynamic2 = NULL;
        if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_LANGLE)))
        {
            lAngle3 = (next_token)(parser0);
            generics4 = (list_init)();
            while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RANGLE)) && !(parser_is_eof)(parser0))
            {
                typeSignature5 = (parse_type_signature)(parser0);
                comma6 = NULL;
                if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RANGLE)))
                {
                    comma6 = (match_token)(parser0, TokenKind_COMMA);
                }
                generic7 = OBJECT_CTOR(TypeSignatureDynamicGeneric_impl, TypeSignatureDynamicGeneric_type);
                (generic7)->typeSignature = typeSignature5;
                (generic7)->comma = comma6;
                (list_push)(generics4, ((Object)(generic7)));
            }
            if ((generics4)->length == 0)
            {
                (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Generic count cannot be zero", 28));
            }
            rAngle8 = (match_token)(parser0, TokenKind_RANGLE);
            dynamic2 = OBJECT_CTOR(TypeSignatureDynamic_impl, TypeSignatureDynamic_type);
            (dynamic2)->lAngle = lAngle3;
            (dynamic2)->generics = generics4;
            (dynamic2)->rAngle = rAngle8;
        }
        typeSignature9 = OBJECT_CTOR(TypeSignature_impl, TypeSignature_type);
        (typeSignature9)->identifier = identifier1;
        (typeSignature9)->dynamic = dynamic2;
        GC_FRAME_DESTROY;
        return typeSignature9;
    }
    GC_FRAME_DESTROY;
}

TypeClause parse_type_clause(Parser parser0)
{
    Token colon1 = NULL;
    TypeSignature typeSignature2 = NULL;
    TypeClause typeClause3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(parser0), GC_LOCAL(colon1), GC_LOCAL(typeSignature2), GC_LOCAL(typeClause3));
    {
        colon1 = (match_token)(parser0, TokenKind_COLON);
        typeSignature2 = (parse_type_signature)(parser0);
        typeClause3 = OBJECT_CTOR(TypeClause_impl, TypeClause_type);
        (typeClause3)->colon = colon1;
        (typeClause3)->typeSignature = typeSignature2;
        GC_FRAME_DESTROY;
        return typeClause3;
    }
    GC_FRAME_DESTROY;
}

CtorExpression parse_ctor_expression(Parser parser0)
{
    Token keyword1 = NULL;
    TypeSignature typeSignature2 = NULL;
    Token lParen3 = NULL;
    Token rParen4 = NULL;
    CtorExpression ctorExpression5 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(typeSignature2), GC_LOCAL(lParen3), GC_LOCAL(rParen4), GC_LOCAL(ctorExpression5));
    {
        keyword1 = (match_token)(parser0, TokenKind_NEW_KEYWORD);
        typeSignature2 = (parse_type_signature)(parser0);
        lParen3 = (match_token)(parser0, TokenKind_LPAREN);
        rParen4 = (match_token)(parser0, TokenKind_RPAREN);
        ctorExpression5 = OBJECT_CTOR(CtorExpression_impl, CtorExpression_type);
        (ctorExpression5)->keyword = keyword1;
        (ctorExpression5)->typeSignature = typeSignature2;
        (ctorExpression5)->lParen = lParen3;
        (ctorExpression5)->rParen = rParen4;
        GC_FRAME_DESTROY;
        return ctorExpression5;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_integer_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token)(parser0, TokenKind_INTEGER_LITERAL);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_char_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token)(parser0, TokenKind_CHAR_LITERAL);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_string_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token)(parser0, TokenKind_STRING_LITERAL);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_boolean_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token2)(parser0, TokenKind_FALSE_KEYWORD, TokenKind_TRUE_KEYWORD);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_identifier_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token)(parser0, TokenKind_IDENTIFIER);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

ParenExpression parse_paren_expression(Parser parser0)
{
    Token lParen1 = NULL;
    Object expression2 = NULL;
    Token rParen3 = NULL;
    ParenExpression parenExpression4 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(parser0), GC_LOCAL(lParen1), GC_LOCAL(expression2), GC_LOCAL(rParen3), GC_LOCAL(parenExpression4));
    {
        lParen1 = (match_token)(parser0, TokenKind_LPAREN);
        expression2 = (parse_expression)(parser0);
        rParen3 = (match_token)(parser0, TokenKind_RPAREN);
        parenExpression4 = OBJECT_CTOR(ParenExpression_impl, ParenExpression_type);
        (parenExpression4)->lParen = lParen1;
        (parenExpression4)->expression = expression2;
        (parenExpression4)->rParen = rParen3;
        GC_FRAME_DESTROY;
        return parenExpression4;
    }
    GC_FRAME_DESTROY;
}

CastExpression parse_cast_expression(Parser parser0)
{
    Token lAngle1 = NULL;
    TypeSignature typeSignature2 = NULL;
    Token rAngle3 = NULL;
    Object expression4 = NULL;
    CastExpression castExpression5 = NULL;
    GC_FRAME_INIT(6, GC_LOCAL(parser0), GC_LOCAL(lAngle1), GC_LOCAL(typeSignature2), GC_LOCAL(rAngle3), GC_LOCAL(expression4), GC_LOCAL(castExpression5));
    {
        lAngle1 = (match_token)(parser0, TokenKind_LANGLE);
        typeSignature2 = (parse_type_signature)(parser0);
        rAngle3 = (match_token)(parser0, TokenKind_RANGLE);
        expression4 = (parse_expression)(parser0);
        castExpression5 = OBJECT_CTOR(CastExpression_impl, CastExpression_type);
        (castExpression5)->lAngle = lAngle1;
        (castExpression5)->typeSignature = typeSignature2;
        (castExpression5)->rAngle = rAngle3;
        (castExpression5)->expression = expression4;
        GC_FRAME_DESTROY;
        return castExpression5;
    }
    GC_FRAME_DESTROY;
}

LiteralExpression parse_null_expression(Parser parser0)
{
    Token value1 = NULL;
    LiteralExpression literalExpression2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(parser0), GC_LOCAL(value1), GC_LOCAL(literalExpression2));
    {
        value1 = (match_token)(parser0, TokenKind_NULL_KEYWORD);
        literalExpression2 = OBJECT_CTOR(LiteralExpression_impl, LiteralExpression_type);
        (literalExpression2)->value = value1;
        GC_FRAME_DESTROY;
        return literalExpression2;
    }
    GC_FRAME_DESTROY;
}

Object parse_base_expression(Parser parser0)
{
    TokenKind kind1;
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        kind1 = ((current_token)(parser0))->kind;
        if (((i32)(kind1)) == ((i32)(TokenKind_INTEGER_LITERAL)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_integer_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_CHAR_LITERAL)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_char_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_STRING_LITERAL)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_string_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_TRUE_KEYWORD)) || ((i32)(kind1)) == ((i32)(TokenKind_FALSE_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_boolean_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_IDENTIFIER)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_identifier_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_LANGLE)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_cast_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_LPAREN)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_paren_expression)(parser0)));
        }
        if (((i32)(kind1)) == ((i32)(TokenKind_NULL_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_null_expression)(parser0)));
        }
        (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"(parser) Unknown expression", 27));
    }
    GC_FRAME_DESTROY;
}

Object parse_wrapper_expression(Parser parser0)
{
    Object left1 = NULL;
    Token lParen2 = NULL;
    ObjectList arguments3 = NULL;
    Object expression4 = NULL;
    Token comma5 = NULL;
    CallExpressionArgument argument6 = NULL;
    Token rParen7 = NULL;
    CallExpression callExpression8 = NULL;
    Token dot9 = NULL;
    Token identifier10 = NULL;
    MemberExpression memberExpression11 = NULL;
    Token keyword12 = NULL;
    TypeSignature typeSignature13 = NULL;
    IsExpression isExpression14 = NULL;
    GC_FRAME_INIT(15, GC_LOCAL(parser0), GC_LOCAL(left1), GC_LOCAL(lParen2), GC_LOCAL(arguments3), GC_LOCAL(expression4), GC_LOCAL(comma5), GC_LOCAL(argument6), GC_LOCAL(rParen7), GC_LOCAL(callExpression8), GC_LOCAL(dot9), GC_LOCAL(identifier10), GC_LOCAL(memberExpression11), GC_LOCAL(keyword12), GC_LOCAL(typeSignature13), GC_LOCAL(isExpression14));
    {
        left1 = (parse_base_expression)(parser0);
        while (1)
        {
            if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_LPAREN)))
            {
                lParen2 = (next_token)(parser0);
                arguments3 = (list_init)();
                while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)) && !(parser_is_eof)(parser0))
                {
                    expression4 = (parse_expression)(parser0);
                    comma5 = NULL;
                    if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)))
                    {
                        comma5 = (match_token)(parser0, TokenKind_COMMA);
                    }
                    argument6 = OBJECT_CTOR(CallExpressionArgument_impl, CallExpressionArgument_type);
                    (argument6)->expression = expression4;
                    (argument6)->comma = comma5;
                    (list_push)(arguments3, ((Object)(argument6)));
                }
                rParen7 = (match_token)(parser0, TokenKind_RPAREN);
                callExpression8 = OBJECT_CTOR(CallExpression_impl, CallExpression_type);
                (callExpression8)->callee = left1;
                (callExpression8)->lParen = lParen2;
                (callExpression8)->arguments = arguments3;
                (callExpression8)->rParen = rParen7;
                left1 = ((Object)(callExpression8));
                continue;
            }
            if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_DOT)))
            {
                dot9 = (match_token)(parser0, TokenKind_DOT);
                identifier10 = (match_token)(parser0, TokenKind_IDENTIFIER);
                memberExpression11 = OBJECT_CTOR(MemberExpression_impl, MemberExpression_type);
                (memberExpression11)->object = left1;
                (memberExpression11)->dot = dot9;
                (memberExpression11)->identifier = identifier10;
                left1 = ((Object)(memberExpression11));
                continue;
            }
            if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_IS_KEYWORD)))
            {
                keyword12 = (next_token)(parser0);
                typeSignature13 = (parse_type_signature)(parser0);
                isExpression14 = OBJECT_CTOR(IsExpression_impl, IsExpression_type);
                (isExpression14)->left = left1;
                (isExpression14)->keyword = keyword12;
                (isExpression14)->typeSignature = typeSignature13;
                left1 = ((Object)(isExpression14));
                continue;
            }
            break;
        }
        GC_FRAME_DESTROY;
        return left1;
    }
    GC_FRAME_DESTROY;
}

Object parse_binary_expression(Parser parser0, i32 parentPrecedence0)
{
    Object left1 = NULL;
    i32 unaryIndex2;
    Token operator3 = NULL;
    Object right4 = NULL;
    UnaryExpression unaryExpression5 = NULL;
    i32 binaryIndex6;
    Token operator7 = NULL;
    Object right8 = NULL;
    BinaryExpression binaryExpression9 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(parser0), GC_LOCAL(left1), GC_LOCAL(operator3), GC_LOCAL(right4), GC_LOCAL(unaryExpression5), GC_LOCAL(operator7), GC_LOCAL(right8), GC_LOCAL(binaryExpression9));
    {
        unaryIndex2 = (unary_operator_precedence)(((current_token)(parser0))->kind);
        if (unaryIndex2 != 0 && unaryIndex2 >= parentPrecedence0)
        {
            operator3 = (next_token)(parser0);
            right4 = (parse_binary_expression)(parser0, unaryIndex2);
            unaryExpression5 = OBJECT_CTOR(UnaryExpression_impl, UnaryExpression_type);
            (unaryExpression5)->operator = operator3;
            (unaryExpression5)->right = right4;
            left1 = ((Object)(unaryExpression5));
        }
        else
        {
            left1 = (parse_wrapper_expression)(parser0);
        }
        while (1)
        {
            binaryIndex6 = (binary_operator_precedence)(((current_token)(parser0))->kind);
            if (binaryIndex6 == 0 || binaryIndex6 <= parentPrecedence0)
            {
                break;
            }
            operator7 = (next_token)(parser0);
            right8 = (parse_binary_expression)(parser0, binaryIndex6);
            binaryExpression9 = OBJECT_CTOR(BinaryExpression_impl, BinaryExpression_type);
            (binaryExpression9)->left = left1;
            (binaryExpression9)->operator = operator7;
            (binaryExpression9)->right = right8;
            left1 = ((Object)(binaryExpression9));
        }
        GC_FRAME_DESTROY;
        return left1;
    }
    GC_FRAME_DESTROY;
}

Object parse_assignment_expression(Parser parser0)
{
    Object left1 = NULL;
    Token operator2 = NULL;
    Object right3 = NULL;
    AssignmentExpression assignmentExpression4 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(parser0), GC_LOCAL(left1), GC_LOCAL(operator2), GC_LOCAL(right3), GC_LOCAL(assignmentExpression4));
    {
        left1 = (parse_binary_expression)(parser0, 0);
        if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_EQUALS)))
        {
            operator2 = (next_token)(parser0);
            right3 = (parse_expression)(parser0);
            assignmentExpression4 = OBJECT_CTOR(AssignmentExpression_impl, AssignmentExpression_type);
            (assignmentExpression4)->left = left1;
            (assignmentExpression4)->operator = operator2;
            (assignmentExpression4)->right = right3;
            GC_FRAME_DESTROY;
            return ((Object)(assignmentExpression4));
        }
        GC_FRAME_DESTROY;
        return left1;
    }
    GC_FRAME_DESTROY;
}

Object parse_expression(Parser parser0)
{
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_NEW_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_ctor_expression)(parser0)));
        }
        GC_FRAME_DESTROY;
        return (parse_assignment_expression)(parser0);
    }
    GC_FRAME_DESTROY;
}

BlockStatement parse_block_statement(Parser parser0)
{
    Token lBrace1 = NULL;
    ObjectList statements2 = NULL;
    Object statement3 = NULL;
    Token rBrace4 = NULL;
    ObjectList semicolons5 = NULL;
    BlockStatement blockStatement6 = NULL;
    GC_FRAME_INIT(7, GC_LOCAL(parser0), GC_LOCAL(lBrace1), GC_LOCAL(statements2), GC_LOCAL(statement3), GC_LOCAL(rBrace4), GC_LOCAL(semicolons5), GC_LOCAL(blockStatement6));
    {
        lBrace1 = (match_token)(parser0, TokenKind_LBRACE);
        statements2 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RBRACE)) && !(parser_is_eof)(parser0))
        {
            statement3 = (parse_statement)(parser0);
            (list_push)(statements2, statement3);
        }
        rBrace4 = (match_token)(parser0, TokenKind_RBRACE);
        semicolons5 = (parse_semicolon_block)(parser0, 0);
        blockStatement6 = OBJECT_CTOR(BlockStatement_impl, BlockStatement_type);
        (blockStatement6)->lBrace = lBrace1;
        (blockStatement6)->statements = statements2;
        (blockStatement6)->rBrace = rBrace4;
        (blockStatement6)->semicolons = semicolons5;
        GC_FRAME_DESTROY;
        return blockStatement6;
    }
    GC_FRAME_DESTROY;
}

VariableStatement parse_variable_statement(Parser parser0)
{
    Token keyword1 = NULL;
    Token identifier2 = NULL;
    TypeClause typeClause3 = NULL;
    Token equals4 = NULL;
    Object initializer5 = NULL;
    ObjectList semicolons6 = NULL;
    VariableStatement variableStatement7 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(identifier2), GC_LOCAL(typeClause3), GC_LOCAL(equals4), GC_LOCAL(initializer5), GC_LOCAL(semicolons6), GC_LOCAL(variableStatement7));
    {
        keyword1 = (match_token)(parser0, TokenKind_LET_KEYWORD);
        identifier2 = (match_token)(parser0, TokenKind_IDENTIFIER);
        typeClause3 = (parse_type_clause)(parser0);
        equals4 = NULL;
        initializer5 = NULL;
        if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_EQUALS)))
        {
            equals4 = (next_token)(parser0);
            initializer5 = (parse_expression)(parser0);
        }
        semicolons6 = (parse_semicolon_block)(parser0, 1);
        variableStatement7 = OBJECT_CTOR(VariableStatement_impl, VariableStatement_type);
        (variableStatement7)->keyword = keyword1;
        (variableStatement7)->identifier = identifier2;
        (variableStatement7)->typeClause = typeClause3;
        (variableStatement7)->equals = equals4;
        (variableStatement7)->initializer = initializer5;
        (variableStatement7)->semicolons = semicolons6;
        GC_FRAME_DESTROY;
        return variableStatement7;
    }
    GC_FRAME_DESTROY;
}

IfStatement parse_if_statement(Parser parser0)
{
    Token keyword1 = NULL;
    Token lParen2 = NULL;
    Object condition3 = NULL;
    Token rParen4 = NULL;
    Object thenCase5 = NULL;
    ElseCase elseCase6 = NULL;
    Token keyword7 = NULL;
    Object thenCase8 = NULL;
    IfStatement ifStatement9 = NULL;
    GC_FRAME_INIT(10, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(lParen2), GC_LOCAL(condition3), GC_LOCAL(rParen4), GC_LOCAL(thenCase5), GC_LOCAL(elseCase6), GC_LOCAL(keyword7), GC_LOCAL(thenCase8), GC_LOCAL(ifStatement9));
    {
        keyword1 = (match_token)(parser0, TokenKind_IF_KEYWORD);
        lParen2 = (match_token)(parser0, TokenKind_LPAREN);
        condition3 = (parse_expression)(parser0);
        rParen4 = (match_token)(parser0, TokenKind_RPAREN);
        thenCase5 = (parse_statement)(parser0);
        elseCase6 = NULL;
        if (((i32)(((current_token)(parser0))->kind)) == ((i32)(TokenKind_ELSE_KEYWORD)))
        {
            keyword7 = (next_token)(parser0);
            thenCase8 = (parse_statement)(parser0);
            elseCase6 = OBJECT_CTOR(ElseCase_impl, ElseCase_type);
            (elseCase6)->keyword = keyword7;
            (elseCase6)->thenCase = thenCase8;
        }
        ifStatement9 = OBJECT_CTOR(IfStatement_impl, IfStatement_type);
        (ifStatement9)->keyword = keyword1;
        (ifStatement9)->lParen = lParen2;
        (ifStatement9)->condition = condition3;
        (ifStatement9)->rParen = rParen4;
        (ifStatement9)->thenCase = thenCase5;
        (ifStatement9)->elseCase = elseCase6;
        GC_FRAME_DESTROY;
        return ifStatement9;
    }
    GC_FRAME_DESTROY;
}

WhileStatement parse_while_statement(Parser parser0)
{
    Token keyword1 = NULL;
    Token lParen2 = NULL;
    Object condition3 = NULL;
    Token rParen4 = NULL;
    Object body5 = NULL;
    WhileStatement whileStatement6 = NULL;
    GC_FRAME_INIT(7, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(lParen2), GC_LOCAL(condition3), GC_LOCAL(rParen4), GC_LOCAL(body5), GC_LOCAL(whileStatement6));
    {
        keyword1 = (match_token)(parser0, TokenKind_WHILE_KEYWORD);
        lParen2 = (match_token)(parser0, TokenKind_LPAREN);
        condition3 = (parse_expression)(parser0);
        rParen4 = (match_token)(parser0, TokenKind_RPAREN);
        body5 = (parse_statement)(parser0);
        whileStatement6 = OBJECT_CTOR(WhileStatement_impl, WhileStatement_type);
        (whileStatement6)->keyword = keyword1;
        (whileStatement6)->lParen = lParen2;
        (whileStatement6)->condition = condition3;
        (whileStatement6)->rParen = ((Object)(rParen4));
        (whileStatement6)->body = body5;
        GC_FRAME_DESTROY;
        return whileStatement6;
    }
    GC_FRAME_DESTROY;
}

ReturnStatement parse_return_statement(Parser parser0)
{
    Token keyword1 = NULL;
    Object value2 = NULL;
    ObjectList semicolons3 = NULL;
    ReturnStatement returnStatement4 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(value2), GC_LOCAL(semicolons3), GC_LOCAL(returnStatement4));
    {
        keyword1 = (match_token)(parser0, TokenKind_RETURN_KEYWORD);
        value2 = NULL;
        if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_SEMICOLON)))
        {
            value2 = (parse_expression)(parser0);
        }
        semicolons3 = (parse_semicolon_block)(parser0, 1);
        returnStatement4 = OBJECT_CTOR(ReturnStatement_impl, ReturnStatement_type);
        (returnStatement4)->keyword = keyword1;
        (returnStatement4)->value = value2;
        (returnStatement4)->semicolons = semicolons3;
        GC_FRAME_DESTROY;
        return returnStatement4;
    }
    GC_FRAME_DESTROY;
}

BreakStatement parse_break_statement(Parser parser0)
{
    Token keyword1 = NULL;
    ObjectList semicolons2 = NULL;
    BreakStatement breakStatement3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(semicolons2), GC_LOCAL(breakStatement3));
    {
        keyword1 = (match_token)(parser0, TokenKind_BREAK_KEYWORD);
        semicolons2 = (parse_semicolon_block)(parser0, 1);
        breakStatement3 = OBJECT_CTOR(BreakStatement_impl, BreakStatement_type);
        (breakStatement3)->keyword = keyword1;
        (breakStatement3)->semicolons = semicolons2;
        GC_FRAME_DESTROY;
        return breakStatement3;
    }
    GC_FRAME_DESTROY;
}

ContinueStatement parse_continue_statement(Parser parser0)
{
    Token keyword1 = NULL;
    ObjectList semicolons2 = NULL;
    ContinueStatement breakStatement3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(semicolons2), GC_LOCAL(breakStatement3));
    {
        keyword1 = (match_token)(parser0, TokenKind_CONTINUE_KEYWORD);
        semicolons2 = (parse_semicolon_block)(parser0, 1);
        breakStatement3 = OBJECT_CTOR(ContinueStatement_impl, ContinueStatement_type);
        (breakStatement3)->keyword = keyword1;
        (breakStatement3)->semicolons = semicolons2;
        GC_FRAME_DESTROY;
        return breakStatement3;
    }
    GC_FRAME_DESTROY;
}

ExpressionStatement parse_expression_statement(Parser parser0)
{
    Object expression1 = NULL;
    ObjectList semicolons2 = NULL;
    ExpressionStatement expressionStatement3 = NULL;
    GC_FRAME_INIT(4, GC_LOCAL(parser0), GC_LOCAL(expression1), GC_LOCAL(semicolons2), GC_LOCAL(expressionStatement3));
    {
        expression1 = (parse_expression)(parser0);
        semicolons2 = (parse_semicolon_block)(parser0, 1);
        expressionStatement3 = OBJECT_CTOR(ExpressionStatement_impl, ExpressionStatement_type);
        (expressionStatement3)->expression = expression1;
        (expressionStatement3)->semicolons = semicolons2;
        GC_FRAME_DESTROY;
        return expressionStatement3;
    }
    GC_FRAME_DESTROY;
}

Object parse_statement(Parser parser0)
{
    TokenKind kind1;
    GC_FRAME_INIT(1, GC_LOCAL(parser0));
    {
        kind1 = ((current_token)(parser0))->kind;
        if (((i32)(kind1)) == ((i32)(TokenKind_LBRACE)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_block_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_LET_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_variable_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_IF_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_if_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_WHILE_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_while_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_RETURN_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_return_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_BREAK_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_break_statement)(parser0)));
        }
        else
        if (((i32)(kind1)) == ((i32)(TokenKind_CONTINUE_KEYWORD)))
        {
            GC_FRAME_DESTROY;
            return ((Object)((parse_continue_statement)(parser0)));
        }
        GC_FRAME_DESTROY;
        return ((Object)((parse_expression_statement)(parser0)));
    }
    GC_FRAME_DESTROY;
}

ExternFunctionMember parse_extern_function_member(Parser parser0)
{
    Token extern_1 = NULL;
    Token keyword2 = NULL;
    Token identifier3 = NULL;
    Token lParen4 = NULL;
    ObjectList parameters5 = NULL;
    Token identifier6 = NULL;
    TypeClause typeClause7 = NULL;
    Token comma8 = NULL;
    FunctionMemberParameter parameter9 = NULL;
    Token rParen10 = NULL;
    TypeClause returnType11 = NULL;
    ObjectList semicolons12 = NULL;
    ExternFunctionMember externFunctionMember13 = NULL;
    GC_FRAME_INIT(14, GC_LOCAL(parser0), GC_LOCAL(extern_1), GC_LOCAL(keyword2), GC_LOCAL(identifier3), GC_LOCAL(lParen4), GC_LOCAL(parameters5), GC_LOCAL(identifier6), GC_LOCAL(typeClause7), GC_LOCAL(comma8), GC_LOCAL(parameter9), GC_LOCAL(rParen10), GC_LOCAL(returnType11), GC_LOCAL(semicolons12), GC_LOCAL(externFunctionMember13));
    {
        extern_1 = (match_token)(parser0, TokenKind_EXTERN_KEYWORD);
        keyword2 = (match_token)(parser0, TokenKind_FUNCTION_KEYWORD);
        identifier3 = (match_token)(parser0, TokenKind_IDENTIFIER);
        lParen4 = (match_token)(parser0, TokenKind_LPAREN);
        parameters5 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)) && !(parser_is_eof)(parser0))
        {
            identifier6 = (match_token)(parser0, TokenKind_IDENTIFIER);
            typeClause7 = (parse_type_clause)(parser0);
            comma8 = NULL;
            if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)))
            {
                comma8 = (match_token)(parser0, TokenKind_COMMA);
            }
            parameter9 = OBJECT_CTOR(FunctionMemberParameter_impl, FunctionMemberParameter_type);
            (parameter9)->identifier = identifier6;
            (parameter9)->typeClause = typeClause7;
            (parameter9)->comma = comma8;
            (list_push)(parameters5, ((Object)(parameter9)));
        }
        rParen10 = (match_token)(parser0, TokenKind_RPAREN);
        returnType11 = (parse_type_clause)(parser0);
        semicolons12 = (parse_semicolon_block)(parser0, 1);
        externFunctionMember13 = OBJECT_CTOR(ExternFunctionMember_impl, ExternFunctionMember_type);
        (externFunctionMember13)->extern_ = extern_1;
        (externFunctionMember13)->keyword = keyword2;
        (externFunctionMember13)->identifier = identifier3;
        (externFunctionMember13)->lParen = lParen4;
        (externFunctionMember13)->parameters = parameters5;
        (externFunctionMember13)->rParen = rParen10;
        (externFunctionMember13)->returnType = returnType11;
        (externFunctionMember13)->semicolons = semicolons12;
        GC_FRAME_DESTROY;
        return externFunctionMember13;
    }
    GC_FRAME_DESTROY;
}

ExternTypeMember parse_extern_type_member(Parser parser0)
{
    Token extern_1 = NULL;
    Token keyword2 = NULL;
    Token identifier3 = NULL;
    Token lBrace4 = NULL;
    ObjectList items5 = NULL;
    Token identifier6 = NULL;
    TypeClause typeClause7 = NULL;
    ObjectList semicolons8 = NULL;
    TypeMemberItem item9 = NULL;
    Token rBrace10 = NULL;
    ObjectList semicolons11 = NULL;
    ExternTypeMember externTypeMember12 = NULL;
    GC_FRAME_INIT(13, GC_LOCAL(parser0), GC_LOCAL(extern_1), GC_LOCAL(keyword2), GC_LOCAL(identifier3), GC_LOCAL(lBrace4), GC_LOCAL(items5), GC_LOCAL(identifier6), GC_LOCAL(typeClause7), GC_LOCAL(semicolons8), GC_LOCAL(item9), GC_LOCAL(rBrace10), GC_LOCAL(semicolons11), GC_LOCAL(externTypeMember12));
    {
        extern_1 = (match_token)(parser0, TokenKind_EXTERN_KEYWORD);
        keyword2 = (match_token)(parser0, TokenKind_TYPE_KEYWORD);
        identifier3 = (match_token)(parser0, TokenKind_IDENTIFIER);
        lBrace4 = (match_token)(parser0, TokenKind_LBRACE);
        items5 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RBRACE)) && !(parser_is_eof)(parser0))
        {
            identifier6 = (match_token)(parser0, TokenKind_IDENTIFIER);
            typeClause7 = (parse_type_clause)(parser0);
            semicolons8 = (parse_semicolon_block)(parser0, 1);
            item9 = OBJECT_CTOR(TypeMemberItem_impl, TypeMemberItem_type);
            (item9)->identifier = identifier6;
            (item9)->typeClause = typeClause7;
            (item9)->semicolons = semicolons8;
            (list_push)(items5, ((Object)(item9)));
        }
        rBrace10 = (match_token)(parser0, TokenKind_RBRACE);
        semicolons11 = (parse_semicolon_block)(parser0, 0);
        externTypeMember12 = OBJECT_CTOR(ExternTypeMember_impl, ExternTypeMember_type);
        (externTypeMember12)->extern_ = extern_1;
        (externTypeMember12)->keyword = keyword2;
        (externTypeMember12)->identifier = identifier3;
        (externTypeMember12)->lBrace = lBrace4;
        (externTypeMember12)->items = items5;
        (externTypeMember12)->rBrace = rBrace10;
        (externTypeMember12)->semicolons = semicolons11;
        GC_FRAME_DESTROY;
        return externTypeMember12;
    }
    GC_FRAME_DESTROY;
}

FunctionMember parse_function_member(Parser parser0)
{
    Token keyword1 = NULL;
    Token identifier2 = NULL;
    Token lParen3 = NULL;
    ObjectList parameters4 = NULL;
    Token identifier5 = NULL;
    TypeClause typeClause6 = NULL;
    Token comma7 = NULL;
    FunctionMemberParameter parameter8 = NULL;
    Token rParen9 = NULL;
    TypeClause returnType10 = NULL;
    BlockStatement body11 = NULL;
    FunctionMember functionMember12 = NULL;
    GC_FRAME_INIT(13, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(identifier2), GC_LOCAL(lParen3), GC_LOCAL(parameters4), GC_LOCAL(identifier5), GC_LOCAL(typeClause6), GC_LOCAL(comma7), GC_LOCAL(parameter8), GC_LOCAL(rParen9), GC_LOCAL(returnType10), GC_LOCAL(body11), GC_LOCAL(functionMember12));
    {
        keyword1 = (match_token)(parser0, TokenKind_FUNCTION_KEYWORD);
        identifier2 = (match_token)(parser0, TokenKind_IDENTIFIER);
        lParen3 = (match_token)(parser0, TokenKind_LPAREN);
        parameters4 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)) && !(parser_is_eof)(parser0))
        {
            identifier5 = (match_token)(parser0, TokenKind_IDENTIFIER);
            typeClause6 = (parse_type_clause)(parser0);
            comma7 = NULL;
            if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RPAREN)))
            {
                comma7 = (match_token)(parser0, TokenKind_COMMA);
            }
            parameter8 = OBJECT_CTOR(FunctionMemberParameter_impl, FunctionMemberParameter_type);
            (parameter8)->identifier = identifier5;
            (parameter8)->typeClause = typeClause6;
            (parameter8)->comma = comma7;
            (list_push)(parameters4, ((Object)(parameter8)));
        }
        rParen9 = (match_token)(parser0, TokenKind_RPAREN);
        returnType10 = (parse_type_clause)(parser0);
        body11 = (parse_block_statement)(parser0);
        functionMember12 = OBJECT_CTOR(FunctionMember_impl, FunctionMember_type);
        (functionMember12)->keyword = keyword1;
        (functionMember12)->identifier = identifier2;
        (functionMember12)->lParen = lParen3;
        (functionMember12)->parameters = parameters4;
        (functionMember12)->rParen = rParen9;
        (functionMember12)->returnType = returnType10;
        (functionMember12)->body = body11;
        GC_FRAME_DESTROY;
        return functionMember12;
    }
    GC_FRAME_DESTROY;
}

TypeMember parse_type_member(Parser parser0)
{
    Token keyword1 = NULL;
    Token identifier2 = NULL;
    Token lBrace3 = NULL;
    ObjectList items4 = NULL;
    Token identifier5 = NULL;
    TypeClause typeClause6 = NULL;
    ObjectList semicolons7 = NULL;
    TypeMemberItem item8 = NULL;
    Token rBrace9 = NULL;
    ObjectList semicolons10 = NULL;
    TypeMember typeMember11 = NULL;
    GC_FRAME_INIT(12, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(identifier2), GC_LOCAL(lBrace3), GC_LOCAL(items4), GC_LOCAL(identifier5), GC_LOCAL(typeClause6), GC_LOCAL(semicolons7), GC_LOCAL(item8), GC_LOCAL(rBrace9), GC_LOCAL(semicolons10), GC_LOCAL(typeMember11));
    {
        keyword1 = (match_token)(parser0, TokenKind_TYPE_KEYWORD);
        identifier2 = (match_token)(parser0, TokenKind_IDENTIFIER);
        lBrace3 = (match_token)(parser0, TokenKind_LBRACE);
        items4 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RBRACE)) && !(parser_is_eof)(parser0))
        {
            identifier5 = (match_token)(parser0, TokenKind_IDENTIFIER);
            typeClause6 = (parse_type_clause)(parser0);
            semicolons7 = (parse_semicolon_block)(parser0, 1);
            item8 = OBJECT_CTOR(TypeMemberItem_impl, TypeMemberItem_type);
            (item8)->identifier = identifier5;
            (item8)->typeClause = typeClause6;
            (item8)->semicolons = semicolons7;
            (list_push)(items4, ((Object)(item8)));
        }
        rBrace9 = (match_token)(parser0, TokenKind_RBRACE);
        semicolons10 = (parse_semicolon_block)(parser0, 0);
        typeMember11 = OBJECT_CTOR(TypeMember_impl, TypeMember_type);
        (typeMember11)->keyword = keyword1;
        (typeMember11)->identifier = identifier2;
        (typeMember11)->lBrace = lBrace3;
        (typeMember11)->items = items4;
        (typeMember11)->rBrace = rBrace9;
        (typeMember11)->semicolons = semicolons10;
        GC_FRAME_DESTROY;
        return typeMember11;
    }
    GC_FRAME_DESTROY;
}

EnumMember parse_enum_member(Parser parser0)
{
    Token keyword1 = NULL;
    Token identifier2 = NULL;
    Token lBrace3 = NULL;
    ObjectList items4 = NULL;
    Token identifier5 = NULL;
    Token comma6 = NULL;
    EnumMemberItem item7 = NULL;
    Token rBrace8 = NULL;
    ObjectList semicolons9 = NULL;
    EnumMember enumMember10 = NULL;
    GC_FRAME_INIT(11, GC_LOCAL(parser0), GC_LOCAL(keyword1), GC_LOCAL(identifier2), GC_LOCAL(lBrace3), GC_LOCAL(items4), GC_LOCAL(identifier5), GC_LOCAL(comma6), GC_LOCAL(item7), GC_LOCAL(rBrace8), GC_LOCAL(semicolons9), GC_LOCAL(enumMember10));
    {
        keyword1 = (match_token)(parser0, TokenKind_ENUM_KEYWORD);
        identifier2 = (match_token)(parser0, TokenKind_IDENTIFIER);
        lBrace3 = (match_token)(parser0, TokenKind_LBRACE);
        items4 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RBRACE)) && !(parser_is_eof)(parser0))
        {
            identifier5 = (match_token)(parser0, TokenKind_IDENTIFIER);
            comma6 = NULL;
            if (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_RBRACE)))
            {
                comma6 = (match_token)(parser0, TokenKind_COMMA);
            }
            item7 = OBJECT_CTOR(EnumMemberItem_impl, EnumMemberItem_type);
            (item7)->identifier = identifier5;
            (item7)->comma = comma6;
            (list_push)(items4, ((Object)(item7)));
        }
        rBrace8 = (match_token)(parser0, TokenKind_RBRACE);
        semicolons9 = (parse_semicolon_block)(parser0, 0);
        enumMember10 = OBJECT_CTOR(EnumMember_impl, EnumMember_type);
        (enumMember10)->keyword = keyword1;
        (enumMember10)->identifier = identifier2;
        (enumMember10)->lBrace = lBrace3;
        (enumMember10)->items = items4;
        (enumMember10)->rBrace = rBrace8;
        (enumMember10)->semicolons = semicolons9;
        GC_FRAME_DESTROY;
        return enumMember10;
    }
    GC_FRAME_DESTROY;
}

CompilationUnit parse_compilation_unit(Parser parser0)
{
    ObjectList externFunctions1 = NULL;
    ObjectList externTypes2 = NULL;
    ObjectList functions3 = NULL;
    ObjectList types4 = NULL;
    ObjectList enums5 = NULL;
    TokenKind kind6;
    Token eof7 = NULL;
    CompilationUnit compilationUnit8 = NULL;
    GC_FRAME_INIT(8, GC_LOCAL(parser0), GC_LOCAL(externFunctions1), GC_LOCAL(externTypes2), GC_LOCAL(functions3), GC_LOCAL(types4), GC_LOCAL(enums5), GC_LOCAL(eof7), GC_LOCAL(compilationUnit8));
    {
        externFunctions1 = (list_init)();
        externTypes2 = (list_init)();
        functions3 = (list_init)();
        types4 = (list_init)();
        enums5 = (list_init)();
        while (((i32)(((current_token)(parser0))->kind)) != ((i32)(TokenKind_EOF)) && !(parser_is_eof)(parser0))
        {
            kind6 = ((current_token)(parser0))->kind;
            if (((i32)(kind6)) == ((i32)(TokenKind_EXTERN_KEYWORD)))
            {
                if (((i32)(((peek_token)(parser0))->kind)) == ((i32)(TokenKind_FUNCTION_KEYWORD)))
                {
                    (list_push)(externFunctions1, ((Object)((parse_extern_function_member)(parser0))));
                    continue;
                }
                if (((i32)(((peek_token)(parser0))->kind)) == ((i32)(TokenKind_TYPE_KEYWORD)))
                {
                    (list_push)(externTypes2, ((Object)((parse_extern_type_member)(parser0))));
                    continue;
                }
            }
            if (((i32)(kind6)) == ((i32)(TokenKind_FUNCTION_KEYWORD)))
            {
                (list_push)(functions3, ((Object)((parse_function_member)(parser0))));
                continue;
            }
            if (((i32)(kind6)) == ((i32)(TokenKind_TYPE_KEYWORD)))
            {
                (list_push)(types4, ((Object)((parse_type_member)(parser0))));
                continue;
            }
            if (((i32)(kind6)) == ((i32)(TokenKind_ENUM_KEYWORD)))
            {
                (list_push)(enums5, ((Object)((parse_enum_member)(parser0))));
                continue;
            }
            (PANIC)(STRING_CTOR(String_impl, String_type, (uchar*)"Unexpected token", 16));
        }
        eof7 = (match_token)(parser0, TokenKind_EOF);
        compilationUnit8 = OBJECT_CTOR(CompilationUnit_impl, CompilationUnit_type);
        (compilationUnit8)->externTypes = externTypes2;
        (compilationUnit8)->types = types4;
        (compilationUnit8)->externFunctions = externFunctions1;
        (compilationUnit8)->functions = functions3;
        (compilationUnit8)->enums = enums5;
        (compilationUnit8)->eof = eof7;
        GC_FRAME_DESTROY;
        return compilationUnit8;
    }
    GC_FRAME_DESTROY;
}

Scope scope_init(Scope parent0)
{
    Scope scope1 = NULL;
    GC_FRAME_INIT(2, GC_LOCAL(parent0), GC_LOCAL(scope1));
    {
        scope1 = OBJECT_CTOR(Scope_impl, Scope_type);
        (scope1)->parent = parent0;
        (scope1)->dataTypes = (list_init)();
        (scope1)->variables = (list_init)();
        (scope1)->functions = (list_init)();
        GC_FRAME_DESTROY;
        return scope1;
    }
    GC_FRAME_DESTROY;
}

void scope_push_scope(Binder binder0)
{
    GC_FRAME_INIT(1, GC_LOCAL(binder0));
    {
        (binder0)->currentScope = (scope_init)((binder0)->currentScope);
    }
    GC_FRAME_DESTROY;
}

void scope_pop_scope(Binder binder0)
{
    GC_FRAME_INIT(1, GC_LOCAL(binder0));
    {
        (binder0)->currentScope = ((binder0)->currentScope)->parent;
    }
    GC_FRAME_DESTROY;
}

void scope_declare_type(Scope scope0, DataType dataType0)
{
    GC_FRAME_INIT(2, GC_LOCAL(scope0), GC_LOCAL(dataType0));
    {
        (list_push)((scope0)->dataTypes, ((Object)(dataType0)));
    }
    GC_FRAME_DESTROY;
}

DataType scope_lookup_type(Scope scope0, String name0, ObjectList generics0)
{
    ObjectListIterator iter1 = NULL;
    DataType dataType2 = NULL;
    GC_FRAME_INIT(5, GC_LOCAL(scope0), GC_LOCAL(name0), GC_LOCAL(generics0), GC_LOCAL(iter1), GC_LOCAL(dataType2));
    {
        iter1 = (list_iterator)((scope0)->dataTypes);
        while ((list_iterator_has_next)(iter1))
        {
            dataType2 = ((DataType)((list_iterator_next)(iter1)));
            if ((type_eq_def)(dataType2, name0, generics0))
            {
                GC_FRAME_DESTROY;
                return dataType2;
            }
        }
        if (((Object)((scope0)->parent)) != ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return (scope_lookup_type)((scope0)->parent, name0, generics0);
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

void scope_declare_variable(Scope scope0, Variable variable0)
{
    GC_FRAME_INIT(2, GC_LOCAL(scope0), GC_LOCAL(variable0));
    {
        (list_push)((scope0)->variables, ((Object)(variable0)));
    }
    GC_FRAME_DESTROY;
}

Variable scope_lookup_variable(Scope scope0, String name0)
{
    i32 i1;
    Variable variable2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(scope0), GC_LOCAL(name0), GC_LOCAL(variable2));
    {
        i1 = 0;
        while (i1 < ((scope0)->variables)->length)
        {
            variable2 = ((Variable)((list_get_value)((scope0)->variables, i1)));
            i1 = i1 + 1;
            if ((string_equals)((variable2)->name, name0))
            {
                GC_FRAME_DESTROY;
                return variable2;
            }
        }
        if (((Object)((scope0)->parent)) != ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return (scope_lookup_variable)((scope0)->parent, name0);
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

void scope_declare_function(Scope scope0, BoundFunctionMember function0)
{
    GC_FRAME_INIT(2, GC_LOCAL(scope0), GC_LOCAL(function0));
    {
        (list_push)((scope0)->functions, ((Object)(function0)));
    }
    GC_FRAME_DESTROY;
}

BoundFunctionMember scope_lookup_function(Scope scope0, String name0)
{
    i32 i1;
    BoundFunctionMember function2 = NULL;
    GC_FRAME_INIT(3, GC_LOCAL(scope0), GC_LOCAL(name0), GC_LOCAL(function2));
    {
        i1 = 0;
        while (i1 < ((scope0)->functions)->length)
        {
            function2 = ((BoundFunctionMember)((list_get_value)((scope0)->functions, i1)));
            i1 = i1 + 1;
            if ((string_equals)((function2)->name, name0))
            {
                GC_FRAME_DESTROY;
                return function2;
            }
        }
        if (((Object)((scope0)->parent)) != ((Object)(NULL)))
        {
            GC_FRAME_DESTROY;
            return (scope_lookup_function)((scope0)->parent, name0);
        }
        GC_FRAME_DESTROY;
        return NULL;
    }
    GC_FRAME_DESTROY;
}

