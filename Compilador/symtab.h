/****************************************************/
/* Victor Hugo Teodoro Pimentel  RA 150976          */
/* Compiladores - Prof. Galvão                      */                        
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
 void st_insert( char * name, char * scope, char * idtype, char * type, int declared, int lineno, int loc, int vet, int params );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
 int st_lookup ( char * name, char * scope ); 

 void st_type_check( char * name, char * idtype );

 void st_vet_check( char * name, char * idtype, char * scope );
 
 int st_var_decl (char * name, char * scope );

 int st_fun_decl ( char * name );

 int st_var_fun_decl ( char *name );

 int st_main_decl ();

 int st_decl ( char * name );

 int st_duplicate ( char * name, char * scope, char * idtype, int lineno );
 
 int st_return ( char * name, char * scope, int lineno );

 char * fun_type( char * name );

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);

#endif
