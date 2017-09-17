DIRS = -I build -I src

tokenizer.yy.c:
	lex -o build/tokenizer.yy.c src/tokenizer.lex

tokenizer.yy.o: tokenizer.yy.c
	gcc $(DIRS) -o build/tokenizer.yy.o -c build/tokenizer.yy.c

tokenizer: tokenizer.yy.o
	gcc $(DIRS) -o build/tokenizer build/tokenizer.yy.o src/main.c

parser.c:
	bison src/parser.y -o build/parser.c

test: tokenizer
	scripts/test.py

clean:
	rm -rf build/*.c build/*.o build/tokenizer