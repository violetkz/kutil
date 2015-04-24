%option noyywrap nodefault yylineno
%{

#include "ns_def.h"
#include "ns.tab.h"
extern void yyerror(const char *s);

char *makebuffer(size_t n);

%}
%%
[ \t\n]    ;   /* Skip  whitespaces */
[A-Za-z0-9_]+  { yylval.strval = strdup(yytext); printf("lex: %s\n",yylval.strval);
                 return IDENTIFIER; }
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
