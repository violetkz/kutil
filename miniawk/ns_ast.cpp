
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_ast.h"
#include "ns_symtbl.h"

extern void free_strval(char*);

ns_value identifer_node::eval() {
    return sym->value;
}

void identifer_node::print() {
    printf("identifer_node: type => %d \n", type );
}

ns_value int_node::eval() {
    return ns_value(i);
}

void int_node::print() {
    printf("int node: node type=> %d, s => %d\n", type, i); 
}

ns_value str_node::eval() {
   return ns_value(str); 
}

void str_node::print() {
    printf("str node: node type=> %d, s => %s\n", type, str); 
}

void regex_str_node::print() {
    printf("str node: node type=> %d, s => %s\n", type, regex_str); 
}

/* rule node */
void rule_node::print() {
    printf("rule node: node type=> %d \n", type); 
    pattern->print();
    action->print();
}

ns_value rule_node::eval() {

    pattern->eval();
    action->eval();
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

/* rule list node  */
void rule_list_node::print() {
    std::list<rule_node*>::iterator it = slist.begin();
    for (;it != slist.end(); ++it) {
        (*it)->print();
    }
}

ns_value rule_list_node::eval() {
    std::list<rule_node*>::iterator it = slist.begin();
    for (;it != slist.end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

/* exp_list_node */
void exp_list_node::print() {
    std::list<node*>::iterator it = elist.begin();
    for (;it != elist.end(); ++it) {
        (*it)->print();
    }
}

ns_value exp_list_node::eval() {

    std::list<node*>::iterator it = elist.begin();
    for (;it != elist.end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

/* builtin function node */
void builtin_func_node::print() {
    printf("func node: node type=> %d, funcname %s\n",
            type, func_name);     
    plist->print();
}

ns_value assign_node::eval() {
    variable_name->value = rvalue->eval();
    return variable_name->value;
}

ns_value builtin_func_node::eval() {

    if (strcmp(func_name, "print") == 0) {

        std::list<node*>& pl = plist->elist;
        std::list<node*>::iterator it = pl.begin();

        for(; it != pl.end(); ++it) {
            std::cout << (*it)->eval();
        }
    }
}

/* if statment */
void stmt_if_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_if_node::eval() {
    // FIXME

    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

void stmt_while_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_while_node::eval() {
    // FIXME

    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

void stmt_for_in_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_for_in_node::eval() {
    // FIXME

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

    //FIXME
    //
    return ns_value(false);
}

ns_value stmt_list_node::eval() {

    std::list<node*>::iterator it = plist.begin();
    for (;it != plist.end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}
