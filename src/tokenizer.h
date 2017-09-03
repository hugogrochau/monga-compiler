extern int yylex(void);

typedef enum token {
  TK_CHAR = 256,
  TK_ELSE,
  TK_FLOAT,
  TK_IF,
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
} TOKEN;
