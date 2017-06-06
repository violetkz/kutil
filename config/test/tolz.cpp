#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

bool strcmp_ncase(const std::string& _f1, const std::string& _f2)
{   
    size_t len = _f1.size();
    if ( len != _f2.size())
        return false;

    std::string _f1_lower;
    std::string _f2_lower;

    _f1_lower.resize(len);
    _f2_lower.resize(len);

    std::transform(_f1.begin(), _f1.end(), _f1_lower.begin(), ::tolower);
    std::transform(_f2.begin(), _f2.end(), _f2_lower.begin(), ::tolower);
    int re =_f1_lower.compare(_f2_lower); 
    return  re == 0;    
}

int main(int args, char *argv[]){
    if (args == 3){
        
        if (strcmp_ncase (argv[1], argv[2])) cout << " == " << endl;
        else
            cout << "!=" << endl;
    }
    return 0;
}
