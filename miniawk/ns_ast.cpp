
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include "ns_ast.h"

extern void free_strval(char*);

ns_value identifer_node::eval() {
    return s->value;
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

ns_value int_node::eval() {
    
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

ns_value *rule_node::eval() {
    puts("rule_node\n");
    pattern->eval();
    action->eval();
    return NULL;
}

/* rule list node  */
void rule_list_node::print() {
    std::list<rule_node*>::iterator it = slist.begin();
    for (;it != slist.end(); ++it) {
        (*it)->print();
    }
}

ns_value *rule_list_node::eval() {
    puts("rule_list_node\n"); 
    std::list<rule_node*>::iterator it = slist.begin();
    for (;it != slist.end(); ++it) {
        (*it)->eval();
    }
    return NULL;
}

/* exp_list_node */
void exp_list_node::print() {
    std::list<node*>::iterator it = elist.begin();
    for (;it != elist.end(); ++it) {
        (*it)->print();
    }
}

ns_value *exp_list_node::eval() {
    puts("exp_list_node\n");
    std::list<node*>::iterator it = elist.begin();
    for (;it != elist.end(); ++it) {
        (*it)->eval();
    }
    return NULL;
}

/* builtin function node */
void builtin_func_node::print() {
    printf("func node: node type=> %d, funcname %s\n",
            type, func_name);     
    plist->print();
}

ns_value *assign_node::eval() {
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
}

ns_value *builtin_func_node::eval() {
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
}

/* if statment */
void stmt_if_node::print() {
    printf("stmt_if_node\n");
}
ns_value *stmt_if_node::eval() {
    // FIXME
    return NULL;
}

void stmt_while_node::print() {
    printf("stmt_if_node\n");
}
ns_value *stmt_while_node::eval() {
    // FIXME
    return NULL;
}

void stmt_for_in_node::print() {
    printf("stmt_if_node\n");
}
ns_value *stmt_for_in_node::eval() {
    // FIXME
    return NULL;
}

