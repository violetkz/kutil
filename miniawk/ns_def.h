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
        STMT_NODE,
        STMT_LIST_NODE,
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

class stmt_node : public node {
public:
    stmt_node(node* p, node* act) 
            :node(STMT_NODE),
            pattern(p), 
            action(act) {
        /* do nothing */
    }
    virtual void print() {
        printf("stmt node: node type=> %d \n", type); 
        pattern->print();
        action->print();
    }
    
    virtual void eval() {
        puts("stmt_node\n");
        pattern->eval();
        action->eval();
    }

public:
    node* pattern;
    node* action;
};

class stmt_list_node : public node {
public:
    stmt_list_node() : node(STMT_LIST_NODE), slist() {
    }
    
    void append(stmt_node *n) {
        slist.push_back(n);
    }

    void print() {
        std::list<stmt_node*>::iterator it = slist.begin();
        for (;it != slist.end(); ++it) {
            (*it)->print();
        }
    }
    
    void eval() {
        puts("stmt_list_node\n"); 
        std::list<stmt_node*>::iterator it = slist.begin();
        for (;it != slist.end(); ++it) {
            (*it)->eval();
        }
    }
public:
    std::list<stmt_node *> slist; 
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

#if 0
class assign_node : public exp_node {
public:
    assign_node(char* name, char* val)
                :exp_node(ASSIGN_NODE),
                variable_name(name), 
                variable_val(val) {
        /* do nothing */
    }
    void print() {
        printf("assign node: node type => %d, vname => [%s],  value => [%s] \n",
               type, 
               variable_name, 
               variable_val
               ); 
    }
public:
    char* variable_name;
    char* variable_val;
};
#endif

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

class builtin_func_node : public exp_node {
public:
    builtin_func_node(const char *name, paramter_list_node *plist)
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
    paramter_list_node* plist;
};


class func_paramter_node : public node {
    const char* param_name;
    
    func_paramter_node(const char* p)
            :node(FUNC_PARAM_NODE), param_name(p) {
        /* do nothing */
    }
    
    void print() {
        printf("func_paramter_node: node type=> %d, param_name => [%s]\n",
                    type, param_name);
    }
};

/* symbol info */
struct symbol {
    std::string id;
    int type;
    union {
        int     int_val;
        char*   chr_val;
        double  dbl_val;
        node*   node_val;
    };
};

symbol* install_symbol(char *name);

#endif //~NS_DEF_H____
