#ifndef ns_string__h__
#define ns_string__h__


class ns_string {
public:
    ns_string(char *s);
    ~ns_string();
    
    ns_string(const ns_string &s);
    ns_string &operator = (const ns_string &s);
private:
    char *str_ptr;
};

#endif //~ns_string__h__
