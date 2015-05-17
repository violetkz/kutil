#ifndef ns_symtbl_hpp__
#define ns_symtbl_hpp__

#include "ns_value.h"
#include "ns_rtctx.h"

#include <map>
#include <string>

/* symbol info */
struct symbol {
    std::string id;
    ns_value    value;
    
    symbol():id(), value() {}
};

/* symbol table */
typedef std::map<std::string, symbol*> symtbl;
typedef std::map<std::string, symbol*>::iterator symtbl_iterator;

struct ns_rt_context {
    symtbl local_env;    
};


symbol *check_symbol(const std::string& name, ns_rt_context *rt);
symbol *find_symbol(const std::string& name, ns_rt_context *rt);

#endif //~ns_symtbl_hpp__
