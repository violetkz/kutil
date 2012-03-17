
#include "config_stmts.hpp"


/*
 * comment_stmt 
 */

comment_stmt::comment_stmt(token& comment)
    :comment_(comment) {
}

#ifdef _DEBUG_PARSER
void comment_stmt::print(std::ostream& o){
    o << comment_ ;
}
#endif

virtual void comment_stmt::str(std::ostream& o){
    o << comment_.value()  << std::endl;
}
/*
 * keyvalue_stmt
 */
keyvalue_stmt(token& key, token& val):
    key_(key),value_(val){
}

#ifdef _DEBUG_PARSER
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

#ifdef _DEBUG_PARSER
void keyvalue_comment_stmt::print(std::ostream& o){
    o << key_ ;
    o << value_;
    o << subcomment_;
}
#endif

void keyvalue_comment_stmt::str(std::ostream& o){
    o << key_.value() << " = ";
    o << value_.value()  << std::endl;
}

#ifdef _DEBUG_PARSER
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
    keyvalue_stmt* stmt = new keyvalue_stmt(t);
    stmt_list.push_back(stmt);
    keyval_map.insert(std::pair<std::string, token>(key.value(), value));
}

void stmt_collector::add_kvm_stmt(token& key,token& value){
    keyvalue_comment_stmt* stmt = new keyvalue_comment_stmt(t);
    keyval_map.insert(std::pair<std::string, token>(key.value(), value));
}
