#ifndef NS_DEF_H____
#define NS_DEF_H____

#include <list>

struct node {
    enum {
        STMT_NODE,
        FUNC_PARAM_LIST_NODE,
        FUNC_NODE,
        STR_NODE,
        REGEX_STR_NODE
    };
    int node_type;
    node(int t) : node_type(t) {}
};

struct str_node : public node {
    char* s;
    str_node(char* str):node(STR_NODE), s(str) {
        /* do nothing */
    }
};

struct regex_str_node : public node {
    char* regex_str;
    
    regex_str_node(char* str):node(REGEX_STR_NODE), regex_str(str) {
        /* do nothing */  
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
};

struct builtin_func_node : public node {
    char* func_name;
    node* plist;

    builtin_func_node(char *name, node *plist)
            :node(FUNC_NODE),
            func_name(name),
            plist(plist) {
        /* do nothing */
    }
};

struct func_paramter_node : public node {
    char* param_name;
    struct func_paramter_node *next; /* point to next paramter */
    
    func_paramter_node(const char* p)
            :node(FUNC_PARM_NOE), param_name(p),  next(NULL)  {
        /* do nothing */
    }
}

struct func_paramter_list : public node {
    std::list<char* > plist;
    func_paramter_list():node(FUNC_PARAM_LIST_NODE), plist(){
        /* do nothing */
    }
    
    func_paramter_list* append(char *p) {
        plist.push_back(p);
        return this;
    }
};

#endif //~NS_DEF_H____
