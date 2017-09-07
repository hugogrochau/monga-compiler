extern int yylex(void);

typedef enum tokenType {
  TK_AS = 256,
  TK_CHARACTER,
  TK_ELSE,
  TK_FLOAT,
  TK_IF,
  TK_INT,
  TK_NEW,
  TK_RETURN,
  TK_VOID,
  TK_WHILE,
  TK_ID,
  TK_EQUAL,
  TK_NOT_EQUAL,
  TK_LESS_EQUAL,
  TK_GREATER_EQUAL,
  TK_LOGIC_AND,
  TK_LOGIC_OR,
  TK_INTEGER_CONSTANT,
  TK_FLOAT_CONSTANT,
  TK_STRING
} TokenType;

typedef struct tokenData {
  long l;
  double d;
  char *c;
} TokenData;

typedef struct token {
  TokenType type;
  TokenData data;
} Token;
