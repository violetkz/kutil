#include "ns_value.h"

void ns_value::release() { 

    if (type == NSVAL_LITERAL_STR &&  ref_count  ) {
        std::cout << "release "<< *chr_val << "|" << *ref_count << std::endl;
        if (*ref_count == 1) {
            std::cout << "delete " << *chr_val << "|" << *ref_count << std::endl;
            delete chr_val;
            chr_val = NULL;

            delete ref_count;
            ref_count = NULL;
            
            type = NSVAL_UNINITIALIZED;
        }
        else {
            -- (*ref_count);
        }
    }
}

ns_value::~ns_value() {
    std::cout << __func__ <<":"<< __LINE__ << ":";
    release();    
}

ns_value::ns_value(const char *s) : type(NSVAL_LITERAL_STR), chr_val(NULL), ref_count(0) {
    std::cout << "create ns_value[s]" << '[' << s << ']'<< std::endl;
    if (s == NULL || strlen(s) == 0) {
        chr_val = new std::string(); 
    }
    else 
        chr_val = new std::string(s); 

    ref_count = new int(1);
}

ns_value::ns_value(const ns_value &s) {
    
    std::cout << __func__ << __LINE__ << std::endl;
    
    std::cout << "type:" <<  s.type << std::endl;
    std::cout << "ref_count:" <<  s.ref_count << std::endl;
    
    type      = s.type;
    ref_count = s.ref_count;

    if (type == NSVAL_LITERAL_STR && ref_count > 0) {
        chr_val  = s.chr_val;
        std::cout << __func__ << __LINE__ << std::endl;
        add_ref();
    }
    else if (type == NSVAL_INTEGER)  int_val  = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;
}

ns_value &ns_value::operator = (const ns_value &s) {
    
    if (&s == this) return *this;

    std::cout <<  __func__ <<"--<<---:"<< __LINE__ << std::endl;
    release();
    
    type      = s.type;
    ref_count =  s.ref_count;

    if (s.type == NSVAL_LITERAL_STR) {
        chr_val = s.chr_val;
        std::cout << __func__ <<":"<< __LINE__ << ":";
        add_ref();
    }
    else if (type == NSVAL_INTEGER)  int_val = s.int_val;
    else if (type == NSVAL_BOOLEAN)  bool_val = s.bool_val;
    
    std::cout << __func__ << "--->end<---" <<":"<< __LINE__ << std::endl;
    
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

ns_value operator+ (const ns_value &l, const ns_value &r) {
    
    if (l.type == r.type) {
        if (l.type == NSVAL_INTEGER) {
            return ns_value(l.int_val + r.int_val);
        }
        else if (l.type == NSVAL_LITERAL_STR) {
            std::string tmp = *l.chr_val + *r.chr_val;
            return  ns_value(tmp.c_str());
        }
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
