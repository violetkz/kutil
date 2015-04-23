#ifndef NS_DEF_H____
#define NS_DEF_H____

#include <list>

struct node {
    enum {
        STMT_NODE,
        FUNC_PARAM_LIST_NODE,
        FUNC_PARAM_NODE,
        FUNC_NODE,
        STR_NODE,
        REGEX_STR_NODE,
        ASSIGN_NODE, 
        EXP_NODE, 
    };
    int node_type;
    node(int t) : node_type(t) {}
    
    virtual void print() {
        printf("base node: node type=> %d\n", node_type); 
    }
};

struct str_node : public node {
    char* s;
    str_node(char* str):node(STR_NODE), s(str) {
        /* do nothing */
    }
    virtual void print() {
        printf("str node: node type=> %d, s => %s\n", node_type, s); 
    }
};

struct regex_str_node : public node {
    char* regex_str;
    
    regex_str_node(char* str):node(REGEX_STR_NODE), regex_str(str) {
        /* do nothing */  
    }
    virtual void print() {
        printf("str node: node type=> %d, s => %s\n", node_type, regex_str); 
    }
};

struct stmt_node : public node {
    node* pattern;
    node* action;
    stmt_node(node* p, node* act)
        :node(STMT_NODE),
        pattern(p), 
        action(act) {
        /* do nothing */
    }
    virtual void print() {
        printf("stmt node: node type=> %d \n", node_type); 
        pattern->print();
        action->print();
    }
};

struct exp_node : public node {
    //const char* param_name;
    struct exp_node *next; /* point to next exp */
    
    exp_node(int n):node(n), next(NULL) {
        /* do nothing */
    }
    
    exp_node* append(exp_node *n) {
        exp_node *tail = this; 
        while  (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = n;
        return this;
    }
    
    virtual void print_exp() {
    }

    void print() {
        exp_node *t = this;
        while (t != NULL) {
            t->print_exp();
            t = t->next;
        }
    }
};

struct assign_node : public exp_node {
    char* variable_name;
    char* variable_val;
    assign_node(char* name, char* val)
        :exp_node(ASSIGN_NODE),
        variable_name(name), 
        variable_val(val) {
        /* do nothing */
    }
    virtual void print_exp() {
        printf("assign node: node type => %d, vname => [%s],  value => [%s] \n",
               node_type, 
               variable_name, 
               variable_val
               ); 
    }
};

struct builtin_func_node : public exp_node {
    const char* func_name;
    node* plist;

    builtin_func_node(const char *name, node *plist)
            :exp_node(FUNC_NODE),
            func_name(name),
            plist(plist) {
        /* do nothing */
    }
    
    void print_exp() {
        printf("func node: node type=> %d, funcname %s\n",
                node_type, func_name);     
        plist->print();
    }
};


struct func_paramter_node : public node {
    const char* param_name;
    struct func_paramter_node *next; /* point to next paramter */
    
    func_paramter_node(const char* p)
            :node(FUNC_PARAM_NODE), param_name(p),  next(NULL)  {
        /* do nothing */
    }
    
    func_paramter_node* append(func_paramter_node *n) {
        func_paramter_node *tail = this; 
        while  (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = n;
        return this;
    }

    void print() {
        func_paramter_node *t = this;
        while (t != NULL) {
            printf("func_paramter_node: node type=> %d, param_name => [%s]\n",
                    t->node_type, t->param_name);
            t = t->next;
        }
    }
};

struct func_paramter_list : public node {
    std::list<char* > plist;
    func_paramter_list():node(FUNC_PARAM_LIST_NODE), plist(){
        /* do nothing */
    }
    
    func_paramter_list* append(char *p) {
        plist.push_back(p);
        return this;
    }
    void print() {
        printf("func_paramter_list\n");
    }
};

#endif //~NS_DEF_H____
