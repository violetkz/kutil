
#include "config_stmts.hpp"
#include "config_lexer.hpp"
#include <fstream>
#include <iostream>


/*
 * comment_stmt 
 */

comment_stmt::comment_stmt(token& comment)
    :comment_(comment) {
}

#ifdef _DEBUG
void comment_stmt::print(std::ostream& o){
    o <<"#" << comment_ ;
}
#endif

void comment_stmt::str(std::ostream& o){
    o << comment_.str()  << std::endl;
}

/*
 * keyvalue_stmt
 */
keyvalue_stmt::keyvalue_stmt(token& key, token& val):
    key_(key),value_(val){
}

#ifdef _DEBUG
void keyvalue_stmt::print(std::ostream& o){
    o << key_ ;
    o << value_;
}
#endif

void keyvalue_stmt::str(std::ostream& o){
    o << key_.str() << " = ";
    o << value_.str()  << std::endl;
}

/*
 * keyvalue_comment_stmt
 */
keyvalue_comment_stmt::keyvalue_comment_stmt(token& key, token& val, token& sub)
    :key_(key),value_(val),subcomment_(sub){
}

#ifdef _DEBUG
void keyvalue_comment_stmt::print(std::ostream& o){
    o << key_ ;
    o << value_;
    o << subcomment_;
}
#endif

void keyvalue_comment_stmt::str(std::ostream& o){
    o << key_.str() << " = " << value_.str() ;
    o << " " << subcomment_.str();
    o << std::endl;
}

#ifdef _DEBUG
std::ostream& operator << (std::ostream& o, stmt& sm){
    sm.print(o);
    return o; 
}
#endif

/*
 * stmt_collector
 */
void stmt_collector::add_m_stmt(token& t) {
    comment_stmt* stmt = new comment_stmt(t);
    stmt_list.push_back(stmt);
}


void stmt_collector::add_kv_stmt(token& key,token& value) {
    //FIXME: perhaps, Should delete the existed item and append new item.
    if (! exist(key.str())) {
        keyvalue_stmt* stmt = new keyvalue_stmt(key, value);
        stmt_list.push_back(stmt);
        keyval_map.insert(map_item(key.str(), stmt));
    }
}

void stmt_collector::add_kvm_stmt(token& key,token value, token& subcomment){
    if (! exist(key.str())) {
        keyvalue_comment_stmt* stmt = new keyvalue_comment_stmt(key, value, subcomment);
        stmt_list.push_back(stmt);
        keyval_map.insert(map_item(key.str(), stmt));
    }
}

void stmt_collector::print(std::ostream& o){
    std::list<stmt *> ::iterator it;
    for(it = stmt_list.begin(); it != stmt_list.end(); ++it){
        //(*it)->str(fs_);
        //(*it)->str(std::cout);
        (*it)->str(o);
    }
}

bool  stmt_collector::exist(const std::string& key){
    bool re = false;
    keyval_map_T::const_iterator it;   
    it = keyval_map.find(key);
    if (it != keyval_map.end()){
       re = true; 
    }
    return re;
}

token stmt_collector::find(const std::string& key){
    token t(T_EOF);
    keyval_map_T::const_iterator it;   
    it = keyval_map.find(key);
    if (it != keyval_map.end()){
        stmt * s = keyval_map[key];
        t = s->get_value();
    }
    return t;
}

stmt_collector::~stmt_collector(){
    std::list<stmt *> ::iterator it;
    for(it = stmt_list.begin(); it != stmt_list.end(); ++it){
        //(*it)->str(std::cout);
        //safe_del(*it);
    }
}
