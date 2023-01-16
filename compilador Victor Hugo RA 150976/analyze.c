/****************************************************/
/* Victor Hugo Teodoro Pimentel  RA 150976          */
/* Compiladores - Prof. Galvao                      */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse(TreeNode *t, void (*preProc)(TreeNode *), void (*postProc)(TreeNode *))
{
	if (t != NULL)
	{
		preProc(t);
		{
			int i;
			for (i = 0; i < MAXCHILDREN; i++)
				traverse(t->child[i], preProc, postProc);
		}
		postProc(t);
		traverse(t->sibling, preProc, postProc);
	}
}

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode *t)
{
	if (t == NULL)
		return;
	else
		return;
}

static void printSemanticError(TreeNode *tree, char *message)
{
	Error = TRUE;
	fprintf(listing, "\nERRO SEMÂNTICO: %s \nLINHA: %d \nMENSAGEM: %s\n", tree->attr.name, tree->lineno, message);
}

/* Procedure insertNode inserts
 * identifiers stored in t into
 * the symbol table
 */
static void insertNode(TreeNode *t)
{
	switch (t->nodekind)
	{
	case statementK:
		switch (t->kind.stmt)
		{
		case variableK:
			if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
				stInsert(t->attr.name, t->lineno, location++, t->attr.scope, "variable", "integer");
			else
				printSemanticError(t, "Variável já declarada.");
			break;

		case functionK:
			if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
			{
				if (t->type == integerK)
					stInsert(t->attr.name, t->lineno, location++, t->attr.scope, "function", "integer");
				else
					stInsert(t->attr.name, t->lineno, location++, t->attr.scope, "function", "void");
			}
			else
				printSemanticError(t, "Função já declarada.");
			break;

		case callK:
			if (strcmp(t->attr.name, "input") == 0 || strcmp(t->attr.name, "output") == 0)
				stInsert(t->attr.name, t->lineno, location++, t->attr.scope, "call", "-");
			else if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
				printSemanticError(t, "Chamada de função inválida.");
			else
				stInsert(t->attr.name, t->lineno, location++, t->attr.scope, "call", "-");
			break;

		case returnK:
			break;

		default:
			break;
		}
		break;

	case expressionK:
		switch (t->kind.exp)
		{
		case idK:
			if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
				printSemanticError(t, "Variável não declarada.");
			else
				stInsert(t->attr.name, t->lineno, 0, t->attr.scope, "variable", "integer");
			break;

		case vectorK:
			if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
				printSemanticError(t, "Vetor não declarado.");
			else
				stInsert(t->attr.name, t->lineno, 0, t->attr.scope, "vector", "integer");
			break;

		case vectorIdK:
			if (statementFinder(t->attr.name, t->attr.scope) == -1 && statementFinder(t->attr.name, "global") == -1)
				printSemanticError(t, "Indice do vetor não declarado.");
			else
				stInsert(t->attr.name, t->lineno, 0, t->attr.scope, "vector index", "integer");
			break;

		case typeK:
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void buildSymtab(TreeNode *syntaxTree)
{
	traverse(syntaxTree, insertNode, nullProc);

	if (statementFinder("main", "global") == -1)
	{
		printf("Função main não foi declarada");
		Error = TRUE;
	}

	if (TraceAnalyze)
	{
		printSymTab(listing);
	}
}

static void checkNode(TreeNode *t)
{
	switch (t->nodekind)
	{
	case expressionK:
		switch (t->kind.exp)
		{
		case operationK:
			break;
		default:
			break;
		}
		break;

	case statementK:
		switch (t->kind.stmt)
		{
		case ifK:
			if (t->child[0]->type == integerK && t->child[1]->type == integerK)
				printSemanticError(t->child[0], "Expressão do IF inválida.");
			break;

		case assignK:
			if (t->child[0]->type == voidK || t->child[1]->type == voidK)
				printSemanticError(t->child[0], "Atribuição de valor não inteiro");
			else if (t->child[1]->kind.stmt == callK)
			{
				if (strcmp(t->child[1]->attr.name, "input") == 0 || strcmp(t->child[1]->attr.name, "output") == 0)
					// nada
					;
				else if (strcmp(statementFinderType(t->child[1]->attr.name, t->child[1]->attr.scope), "void") == 0) {
					printf("%s -> %s\n", t->child[1]->attr.name, statementFinderType(t->child[1]->attr.name, t->child[1]->attr.scope));
					printSemanticError(t->child[1], "Atribuição de função VOID.");
				}
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void typeCheck(TreeNode *syntaxTree)
{
	traverse(syntaxTree, nullProc, checkNode);
}
