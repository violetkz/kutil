
#ifndef config_token_hpp
#define config_token_hpp

#include <string>

enum TOKEN_TYPE{
    T_START         = 0,
    T_COMMENT       = '#',
    T_KEY           = 'K',
    T_DELIMITER     = '=', 
    T_VALUE         = 'V',
    T_VALUE_STRING  = 'S',
    T_VALUE_NUMBER  = 'N',
    T_VALUE_BOOLEAN = 'B',
    T_EOF           = -1
};

class token{
    
public:
    token();
    token(int t);
    token(int t, const std::string& v);
    token(const token& t);
    token& operator = (const token& t);

    ~token();
    std::string& value()const{
        return val_ptr_->val_;
    }
    std::string  str() const{
        return val_ptr_->val_;
    }
    int         type_;

    friend std::ostream& operator << (std::ostream& out, const token& t);
private:
    //inner class of reference count.    
    struct val_ptr{
        int ref;
        std::string val_;
        
        val_ptr(const std::string& v);
        val_ptr(int tag);
    };

    val_ptr*    val_ptr_;
};

std::ostream& operator << (std::ostream& out, const token& t);
#endif 
