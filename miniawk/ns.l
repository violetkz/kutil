%option noyywrap nodefault yylineno
%{

#include "ns_def.h"
#include "ns.tab.h"
extern void yyerror(const char *s);

char *makebuffer(size_t n);

%}
%%
[ \t\n]    ;   /* Skip  whitespaces */

"if"    { return IF;  } 
"else"  { return ELSE;}
"for"   { return FOR; }
"in"    { return IN;  }
"and"   { return AND; }
"or"    { return OR;  }

">"     { return CMP_GT; }
"<"     { return CMP_LS; }
"=="    { return CMP_EQ; }
">="    { return CMP_GE; }
"<="    { return CMP_LE; }


"len"    |
"substr" |
"split"  |
"print"  |
"getline"  {yylval.fn = strdup(yytext); return BUILTIN_FUNC;}

[0-9]+     {yylval.intval = atoi(yytext); return NUM_INT;}
[A-Za-z_][A-Za-z0-9_]*  { 
                yylval.sym = install_symbol(yytext);
                /* yylval.strval = yytext;  */
                return IDENTIFIER; 
               }
\"[^"]*\"      { yylval.strval = strdup(yytext); return STR; }
"/"            { 
                int c;
                int i = 0;
                int escapeflg = 0;
                
                char* buff = makebuffer(1024);
                while (i < 1024) { 
                    c = yyinput();
                    if (c == EOF || c == '\0') {
                        puts("[error]: bad regex str.\n");
                        yyterminate();
                    }
                    if (escapeflg == 0) {  /* the presourse char is not escape char */
                        if (c == '/')  break;
                        if (c != '\\') buff[i++] = c;
                        else {
                            escapeflg = 1; /* set escapeflg as True */
                        }

                    }
                    else { 
                        if (c == '/') {
                            buff[i++] = c;
                        }
                        else {
                            buff[i++] = '\\';
                            buff[i++] = 'c';
                        }
                        escapeflg = 0;
                    }
                }
                buff[i] = '\0';
                yylval.strval = buff;;
                return REGEXSTR;
            }
"[" |
"]" |
"=" |
";" |
"," |
"{" |
"}" |
")" |
"("         {return yytext[0]; }


.           { yyerror("unkown token."); }
%%

char* makebuffer(size_t n) {
    char* buff = (char *)malloc(n);
    memset(buff, 0x00, n);
    return buff;
}

void free_strval(char *s) {
    if (s != NULL) free(s);
}
