
#ifndef CONFIG_HPP_H
#define CONFIG_HPP_H

#include <fstream>
#include <list>
#include <map>
#include "config_token.hpp"
#include "config_lexer.hpp"
#include "stmt_collector.hpp"


class conf_parser {
    public:
        conf_parser(std::ifstream& fs, stmt_collector& sc);
        ~conf_parser();

        /*
        void set_delimiter(const char delimiter);

        std::string & get(const std::string& key);
        //int           get(const std::string& key);
        //bool          get(const std::string& key);

        void set(const std::string& key, const std::string& value);
        void set(const std::string& key, bool flag);
        void set(const std::string& key, const char * value);
        void set(const std::string& key, int value);

        void save();

        */
        void parse();

    private:
        void move();
        void match(int t);
        void keyval();
        void comment();
        
    private:
        lexer    lex_;
        token    look_;
        stmt_collector& stmt_collector_;
};
#endif
