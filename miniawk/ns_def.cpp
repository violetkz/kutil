
#include <cstdio>
#include <cstring>
#include <map>
#include "ns_def.h"

struct mycmp {
    bool operator() (char* a, char* b) const {
        return (strcpy(a, b) < 0) ? true:false;
    }
};

class ns_symtbl {

public:
    /* symbol table */
    typedef std::map<char*, symtol*, mycmp> symtbl;
    typedef std::map<char*, symtol*, mycmp>::iterator symtbl_iterator;

public:
    static ns_symtbl::symtbl* get_tbl() {
        if (tbl == NULL) {
            tbl = new ns_symtbl::symtbl;
        }
        return tbl;
    }

private:
    static symtbl* tbl;
};

ns_symtbl::symtbl* ns_symtbl::tbl = NULL;

void install_symbol(char* name) {
    ns_symtbl::symtbl* tbl = ns_symtbl::get_tbl();
    
    ns_symtbl::symtbl_iterator it = tbl->find(name);
    
    printf("-debug-: name: %s count: %d\n", name, tbl->count(name));
    /* if not existed, create new item */
    if (it == tbl->end()) { 
        (*tbl)[name] = new symtol;
        printf("-debug-: install symbol=> %s\n", name);
    }
    else {
        printf("-debug-: found symbol => %s\n", name);    
    }
}
