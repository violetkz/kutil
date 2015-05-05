
#include "ns_string.h"

ns_string::ns_string(char *s) : str_ptr(NULL), ref_count(NULL)
{
    if (s != NULL) {
        str_ptr = strdup(s);
        ref_count = new int(0);
    }
}

ns_string::~ns_string()
{
    *ref_count--; 
    check_ref_cont();
}

void destruct() {
    if (str_ptr != NULL && *ref_count <= 0) {
        free(str_ptr);
        str_ptr = NULL;
        delete(ref_count);
    } 
}

ns_string::ns_string(const ns_string &s) {
    
    if (s == *this) return;
    
    *ref_count--;
    check_ref_cont();
    
    *(s.ref_count)++;
    str_ptr = s.str_ptr;
}

