
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <cstdio>
#include <cstdlib>


#include "config.hpp"

int main(){
    conf_parser a("test.cfg");
    a.parse();
    
    std::cout << "GET/SET test" << std::endl;
    std::cout << a.get("test_key1") << std::endl;
    std::cout << a.get("test_key2") << std::endl;
    std::cout << a.get("test_key3") << std::endl;
    
    a.set("key_X1", "val~1");
    a.set("key_X2", "val~22");
    a.set("key_X3", "val~3");
    a.set("key_X4", "val~4");
    std::cout << a.get("key_X1") << std::endl;
    std::cout << a.get("key_X2") << std::endl;
    std::cout << a.get("key_X3") << std::endl;
    std::cout << a.get("key_X4") << std::endl;
    a.set("key_X9",false);
    a.set("key_X10",true);
    std::cout << a.get("key_X9") << std::endl;
    std::cout << a.get("key_X10") << std::endl;

   // a.save();
    return 0;
}
