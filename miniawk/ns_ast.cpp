
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_ast.h"
#include "ns_symtbl.h"

extern void free_strval(char*);

#define _t_  printf("%s:[%d]\n",__func__,__LINE__)

ns_value identifer_node::eval() {
    _t_; 
    return sym->value;
}

void identifer_node::print() {
    printf("identifer_node: type => %d \n", type );
}

ns_value int_node::eval() {
    _t_; 
    return ns_value(i);
}

void int_node::print() {
    printf("int node: node type=> %d, s => %d\n", type, i); 
}

ns_value str_node::eval() {
    _t_; 
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
    _t_; 
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
    _t_; 
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
    _t_;
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

    _t_;
    variable_name->value = rvalue->eval();

    return variable_name->value;
    
#if 0
    puts("assign_node\n");
    assert(rvalue != NULL);
    int type = rvalue->type;
    str_node *t;
    int_node *inod;
    switch (type) {
        case STR_NODE:
            variable_name->type = STR_NODE;
            t = static_cast<str_node*>(rvalue);

            /* check if need free previous string buffer memory */
            if (variable_name->chr_val != NULL) {
                //free_strval(variable_name->chr_val);                
            }

            /* assign new value */
            variable_name->chr_val = t->str;
            break;

        case NUM_INT_NODE:
            variable_name->type = NUM_INT_NODE;
            inod = static_cast<int_node*>(rvalue);
            variable_name->int_val = inod->i;
            break;

        case REGEX_STR_NODE:
            /* FIXME */
            break;
        default:
            break;
    };
    return NULL;
#endif
}

ns_value builtin_func_node::eval() {

    _t_;
    if (strcmp(func_name, "print") == 0) {

        std::list<node*>& pl = plist->elist;
        std::list<node*>::iterator it = pl.begin();

        for(; it != pl.end(); ++it) {
            std::cout << (*it)->eval();
        }
    }
#if 0
    puts("builtin_func_node\n");
    /* FIXME: just for tesint */
    if (strcmp(func_name, "print") == 0) {
        std::list<node*>& pl = plist->elist;
        std::list<node*>::iterator it = pl.begin();
        std::string fmt;
        for(; it != pl.end(); ++it) {
            if ((*it)->type == STR_NODE) {
                str_node *sn = static_cast<str_node*>(*it);
                printf(" %s ", sn->str);
            }
            else if ((*it)->type == NUM_INT_NODE) {
                int_node *in = static_cast<int_node*>(*it);
                printf(" %d ", in->i);
            }
            else if ((*it)->type == IDENTIFIER_NODE) {
                identifer_node *idn = static_cast<identifer_node*>(*it);
                symbol *s = idn->sym;
                switch (s->type) {
                    case STR_NODE: 
                        puts(s->chr_val);
                        break;
                    case NUM_INT_NODE:
                        printf("%d", s->int_val);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return NULL;
#endif
}

/* if statment */
void stmt_if_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_if_node::eval() {
    // FIXME
    _t_;
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

void stmt_while_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_while_node::eval() {
    // FIXME
    _t_;
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}

void stmt_for_in_node::print() {
    printf("stmt_if_node\n");
}

ns_value stmt_for_in_node::eval() {
    // FIXME
    _t_;
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}


ns_value operator_node::eval() {
    _t_;
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
    
    _t_;
    ns_value l = left->eval();
    ns_value r = right->eval();

    //FIXME
    //
    return ns_value(false);
}

ns_value stmt_list_node::eval() {
    _t_;
    std::list<node*>::iterator it = plist.begin();
    for (;it != plist.end(); ++it) {
        (*it)->eval();
    }
    return ns_value(NSVAL_STATUS, NSVAL_STATUS_OK);
}
