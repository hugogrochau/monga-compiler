# monga-compiler

## Description
A compiler for the monga language. Written for the INF1715 class @ PUC-Rio

## Dependencies
- Python 3
- gcc
- Clang 3.8

## Includes
- Tokenizer [src/tokenizer.lex](src/tokenizer.lex)
- Parser [src/parser.y](src/parser.y)
- AST creator [src/ast_create.c](src/ast_create.c),
- AST knitter [src/knit.c](src/ast_knit.c)
- AST typer and type checker [src/ast_type.c](src/ast_type.c)
- AST code generator [src/code_generator.c](src/code_generator.c)

## Running
`make test`

## Author
@hugogrochau