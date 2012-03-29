
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
    o << comment_ ;
}
#endif

void comment_stmt::str(std::ostream& o){
    o << comment_.value()  << std::endl;
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
    o << key_.value() << " = ";
    o << value_.value()  << std::endl;
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
    o << key_.value() << " = ";
    o << value_.value() << " " ;
    o << subcomment_.value() << std::endl;
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

void stmt_collector::add_kv_stmt(token& key,token& value){
    keyvalue_stmt* stmt = new keyvalue_stmt(key, value);
    stmt_list.push_back(stmt);
    keyval_map.insert(std::pair<std::string, token>(key.value(), value));
}

void stmt_collector::add_kvm_stmt(token& key,token& value, token& subcomment){
    keyvalue_comment_stmt* stmt = new keyvalue_comment_stmt(key, value, subcomment);
    stmt_list.push_back(stmt);
    keyval_map.insert(std::pair<std::string, token>(key.value(), value));
}

void stmt_collector::print(){
    std::list<stmt *> ::iterator it;
    for(it = stmt_list.begin(); it != stmt_list.end(); ++it){
        //(*it)->str(fs_);
        (*it)->str(std::cout);
    }
}

token stmt_collector::find(const std::string& key){
    token t;
    keyval_map_T::const_iterator it;   
    it = keyval_map.find(key);
    if (it != keyval_map.end()){
        t = keyval_map[key];
    }
    else{
        //TODO:
        //throw key_not_found exception.
        //return *(new std::string("KEY WAS NOT FOUND"));
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
