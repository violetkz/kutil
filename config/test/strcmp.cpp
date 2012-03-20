
#include <string>
#include <algorithm>
#include <iostream>

bool strcmp_ncase(const std::string& _f1, const std::string& _f2)
{   
    size_t len = _f1.size();
    if ( len != _f2.size())
        return false;

    std::string _f1_lower;
    std::string _f2_lower;

    _f1_lower.reserve(len);
    _f2_lower.reserve(len);

    std::transform(_f1.begin(), _f1.end(), _f1_lower.begin(), ::tolower);
    std::transform(_f2.begin(), _f2.end(), _f2_lower.begin(), ::tolower);
    int re =_f1.compare(_f2); 
    return  re;    
}

int main(){

    std::string tmp("ON");
    if (strcmp_ncase(tmp, "on")){
        std::cout << "==" << std::endl;
    }
}
