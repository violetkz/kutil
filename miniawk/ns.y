
%{
#include "ns_def.h"
%}

%%

smst: /* empty */ {$$ = NULL;}
    | pattern '{' action '}' { $$ = node_new(smst_node, $1, $2); }
    ;

pattern: /* empty */ {$$ = NULL;}
    | regexstr  {$$ = $1;}
    | str       {$$ = $1;}

action:  /* empty */ {$$ = NULL;}
    | func_exp  {$$ = node_new(func_exp_node, $1, NULL); }
    
%%
