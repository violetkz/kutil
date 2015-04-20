%{
#include "ns_def.h"
%}

%union {
    char* strval;
    int   func; 
    struct node* ast;
};

%token <strval> STR REGEXSTR IDENTIFIER
%type <ast> stmt  pattern action func_exp param_list
%start stmt
%%

stmt: /* empty */ {$$ = NULL;}
    | pattern '{' action '}' { $$ = new stmt_node($1, $3); }
    ;

pattern: /* empty */ {$$ = NULL;}
    | REGEXSTR  {$$ = $1;}
    | STR       {$$ = $1;}
    ;

action:  /* empty */ {$$ = NULL;}
    | func_exp  {$$ = $1; }
    ;

func_exp:  IDENTIFIER '(' param_list ')' 
        { $$ = new builtin_func_node(func_name, $3); }
    ;

/* FIXME */
param_list:  /* empty */ {$$ = NULL; }
    | IDENTIFIER  { $$ = new func_paramter_list($1); }
    | param_list ',' IDENTIFIER  { $$ = append_param($1, $3); };

%%

