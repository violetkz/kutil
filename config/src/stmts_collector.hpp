
#ifndef STMTS_COLLECTOR_HPP
#define STMTS_COLLECTOR_HPP

class stmt_collector {
    public:
        void add_m_stmt(token& t);
        void add_kv_stmt(token& key,token& value);
        void add_kvm_stmt(token& key,token value,token& subcomment);
        
        token find(const std::string& key);
        void print(std::ostream& o);

        ~stmt_collector();

    private:
        std::list<stmt *> stmt_list;
        typedef std::map<const std::string, token>  keyval_map_T;
        keyval_map_T keyval_map;
};

#endif
