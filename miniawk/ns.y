%{
#include <stdio.h>
#include "ns_def.h"
int yylex(void); 
void yyerror(const char *s);

%}

%union {
    char* strval;
    struct node*      ast;
    struct exp_node*  ast_exp;
    struct func_paramter_node* ast_param;
};

%token <strval> STR REGEXSTR IDENTIFIER 
%type <ast>     stmt  pattern 
%type <ast_exp> func_exp assign_exp exp explist 
%type <ast_param>  param param_list

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
            /* $$ = $1;

               if (!$$) {
                    $$ = new std::list<exp_node* >;
                    $$->push_back($2);
               } else {
                    $$->push_back($2);
               }
               
             */
                    if ($1 == NULL) {
                        $$ = $2;
                    }
                    else {
                        exp_node* e = static_cast<exp_node *>($1);
                        $$ = e->append($2);
                    }
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

param_list:  /* empty */ { $$ = NULL; }
    | param  
    | param_list ',' param  {
            
            func_paramter_node* pl = static_cast<func_paramter_node *>($1);
            $$ = pl->append($3);
            };

param: IDENTIFIER  {$$ = new func_paramter_node($1);}
     | STR  {$$ = new func_paramter_node($1);}

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
