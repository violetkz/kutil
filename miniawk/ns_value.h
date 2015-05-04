#ifndef ns_value_h___
#define ns_value_h___

struct ns_value {
    enum ns_value_type {
        NSVAL_INTEGER,      /* integer */
        NSVAL_LITERAL_STR,  /* literal string */
        NSVAL_BOOLEAN,      /* boolean */
        NSVAL_EXPERESS_AST, /* expression  */
        NSVAL_UNINITITAL,   /* uninitital */
        NSVAL_ILLEGAL       /* illegal */
    };
    ns_value_type type;
    union {
        int     int_val;
        char    *chr_val;
        bool    bool_val;
        node    *node_val;
    };
    
    ns_value() : type(NSVAL_UNINITITAL), int_val(0) {}
    ns_value(int v) : type(NSVAL_INTEGER), int_val(v) {}
    ns_value(bool b) : type(NSVAL_BOOLEAN), bool_val(b) {}
    ns_value(char *s) : type(NSVAL_LITERAL_STR), chr_val(s) {}
    
};

/* helper function.  
 * make a ns_value with illegal status used for expression eval
 * FIXME: I suppose  here using 'static const'  
 */
ns_value make_illegal_value {
    ns_value illegal;
    ns_value.type = NSVAL_ILLEGAL;
    return illegal;
}

ns_value operator+ (const ns_value &l, const ns_value &r);
ns_value operator- (const ns_value &l, const ns_value &r);
ns_value operator* (const ns_value &l, const ns_value &r);
ns_value operator/ (const ns_value &l, const ns_value &r);


#endif  //~ns_value_h___
