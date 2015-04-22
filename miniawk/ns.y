%{
#include "ns_def.h"
int yylex(void); 
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
    | func_exp  {$$ = $1;}
    ;

func_exp:  IDENTIFIER '(' param_list ')' 
        { $$ = new builtin_func_node(func_name, $3); }
    ;

param_list:  /* empty */ {$$ = new func_paramter_list; }
    | IDENTIFIER  { $$ = $$->append($1); }
    | param_list ',' IDENTIFIER  { $$ = $1->append($3); };

%%


int main(void) {
  yyparse();
  }
