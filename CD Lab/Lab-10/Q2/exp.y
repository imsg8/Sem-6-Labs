%{
#include<stdio.h>
#include<stdlib.h>
%}
%token IF ELSE NUMBER IDENTIFIER ASSIGN EQUALS NL
%%
program : if_statement NL {printf("valid");exit(0);};

if_statement : IF '(' condition ')' '{' statements '}' ELSE '{' statements '}' | IF '(' condition ')' '{' statements '}';

condition : NUMBER | IDENTIFIER '<' NUMBER | NUMBER EQUALS NUMBER;

statements: statement | statements statement;

statement : IDENTIFIER ASSIGN expression ';';

expression: NUMBER | IDENTIFIER | expression '+' expression;
%%
int yyerror(char *msg)
{
printf("Invalid Expression\n");
exit(0);
}
void main ()
{
printf("Enter the expression\n");
yyparse();
}