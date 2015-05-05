#ifndef ns_value_h___
#define ns_value_h___

enum ns_value_type {
    NSVAL_INTEGER,          /* integer */
    NSVAL_LITERAL_STR,      /* literal string */
    NSVAL_BOOLEAN,          /* boolean */
    NSVAL_EXPERESS_AST,     /* expression  */
    NSVAL_UNINITIALIZED,    /* un-initialized */
    NSVAL_ILLEGAL           /* illegal */
};

struct ns_value {
    ns_value_type type;
    union {
        int     int_val;
        char    *chr_val;
        bool    bool_val;
        node    *node_val;
    };
    
    ns_value() : type(NSVAL_UNINITIALIZED), int_val(0) {}
    ns_value(int v) : type(NSVAL_INTEGER), int_val(v) {}
    ns_value(bool b) : type(NSVAL_BOOLEAN), bool_val(b) {}
    ns_value(char *s) : type(NSVAL_LITERAL_STR), chr_val(s) {}
    ns_value(ns_value_type t) : type(t), int_val(0) {}
};

const ns_value operator+ (const ns_value &l, const ns_value &r);
const ns_value operator- (const ns_value &l, const ns_value &r);
const ns_value operator* (const ns_value &l, const ns_value &r);
const ns_value operator/ (const ns_value &l, const ns_value &r);

#endif  //~ns_value_h___
