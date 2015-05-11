%{
#include "ns_ast.h"
#include <stdio.h>
#include <stdarg.h>


int yylex(void); 
void yyerror(const char *fmt, ...);

#define YYDEBUG  1
%}

%union {
    char *strval;
    int   intval;
    char *fn;
    symbol          *sym;
    node            *ast;
    builtin_func_node   *ast_func;
    assign_node         *ast_assign;
    exp_list_node       *ast_explist;
    rule_list_node      *ast_rules;
    rule_node           *ast_rule;
    stmt_list_node      *ast_stmt_list;
    stmt_if_node        *ast_stmt_if;
    stmt_while_node     *ast_stmt_while;
    stmt_for_in_node    *ast_stmt_if_in;
};

%token  IF ELSE AND OR FOR IN CMP_GT CMP_LS CMP_EQ CMP_LE CMP_GE WHILE CMP_NE
%token  MAIN

%token <strval> STR REGEXSTR
%token <fn>     BUILTIN_FUNC
%token <sym>    IDENTIFIER
%token <intval> NUM_INT

%type <ast>         pattern stmt exp
%type <ast_func>    func_exp 
%type <ast_assign>  assign_exp 
%type <ast_explist> exp_list
%type <ast_rules>   rule_list
%type <ast_rule>    rule
%type <ast_stmt_list>  stmt_list;

/* Lowest to highest */
%right '='
%left OR AND
%nonassoc CMP_GE CMP_LE CMP_LS CMP_EQ CMP_GT CMP_NE
%left '+' '-'
%left '*' '/' '%'

%start start
%%
start: rule_list { if ($1 != NULL) {
                    $1->eval();
                    }
                 }
    | MAIN '{' stmt_list '}'
                { 
                if ($3 != NULL) $3->eval();
                }
    ;
 
rule_list: /* empty */ { $$ = NULL; } 
    | rule_list rule   { 
                            $$ = $1;
                            if ($$ == NULL) {
                                $$ = new rule_list_node;
                            }
                            $$ -> append($2);
                       }
    ;
    
rule: pattern '{' stmt_list '}' { $$ = new rule_node($1, $3); }
    ;

pattern: /* empty */ {$$ = NULL;}
    | REGEXSTR  { $$ = new regex_str_node($1);}
    | STR       { $$ = new str_node($1);}
    ;


stmt:    FOR IDENTIFIER IN IDENTIFIER '{' stmt_list '}'  
                { $$ = new stmt_for_in_node($2, $4, $6); }
        | WHILE '(' exp ')' '{' stmt_list '}'
                { $$ = new stmt_while_node($3, $6); }
        | IF '(' exp ')' '{' stmt_list '}'
                { $$ = new stmt_if_node($3, $6); }
        | IF '(' exp ')' '{' stmt_list '}' ELSE '{' stmt_list '}'
                { $$ = new stmt_if_node($3, $6, $10); }
        | exp ';'
                { $$ = $1; }
        /*
        | BREAK ';'
        | CONTINUE ';'
        */
        ;

stmt_list: /* empty */    { $$ = NULL; }
         | stmt_list stmt {
                            $$  = $1;
                            if ($$ == NULL) {
                                $$ = new stmt_list_node;
                            }

                            $$->append($2);
                           }
        ;

/* expression */
exp:  
    func_exp      {$$ = $1;}
    | assign_exp  {$$ = $1;}
    | '(' exp ')'       { $$ = $2; }
    /* +, -, *, /, operator */
    | exp '+' exp       { $$ = new operator_node('+', $1, $3); } 
    | exp '-' exp       { $$ = new operator_node('-', $1, $3); }
    | exp '*' exp       { $$ = new operator_node('*', $1, $3); }
    | exp '/' exp       { $$ = new operator_node('/', $1, $3); }
    | exp '%' exp       { $$ = new operator_node('%', $1, $3); }

    /* comparation expression */
    | exp CMP_GT exp    { $$ = new compare_node(CMP_GT, $1, $3); }
    | exp CMP_LS exp    { $$ = new compare_node(CMP_LS, $1, $3); }
    | exp CMP_EQ exp    { $$ = new compare_node(CMP_EQ, $1, $3); }
    | exp CMP_NE exp    { $$ = new compare_node(CMP_NE, $1, $3); }
    | exp CMP_LE exp    { $$ = new compare_node(CMP_LE, $1, $3); }
    | exp CMP_GE exp    { $$ = new compare_node(CMP_GE, $1, $3); }
    | exp AND    exp    { $$ = new compare_node(AND, $1, $3);    }
    | exp OR     exp    { $$ = new compare_node(OR, $1, $3);     }
    
    | IDENTIFIER        { $$ = new identifer_node($1);         }
    | STR               { $$ = new str_node($1);               }
    | REGEXSTR          { $$ = new regex_str_node($1);         }
    | NUM_INT           { $$ = new int_node($1);               }
    | array_ref         
    | array_def         
    ;

array_ref: IDENTIFIER '[' exp ']' { $$ = new array_ref_node($1);}
        ;

array_def: '[' exp_list ']' { $$ = new array_def($1); }
         ;

exp_list: /* empty */ {$$ = NULL;}
    | exp             
                    { 
                    $$ = new exp_list_node;
                    $$->append($1);
                    }
    | exp_list ',' exp 
                    { 
                    $$  = $1;
                    if ($$ == NULL) {
                        $$ = new exp_list_node;
                    }

                    $$->append($3);
                    }
    ;

func_exp: BUILTIN_FUNC '(' exp_list ')' 
        { $$ = new builtin_func_node($1, $3); }
    ;

assign_exp: IDENTIFIER '=' exp  { $$ = new assign_node($1, $3);           }  
        | array_ref '=' exp     { $$ = new assign_array_ref_node($1, $3); }
    ;
%%

void yyerror(const char *fmt, ...){
    extern int yylineno;
    extern char * yytext;
    va_list ap;
    va_start(ap, fmt);
    char msg[2048];
    vsnprintf(msg, 2048, fmt, ap);
    printf("* Error *, Line: %d, Token:[%s]. msg: %s \n", yylineno, yytext, msg);
    va_end(ap);
}

