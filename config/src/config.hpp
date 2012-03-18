
#ifndef CONFIG_HPP_0X0001
#define CONFIG_HPP_0X0001

#include <string>
#include "config_parser.hpp"
class config {
public:
    void parse();

    
private:
    std::string config_file_path;
    conf_parser parser_;
};

#endif
