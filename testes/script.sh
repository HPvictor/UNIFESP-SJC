flex cminus.l
bison -d cminus.y
gcc -c *.c -fno-builtin-exp -Wno-implicit-function-declaration
gcc *.o -lfl -o cminus -fno-builtin-exp
