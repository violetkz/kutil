%{
#include <stdio.h>
#include "ns_def.h"
int yylex(void); 
void yyerror(const char *s);

#define YYDEBUG  1
%}

%union {
    char* strval;
    node*               ast;
    builtin_func_node*  ast_func;
    exp_node*           ast_exp;
    assign_node*        ast_assign;
    explist_node*       ast_explist;
    paramter_list_node* ast_param_list;
    func_paramter_node* ast_param;
};

%token <strval> STR REGEXSTR IDENTIFIER 
%type <ast>         stmt pattern param 
%type <ast_exp>     exp
%type <ast_func>    func_exp 
%type <ast_assign>  assign_exp 
%type <ast_explist> explist
%type <ast_param_list> param_list

%start start
%%
start: stmt  { $1->print();}

stmt: /* empty */             { $$ = NULL;}
    | pattern '{' explist '}' { $$ = new stmt_node($1, $3); }
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

exp:  
    func_exp      {$$ = $1;}
    | assign_exp  {$$ = $1;}
    ;

func_exp:  IDENTIFIER '(' param_list ')' ';' 
        {$$ = new builtin_func_node($1, $3); }
    ;

assign_exp: IDENTIFIER '=' STR ';'  { $$ = new assign_node($1, $3); }  

param_list:  /* empty */ { $$ = NULL;}
    | param  { 
                if($$ == NULL) {
                    $$ = new paramter_list_node; 
                    $$->append($1);
                }
             }
    | param_list ',' param 
        {   $$ = $1;
            if ($$ == NULL) {
                $$ = new paramter_list_node;
            }
            $$->append($3);
        };

param: IDENTIFIER { $$ = new identifer_node($1); }
     | STR        { $$ = new str_node($1); }
     ;

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
