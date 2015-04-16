%option noyywrap
%{
#include <stdio.h> /* just for printf */
enum tokent {
    T_ACTION = 300,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    PATTERN_STR
};

%}

%%
[ \t\n]    ;  /* Skip  whitespaces */
\".*\"      {puts(yytext); return PATTERN_STR; }
"/"         { 
                int c;
                char action[512];
                int i = 0;
                int escapeflg = 0;
                while (1) {
                    c = input();
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
                puts(action);
                return T_ACTION;
            }
"{"         { puts("{"); return '{'; }
"}"         { puts("}"); return '}'; }
.           ECHO;
<<EOF>>     { yyterminate(); }
%%

int main(int argc, char **argv) {
    yyin = fopen("test.miniawk", "r");
    int tok;
    while (tok = yylex()) {
        printf("Token: %d\n", tok); 
    }
    return 0;
}
