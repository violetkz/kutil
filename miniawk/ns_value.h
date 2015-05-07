#ifndef ns_value_h___
#define ns_value_h___

#include <iostream>

enum ns_value_type {
    NSVAL_INTEGER       = 0, /* integer */
    NSVAL_LITERAL_STR   = 1, /* literal string */
    NSVAL_BOOLEAN       = 2, /* boolean */
    NSVAL_EXPERESS_AST  = 3, /* expression  */
    NSVAL_UNINITIALIZED = 4, /* uninitialized */
    NSVAL_ILLEGAL       = 5, /* illegal */
    NSVAL_STATUS        = 6  /* stmt stauts */
};

enum ns_status_type {
    NSVAL_STATUS_OK, 
    NSVAL_STATUS_FAILED
};

struct node; //previous declaration

class ns_value {
public:
    ns_value_type type;
    union {
        int         int_val;
        std::string       *chr_val;
        bool        bool_val;
        node        *node_val;
    };

public: 
    ~ns_value();


    ns_value(int v) : type(NSVAL_INTEGER), int_val(v) ,ref_count(0){}
    ns_value(bool b) : type(NSVAL_BOOLEAN), bool_val(b) ,ref_count(0){}
    ns_value(const char *s);
    ns_value(ns_value_type t) : type(t), int_val(0) ,ref_count(0){}
    ns_value(ns_value_type t, ns_status_type status) 
            : type(t), int_val(status), ref_count(0){}

    ns_value() : type(NSVAL_UNINITIALIZED), int_val(0), ref_count(0) {}
    ns_value(const ns_value& n);
    inline int count() const {return *ref_count;}

    ns_value &operator = (const ns_value &s);
private:
    inline void add_ref() { 
        if (type == NSVAL_LITERAL_STR ) {
            (*ref_count)++;
            std::cout <<"add_ref "<< *chr_val << "|" << *ref_count << std::endl;
        }
    }
    inline void release();
private:
    int *ref_count;
};

std::ostream &operator << (std::ostream &out, const ns_value &v);
ns_value operator+ (const ns_value &l, const ns_value &r);
ns_value operator- (const ns_value &l, const ns_value &r);
ns_value operator* (const ns_value &l, const ns_value &r);
ns_value operator/ (const ns_value &l, const ns_value &r);

#endif  //~ns_value_h___
