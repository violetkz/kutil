%{
#include <stdio.h>
#include "ns_def.h"
int yylex(void); 
void yyerror(const char *s);

%}

%union {
    char* strval;
    int   func; 
    struct node* ast;
};

%token <strval> STR REGEXSTR IDENTIFIER EOL
%type <ast> stmt  pattern action func_exp param_list
%start start
%%

start: stmt EOL { $1->print(); }

stmt: /* empty */ {$$ = NULL;}
    | pattern '{' action '}' { puts("stmt\n"); 
                              $$ = new stmt_node($1, $3);
                             }
    ;

pattern: /* empty */ {$$ = NULL;}
    | REGEXSTR  {puts("REGEXSTR\n"); $$ = new regex_str_node($1);}
    | STR       {puts("STR\n"); $$ = new str_node($1);}
    ;

explist: /* empty */ {$$ = NULL;}
    | exp { $$ = new exp_node(); }
    | explist exp { $$ = $1->append($2); }
    ;

action:  /* empty */ {$$ = NULL;}
    | func_exp  {puts("action-exp\n"); $$ = $1;}
    ;

func_exp:  IDENTIFIER '(' param_list ')' ';' 
        {puts("func_exp"); $$ = new builtin_func_node($1, $3); }
    ;

param_list:  /* empty */ {puts("param_list empty\n"); $$ = NULL; }
    | IDENTIFIER  {
        puts("IDENTIFIER");
        $$ = new func_paramter_node($1); 
        }
    | param_list ',' IDENTIFIER  {
            puts("param_list,IDENTIFIER\n");
            func_paramter_node* pl = static_cast<func_paramter_node *>($1);
            $$ = pl->append(new func_paramter_node($3));
            };

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
