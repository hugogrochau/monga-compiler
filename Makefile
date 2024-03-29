OPTIONS = -I build -I src -Wall

T1_DEPENDENCIES = src/util.c src/ast_create.c build/tokenizer.yy.c build/parser.c src/main_t1.c
T2_DEPENDENCIES = src/util.c src/ast_create.c build/tokenizer.yy.c build/parser.c src/main_t2.c
T3_DEPENDENCIES = src/util.c src/ast_create.c src/ast_print.c build/tokenizer.yy.c build/parser.c src/main_t3.c
T4_DEPENDENCIES = src/util.c src/ast_create.c src/symbol_table.c src/ast_knit.c src/ast_type.c src/ast_print.c build/tokenizer.yy.c build/parser.c src/main_t4.c
T5_DEPENDENCIES = src/util.c src/ast_create.c src/symbol_table.c src/ast_knit.c src/ast_type.c src/code_generator.c build/tokenizer.yy.c build/parser.c src/main_t5.c

default: test

build/tokenizer.yy.c: build/parser.c src/tokenizer.h src/tokenizer.lex
	lex -o build/tokenizer.yy.c src/tokenizer.lex

build/parser.c: src/parser.y
	bison -d -o build/parser.c src/parser.y

build/t1: $(T1_DEPENDENCIES)
	gcc $(OPTIONS) -o build/t1 $(T1_DEPENDENCIES)

build/t2: $(T2_DEPENDENCIES)
	gcc $(OPTIONS) -o build/t2 $(T2_DEPENDENCIES)

build/t3: $(T3_DEPENDENCIES)
	gcc $(OPTIONS) -o build/t3 $(T3_DEPENDENCIES)

build/t4: $(T4_DEPENDENCIES)
	gcc $(OPTIONS) -o build/t4 $(T4_DEPENDENCIES)

build/t5: $(T5_DEPENDENCIES)
	gcc $(OPTIONS) -o build/t5 $(T5_DEPENDENCIES)

test: build/t1 build/t2 build/t3 build/t4 build/t5
	scripts/test.py

clean:
	rm -rf build/*
	touch build/.gitkeep
