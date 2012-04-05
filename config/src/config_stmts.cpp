
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

void stmt_collector::add_kv_stmt(token& key,token& value){
    it = keyval_map.find(key);
    if (it != keyval_map.end()){
    
    keyvalue_stmt* stmt = new keyvalue_stmt(key, value);
    stmt_list.push_back(stmt);
#if 0
    std::cout << "k:[" << key.value() <<"]"<< std::endl;
    std::cout << "v:" << value << std::endl;
#endif
    keyval_map.insert(std::pair<std::string, token>(key.value(), value));
}

//XXX: bugs !!!
//    double insert same key-value.
void stmt_collector::add_kvm_stmt(token& key,token value, token& subcomment){
    keyvalue_comment_stmt* stmt = new keyvalue_comment_stmt(key, value, subcomment);
    stmt_list.push_back(stmt);
#if 0
    std::cout << "k:[" << key.value() <<"]"<< std::endl;
    std::cout << "v:" << value << std::endl;
    keyval_map_T::const_iterator it;   
    for (it = keyval_map.begin(); it != keyval_map.end(); ++it){
        std::cout << it->first << "=>" << it->second << std::endl;
    }
#endif
    std::pair<keyval_map_T::const_iterator, bool> ret;
    ret = keyval_map.insert(std::pair<std::string, token>(key.value(), value));
    if (!ret.second){
        std::cout << "insert failed \n" ;
    }
#if 0
    //keyval_map_T::const_iterator it;   
    std::cout << "after\n";
    for (it = keyval_map.begin(); it != keyval_map.end(); ++it){
        std::cout << it->first << "=>" << it->second << std::endl;
    }
#endif
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
