DIRS = -I build -I src

T1_DEPENDENCIES = src/ast_creation.c build/tokenizer.yy.c build/parser.c src/main_t1.c
T2_DEPENDENCIES = src/ast_creation.c build/tokenizer.yy.c build/parser.c src/main_t2.c
T3_DEPENDENCIES = src/ast_creation.c src/ast_printer.c build/tokenizer.yy.c build/parser.c src/main_t3.c
T4_DEPENDENCIES = src/ast_creation.c src/symbol_table.c src/ast_knit.c build/tokenizer.yy.c build/parser.c src/main_t4.c

default: test

build/tokenizer.yy.c: build/parser.c src/tokenizer.h src/tokenizer.lex
	lex -o build/tokenizer.yy.c src/tokenizer.lex

build/t1: $(T1_DEPENDENCIES)
	gcc $(DIRS) -o build/t1 $(T1_DEPENDENCIES)

build/parser.c: src/parser.y
	bison -d -o build/parser.c src/parser.y

build/t2: $(T2_DEPENDENCIES)
	gcc $(DIRS) -o build/t2 $(T2_DEPENDENCIES)

build/t3: $(T3_DEPENDENCIES)
	gcc $(DIRS) -o build/t3 $(T3_DEPENDENCIES)

build/t4: $(T4_DEPENDENCIES)
	gcc $(DIRS) -o build/t4 $(T4_DEPENDENCIES)

test: build/t1 build/t2 build/t3
	scripts/test.py

clean:
	rm -rf build/*
	touch build/.gitkeep
