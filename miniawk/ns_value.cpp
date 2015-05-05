
#include "ns_value.h"

ns_value operator+ (const ns_value &l, const ns_value &r) {
    
    if (l.type == r.type)
        if (l.type == NSVAL_INTEGER) {
            retuen ns_value(l.int_val + r.int_val);
        }
        else if (l.type == NSVAL_LITERAL_STR) {
            //return ns_value(
            //TODO
        }
    }
    else if (l.type == NSVAL_INTEGER 
    else return ns_value(NSVAL_ILLEGAL);
}

ns_value operator- (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        retuen ns_value(l.int_val - r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);

}

ns_value operator* (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        retuen ns_value(l.int_val * r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}

ns_value operator/ (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER && r.int_val != 0) {
        retuen ns_value(l.int_val / r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}
