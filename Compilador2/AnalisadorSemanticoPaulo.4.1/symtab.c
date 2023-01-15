/****************************************************/
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

/* the list of line numbers of the source
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name,
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     char * scope;
     char * typeID;
     char * type;
     int declared;
     int duplicated;
     LineList lines;
     int vet;
     int params;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
   } * BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert ( char * name, char * scope, char * typeID, char * type, int declared, int lineno, int loc, int vet, int params )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && ((strcmp(name,l->name) != 0) || (strcmp(scope, l->scope)!=0)))
    l = l->next;
  if (l == NULL || (l->typeID != typeID && strcmp(typeID, "") != 0)) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->scope = scope;
    l->typeID = typeID;
    l->type = type;
    l->declared = declared;
    l->duplicated = -1;
    l->vet = vet;
    l->params = params;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* found in table, so just add line number */
  { if (strcmp(typeID, "") == 0 || lineno == l->lines->lineno || getLine(l, lineno) == 0) {
      l->duplicated = lineno;
    }
    else {
      if (strcmp(l->typeID, "decl") == 0 && lineno != l->lines->lineno)
        l->duplicated = lineno;
      LineList t = l->lines;
      while (t->next != NULL) t = t->next;
      t->next = (LineList) malloc(sizeof(struct LineListRec));
      t->next->lineno = lineno;
      t->next->next = NULL;
    }
  }
} /* st_insert */

int getLine ( BucketList l, int line )
{
  LineList aux = l->lines;
  while (aux != NULL) {
    if (aux->lineno == line)
      return 0;
    aux = aux->next;
  }
  return -1;
}

/* Function st_lookup returns the memory
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name, char * scope )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(scope, l->scope)!=0))))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}

void st_type_check( char * name, char * typeID )
{ int h = hash(name);
  char *type = "fun";
  BucketList l =  hashTable[h];
  BucketList m =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0)) || (strcmp(l->typeID, type) != 0)))
    l = l->next;
  if ( l != NULL ) {
    while ( m != NULL ) {
      if ((strcmp(name,m->name) == 0) && (strcmp(m->typeID, typeID) == 0))
        m->type = l->type;
      m = m->next;
    }
  }
}

void st_vet_check( char * name, char * typeID, char * scope )
{ int h = hash(name);
  char *type = "decl";
  BucketList l =  hashTable[h];
  BucketList m =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0)) || (strcmp(l->typeID, type) != 0)))
    l = l->next;
  if ( l != NULL ) {
    while ( m != NULL ) {
      if ((strcmp(name,m->name) == 0) && (strcmp(m->typeID, typeID) == 0) && (strcmp(m->scope, l->scope) == 0))
        m->vet = l->vet;
      m = m->next;
    }
  }
}

int st_var_decl (char * name, char * scope )
{ int h = hash(name);
  char * typeID = "var";
  int flag = 0;
  BucketList l =  hashTable[h];
  while (l != NULL) {
    if ((l->declared == 1) && (strcmp(l->scope, scope) == 0 || strcmp(l->scope, "Global") == 0) && strcmp(l->name, name) == 0)
      flag = 1;
    l = l->next;
  }
  if (flag == 0) return 0;
  else return flag;
}

int st_fun_decl ( char * name )
{ int h = hash(name);
  char * typeID = "fun";
  char * empty = "";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else
  { l =  hashTable[h];
    while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(typeID,l->typeID) != 0))))
      l = l->next;
    if (l == NULL) return 0;
    else return 1;
  }
}

int st_var_fun_decl ( char *name )
{ int h = hash(name);
  char *typeID = "fun";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0)) || (strcmp(l->typeID, typeID) != 0)))
    l = l->next;
  if (l != NULL){
    return 0;
  }
  else
    return -1;
}

int st_main_decl ()
{ char * name = "main";
  int h = hash(name);
  char * typeID = "fun";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(typeID,l->typeID) != 0))))
    l = l->next;
  if (l == NULL) return 0;
  else return 1;

}

int st_decl ( char * name )
{ int h = hash(name);
  char * typeID = "var";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(typeID,l->typeID) != 0))))
    l = l->next;
  if (l == NULL) return -1;
  else
  { typeID = "fun";
    l =  hashTable[h];
    while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(typeID,l->typeID) != 0))))
      l = l->next;
      if (l == NULL) return 1;
      else return 0;
  }
}

int st_duplicate ( char * name, char * scope, char * typeID, int lineno )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(scope, l->scope) != 0) || (strcmp(typeID,l->typeID) != 0))))
    l = l->next;
  if (l == NULL) return 1;
  else
  { if (l == NULL) return -1;
    else if (l->declared == 0) return -1;
    else {
      if (l->duplicated == lineno)
        return l->duplicated;
      else return -1;
    }
  }
}

int st_return ( char * name, char * scope, int lineno )
{ int h = hash(name);
  char * typeID = "call";
  char * typedata = "int";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((lineno != l->lines->lineno) || (strcmp(typeID, l->typeID) != 0))))
    l = l->next;
  if (l == NULL) return -1;
  else
  { if ((strcmp(typedata, l->type)) != 0 ) return 0;
    else return 1;
  }
}

char * fun_type( char * name )
{ int h = hash(name);
  char * fun = "fun";
  char * empty = "";
  BucketList l =  hashTable[h];
  while ((l != NULL) && (((strcmp(name,l->name) != 0) || (strcmp(fun,l->typeID) != 0))))
    l = l->next;
  if (l == NULL) return empty;
  else return l->type;
}

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i;
  char * empty = "";
  char * fun = "fun";
  char * call = "call";

  char * sep = "---------------";
  fprintf(listing, "%s %s %s %s %s %s\n", sep, sep, sep, sep, sep, sep);
  fprintf(listing, "%-15s %-15s %-15s %-15s %-15s %-15s\n", "Variable Name", "Scope",  "ID Type", "Data Type", "Memloc", "Line Numbers");
  fprintf(listing, "%s %s %s %s %s %s\n", sep, sep, sep, sep, sep, sep);

  for (i=0;i<SIZE;++i) {
    if (hashTable[i] != NULL) {
      BucketList l = hashTable[i];
      while (l != NULL){
        LineList t = l->lines;
        if (l->vet == -1)
          fprintf(listing,"%-15s ", l->name);
        else
          if (l->vet < 10)
            fprintf(listing,"%s[%d]%-11s ", l->name, l->vet, "");
          else if (l->vet < 100)
            fprintf(listing,"%s[%d]%-8s ", l->name, l->vet, "");
          else
            fprintf(listing,"%s[%d]%-9s ", l->name, l->vet, "");
        fprintf(listing,"%-15s ",l->scope);
        if((strcmp(empty,l->typeID) == 0)) {
          fprintf(listing,"%-15s ", fun);
          fprintf(listing,"%-15s ", fun_type(l->name));
        }
        else {
          fprintf(listing,"%-15s ",l->typeID);
          fprintf(listing,"%-15s ",l->type);
        }
        fprintf(listing,"%-15d ",l->memloc);
        while (t != NULL) {
          fprintf(listing,"%d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
