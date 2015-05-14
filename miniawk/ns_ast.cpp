#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_ast.h"
#include "ns_symtbl.h"
#include "ns.tab.h"

extern void free_strval(char*);

ns_value identifer_node::eval() {
    return sym->value;
}

ns_value int_node::eval() {
    return ns_value(i);
}

ns_value str_node::eval() {
    return ns_value(str); 
}

ns_value rule_node::eval() {
    pattern->eval();
    action->eval();
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value rule_list_node::eval() {
    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value exp_list_node::eval() {

    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value assign_node::eval() {
    variable_name->value = rvalue->eval();
    return variable_name->value;
}

ns_value assign_array_elem_node::eval() {
    ns_value pv = postfix->eval();

    if (pv.is_iteratale()) {
        ns_value idx = index->eval();        
        if (idx.is_int()) {
            set_elem(pv, idx.int_val, rvalue->eval());  
        }
        return pv;
    }
    return ns_value(NSVAL_ILLEGAL);
}

ns_value builtin_func_node::eval() {

    if (strcmp(func_name, "print") == 0) {

        exp_list_node::nl_iter it = plist->begin();

        for(; it != plist->end(); ++it) {
            std::cout << (*it)->eval();
        }
        std::cout << std::endl;
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_if_node::eval() {
    ns_value cond = condition_exp->eval();
    if (cond) {
        stmts->eval();
    }
    else if (else_stmts != NULL) {
        else_stmts->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_while_node::eval() {
    while (condition_exp->eval()) {
        stmts->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value stmt_for_in_node::eval() {
    // TODO  
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

ns_value operator_node::eval() {

    ns_value l = left->eval();
    ns_value r = right->eval();
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

ns_value compare_node::eval() {

    ns_value l = left->eval();
    ns_value r = right->eval();

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

ns_value stmt_list_node::eval() {

    nl_iter it = begin();
    for (;it != end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}


ns_value array_def_node::eval() {
    exp_list_node::nl_iter it = elements->begin();
    ns_value v_list(NSVAL_LIST);
    for (; it != elements->end(); ++it) {
        ns_value v = (*it)->eval();     
        if (! v.is_illegal_value()) {
            v_list.list_val->push_back(v);
        }
    }
    return v_list;
}

ns_value array_ref_node::eval() {
    ns_value pv = postfix->eval();
    if (pv.is_iteratale()) {
        ns_value idx = index->eval();        
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

