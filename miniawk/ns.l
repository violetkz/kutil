%option noyywrap nodefault yylineno
%{
#include "ns.tab.h"
%}
%%
[ \t\n]    ;  /* Skip  whitespaces */
[A-Za-z0-9_]+  { yylval.strval = strdup(yytext); return  IDENTIFIER; }
\".*\"      { yylval.strval = strdup(yytext); return STR; }
"/"         { 
                int c;
                char action[1024];
                int i = 0;
                int escapeflg = 0;
                while (i < 1024) { 
                    c = yyinput();
                    if (c == EOF || c == '\0') {
                        puts("[error]: bad action str.\n");
                        yyterminate();
                    }
                    if (escapeflg == 0) {  /* the presourse char is not escape char */
                        if (c == '/')  break;
                        if (c != '\\') action[i++] = c;
                        else {
                            escapeflg = 1; /* set escapeflg as True */
                        }

                    }
                    else { 
                        if (c == '/') {
                            action[i++] = c;
                        }
                        else {
                            action[i++] = '\\';
                            action[i++] = 'c';
                        }
                        escapeflg = 0;
                    }
                }
                action[i] = '\0';
                yylval.strval = strdup(action);
                return REGEXSTR;
            }
"," |
"{" |
"}" |
")" |
"("         {return yytext[0];}
.           {yyerror("unkown token. %c\n", *yytext);}
%%
