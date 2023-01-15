/****************************************************/
/* Victor Hugo Teodoro Pimentel  RA 150976          */
/* Compiladores - Prof. Galvão                      */                     
/****************************************************/

%expect 1 /* para ocultar o warning: 1 shift/reduce conflict [-Wconflicts-sr] */

%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
char * scope = "Global";
char * idtype = "";
char * datatype = "";
int counter = 0;
int params = 0;

%}

%token IF ELSE INT RETURN VOID WHILE
%token ID NUM
%token PLUS MINUS TIMES OVER LT LET GT GET EQ NEQ ASSIGN SEMI COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token ERROR

%% /* Grammar for CMINUS */

programa:
  declaracao_lista
  { savedTree = $1; }
;

declaracao_lista:
  declaracao_lista declaracao
  { YYSTYPE t = $1;
    if (t != NULL)
    { while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $2;
      $$ = $1;
    }
      else $$ = $2;
  }
  | declaracao
  { $$ = $1; }
;

declaracao:
  var_declaracao
  { $$ = $1; }
  | fun_declaracao
  { $$ = $1; 
    scope = "Global";
  }
;

id: 
  ID 
  { $$ = newExpNode(IdK);
    $$->idname = copyString(tokenString);
    savedName = copyString(tokenString);
    $$->idtype = idtype;
    $$->datatype = datatype;
    $$->scope = scope;
    $$->declared = 0;
    $$->vet = -1;
    $$->params = params;
    $$->attr.name = copyString(tokenString);
  } 
;

fun_id: 
  { scope = savedName; }
;

vet_num: 
  NUM 
  { $$ = newExpNode(ConstK);                    
    $$->attr.val = atoi(tokenString);
    $$->vet = atoi(tokenString);
    $$->params = params;
  }
;

var_declaracao:
  INT id SEMI
  { $$ = newExpNode(VarK);
	  $$->attr.name = $2->attr.name;
    $$->idtype = "decl";
    $$->idname = $2->attr.name;
    $$->datatype = "int";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
    $$->lineno = $2->lineno;
  }
  | INT id LBRACKET vet_num RBRACKET SEMI
  { $$ = newExpNode(VarK);
	  $$->attr.name = $2->attr.name;
    $$->idtype = "decl";
    $$->idname = $2->attr.name;
    $$->datatype = "int";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = $4->attr.val;
    $$->params = params;
    $$->lineno = $2->lineno;
  }
  | VOID id SEMI
  { $$ = newExpNode(VarK);
	  $$->attr.name = $2->attr.name;
    $$->idtype = "decl";
    $$->idname = $2->attr.name;
    $$->datatype = "void";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
    $$->lineno = $2->lineno;
  }
  | VOID id LBRACKET vet_num RBRACKET SEMI
  { $$ = newExpNode(VarK);
	  $$->attr.name = $2->attr.name;
    $$->idtype = "decl";
    $$->idname = $2->attr.name;
    $$->datatype = "void";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = $4->attr.val;
    $$->params = params;
    $$->lineno = $2->lineno;
  }
;

fun_declaracao:
  VOID id fun_id LPAREN params RPAREN composto_decl
  { $$ = newExpNode(FunK);
	  $$->attr.name = scope;
    $$->idtype = "fun";
    $$->datatype = "void";
    $$->scope = scope;
    $$->idname = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
    $$->child[0] = $5;
	  $$->child[1] = $7;
    $$->lineno = $2->lineno;
  }
  | INT id fun_id LPAREN params RPAREN composto_decl
  { $$ = newExpNode(FunK);
	  $$->attr.name = scope;
    $$->idtype = "fun";
    $$->datatype = "int";
    $$->scope = scope;
    $$->idname = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
    $$->child[0] = $5;
	  $$->child[1] = $7;
    $$->lineno = $2->lineno;
  }
;

params:
  param_lista
  { $$ = $1; }
  | VOID
  { $$=newExpNode(TypeK);
		$$->attr.name = "void";
    $$->child[0] = NULL;
  }
;

param_lista:
  param_lista COMMA param
  { YYSTYPE t = $1;
    if (t != NULL){
      while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $3;
      $$ = $1;
    }
    else $$ = $3;
  }
  | param
  { $$ = $1; }
;

param:
  INT id
  { $$ = newExpNode(ParamK);
    $$->attr.name = $2->attr.name;
    $$->idname = $2->attr.name;
    $$->idtype = "param";
    $$->datatype = "int";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
  }
  | INT id LBRACKET RBRACKET
  { $$ = newExpNode(ParamK);
    $$->attr.name = $2->attr.name;
    $$->idname = $2->attr.name;
    $$->idtype = "param";
    $$->datatype = "int";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
  }
  | VOID id
  { $$ = newExpNode(ParamK);
    $$->attr.name = $2->attr.name;
    $$->idname = $2->attr.name;
    $$->idtype = "param";
    $$->datatype = "void";
    $$->scope = scope;
    $$->declared = 1;
    $$->vet = -1;
    $$->params = params;
  }
  LBRACKET RBRACKET
  { }
;

composto_decl:
  LBRACE local_declaracoes statement_lista RBRACE
  { YYSTYPE t = $2;
    if (t != NULL){
      while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $3;
      $$ = $2;
    }
    else $$ = $3;
  }
  | LBRACE local_declaracoes RBRACE 
  { $$ = $2; }
  | LBRACE statement_lista RBRACE
  { $$ = $2; }
  | LBRACE RBRACE
  { }
;

local_declaracoes:
  local_declaracoes var_declaracao
  { YYSTYPE t = $1;
    if (t != NULL){
      while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $2;
      $$ = $1;
    }
    else $$ = $2;
  }
  | var_declaracao
  { $$ = $1; }
;

statement_lista:
  statement_lista statement
  { YYSTYPE t = $1;
    if (t != NULL){
      while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $2;
      $$ = $1;
    }
    else $$ = $2;
  }
  | statement
  { $$ = $1; }
;

statement:
  expressao_decl
  { $$ = $1; }
  | composto_decl
  { $$ = $1; }
  | selecao_decl
  { $$ = $1; }
  | iteracao_decl
  { $$ = $1; }
  | retorno_decl
  { $$ = $1; }
;

expressao_decl:
  expressao SEMI
  { $$ = $1; }
  | SEMI
  { }
;

selecao_decl:
  IF LPAREN expressao RPAREN statement
  { $$ = newStmtNode(IfK);
    $$->child[0] = $3;
		$$->child[1] = $5;
    $$->scope = $3->scope;
  }
  | IF LPAREN expressao RPAREN statement ELSE statement
  { $$ = newStmtNode(IfK);
    $$->child[0] = $3;
    $$->child[1] = $5;
    $$->child[2] = $7;
    $$->scope = $3->scope;
  }
;

iteracao_decl:
  WHILE LPAREN expressao RPAREN statement
  { $$ = newStmtNode(WhileK);
    $$->child[0] = $3;
    $$->child[1] = $5;
    $$->scope = $3->scope;
  }
;

retorno_decl:
  RETURN SEMI
  { $$ = newStmtNode(ReturnK);
  }
  | RETURN expressao SEMI
  { $$ = newStmtNode(ReturnK);
    $$->child[0] = $2;
  }
;

expressao:
  var ASSIGN expressao
  { $$ = newStmtNode(AssignK);
	  $$->attr.name = $1->attr.name;
    $$->scope = scope;
    $$->child[0] = $1;
    $$->child[1] = $3;
  }
  | simples_expressao
  { $$ = $1; }
;

var:
  id
  { $$ = $1;
    $$->idtype = "var";
    $$->datatype = "int";
    $$->declared = 0;
  }
  | id LBRACKET expressao RBRACKET
  { $$ = $1;
    $$->idtype = "var";
    $$->datatype = "int";
    $$->declared = 0;
		$$->child[0] = $3;
  }
;

simples_expressao:
  soma_expressao relacional soma_expressao
  { $$ = $2;
    $$->scope = scope;
    $$->child[0] = $1;
    $$->child[1] = $3;
  }
  | soma_expressao
  { $$ = $1; }
;

relacional:
  LET
  { $$ = newExpNode(OpK);
    $$->attr.op = LET;
  }
  | LT
  { $$ = newExpNode(OpK);
    $$->attr.op = LT;
  }
  | GT
  { $$ = newExpNode(OpK);
    $$->attr.op = GT;
  }
  | GET
  { $$ = newExpNode(OpK);
    $$->attr.op = GET;
  }
  | EQ
  { $$ = newExpNode(OpK);
    $$->attr.op = EQ;
  }
  | NEQ
  { $$ = newExpNode(OpK);
    $$->attr.op = NEQ;
  }
;

soma_expressao:
  soma_expressao soma termo
  { $$ = $2;
    $$->scope = scope;
	  $$->child[0] = $1;
	  $$->child[1] = $3;
  }
  | termo
  { $$ = $1; }
;

soma:
  PLUS
  { $$ = newExpNode(OpK);
    $$->attr.op = PLUS;
  }
  | MINUS
  { $$ = newExpNode(OpK);
    $$->attr.op = MINUS;
  }
;

termo:
  termo mult fator
  { $$ = $2;
	  $$->scope = scope;
    $$->child[0] = $1;
		$$->child[1] = $3;
  }
  | fator
  { $$ = $1; }
;

mult:
  TIMES
  { $$ = newExpNode(OpK);
    $$->attr.op = TIMES;
  }
  | OVER
  { $$ = newExpNode(OpK);
    $$->attr.op = OVER;
  }
;

fator:
  LPAREN expressao RPAREN
  { $$ = $2; }
  | var
  { $$ = $1; }
  | ativacao
  { $$ = $1;
    params = 0;
  }
  | NUM
  { $$ = newExpNode(ConstK);
    $$->attr.val = atoi(tokenString);
  }
;

ativacao:
  id LPAREN arg_lista RPAREN
  { $$ = newExpNode(CallK);
    $$->attr.name = $1->attr.name;
    $$->idname = $1->attr.name;
    $$->scope = scope;
    $$->declared = 0;
    $$->idtype = "call";
    $$->vet = -1;
		$$->child[0] = $3;
    $$->params = params;
  }
  | id LPAREN RPAREN
  { $$ = newExpNode(CallK);
    $$->attr.name = $1->attr.name;
    $$->idname = $1->attr.name;
    $$->scope = scope;
    $$->declared = 0;
    $$->idtype = "call";
    $$->vet = -1;
    $$->params = params;
  }
;

arg_lista:
  arg_lista COMMA expressao
  { YYSTYPE t = $1;
    if (t != NULL){
      while (t->sibling != NULL)
        t = t->sibling;
      t->sibling = $3;
      params ++;
      $$ = $1;
    }
    else $$ = $3;
  }
  | expressao
  { params ++;
    $$ = $1;
  }
;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the CMINUS scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}
