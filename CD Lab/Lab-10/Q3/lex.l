%{
#include "exp.tab.h"
%}

%%
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"(" { return '('; }
")" { return ')'; }
"$" { return NL; }
%%
