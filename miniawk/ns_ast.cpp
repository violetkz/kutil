#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_ast.h"
#include "ns_symtbl.h"
#include "ns.tab.h"

extern void free_strval(char*);

ns_value variable_node::eval(ns_rt_context *rtctx) {
    symbol *syn = check_symbol(id, rtctx);
    if (!s) { //xxx
    }
    return sym->value;
}

ns_value int_node::eval(ns_rt_context *rtctx) {
    return ns_value(i);
}

ns_value str_node::eval(ns_rt_context *rtctx) {
    return ns_value(str); 
}

ns_value rule_node::eval(ns_rt_context *rtctx) {
    pattern->eval(rtctx);
    action->eval(rtctx);
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value rule_list_node::eval(ns_rt_context *rtctx) {
    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval(rtctx);
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value exp_list_node::eval(ns_rt_context *rtctx) {

    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval(rtctx);
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value assign_node::eval(ns_rt_context *rtctx) {
    variable_name->value = rvalue->eval(rtctx);
    return variable_name->value;
}

ns_value assign_array_elem_node::eval(ns_rt_context *rtctx) {
    ns_value pv = postfix->eval(rtctx);

    if (pv.is_iteratale()) {
        ns_value idx = index->eval(rtctx);        
        if (idx.is_int()) {
            set_elem(pv, idx.int_val, rvalue->eval(rtctx));  
        }
        return pv;
    }
    return ns_value(NSVAL_ILLEGAL);
}

ns_value builtin_func_node::eval(ns_rt_context *rtctx) {

    if (strcmp(func_name, "print") == 0) {

        exp_list_node::nl_iter it = plist->begin();

        for(; it != plist->end(); ++it) {
            std::cout << (*it)->eval(rtctx);
        }
        std::cout << std::endl;
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_if_node::eval(ns_rt_context *rtctx) {
    ns_value cond = condition_exp->eval(rtctx);
    if (cond) {
        stmts->eval(rtctx);
    }
    else if (else_stmts != NULL) {
        else_stmts->eval(rtctx);
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_while_node::eval(ns_rt_context *rtctx) {
    while (condition_exp->eval(rtctx)) {
        stmts->eval(rtctx);
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_for_in_node::eval(ns_rt_context *rtctx) {
    // TODO  
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value operator_node::eval(ns_rt_context *rtctx) {

    ns_value l = left->eval(rtctx);
    ns_value r = right->eval(rtctx);
    ns_value n;
    switch (opt) {
        case '+':  n = l + r; 
                   break;
        case '-':  n = l - r;
                   break;
        case '*':  n = l * r;
                   break;
        case '/':  n = l / r;
                   break;
        case '%':  n = l % r;
                   break;
        default:
                   n = ns_value(NSVAL_ILLEGAL);
                   fprintf(stderr, "* error *: un-defined operator: %c\n", opt);
                   break;
    }
    return n;
}

ns_value compare_node::eval(ns_rt_context *rtctx) {

    ns_value l = left->eval(rtctx);
    ns_value r = right->eval(rtctx);

    bool v = false;
    switch (cmp_opt) {
        case CMP_GT:
            v = l > r;
            break;
        case CMP_LS:
            v = l < r;
            break;
        case CMP_EQ:
            v = l == r;
            break;
        case CMP_NE:
            v = l != r;
            break;
        case CMP_GE:
            v = l >= r;
            break;
        case CMP_LE:
            v = l <= r;
            break;
        case OR:
            v = l || r;
            break;
        case AND:
            v = l && r;
            break;
        default:
            v = false; 
            break;
    }
    return ns_value(v);
}

ns_value stmt_list_node::eval(ns_rt_context *rtctx) {

    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval(rtctx);
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}


ns_value array_def_node::eval(ns_rt_context *rtctx) {
    exp_list_node::nl_iter it = elements->begin();
    ns_value v_list(NSVAL_LIST);
    for (; it != elements->end(); ++it) {
        ns_value v = (*it)->eval(rtctx);     
        if (! v.is_illegal_value()) {
            v_list.list_val->push_back(v);
        }
    }
    return v_list;
}

ns_value array_ref_node::eval(ns_rt_context *rtctx) {
    ns_value pv = postfix->eval(rtctx);
    if (pv.is_iteratale()) {
        ns_value idx = index->eval(rtctx);        
        if (idx.is_int()) {
            return get_elem(pv, idx.int_val);            
        }
        std::cerr 
            << "index is not integer type." << std::endl;
    }
    std::cerr
            << "the object is not iteratable" << std::endl;

    return ns_value(NSVAL_ILLEGAL);
}

def_func_node::def_func_node(char *name, identifier_list_node *args, node *stmts)
    :node(DEF_FUNC_NODE), func_name(name), arg_list(args), stmt_list(stmts) {
}

ns_value def_func_node::eval(ns_rt_context *rtctx) {
    return ;
}

