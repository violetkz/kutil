#ifndef ns_symtbl_hpp__
#define ns_symtbl_hpp__

#include "ns_value.h"


/* symbol info */
struct symbol {
    std::string id;
    ns_value    value;
};

symbol *install_symbol(const char *name);
symbol *find_symbol(const char *name);

#endif //~ns_symtbl_hpp__
