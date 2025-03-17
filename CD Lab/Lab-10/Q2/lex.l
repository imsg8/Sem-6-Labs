%{
#include "exp.tab.h"
%}

%%
if { return IF; }
else { return ELSE; }
[0-9]+ {return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
"("  { return '('; }
")"  { return ')'; }
"{"  { return '{'; }
"}"  { return '}'; }
";"  { return ';'; }
"<"  { return '<'; }
"==" { return EQUALS; }
"="  { return ASSIGN; }
"+"  { return '+'; }
"$"  {return NL; }
%%
