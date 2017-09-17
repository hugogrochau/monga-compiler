DIRS = -I build -I src

tokenizer.yy.c: parser.c
	lex -o build/tokenizer.yy.c src/tokenizer.lex

tokenizer.yy.o: tokenizer.yy.c
	gcc $(DIRS) -o build/tokenizer.yy.o -c build/tokenizer.yy.c

tokenizer: tokenizer.yy.o
	gcc $(DIRS) -o build/tokenizer build/tokenizer.yy.o src/main_t1.c

parser.c:
	bison -d -o build/parser.c src/parser.y

parser: tokenizer.yy.c parser.c
	gcc $(DIRS) -o build/parser build/tokenizer.yy.o build/parser.c src/main_t2.c

test: tokenizer
	scripts/test.py

clean:
	rm -rf build/*.c build/*.o build/tokenizer