#ifndef ns_symtbl_hpp__
#define ns_symtbl_hpp__

#include "ns_value.h"
#include "ns_rtctx.h"

/* symbol info */
struct symbol {
    std::string id;
    ns_value    value;
    
    symbol():id(), value() {}
};

symbol *install_symbol(const char *name);
symbol *find_symbol(const char *name, ns_rt_context *rt);

#endif //~ns_symtbl_hpp__
