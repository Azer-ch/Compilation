#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

typedef enum
{
    NODE_TYPE_UNKNOWN,
    tInt,
    tBoolean,
    tString,
    tVoid
} TYPE_IDENTIFIER;

typedef enum
{
    CLASS_UNKNOWN,
    variable,
    function,
    parametre,
    attribute,
    classs
} CLASS;

struct NODE
{
    char * name;
    TYPE_IDENTIFIER type;
    CLASS classs;
    int isInit;
    int isUsed;
    int nbParam;
    struct NODE *next;
};
typedef struct NODE *NODE;
typedef NODE TABLE_NODE;

NODE create(const char *name, TYPE_IDENTIFIER type, CLASS classe, NODE suivant);
NODE insert(NODE noeud, TABLE_NODE table);
NODE search(const char *name, TABLE_NODE table);

void checkID(char *name);
void checkVarID(char *name);
int checkIDDeclare(char *name);
void checkFuncIDDeclare(char *name);
void initVar(char *name);
void checkVarInitialise(char *name);
void endFunction();
void endClass();
void destructSymbolsTable(TABLE_NODE SymbolsTable);
void displaySymbolsTable(TABLE_NODE SymbolsTable);
void checkFuncID(char *name);
void checkClassID(char *name);
void funcDecEnd();
void funcCallEnd();
void checkID(char *name);
int checkIDDeclareOnInit(char *name);
void checkIDOnInit(char *name);
char *concat(const char *s1, char *s2);
void semanticWarning(char *str);
void semanticError(const char *str);

#endif // SEMANTIC_H_INCLUDED