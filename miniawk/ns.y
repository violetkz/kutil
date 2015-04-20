
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
    | func_exp  {$$ = $1; }

func_exp:  func_name '(' param_list ')'  { $$ = builtin_func_node(func_name, $3); }

param_list:  /* empty */ {$$ = NULL; }
    | param  { $$ = func_paramter_list($1); }
    | param_list ',' param  { $$ = append_param($1, $2); };

%%

