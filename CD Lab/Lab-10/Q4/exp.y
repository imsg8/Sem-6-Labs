%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex();
void yyerror(const char *s);
%}

%token NUM NL

%%
i : input NL {printf("Valid");exit(0);};

input:input line | ;

line:'\n'| exp '\n';

exp:
    NUM
    | exp exp '+'
    | exp exp '-'
    | exp exp '*'
    | exp exp '/' { 
        if ($2 == 0) {
            yyerror("Division by zero");
            exit(1);
        }
        $$ = $1 / $2; 
    }
    | exp exp '^'
    | exp 'n'
    ;
%%
int main() {
    printf("Enter postfix expressions :\n");
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
