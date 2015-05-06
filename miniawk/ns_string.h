#ifndef ns_string__h__
#define ns_string__h__

#include <iostream>

class ns_string {
public:
    ns_string(char *s);
    ~ns_string();

    const char *c_str() const { return str_ptr; }
    int  count() const {return *ref_count; }
    
    ns_string(const ns_string &s);
    ns_string &operator = (ns_string &s);

private:
    inline void add_ref_count() { *ref_count++; }
    inline void release()       { *ref_count--; }
    inline void destruct();
private:
    char *str_ptr;
    int  *ref_count;
};

std::ostream &operator << (std::ostream &out, const ns_string &n); 

#endif //~ns_string__h__
