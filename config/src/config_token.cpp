
#include "config_token.hpp"
#include  <iostream>

token::val_ptr::val_ptr(const std::string& v)
        :ref(0), val_(v){
}
token::val_ptr::val_ptr(int tag) :ref(0) {
        switch (tag){
            case 0:     val_ = "";
                        break;
            case -1:     val_ = "<EOF";
                        break;
            default:
               val_ = std::string(1, static_cast<char>(tag));
        }
}


token::token():type_(T_START),val_ptr_(new val_ptr(T_START)){
}

token::token(int t):type_(t),val_ptr_(new val_ptr(t)){
}

token::token(int t, const std::string& v)
    :type_(t),val_ptr_(new val_ptr(v)){
}

token::~token(){
        if (val_ptr_->ref == 0){
            delete val_ptr_;
        }
        else val_ptr_->ref -= 1;
}

token::token(const token& t){
    type_ = t.type_;
    val_ptr_ = t.val_ptr_;
    
    val_ptr_-> ref += 1;
}

std::string token::str(){

    std::string s;
    switch (type_){
        case T_VALUE_STRING:
            //XXX: replace the following code with better way
            s += '"';
            s += val_ptr_->val_;
            s += '"';
            break;
        case T_COMMENT:
            s += '#';
            s += val_ptr_->val_;
            break;
        default:
            return val_ptr_->val_;
    }
    return s;
}

token& token::operator = (const token& t){
    if (this->val_ptr_ == t.val_ptr_){
        return *this;
    }

    if (val_ptr_->ref == 0){
        delete val_ptr_;
    }
    else --(val_ptr_->ref);

    type_ = t.type_;
    val_ptr_ = t.val_ptr_;
    
    ++(t.val_ptr_->ref);
    
    return *this;
}

std::ostream& operator << (std::ostream& out, const token& t){
    
    if (t.type_ == -1)
        out << '[' << "EOF" << "]:" ;
    else if (t.type_ == '\n')
        out << '[' << "LF"  << "]";
    else out << '[' << static_cast<char>(t.type_) << "]:" ;
  
    //out << '[' << t.value() << ']' << std::endl;
    out << t.val_ptr_->ref << ":" ;
    if (t.val_ptr_->val_.size() > 1) {
        out << t.val_ptr_->val_ << std::endl; ;
    }
    
#if 0
    out << t.val_ptr_->ref << ":" ;
    out << t.val_ptr_->val_ << std::endl; ;
#endif
    return out;
}

#ifdef debug_token
void  func1(){
    token a[10];
    token b[10];
    for (int i = 0; i < 10; i++){
        a[i] = token('a' + i);
    }
    
    for (int k = 0; k < 10; k++){
        b[k] = a[k];
    }
}
token func2(int i){
    std::string a(i, 'X');
    return token(i, a);
}
int main(){
#if 0
    token a(1);
    
    token b(a);
    
    token c(9);
    
    c = b;
    
    token d(2,"string test xxxxxx");
    token e(d);
    token x = e;
    

    x = e;
    
    token c(44, "ss");
    //for (int i = 0; i < 10; ++i){
        token s(c);
        std::cout << s.getvalue() << std::endl;
        token s1(c);
        std::cout << s1.getvalue() << std::endl;
        token s3(c);
        std::cout << s3.getvalue() << std::endl;
        
        token c3(100);
        token c4(-1);
        std::cout << c3.getvalue() << std::endl;
        std::cout << c4.getvalue() << std::endl;
   // }
        token a1('1');
        token a2('2');
        
        a1 = a2;
        func1();
        token look_ ;
        look_ = func2('K');
        look_ = func2('B');
        token a = look_;
        a = func2('c');
#endif
        token look_ ;
        look_ = func2('K');
        token look2_(look_);
        look2_ = look_;
}
#endif
