
#ifndef CONFIG_STMTS_HPP_H
#define CONFIG_STMTS_HPP_H

#include <list>
#include <map>
#include "config_token.hpp"
#include "config_lexer.hpp"

/*
 */
class stmt{
    public:
        enum STMT_TYPE {COMMENT, ITEM};
        int get_type();
        virtual void str(std::ostream& o){}
        virtual ~stmt(){}
#ifdef _DEBUG
        virtual void print(std::ostream& o){}
#endif
};


class comment_stmt: public stmt{
    public:
        comment_stmt(token& comment);
#ifdef _DEBUG
        virtual void print(std::ostream& o);
#endif
        virtual void str(std::ostream& o);
        virtual ~comment_stmt(){}
    private:
        token comment_;
};


class keyvalue_stmt: public stmt{
    public:
        keyvalue_stmt(token& key, token& val);
#ifdef _DEBUG
        virtual void print(std::ostream& o);
#endif
        virtual void str(std::ostream& o);
        virtual ~keyvalue_stmt(){}
    private:
        token key_;
        token value_;
};


class keyvalue_comment_stmt: public stmt{
    public:
        keyvalue_comment_stmt(token& key, token& val, token& sub);
#ifdef _DEBUG
        virtual void print(std::ostream& o);
#endif
        virtual void str(std::ostream& o);
        virtual ~keyvalue_comment_stmt(){}
    private:
        token key_;
        token value_;
        token subcomment_;
};

std::ostream& operator << (std::ostream&, stmt& sm);


class stmt_collector {
    public:
        void add_m_stmt(token& t);
        void add_kv_stmt(token& key,token& value);
        void add_kvm_stmt(token& key,token& value,token& subcomment);

        token find(const std::string& key);
        void print();

        ~stmt_collector();

    private:
        std::list<stmt *> stmt_list;
        typedef std::map<const std::string, token>  keyval_map_T;
        keyval_map_T keyval_map;
};
#endif
