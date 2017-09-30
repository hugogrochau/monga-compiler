DIRS = -I build -I src

tokenizer.yy.c: parser.c src/tokenizer.h src/tokenizer.lex
	lex -o build/tokenizer.yy.c src/tokenizer.lex

tokenizer: tokenizer.yy.c src/main_t1.c
	gcc $(DIRS) -o build/tokenizer build/tokenizer.yy.c src/main_t1.c

parser.c: src/parser.y
	bison -d -o build/parser.c src/parser.y

parser: tokenizer.yy.c parser.c src/main_t2.c
	gcc $(DIRS) -o build/parser build/tokenizer.yy.c build/parser.c src/main_t2.c

test: tokenizer parser
	scripts/test.py

clean:
	rm -rf build/*
	touch build/.gitkeep
