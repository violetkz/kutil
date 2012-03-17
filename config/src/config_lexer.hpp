#ifndef  CONFIG_LEX_HPP
#define  CONFIG_LEX_HPP

#include "config_token.hpp"
/*
 * ==============================================
 *  Class      :  Lexer
 *  Description:  the lexer for configure parser
 * =============================================
 */
struct status {
    int c;
    int linenumber;
};
class lexer{
    public:
        lexer(std::fstream& fio);
        token scan();
    private:
        inline void scan_word(std::string& s);
        inline void scan_number(std::string& s);
        inline void scan_string(std::string& s);
        inline void scan_comment(std::string& s);
        inline void skip_white();

        struct status       stat_;
        std::fstream&      io;
};

#endif //~CONFIG_LEX_HPP
