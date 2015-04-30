%{
#include <stdio.h>
#include "ns_def.h"
int yylex(void); 
void yyerror(const char *s);

#define YYDEBUG  1
%}

%union {
    char* strval;
    int   intval;
    char* fn;
    symbol*             sym;
    node*               ast;
    builtin_func_node*  ast_func;
    exp_node*           ast_exp;
    assign_node*        ast_assign;
    explist_node*       ast_explist;
    paramter_list_node* ast_param_list;
    func_paramter_node* ast_param;
    rule_list_node*     ast_rules;
    rule_node*          ast_rule;
};

%token  IF ELSE AND OR FOR IN

%token <strval> STR REGEXSTR
%token <fn>     BUILTIN_FUNC
%token <sym>    IDENTIFIER
%token <intval> NUM_INT

%type <ast>         pattern param rvalue
%type <ast_exp>     exp
%type <ast_func>    func_exp 
%type <ast_assign>  assign_exp 
%type <ast_explist> explist
%type <ast_param_list> param_list
%type <ast_rules>   rule_list
%type <ast_rule>    rule

%start start
%%
start: rule_list { if ($1 != NULL) {
                    $1->print();
                    $1->eval();
                    }
                 }
 
rule_list: /* empty */ { $$ = NULL; } 
    | rule_list rule   { 
                            $$ = $1;
                            if ($$ == NULL) {
                                $$ = new rule_list_node;
                            }
                            $$ -> append($2);
                       }
    ;
    
rule: pattern '{' explist '}' { $$ = new rule_node($1, $3); }
    ;

pattern: /* empty */ {$$ = NULL;}
    | REGEXSTR  { $$ = new regex_str_node($1);}
    | STR       { $$ = new str_node($1);}
    ;

explist: /* empty */ {$$ = NULL;}
    | explist exp { 
                    $$  = $1;
                    if ($$ == NULL) {
                        $$ = new explist_node;
                    }

                    $$->append($2);
                  }
    ;

stmt:    FOR IDENTIFIER IN IDENTIFIER '{' stmt_list '}'  
                {  $$ = new stmt_for_in_node($2, $4, $6); }
        | WHILE '(' exp ')' '{' stmt_list '}'
                { $$ = new stmt_while_node($3, $6); }
        | IF '(' exp ')' '{' stmt_list '}'
                { $$ = new stmt_if_node($3, $6); }
        | IF '(' exp ')' '{' stmt_list '}' ELSE '{' stmt_list '}'
                { $$ = new stmt_if_else_node($3, $6, $10); }
        | exp ';'
                { $$ = new stmt_node($1); }

stmt_list: /* empty */ 
         | stmt_list, stmt

/* expression */
exp:  
    func_exp      {$$ = $1;}
    | assign_exp  {$$ = $1;}
    | '(' exp ')'       { $$ = $2; }
    | exp '+' exp       { $$ = new operator_node('+', $1, $3); } 
    | exp '-' exp       { $$ = new operator_node('-', $1, $3); }
    | exp '*' exp       { $$ = new operator_node('*', $1, $3); }
    | exp '/' exp       { $$ = new operator_node('/', $1, $3); }
    | exp CMP exp       { $$ = new compare_node($2, $1, $3);   }
    | IDENTIFIER        { $$ = new identifer_node($1);         }
    | STR               { $$ = new str_node($1);               }
    | REGEXSTR          { $$ = new regex_str_node($1);         }
    | NUM_INT           { $$ = new int_node($1);               }
    ;

func_exp: BUILTIN_FUNC '(' param_list ')' 
        {$$ = new builtin_func_node($1, $3); }
    ;

assign_exp: IDENTIFIER '=' exp  {
              $$ = new assign_node($1, $3);
          }  

param_list:  /* empty */ { $$ = NULL;} 
    | param { $$ = new paramter_list_node;
              $$->append($1);
            }
    | param_list ',' param 
        {   $$ = $1;
            if ($1 == NULL) {
                $$ = new paramter_list_node;
            }
            $$->append($3);
        }
    ;

param: exp { $$ = $1; }
/*
param: IDENTIFIER { $$ = new identifer_node($1);}
     | STR        { $$ = new str_node($1);}
     | NUM_INT    { $$ = new int_node($1);}
     ;
*/

%%

void yyerror(const char *s) {
    extern int yylineno;
    extern char * yytext;
    printf("[Error], Line: %d, Msg: [%s] \n", yylineno, yytext);
}

int main(void) {
  extern FILE* yyin;
  yyin = fopen("test.miniawk", "r");
  yyparse();
  return 0;
}
