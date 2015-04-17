%{
#include <vector>
#include <string>
#include "ast.hpp" 

%union {
ast         *t;
symbol      *s;
symlist     *sl;
int         fn;
}

%token <s> ACTION;
%token <fn> FUNC;
%token EOL

%token IF ESLE
%right '='

%type <t> expression expression_list rule pattern action pattern_action_list

%start start
%}

%%
start : empty pattern_action_list 

empty: 
     { /* do nothing */; }
     ;

pattern_action_list:
   pattern_action             { $$ = node($1, node_rule_list, NULL); }
   | pattern_action_list rule { $$ = append_right($1, node($2, node_rule_list, NULL));}
   ;

rule : pattern action         { $$ = node($1, node_rule, $2); }
     ;

pattern: /* empty */          { $$ = NULL;}
       | conditional          { $$ = $1; }
     
action: /* empty */
      | expression            { $$ = $1; }
      | '{' expression_list '}' { $$ = $2 }

expression_list: 
      expression    {$$ = node($1, node_expression, NULL);}
      | expression_list expression { $$ = append_right($1,   node($1, node_expression, NULL)) }

expression:
          | IF_expression   {$$ = node($1, if_expression, NULL);}
          | Assign_expression { $$ = $1 };
          | FUNC_expression   { $$ = node($1, func, NULL); }

%%
                   
