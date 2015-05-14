#ifndef ns_value_h___
#define ns_value_h___

#include <iostream>
#include <list>

enum ns_value_type {
    NSVAL_INTEGER       = 0, /* integer */
    NSVAL_LITERAL_STR   = 1, /* literal string */
    NSVAL_BOOLEAN       = 2, /* boolean */
    NSVAL_EXPERESS_AST  = 3, /* expression  */
    NSVAL_UNINITIALIZED = 4, /* uninitialized */
    NSVAL_ILLEGAL       = 5, /* illegal */
    NSVAL_STATUS        = 6, /* stmt stauts */
    NSVAL_LIST          = 7, /* list */
    NSVAL_CHAR          = 8, /* char */
};

enum ns_status_type {
    NSVAL_STATUS_OK, 
    NSVAL_STATUS_FAILED
};

struct node; //previous declaration

class ns_value {
public:
    ns_value_type type;
    union {
        //char                    chr_val;    /* value for char */
        int                     int_val;    /* value for integer or status */
        bool                    bool_val;   /* value for boolean */
        std::string             *chr_val;   /* value for string  */
        node                    *node_val;  /* placeholder. not implemention. */
        std::list<ns_value>     *list_val;  /* value for array    */
    };

public: 
    ns_value():type(NSVAL_UNINITIALIZED), int_val(0), ref_count(0) {}
    ns_value(const ns_value& n);
    ~ns_value();

    explicit ns_value(int v) : type(NSVAL_INTEGER), int_val(v) ,ref_count(0) {}
    explicit ns_value(bool b) : type(NSVAL_BOOLEAN), bool_val(b) ,ref_count(0){}
    explicit ns_value(const char *s);
    explicit ns_value(ns_value_type t);
    explicit ns_value(ns_value_type t, ns_status_type status) 
            : type(t), int_val(status), ref_count(0){}
    inline int count() const {return (ref_count) ? *ref_count : 0;}
    ns_value &operator = (const ns_value &s);

    operator bool();

    inline bool is_int() const {
        return (type == NSVAL_INTEGER); 
    }

    inline bool is_illegal_value() const { 
        return (type == NSVAL_ILLEGAL);
    }

    inline bool is_iteratale() const { 
        return (type == NSVAL_LITERAL_STR || type == NSVAL_LIST); 
    }

private:
    inline void add_ref(); 
    inline void release();
    inline void destruct();
    static bool is_ref_count_type(ns_value_type t);
private:
    static const int need_ref_count_bit_map;
    int *ref_count;
};

std::ostream &operator << (std::ostream &out, const ns_value &v);
ns_value operator+ (const ns_value &l, const ns_value &r);
ns_value operator- (const ns_value &l, const ns_value &r);
ns_value operator* (const ns_value &l, const ns_value &r);
ns_value operator/ (const ns_value &l, const ns_value &r);
ns_value operator% (const ns_value &l, const ns_value &r);

bool operator == (const ns_value &l, const ns_value &r);
bool operator != (const ns_value &l, const ns_value &r);
bool operator >  (const ns_value &l, const ns_value &r);
bool operator <  (const ns_value &l, const ns_value &r);
bool operator <= (const ns_value &l, const ns_value &r);
bool operator >= (const ns_value &l, const ns_value &r);


ns_value get_elem(const ns_value &n, unsigned int index);
const ns_value& set_elem(const ns_value &n, unsigned int index, const ns_value &v);
#endif  //~ns_value_h___
