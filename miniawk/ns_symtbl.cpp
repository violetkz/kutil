#include <map>
#include <cstdio> //for printf. need remove in future.
#include "ns_symtbl.h"

class ns_symtbl {
    public:
        /* symbol table */
        typedef std::map<std::string, symbol*> symtbl;
        typedef std::map<std::string, symbol*>::iterator symtbl_iterator;

    public:
        static ns_symtbl::symtbl *get_tbl() {
            if (tbl == NULL) {
                tbl = new ns_symtbl::symtbl;
            }
            return tbl;
        }

    private:
        static symtbl *tbl;
};

ns_symtbl::symtbl *ns_symtbl::tbl = NULL;

/* install a symbol into table */
symbol *install_symbol(const char *name) {
    ns_symtbl::symtbl *tbl = ns_symtbl::get_tbl();

    std::string id(name);
    ns_symtbl::symtbl_iterator it = tbl->find(id);

    /* if not existed, create new item */
    symbol *n = NULL;
    if (it == tbl->end()) { 
        n = new symbol;
        n->id = id;
        (*tbl)[id] = n;
    }
    else {
        n = (*tbl)[id];
    }
    return n;
}

/* find a symbol from table by name and return pointer of symbol if existed
 * esle return NULL 
 */ 
symbol *find_symbol(const char *name) {
    symbol *re = NULL;
    
    ns_symtbl::symtbl *tbl = ns_symtbl::get_tbl();

    std::string id(name);
    ns_symtbl::symtbl_iterator it = tbl->find(id);

    if (it != tbl->end()) {
        re = (*tbl)[id];
    }
    return re;
}
