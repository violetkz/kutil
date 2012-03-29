
#include "config_token.hpp"
#include "config_lexer.hpp"
#include "config.hpp"
#include <sstream>

config::config(const char *file)
    :config_file_path_(file),stmt_collector_()
{
}

void config::parse(){
    std::ifstream f(config_file_path_.c_str());
    if (f.bad()){
        //FIXME: handle the file open error.
    }

    conf_parser cp(f, stmt_collector_);
    cp.parse();
}

#ifdef _DEBUG
void config::print(){
    stmt_collector_.print();
}
#endif
#if 0
    std::string get(const std::string& key);
    int         get(const std::string& key);
    bool        get(const std::string& key);
#endif


std::string config::get(const std::string& key){

    token t = stmt_collector_.find(key);
    return t.value();
}

int config::get_int(const std::string& key){
    token t =  stmt_collector_.find(key);
    int i=0xFFFFFF;
    if (t.type_ == T_VALUE_NUMBER ){
        std::istringstream iss(t.value());
        iss >> i;
    }
    return i;
}

bool config::get_bool(const std::string& key){
    token t = stmt_collector_.find(key);
    bool f = false;
    if (t.type_ == T_VALUE_BOOLEAN ){
       if (strcmp_ncase(t.value(), "on") || strcmp_ncase(t.value(), "true"))
           f = true;
    }
    return f;
}

void config::set(const std::string& key, const std::string& value, const std::string& subcomment ){

    token k = token(T_KEY ,key);
    token v = token(T_VALUE_STRING,value);
    if (subcomment == "") {
        stmt_collector_.add_kv_stmt(k,v);
    }
    else {
        token m = token(T_COMMENT,subcomment);
        stmt_collector_.add_kvm_stmt(k,v,m);
    }
}

void config::set(const std::string& key, const char * value){
    std::string v(value);
    set(key, v, "");
}

void config::set(const std::string& key, bool flag){
    
    std::string f = flag ? "true" : "false";
    set(key, f, "");
}

void config::set_comment(const std::string& comment){
    token m = token(T_COMMENT,comment);
    stmt_collector_.add_m_stmt(m);
}

/*
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
