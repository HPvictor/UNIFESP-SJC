/****************************************************/
/* Ricardo Elizeu Neto  RA 104121                   */
/* Compiladores - Profa. Lorena                     */
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the C- compiler                              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

typedef struct LineListRec
{ int lineno;
  struct LineListRec * next;
} * LineList;

LineList assigns = NULL;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

static void stmtError(TreeNode * t, char * message)
{ fprintf(listing,"Error at line %d: %s %s.\n",t->lineno,t->idname,message);
  Error = TRUE;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case AssignK:
          if (assigns == NULL)
          { assigns = (LineList) malloc(sizeof(struct LineListRec));
            assigns->lineno = t->lineno;
            assigns->next = NULL;
          }
          else
          { LineList a = assigns;
            while (a->next != NULL) a = a->next;
              a->next = (LineList) malloc(sizeof(struct LineListRec));
              a->next->lineno = t->lineno;
              a->next->next = NULL;
          }
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if ((st_lookup(t->idname, t->scope) == -1) && (st_var_decl(t->idname, t->scope) !=-1))
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, location++, t->vet, t->params);
          else 
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, 0, t->vet, t->params);
          break;
        case VarK:
          if (st_lookup(t->idname, t->scope) == -1)
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, location++, t->vet, t->params);
          else
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, 0, t->vet, t->params);
          break;
        case CallK:
          if (st_lookup(t->idname, t->scope) == -1)
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, -1, t->vet, t->params);
          else
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, 0, t->vet, t->params);
          break;
        case FunK:
          if (st_lookup(t->idname, t->scope) == -1)
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, -1, t->vet, t->params);
          else
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, 0, t->vet, t->params);
          break;
        case ParamK:
          if (st_lookup(t->idname, t->scope) == -1)
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, location++, t->vet, t->params);
          else
            st_insert(t->idname, t->scope, t->idtype, t->datatype, t->declared, t->lineno, 0, t->vet, t->params);
          break;
        default:
          break;
    }
    break;
  default:
    break;
  }
}

static void specialType (TreeNode *t){
  switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case CallK:
          st_type_check(t->idname, t->idtype);
          break;
        case IdK:
          st_vet_check(t->idname, t->idtype, t->scope);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  traverse(syntaxTree,specialType,nullProc);
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Error at line %d: %s.\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ char * tdecl = "decl";
  char * tvar = "var";
  char * tvoid = "void";
  char * empty = "";
  switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if(st_var_decl(t->idname, t->scope) == 0)
            stmtError(t,"was not declared in this scope");
          if(st_return(t->idname, t->scope, t->lineno) == 0)
          { if(strcmp(tvar,t->idtype) == 0)
            { LineList a = assigns;
              while ((a != NULL) && (a->lineno != t->lineno)) 
                a = a->next;
              if(a != NULL) stmtError(t,"invalid attribution");
            }
          }
          break;
          case VarK:
            if(st_var_fun_decl(t->idname) == 0)
            { if(strcmp(tdecl,t->idtype) == 0)
                stmtError(t,"already declared as function");
            }
            if((strcmp(tdecl,t->idtype) == 0) && (strcmp(tvoid,t->datatype) == 0))
              stmtError(t,"declared as void");
            int aux = st_duplicate(t->idname, t->scope, t->idtype, t->lineno);
            if (aux != -1)
              stmtError(t,"already declared");
            break;
          case CallK:
            if(st_fun_decl(t->idname) == 0)
              stmtError(t,"not declared in this scope");
            break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
  if(st_main_decl() == 0)
  { fprintf(listing,"Error: main was not declared.\n");
    Error = TRUE;
  }


}
