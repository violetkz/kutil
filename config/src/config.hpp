
#ifndef CONFIG_HPP_0X0001
#define CONFIG_HPP_0X0001

#include <string>
#include "config_parser.hpp"
#include "config_stmts.hpp"

class config {
public:
    config(const char *file);
    void parse();
    void print();
    
    std::string get(const std::string& key);
    int         get_int(const std::string& key);
    bool        get_bool(const std::string& key);
    void        set(const std::string& key, const std::string& value, const std::string& subcomment = "");
    void        set(const std::string& key, const char * value);
    void        set(const std::string& key, bool flag);
    void        set_comment(const std::string& comment);

private:
    config(const config&){}

private:
    std::string         config_file_path_;
    //conf_parser         parser_;
    stmt_collector      stmt_collector_;    
};

#endif
