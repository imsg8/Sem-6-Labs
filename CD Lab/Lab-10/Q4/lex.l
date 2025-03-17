%{
#include "exp.tab.h"
%}

%%
[0-9]+ { return NUM; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"^" { return '^'; }
"n" { return 'n'; }
"$" {return NL; }
"\n" { return '\n'; }
%%
