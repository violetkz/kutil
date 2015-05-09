#include "ns_value.h"
#include <cstring>

void ns_value::destruct() {
    if (type == NSVAL_LITERAL_STR &&  ref_count != NULL ) {
        if (*ref_count == 1) {
            if (chr_val != NULL) {
                delete chr_val;
                chr_val = NULL;
            }

            delete ref_count;
            ref_count = NULL;
        }
    }
}

void ns_value::release() { 
    if (type == NSVAL_LITERAL_STR && ref_count != NULL ) {
        -- (*ref_count);
    }
}

void ns_value::add_ref() { 
    if (type == NSVAL_LITERAL_STR && ref_count != NULL ) {
        (*ref_count)++;
    }
}

ns_value::~ns_value() {
    destruct();
}

ns_value::ns_value(const char *s) : type(NSVAL_LITERAL_STR), chr_val(NULL), ref_count(0) {
    if (s == NULL || strlen(s) == 0) {
        chr_val = new std::string(); 
    }
    else 
        chr_val = new std::string(s); 

    ref_count = new int(1);
}

ns_value::ns_value(const ns_value &s) : type(s.type), ref_count(s.ref_count), int_val(0) {

    if (type == NSVAL_LITERAL_STR) {
        chr_val  = s.chr_val;
        add_ref();
    }
    else if (type == NSVAL_INTEGER)  int_val  = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;
    else  int_val = 0;
}

ns_value &ns_value::operator = (const ns_value &s) {

    if (&s == this) return *this;

    release();

    type      = s.type;
    ref_count =  s.ref_count;

    if (s.type == NSVAL_LITERAL_STR) {
        chr_val = s.chr_val;
        add_ref();
    }
    else if (type == NSVAL_INTEGER)  int_val = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;

    return *this;
}

std::ostream &operator << (std::ostream &out, const ns_value &v) {
    switch (v.type) {
        case NSVAL_UNINITIALIZED:
            out << "uninitialized value" ;
            break;
        case NSVAL_ILLEGAL:
            out << "illegal value";
            break;
        case NSVAL_STATUS:
            out << "status:" << v.int_val;
        case NSVAL_INTEGER:
            out << v.int_val;
            break;
        case NSVAL_LITERAL_STR:
            out << *v.chr_val;
            break;
        case NSVAL_BOOLEAN:
            out << v.bool_val;
            break;
        default:
            out << "unkown type" << v.type;
            break;
    }
    return out;
}

ns_value operator+ (const ns_value &l, const ns_value &r) {

    if (l.type == r.type) {
        if (l.type == NSVAL_INTEGER) {
            return ns_value(l.int_val + r.int_val);
        }
        else if (l.type == NSVAL_LITERAL_STR) {
            std::string tmp = *l.chr_val + *r.chr_val;
            return  ns_value(tmp.c_str());
        }
        return ns_value(NSVAL_ILLEGAL);
    }
    return ns_value(NSVAL_ILLEGAL);
}

ns_value operator- (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        return ns_value(l.int_val - r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);
}

ns_value operator* (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER) {
        return ns_value(l.int_val * r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}

ns_value operator/ (const ns_value &l, const ns_value &r) {
    if (l.type == r.type && l.type == NSVAL_INTEGER && r.int_val != 0) {
        return ns_value(l.int_val / r.int_val);
    }
    else return ns_value(NSVAL_ILLEGAL);  
}
