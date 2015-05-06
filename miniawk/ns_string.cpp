#include "ns_string.h"
#include <cstring>
#include <cstdlib>

std::ostream &operator << (std::ostream &out, const ns_string& n) {
    out << "ref count: " << n.count() << " " 
            << "c_str: [" << n.c_str() << "]" ;
    return out;
}

ns_string::ns_string(char *s) : str_ptr(NULL), ref_count(NULL) {
    if (s != NULL) {
        str_ptr = strdup(s);
        ref_count = new int(1);
    }
}

ns_string::~ns_string() {
    release();
    destruct();
}

void ns_string::destruct() {
    if (str_ptr != NULL && *ref_count <= 0) {
        free(str_ptr);
        str_ptr = NULL;
        delete(ref_count);
    } 
}

ns_string::ns_string(const ns_string &s) {
    add_ref_count(); 
    str_ptr = s.str_ptr;
}

ns_string &ns_string::operator = (ns_string &s) {

    if (&s == this) return *this;

    this->release();
    this->destruct();

    s.add_ref_count();
    str_ptr = s.str_ptr;

    return *this;
}
