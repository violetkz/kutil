
#include <string>
#include <algorithm>
#include <iostream>
#include <locale>
#include <cctype>

using namespace std;
bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}


bool strcmp_ncase(const std::string& _f1, const std::string& _f2)
{   
    size_t len = _f1.size();
    if ( len != _f2.size())
        return false;

    if (_f1 == _f2){
        std::cout<< __func__ << "f1==f2: ==" << std::endl;
    }
    
    /* SHIT CPP!!! shit string!!!! */ 
    std::string _f1_lower('x', len); 
    std::string _f2_lower('a', len);

    //_f1_lower.reserve(len);
    //_f2_lower.reserve(len);

    std::transform(_f1.begin(), _f1.end(), _f1_lower.begin(), ::tolower);
    std::transform(_f2.begin(), _f2.end(), _f2_lower.begin(), ::tolower);
    int re =_f1_lower.compare(_f2_lower); 
    if (_f1_lower == _f2_lower){
        std::cout<< __func__ << "==" << std::endl;
    }
    return  re == 0;    
}

int main(){

    std::string tmp("test1");
    if (strcmp_ncase(tmp, "false")){
        std::cout << "1==" << std::endl;
    }
   
    if (iequals(tmp, "false")){
        std::cout << "==" << std::endl;
    }
    
    string t1 = "test1";
    string t2  = "false";
    
    if (t1 == t2) {
        cout << " if (t1 == t2) " << endl;
    }
    if (strcmp_ncase(t1,t2)){
        cout << "strcmp_ncase(t1,t2)" << endl;
    }

}
