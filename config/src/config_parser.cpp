#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <cstdio>
#include <cstdlib>


#include "config.hpp"

/* 
 * * CONFIG FILE SYNTAX: *
 *
 * config_file: stmts
 * stmts      : stmts | stmt '\n'
 * stmt       : keyval_stmt | comment
 * keyval_stmt: keyval | keyval comment
 * keyval     : key delimiter value
 * key        : [A-Za-z0-9_\-]+
 * delimiter  : '='
 * value      : string | number | boolean
 * string     : '"' [^"] '"'
 * boolean    : "on" | "true" | "off" | "false"
 * whitespace : [\t \v\f]+
 * comment:   : #[^\n]*$
 */
conf_parser::conf_parser(std::ifstream& fs, stmt_collector& sc)
    :lex_(fs), look_(),stmt_collector_(sc) {
}

void conf_parser::move(){
    look_ = lex_.scan();
}

void conf_parser::match(int t){
    if (look_.type_ == t){
        move();
    }
    else { //FIXME 
        fprintf(stderr,"syntax error");
        ::exit(-1);
    }
}

void conf_parser::keyval(){
    token key = look_;
    token value;
    move();
    match(T_DELIMITER); 
    switch(look_.type_){
        case T_VALUE_BOOLEAN:
        case T_VALUE_STRING:
        case T_VALUE_NUMBER: value = look_;
                            break;
        default:
            //FIXME: handle error
            fprintf(stderr,"syntax error");
            ::exit(-1);
    }
    move();
    //stmt *stmt = NULL;
    if (look_.type_ == T_COMMENT){
        token c=look_;
        //stmt = new keyvalue_comment_stmt(key, value, look_);
        move();
        match('\n');
        stmt_collector_.add_kvm_stmt(key, value, c);
    }
    else {
        match('\n');
        //stmt = new keyvalue_stmt(key, value);
        stmt_collector_.add_kv_stmt(key, value);
    }
}

void conf_parser::comment(){
    //comment_stmt *c = new comment_stmt(look_);   
    //stmt_list_.push_back(c);
    token c = look_;
    move();
    match('\n');
    stmt_collector_.add_m_stmt(c);
}

void conf_parser::parse(){
    move();
    while (look_.type_ != T_EOF){
        switch (look_.type_){
            case T_KEY:     keyval();
                            break;
            case T_COMMENT: comment();
                            break;
            default:
                move();
                break;
        }
    }
};
/*
std::string& conf_parser::get(const std::string& key){

    keyval_map_T::const_iterator it;   
    it = keyval_map.find(key);
    if (it != keyval_map.end()){
        token t = keyval_map[key];
        return t.value();
    }
    else{
        //TODO:
        //throw key_not_found exception.
        return *(new std::string("KEY WAS NOT FOUND"));
    }
}

void conf_parser::set(const std::string& key, const std::string& value){
    
    token t = token(T_VALUE_STRING,value);
    keyval_map.insert(std::pair<std::string, token>(key, t));

}

void conf_parser::set(const std::string& key, const char * value){
    
    std::string v(value);
    token t = token(T_VALUE_STRING,v);
    keyval_map.insert(std::pair<std::string, token>(key, t));

}

void conf_parser::set(const std::string& key, bool flag){
    
    std::string f = flag ? "true" : "false";

    token t = token(T_VALUE_STRING,f);
    keyval_map.insert(std::pair<std::string, token>(key, t));

}

void conf_parser::save(){
    //fs_.seekp(std::ios_base::beg);
    std::list<stmt *> ::iterator it;
    for(it = stmt_list.begin(); it != stmt_list.end(); ++it){
        //(*it)->str(fs_);
        (*it)->str(std::cout);
    }
//    fs_.flush();
}
*/

conf_parser::~conf_parser(){
    /*
    std::list<stmt *> ::iterator it;
    for(it = stmt_list.begin(); it != stmt_list.end(); ++it){
        //(*it)->str(std::cout);
        safe_del(*it);
    }
    fs_.close();
    */
}

#ifdef _DEBUG
#if 0
std::ostream& operator << (std::ostream& o, stmt& sm){
    sm.print(o);
    return o; 
}
#endif
#endif
