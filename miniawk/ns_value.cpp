#include "ns_value.h"

void ns_value::release() { 

    *ref_count--;
    if (type == NSVAL_LITERAL_STR && *ref_count <= 0) {
        delete chr_val;
        chr_val = NULL;
        
        delete ref_count;
        ref_count = NULL;
    }
}

ns_value::~ns_value() {
    release();    
}

ns_value::ns_value(const char *s) : type(NSVAL_LITERAL_STR), chr_val(NULL) {
    if (s) {
        chr_val = new std::string(s); 
        ref_count = new int;
        *ref_count = 1;
    }
}

ns_value::ns_value(const ns_value &s) {
    type      = s.type;
    ref_count = s.ref_count;

    if (type == NSVAL_LITERAL_STR)   chr_val  = s.chr_val;
    else if (type == NSVAL_INTEGER)  int_val  = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;

    add_ref();
}

ns_value &ns_value::operator = (const ns_value &s) {
    release();
    
    type      = s.type;
    ref_count =  s.ref_count;

    if (s.type == NSVAL_LITERAL_STR) {
        add_ref();
        chr_val = s.chr_val;
    }
    else if (type == NSVAL_INTEGER)  int_val = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;
    return *this;
}

std::ostream &operator << (std::ostream &out, const ns_value &v) {
    switch (v.type) {
        case NSVAL_UNINITIALIZED:
            out << " NSVAL_UNINITIALIZED " ;
            break;
        case NSVAL_ILLEGAL:
            out << " NSVAL_INTEGER ";
            break;
        case NSVAL_INTEGER:
            out << " NSVAL_INTEGER: " << v.int_val ;
            break;
        case NSVAL_LITERAL_STR:
            out << " NSVAL_LITERAL_STR: " << *v.chr_val;
            break;
        case NSVAL_BOOLEAN:
            out << " NSVAL_BOOLEAN: " << v.bool_val;
            break;

        default:
            break;

    }

    out << std::endl;
    return out;
}

const ns_value operator+ (const ns_value &l, const ns_value &r) {
    
    if (l.type == r.type) {
        if (l.type == NSVAL_INTEGER) {
            return ns_value(l.int_val + r.int_val);
        }
        else if (l.type == NSVAL_LITERAL_STR) {
            return  ns_value(NSVAL_ILLEGAL);
        }
    }
    //else if (l.type == NSVAL_INTEGER
    else return ns_value(NSVAL_ILLEGAL);
}

const ns_value operator- (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        return ns_value(l.int_val - r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);

}

const ns_value operator* (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        return ns_value(l.int_val * r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}

const ns_value operator/ (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER && r.int_val != 0) {
        return ns_value(l.int_val / r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}
