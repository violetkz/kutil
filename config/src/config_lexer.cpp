/*
 * ===========================================================================
 *
 *       Filename:  confile_lexer.cpp
 *    Description:  the lexer implenmention for configure file parser.
 *
 *        Version:  1.0
 *        Created:  2012/3/7 17:08:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *
 * ==========================================================================
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "config_lexer.hpp"

// compare std::string without case.
bool strcmp_ncase(const std::string& _f1, const std::string& _f2)
{   
    size_t len = _f1.size();
    if ( len != _f2.size())
        return false;

    std::string _f1_lower;
    std::string _f2_lower;

    _f1_lower.reserve(len);
    _f2_lower.reserve(len);

    std::transform(_f1.begin(), _f1.end(), _f1_lower.begin(), ::tolower);
    std::transform(_f2.begin(), _f2.end(), _f2_lower.begin(), ::tolower);

    return _f1.compare(_f2) == 0;    
}

lexer::lexer(std::ifstream& fio):io(fio) {
    memset(&stat_, 0x00, sizeof(stat_));
}

void lexer::scan_word(std::string& s){
    do{
        s.push_back(stat_.c);
        stat_.c = io.get();
    }while(isalpha(stat_.c) || isalnum(stat_.c) || stat_.c == '_' );
}

void lexer::scan_number(std::string& s){
    do{
        s.push_back(stat_.c);
        stat_.c = io.get();
    } while(isalnum(stat_.c));
}

void lexer::scan_string(std::string& s){
    stat_.c = io.get(); //skip char '"'
    while(!io.eof() && stat_.c != '"') {
        s.push_back(stat_.c);
        stat_.c = io.get();
    }
    if (stat_.c != '"'){
        std :: cout << "string failed" << std::endl;
    }
}

void lexer::scan_comment(std::string& s){
    while(!io.eof() ) {
        if(stat_.c == '\n' || stat_.c == '\r') {
            // Need put back the char '\n'and '\r' to iostream 
            // to help make the token(T_LINEBREAK");
            io.putback(stat_.c); 
            break;
        }
        else{
            s.push_back(stat_.c);
            stat_.c = io.get();
        }
    }
}

void lexer::skip_white(){
    while (!io.eof()){
        stat_.c = io.get();
        if (stat_.c ==' ' || stat_.c == '\t' || stat_.c == '\r') {
            continue;
        }
        else break;
    }
}

token lexer::scan(){
    skip_white();
    
    //token t;
    //TODO: I think there are some way to avoid use tmp string.
    //std::string& tmp = t.value();
    std::string tmp;
    if (isalpha(stat_.c)){
        scan_word(tmp);
        if (strcmp_ncase(tmp, "on") 
            || strcmp_ncase(tmp, "true")
            || strcmp_ncase(tmp, "off") 
            || strcmp_ncase(tmp, "false")){
            return token(T_VALUE_BOOLEAN, tmp);
        }
        return token(T_KEY, tmp);
    }
    else if (isalnum(stat_.c)){
        scan_number(tmp);
        return token(T_VALUE_NUMBER, tmp);
    }
    else if (stat_.c == '"'){
        scan_string(tmp);
        return token(T_VALUE_STRING, tmp);
    }
    else if (stat_.c == '#') {
        scan_comment(tmp);
        return  token(T_COMMENT,tmp); 
    }
    else if (stat_.c == '=') {
        return token(T_DELIMITER);
    }
    else if (stat_.c == '\n') {
        stat_.linenumber++;
        return token(stat_.c);
    }
    return token(stat_.c);
}

#ifdef _debug_lexer
int main(int argv, char *args[]){
    for (int i = 1; i < argv; ++i){
        std::ifstream f(args[i]);
        if (f.bad()) {
            fprintf(stderr, "open file failed");
            exit (-1);
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
#endif
