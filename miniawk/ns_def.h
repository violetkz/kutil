#ifndef NS_DEF_H____
#define NS_DEF_H____

#include <stdio.h>
#include <list>
#include <string>

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
        NUM_INT_NODE
    };
    
    node(int t) : type(t) {}
    virtual ~node() {}

    /* print self node */ 
    virtual void print() {}
    
    /* eval */
    virtual void eval() {}
    
public:
    int type;
};

class identifer_node : public node {
public:
    identifer_node(symbol* s) : node(IDENTIFIER_NODE), sym(s) {
        /* do nothing */
    }
    void print() {
        printf("identifer_node: type => %d \n", type );
    }
public:
    symbol* sym;
};

/* string node */
class int_node : public node {
public:
    int_node(int n) : node(NUM_INT_NODE), i(n) {
        /* do nothing */
    }
    virtual void print() {
        printf("str node: node type=> %d, s => %d\n", type, i); 
    }
public:
    int i;
};

/* string node */
class str_node : public node {
public:
    str_node(char* s) : node(STR_NODE), str(s) {
        /* do nothing */
    }
    virtual void print() {
        printf("str node: node type=> %d, s => %s\n", type, str); 
    }
public:
    char* str;
};

class regex_str_node : public node {
public:
    regex_str_node(char* str):node(REGEX_STR_NODE), regex_str(str) {
        /* do nothing */  
    }
    virtual void print() {
        printf("str node: node type=> %d, s => %s\n", type, regex_str); 
    }

public:
    char* regex_str;
};

class rule_node : public node {
public:
    rule_node(node* p, node* act) 
            :node(RULE_NODE),
            pattern(p), 
            action(act) {
        /* do nothing */
    }
    virtual void print() {
        printf("rule node: node type=> %d \n", type); 
        pattern->print();
        action->print();
    }
    
    virtual void eval() {
        puts("rule_node\n");
        pattern->eval();
        action->eval();
    }

public:
    node* pattern;
    node* action;
};

class rule_list_node : public node {
public:
    rule_list_node() : node(RULE_LIST_NODE), slist() {
    }
    
    void append(rule_node *n) {
        slist.push_back(n);
    }

    void print() {
        std::list<rule_node*>::iterator it = slist.begin();
        for (;it != slist.end(); ++it) {
            (*it)->print();
        }
    }
    
    void eval() {
        puts("rule_list_node\n"); 
        std::list<rule_node*>::iterator it = slist.begin();
        for (;it != slist.end(); ++it) {
            (*it)->eval();
        }
    }
public:
    std::list<rule_node *> slist; 
};

class exp_node : public node {
public:
    exp_node(int n):node(n) {
        /* do nothing */
    }
    void print() {
        printf("expnode");
    }
};

class explist_node : public node {
public:
    explist_node() : node(EXPLIST_NODE), elist() {
    }
    
    void append(exp_node *n) {
        elist.push_back(n);
    }

    void print() {
        std::list<exp_node*>::iterator it = elist.begin();
        for (;it != elist.end(); ++it) {
            (*it)->print();
        }
    }

    void eval() {
        puts("explist_node\n");
        std::list<exp_node*>::iterator it = elist.begin();
        for (;it != elist.end(); ++it) {
            (*it)->eval();
        }
    }
public:
    std::list<exp_node *> elist; 
};

class assign_node : public exp_node {
public:
    assign_node(symbol *id, node* val):exp_node(ASSIGN_NODE),
                variable_name(id), 
                rvalue(val) {
        /* do nothing */
    }
    void eval();

public:
    symbol* variable_name;
    node*  rvalue;
};

class stmt_while_node {
public:
    void print();
    void eval();
/* FIXME */

};

class stmt_for_in_node {
public:
    void print();
    void eval();
public:
    identifer_node  *tmp_id;
    identifer_node  *id; 
    stmt_list_node  *stmt;
};
#if 0
class paramter_list_node : public node {
public:
    paramter_list_node() : node(FUNC_PARAM_LIST_NODE), plist() {
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
#endif

class builtin_func_node : public exp_node {
public:
    builtin_func_node(const char *name, explist_node *plist)
                    :exp_node(FUNC_NODE),
                    func_name(name),
                    plist(plist) {
        /* do nothing */
    }
    
    void print() {
        printf("func node: node type=> %d, funcname %s\n",
                type, func_name);     
        plist->print();
    }

    void eval();

public:
    const char* func_name;
    explist_node *plist;
};


/* symbol info */
struct symbol {
    std::string id;
    int type;
    union {
        int     int_val;
        char    *chr_val;
        std::string     str;
        node    *node_val;
    };
};

symbol* install_symbol(char *name);

#endif //~NS_DEF_H____
