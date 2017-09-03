extern int yylex(void);

typedef enum token {
  TK_AS = 256,
  TK_CHAR,
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
} TOKEN;
