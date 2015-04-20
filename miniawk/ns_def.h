

struct node {
    int node_type;
    node(int t) : node_type(t) {}
};

struct stmt_node : public node {
    node* pattern;
    node* action;
    stmt_node(node* p, node* act):node(STMT_NODE), pattern(p), action(act) {}
};

struct builtin_func_node : public node {
    char* func_name;
    //std::list<char *> plist;
    node* plist;
    builtin_func_node(char *name, node *plist)
            :node(func_node),
            func_name(name),
            plist(plist) {}
}

struct func_paramter_list : public node {
    std::list<char* > plist;
    func_paramter_list(char *node);
}
