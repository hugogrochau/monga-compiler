DIRS = -I build -I src

tokenizer.yy.c:
	lex -o build/tokenizer.yy.c src/tokenizer.lex

tokenizer.yy.o: tokenizer.yy.c
	gcc $(DIRS) -o build/tokenizer.yy.o -c build/tokenizer.yy.c

main: tokenizer.yy.o
	gcc $(DIRS) -o build/main build/tokenizer.yy.o src/main.c

clean:
	rm -rf build/*.c build/*.o build/tokenizer