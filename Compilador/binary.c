/****************************************************/
/* Ricardo Elizeu Neto  RA 104121                   */
/* Lab de Compiladores - Prof. Galvão               */
/* File: binary.c                                   */
/* The code generator implementation                */
/* for the C- compiler                              */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "assembly.h"

const char * opcodes[] =  { "nop", "halt", "add", "addi", "sub", "mult", "divi", "mod", "and", "or", "not", "xor", "slt", "sgt", "sle", "sge", 
                            "shl", "shr", "move", "ldi", "beq", "bne", "jmp", "in", "out", "str", "load", "jr" };

const char * opcodeBins[] =  {  "000000", "111111", "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010", "001011",
                                "001100", "001101", "001110", "001111", "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111", "011000",
                                "011001", "011010" };

const char * regBins[] = {  "00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110",
                            "01111", "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", "11101",
                            "11110", "11111" };


char * getImediate (int im, int size) {
    int i = 0;
    char * bin = (char *) malloc(size + 2);
    size --;
    for (unsigned bit = 1u << size; bit != 0; bit >>= 1) {
        bin[i++] = (im & bit) ? '1' : '0';
    }
    bin[i] = '\0';
    return bin;
}

char * assembly2binary (Instruction i) {
    char * bin = (char *) malloc((32 + 4 + 2) * sizeof(char));
    
    if (i.format == format1) {
        sprintf(bin, "%s_%s%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], regBins[i.reg3], "00000000000");
    }
    else if (i.format == format2) {
        sprintf(bin, "%s_%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], getImediate(i.im, 16));
    }
    else if (i.format == format3) {
        sprintf(bin, "%s_%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], "00000", getImediate(i.im, 16));
    }
    else {
        sprintf(bin, "%s_%s", opcodeBins[i.opcode], getImediate(i.im, 26));
    }
    //colocar separador '_'
    return bin;
}

void generateBinary (AssemblyCode head, int size) {
    AssemblyCode a = head;
    FILE * c = code;
    char * bin;

    fprintf(c, "module MemoriaDeInstrucoes(	input [5:0] Endereco,\n");
                                fprintf(c, "\t\toutput [5:0] Opcode,\n");
                                fprintf(c, "\t\toutput [4:0] CampoA,\n");
                                fprintf(c, "\t\toutput [4:0] CampoB,\n");
                                fprintf(c, "\t\toutput [4:0] CampoC,\n");
                                fprintf(c, "\t\toutput [10:0] CampoD );\n");

    fprintf(c, "\n\twire [31:0] Memoria [%d:0];\n\twire [31:0] Instrucao;\n\n", size);
    printf("\nC- Binary Code\n");

    while (a != NULL) {
        if (a->kind == instr) {
            fprintf(c, "\tassign Memoria[%d]\t=\t32'b", a->lineno);
            printf("%d:\t", a->lineno);
            bin = assembly2binary(a->line.instruction);
            fprintf(c, "%s;\n", bin);
            printf("%s\t// %s\n", bin, opcodes[a->line.instruction.opcode]);
        }
        else {
            printf("// %s\n", a->line.label);
        }
        a = a->next;
    }
    
    fprintf(c, "\n\tassign Instrucao = Memoria[Endereco];\n");

    fprintf(c, "\tassign Opcode = Instrucao[31:26];\n");
    fprintf(c, "\tassign CampoA = Instrucao[25:21];\n");
    fprintf(c, "\tassign CampoB = Instrucao[20:16];\n");
    fprintf(c, "\tassign CampoC = Instrucao[15:11];\n");
    fprintf(c, "\tassign CampoD = Instrucao[10:0];\n");

    fprintf(c, "\nendmodule\n");
}