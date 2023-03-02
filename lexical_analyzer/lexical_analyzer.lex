%option yylineno

DELIM     [ \t]
BL        {DELIM}+
SEMICOLON ";"
DIGIT   [0-9]
LETTER    [a-zA-Z]

INTEGER_LITERAL ("-")?{DIGIT}+
BOOLEAN_LITERAL true|false
STRING_LITERAL \"[^\n"]*\"
NULL_LITERAL null

KEYWORDS "class"|"static"|"extends"
ACCESS "public"|"private"|"protected"|""
DATATYPE "int"|"boolean"|"void"|"String"
CONDITIONAL "if"|"else"|"else if"|"switch"|"case"
ITERATIVE "for"|"while"|"do"
IMPORT "import"[^\n]*";"

ARITH_OP "+"|"-"|"/"|"%"|"*";
LOGICAL_OP "&&"|"||"|"!"|"!="
REL_OP "<"|">"|"<="|">="|"=="
UNARY "++"|"--"

IDENTIFIER        ({LETTER}|"_")({LETTER}|{DIGIT}|"_")*
NONIDENTIFIER  {DIGIT}({LETTER}|{DIGIT}|"_")*

OPENING_PARENTHESIS  \(
CLOSING_PARENTHESIS  \)

OPENING_CURLY_BRACKETS  \{
CLOSING_CURLY_BRACKETS  \}

OPENING_BRACKET  \[
CLOSING_BRACKET  \]

COMMENT       "//".*|"/*"(.*[\n].*)*"*/"

%%

{IMPORT} {printf("%s\t==> IMPORT\n",yytext);}

{BL}                                  /* no actions */

"\n"			                      /* no actions */


{COMMENT}         		      /* no actions */

{CONDITIONAL} { printf("%s\t==> CONDITIONAL\n",yytext);}

{ITERATIVE} {printf("%s\t==> ITERATIVE CONSTRUCT\n",yytext);}

{DATATYPE}  {printf("%s\t==> DATATYPE\n",yytext);}

{ACCESS} {printf("%s\t==> ACCESS SPECIFIER\n",yytext);}

{KEYWORDS} {printf("%s\t==> KEYWORDS\n",yytext);}

{IDENTIFIER} {printf("%s\t==> IDENTIFIER\n",yytext);}

{INTEGER_LITERAL}                           { printf( "%s\t ==> INTEGER_LITERAL \n",yytext) ; }

{BOOLEAN_LITERAL}                           { printf( "%s\t ==> BOOLEAN_LITERAL \n",yytext) ; }

{STRING_LITERAL}                            { printf( "%s\t ==> STRING_LITERAL \n",yytext) ; }

{NONIDENTIFIER} {printf("%s\t==> NONIDENTIFIER\n",yytext);}

"System.out.println"                        { printf("%s\t ==> PRINT KEYWORD \n",yytext); }
"this"                                      { printf("%s\t ==> THIS KEYWORD \n",yytext); }
"new"                                       { printf("%s\t ==>  NEW OPERATOR \n",yytext); }
"=" {printf("%s\t==> ASSIGNMENT OP\n",yytext);}

{SEMICOLON} {printf("%s\t==> SEMICOLON\n",yytext);}

{UNARY} {printf("%s\t==> UNARY OP\n",yytext);}

{ARITH_OP} {printf("%s\t==> ARITHMETIC OPERATOR\n",yytext);}

{LOGICAL_OP} {printf("%s\t==> LOGICAL OP\n",yytext);}

{REL_OP} {printf("%s\t==> RELATIONAL OP\n",yytext);}

{OPENING_PARENTHESIS}                     {printf("%s\t ==> PARENTHESIS_OPEN \n",yytext);}

{CLOSING_PARENTHESIS}                    {printf("%s\t ==> PARENTHESIS_CLOSE \n ",yytext);}

{OPENING_BRACKET}                        {printf("%s\t ==> BRACKET_OPEN \n ",yytext);}

{CLOSING_BRACKET}                                   {printf("%s\t ==> BRACKET_CLOSE \n",yytext);}

{OPENING_CURLY_BRACKETS}                            {printf("%s\t ==> CURLY_BRACKET_OPEN \n ",yytext);}

{CLOSING_CURLY_BRACKETS}                             {printf("%s\t ==> CURLY_BRACKET_CLOSE \n ",yytext);}

%%
int main(int argc, char *argv[])
{
     yyin = fopen(argv[1], "r");
     yylex();
     fclose(yyin);
}



int yywrap()
{

}