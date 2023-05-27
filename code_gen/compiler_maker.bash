#!/bin/bash
flex javaComp.lex && bison -d javaComp.y && gcc -o miniJavaCompiler javaComp.tab.c lex.yy.c