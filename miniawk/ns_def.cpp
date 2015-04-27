
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_def.h"

void assign_node::eval() {
    int type = rvalue->type;
    switch (type) {
        case STR_NODE:
            variable_name->type = STR_NODE;
            str_node* t = static_cast<str_node*>(rvalue);
            variable_name->chr_val = t->str;
            break;
        case NUM_INT_NODE:
            variable_name->type = NUM_INT_NODE;
            int_node* inod = static_cast<int_node*>(rvalue);
            variable_name->int_val = inod->i;
            break;
        case REGEX_STR_NODE:
            /* FIXME */
            break;
        default:
            break;
    };
}

class ns_symtbl {
public:
    /* symbol table */
    typedef std::map<std::string, symbol*> symtbl;
    typedef std::map<std::string, symbol*>::iterator symtbl_iterator;

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

symbol* install_symbol(char* name) {
    ns_symtbl::symtbl* tbl = ns_symtbl::get_tbl();
    
    std::string id(name);
    ns_symtbl::symtbl_iterator it = tbl->find(id);
    
    /* if not existed, create new item */
    symbol* n = NULL;
    if (it == tbl->end()) { 
        n = new symbol;
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
