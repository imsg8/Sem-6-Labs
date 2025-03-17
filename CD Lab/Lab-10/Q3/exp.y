%{
#include <stdio.h>
#include <stdlib.h>
int result;
%}

%token NUMBER NL

%%
input:expression NL { result = $1;printf("Result: %d\n", result);exit(0);};

expression: NUMBER '+'  NUMBER     { $$ = $1 + $3; }|  NUMBER '-'  NUMBER   { $$ = $1 - $3; }|  NUMBER '*'  NUMBER   { $$ = $1 * $3; }
|  NUMBER '/'  NUMBER   { 
        if ($3 == 0) {
            yyerror("Division by zero");
            exit(1);
        }
        $$ = $1 / $3; 
    };
%%
int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
