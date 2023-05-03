#include "semantic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TABLE_NODE table, local_table, class_table;

NODE g_node, g_nodeFunc, g_nodeClass;

TYPE_IDENTIFIER g_type;
int g_IfFunc;
int g_IfFuncParameters;
int g_IfClass;
int g_nbParam;

NODE create (const char* name, TYPE_IDENTIFIER type, CLASS classs, NODE next){
    NODE node = (NODE)malloc(sizeof(struct NODE));
    node->name = (char *)malloc(strlen(name)+2);
    strcpy(node->name, name);
    node->type = type;
    node->isUsed = 0;
    node->isInit = 0;
    node-> nbParam = 0;
    node->classs = classs;
    node->next = next;
    return node;
}

NODE insert (NODE node, TABLE_NODE table) {
    if( !table ) {
        return node;
    }
    else {
        NODE last = table;
        while( last->next ) {
            last = last->next;
        }
        last->next = node;
        return table;
    }
}

NODE search (const char* name, TABLE_NODE table) {
    if( !table )
        return NULL;
    NODE node = table;
    while( node ){
        if (strcmp(name, node->name) == 0){
            return node;
        }
        node = node->next;
    }
    return NULL;
}


void destructSymbolsTable( TABLE_NODE table )
{
    if( !table )
        return;
    NODE node = table;
    while( node )
    {
        free(node->name);
        free(node);
        node = node->next;
    }
}


void displaySymbolsTable( TABLE_NODE SymbolsTable ){
    if( !SymbolsTable )
        return;
    NODE Node = SymbolsTable;
    while( Node )
    {
        switch( Node->type )
        {
            case tInt :
                printf("int ");
                break;

            case tBoolean :
                printf("boolean ");
                break;

            case tString :
                printf("string ");
                break;

            case tVoid :
                printf("void ");
                break;

            case NODE_TYPE_UNKNOWN :
                switch (Node->classs)
                {
                    case classs:
                        printf("class ");
                        break;

                    default:
                        break;
                }
                break;

            default :
                printf("Unknown ");
        }

        switch (Node->classs)
        {
            case variable:
                printf("variable ");
                break;

            case parametre:
                printf("parametre ");
                break;

            case function:
                printf("function ");
                break;
            case attribute:
                printf("attribute ");
                break;
            default:
                break;
        }

        printf("%s %d %d", Node->name, Node->isUsed, Node->isInit);
        printf("\n");

        Node = Node->next;
    }
}


void checkVarID (char* name){
    CLASS classs;
    if (g_IfFunc){
        if (g_IfFuncParameters){
            classs = parametre;
            g_nbParam ++;
        }else{
            classs = variable;
        }
        if(search(name, local_table) ){
            semanticError(concat("variable identifier already defined: ", name));
        }else{
            NODE node = create(name, g_type, classs, NULL);
            local_table = insert(node, local_table);

        }
    }
    else{
        if(search(name, table) ){
            semanticError(concat("attribute identifier already defined: ", name));
        }else{
            NODE node = create(name, g_type, attribute, NULL);
            table = insert(node, table);
        }
    }
}

void checkFuncID (char* name){
         if( search(name, table) ){
                                semanticError(concat("function  already defined: ", name));
                            }else{
                                g_nodeFunc = create(name, g_type, function, NULL);
                                table = insert(g_nodeFunc, table);
                            }
                            g_IfFunc = 1;
                            g_IfFuncParameters = 1;
                            g_nbParam = 0;
}

void checkClassID (char* name){
         if( search(name, class_table) ){
                                semanticError(concat("class already defined: ", name));
                            }else{
                                g_nodeClass = create(name, NODE_TYPE_UNKNOWN, classs, NULL);
                                class_table = insert(g_nodeClass, class_table);
                            }
                            g_IfClass = 1;
}

void funcDecEnd(){
    if(!g_nodeFunc)
        return;
    g_nodeFunc->nbParam = g_nbParam;
    g_nbParam = 0;
    g_IfFuncParameters = 0;
}

void funcCallEnd(){
    if(!g_nodeFunc)
        return;
    if ( g_nodeFunc->nbParam != g_nbParam){
								semanticError(concat("wrong number of parameters in method call:  ", g_nodeFunc->name));
                                fprintf(stderr,"expected %d parameter(s) found %d\n",g_nodeFunc->nbParam,g_nbParam);
    }
    g_nbParam = 0;
}

int checkIDDeclare (char* name){
    NODE node;
    if (g_IfFunc){
        node = search(name, local_table);
        if ( !node ){
            node = search(name, table);
            if( !node ){
                semanticError(concat("variable undeclared: ", name));
                return 0;
            }else
            {
                node->isUsed = 1;
            }
        }else
        {
            node->isUsed = 1;
        }
    }else{
        node = search(name, table);
        if( !node ){
            semanticError(concat("variable undeclared: ", name));
            return 0;
        }else
        {
            node->isUsed = 1;
        }
    }
    return 1;
}

int checkIDDeclareOnInit (char* name){

    NODE node;
    if (g_IfFunc){
        node = search(name, local_table);
        if ( !node ){
            node = search(name, table);
            if( !node ){
                semanticError(concat("variable undeclared: ", name));
                return 0;
            }
        }
    }else{
        node = search(name, table);
        if( !node ){
            semanticError(concat("variable undeclared: ", name));
            return 0;
        }
    }
    return 1;
}

void initVar (char* name,int lineNumber){
    NODE node;
    if (g_IfFunc){
        node = search(name, local_table);
        if ( !node ){
            node = search(name, table);
        }
    }else{
        node = search(name, table);
    }
    node->isInit = 1;
    node->lineNumber = lineNumber;
}

void checkVarInitialise (char* name){

    NODE node;

    if (g_IfFunc){
        node = search(name, local_table);
        if ( !node ){
            node = search(name, table);}
    }else{
        node = search(name, table);
    }
    if(node && node->classs == variable && !node->isInit)
        semanticError(concat("variable not initialised: ", name));
    if(node && node->classs == attribute && !node->isInit)
        semanticError(concat("attribute not initialised: ", name));
}

void endFunction()
{
    NODE tmp_table;
    if (g_IfFunc == 1){
        g_IfFunc = 0;
        tmp_table = local_table;
        local_table = NULL;
    }
    while( tmp_table!=NULL ){
        if (tmp_table->classs == variable && !tmp_table->isUsed)
        {
            semanticWarning(tmp_table->name,tmp_table->lineNumber);
        }
        tmp_table = tmp_table->next;
    }
}

void endClass()
{
    if (g_IfClass == 1){
        g_IfClass = 0;
        table = NULL;
    }
}



void checkID(char* name){
    if(checkIDDeclare(name)) {
        checkVarInitialise(name);
    }
}

void checkFuncIDDeclare(char* name){
    NODE node;
        node = search(name, table);
        if( !node ){
            semanticError(concat("function not declared: ", name));
            g_nodeFunc=NULL;
        }else
        {
            g_nodeFunc=node;
        }
}



void checkIDOnInit(char* name,int lineNumber){
    if(checkIDDeclareOnInit(name)) {
        initVar(name,lineNumber);
    }
}


char* concat(const char* s1, char* s2){
    char* message;
    message = malloc(strlen(s1)+ strlen(s2)+2);
    strcpy(message, s1);
    strcat(message, s2);
    return message;
}