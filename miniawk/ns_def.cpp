
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_def.h"

struct mycmp {
    bool operator() (char* a, char* b) const {
        return (strcpy(a, b) < 0) ? true:false;
    }
};

class ns_symtbl {

public:
    /* symbol table */
    typedef std::map<std::string, symtol*> symtbl;
    typedef std::map<std::string, symtol*>::iterator symtbl_iterator;

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
    
    std::string id(name);
    ns_symtbl::symtbl_iterator it = tbl->find(id);
    
    /* if not existed, create new item */
    ns_symtbl::symtbl* n = NULL;
    if (it == tbl->end()) { 
        n = new symtol;
        n->id = id;
        (*tbl)[id] = n;
        printf("-debug-: install symbol=> %s\n", name);
    }
    else {
        n = (*tbl)[id];
        printf("-debug-: found symbol => %s\n", name);    
    }
    return n;
}
