all: tokenizer parser build

tokenizer:
	flex cminus.l

parser:
	bison -d cminus.y

build:
	gcc -c *.c -fno-builtin-exp -Wno-implicit-function-declaration
	gcc *.o -lfl -o cminus -fno-builtin-exp

clean:
	rm -f cminus
	rm -f lex.yy.c
	rm -f *.o
	rm -f c-.tab.*
