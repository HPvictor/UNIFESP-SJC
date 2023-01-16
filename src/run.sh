#\!/bin/bash
flex scanner.l
bison -d parser.y
gcc -c *.c
gcc -o cminus *.o -lfl
./cminus teste.cminus > result.txt
