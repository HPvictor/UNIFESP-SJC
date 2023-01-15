flex compiler.l
bison -d compiler.y
gcc -c *.c -fno-builtin-exp -Wno-implicit-function-declaration
gcc *.o -lfl -o compiler -fno-builtin-exp
