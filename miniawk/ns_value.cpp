
#include "ns_value.h"

ns_value operator+ (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        retuen ns_value(l.int_val + r.int_val);
    }
    else return make_illegal_value(); 
}

ns_value operator- (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        retuen ns_value(l.int_val - r.int_val);
    }
    else return make_illegal_value(); 
}

ns_value operator* (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        retuen ns_value(l.int_val * r.int_val);
    }
    else return make_illegal_value(); 
}

ns_value operator/ (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER && r.int_val != 0) {
        retuen ns_value(l.int_val / r.int_val);
    }
    else return make_illegal_value(); 
}
