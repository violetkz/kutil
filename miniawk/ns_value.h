#ifndef ns_value_h___
#define ns_value_h___

#include "ns_string.h"
#include <iostream>

enum ns_value_type {
    NSVAL_INTEGER,          /* integer */
    NSVAL_LITERAL_STR,      /* literal string */
    NSVAL_BOOLEAN,          /* boolean */
    NSVAL_EXPERESS_AST,     /* expression  */
    NSVAL_UNINITIALIZED,    /* uninitialized */
    NSVAL_ILLEGAL           /* illegal */
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
    ns_value() : type(NSVAL_UNINITIALIZED), int_val(0) {}
    ns_value(const ns_value& n);
    ~ns_value();

    ns_value &operator = (const ns_value &s);

    ns_value(int v) : type(NSVAL_INTEGER), int_val(v) {}
    ns_value(bool b) : type(NSVAL_BOOLEAN), bool_val(b) {}
    ns_value(const char *s);
    ns_value(ns_value_type t) : type(t), int_val(0) {}

    inline int count() const {return *ref_count; }

private:
    inline void add_ref() { *ref_count++; }
    inline void release();
private:
    int *ref_count;
};

//const ns_value &operator = (const ns_value &l, const ns_value &r);
std::ostream &operator << (std::ostream &out, const ns_value &v);
const ns_value operator+ (const ns_value &l, const ns_value &r);
const ns_value operator- (const ns_value &l, const ns_value &r);
const ns_value operator* (const ns_value &l, const ns_value &r);
const ns_value operator/ (const ns_value &l, const ns_value &r);

#endif  //~ns_value_h___
