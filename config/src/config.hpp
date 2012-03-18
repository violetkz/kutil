
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
    
private:
    config(const config&){}

private:
    std::string         config_file_path_;
    //conf_parser         parser_;
    stmt_collector      stmt_collector_;    
};

#endif
