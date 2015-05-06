#ifndef NS_DEF_H____
#define NS_DEF_H____

#include <stdio.h>
#include <list>
#include <string>

#include "ns_value.h"

struct symbol;

/* the base class to present AST node */
class node {
public:
    enum {
        RULE_NODE,
        RULE_LIST_NODE,
        FUNC_PARAM_LIST_NODE,
        FUNC_PARAM_NODE,
        FUNC_NODE,
        STR_NODE,
        REGEX_STR_NODE,
        ASSIGN_NODE, 
        EXP_NODE, 
        EXPLIST_NODE,
        IDENTIFIER_NODE,
        NUM_INT_NODE,
        STMT_WHILE_NODE,
        STMT_IF_NODE,
        STMT_LIST_NODE,
        STMT_FOR_IN_NODE,
        OPERATOR_NODE,
        COMPARE_NODE
    };
    
    node(int t) : type(t) {}
    virtual ~node() {}

    /* print self node */ 
    virtual void print() {}
    
    /* eval */
    virtual ns_value *eval() {return NULL;}
    
public:
    int type;
};

class identifer_node : public node {
public:
    identifer_node(symbol *s) : node(IDENTIFIER_NODE), sym(s) {
        /* do nothing */
    }
    void print();
    ns_value *eval();
public:
    symbol *sym;
};

/* string node */
class int_node : public node {
public:
    int_node(int n) : node(NUM_INT_NODE), i(n) {
        /* do nothing */
    }
    void print();
    ns_value *eval();
public:
    int i;
};

/* string node */
class str_node : public node {
public:
    str_node(char *s) : node(STR_NODE), str(s) {
        /* do nothing */
    }
    virtual void print();
    ns_value *eval();
public:
    char *str;
};

class regex_str_node : public node {
public:
    regex_str_node(char *str)
        :node(REGEX_STR_NODE), regex_str(str) {
        /* do nothing */  
    }
    void print();

public:
    char *regex_str;
};

class rule_node : public node {
public:
    rule_node(node *p, node *act) 
            :node(RULE_NODE),
            pattern(p), 
            action(act) {
        /* do nothing */
    }
    void print();    
    ns_value *eval(); 

public:
    node *pattern;
    node *action;
};

#if 0
template <class T> base_list_node : public node {
public:
    base_list_node(int type) : node(t);
    void append(T *n){};
public:
    std::list<T *> list_;
};
#endif

class rule_list_node : public node {
public:
    rule_list_node() : node(RULE_LIST_NODE), slist() {
    }
    
    inline void append(rule_node *n) {
        slist.push_back(n);
    }

    void print();
    ns_value *eval(); 
public:
    std::list<rule_node *> slist; 
};

class exp_list_node : public node {
public:
    exp_list_node() : node(EXPLIST_NODE), elist() {
    }
    
    inline void append(node *n) {
        elist.push_back(n);
    }

    void print(); 
    ns_value *eval(); 
public:
    std::list<node *> elist; 
};

class assign_node : public node {
public:
    assign_node(symbol *id, node *val)
            : node(ASSIGN_NODE),
             variable_name(id), 
             rvalue(val) {
        /* do nothing */
    }
    ns_value *eval();

public:
    symbol *variable_name;
    node *rvalue;
};


class stmt_list_node : public node {
public:
    stmt_list_node() : node(STMT_LIST_NODE), plist() {
        /* do nothing */
    }
    void append(node *n) {
        plist.push_back(n);
    }

    void print() {
        std::list<node*>::iterator it = plist.begin();
        for (;it != plist.end(); ++it) {
            (*it)->print();
        }
    }
public:
    std::list<node*>  plist; 
};

class stmt_while_node : public node {
public:
    stmt_while_node(node *condition, stmt_list_node *stmt_list) 
        :node(STMT_WHILE_NODE), condition_exp(condition), stmts(stmt_list) {
    }
    void print();
    ns_value *eval();
public:
    node *condition_exp;
    stmt_list_node *stmts;
};

class stmt_if_node : public node {
public:
    stmt_if_node(node *condition, stmt_list_node *action) 
        : node(STMT_IF_NODE), condition_exp(condition), stmts(action), else_stmts(NULL) {
     }

    stmt_if_node(node *condition,
            stmt_list_node *action,
            stmt_list_node *else_action)
        : node(STMT_IF_NODE), condition_exp(condition), stmts(action), else_stmts(else_action) {
     }

    void print();
    ns_value *eval();
public:
    node *condition_exp;
    stmt_list_node *stmts;
    stmt_list_node *else_stmts;
};

class stmt_for_in_node : public node {
public:
    stmt_for_in_node(symbol *tmp, symbol *ln, stmt_list_node *stmt_list)
        : node(STMT_FOR_IN_NODE), tmp_id(tmp), id(ln), stmts(stmt_list) {
    }
    void print();
    ns_value *eval();
public:
    symbol  *tmp_id;
    symbol  *id; 
    stmt_list_node  *stmts;
};

class operator_node : public node {
public:
    operator_node(char opt, node *l, node *r) 
        : node(OPERATOR_NODE), opt(opt), left(l), right(r) {
    }

public:
    char    opt; 
    node  *left;
    node  *right;
};

class compare_node : public node {
public:
    compare_node(int opt, node *l, node *r) 
        : node(COMPARE_NODE), cmp_opt(opt), left(l), right(r) {
    }

public:
    int    cmp_opt; 
    node  *left;
    node  *right;
};


class builtin_func_node : public node {
public:
    builtin_func_node(const char *name, exp_list_node *plist)
                    :node(FUNC_NODE),
                    func_name(name),
                    plist(plist) {
        /* do nothing */
    }
    
    void print(); 
    ns_value *eval();

public:
    const char *func_name;
    exp_list_node *plist;
};




#endif //~NS_DEF_H____
