#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "config_lexer.hpp"


int main(int argv, char *args[]){
    for (int i = 1; i < argv; ++i){
        std::ifstream f(args[i]);
        if (f.bad()) {
            fprintf(stderr, "open file failed");
            ::exit (-1);
        }
        lexer a(f);
        token t; 
        do {
            t = a.scan();
            //std::cout << t->type_ << std::endl;
            //std::cout << t->str() << std::endl;
            std::cout << t;
        }while (t.type_ != T_EOF);
    }
}

