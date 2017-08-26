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
} TOKEN;
