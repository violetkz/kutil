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
bool strcmp_ncase(const std::string& a, const std::string& b)
{   
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

lexer::lexer(std::ifstream& fio):io(fio) {
    memset(&stat_, 0x00, sizeof(stat_));
}

void lexer::scan_word(std::string& s){
    do{
        s.push_back(stat_.c);
        stat_.c = io.get();
    }while(isalpha(stat_.c) || isalnum(stat_.c) || stat_.c == '_' );
    io.putback(stat_.c); 
}

void lexer::scan_number(std::string& s){
    do{
        s.push_back(stat_.c);
        stat_.c = io.get();
    } while(isalnum(stat_.c));
    io.putback(stat_.c); 
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
    stat_.c = io.get();
    while (!io.eof()){
        if (stat_.c ==' ' || stat_.c == '\t' || stat_.c == '\r') {
            stat_.c = io.get();
            continue;
        }
        else{ //io.putback(stat_.c);
            break;
        }
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
