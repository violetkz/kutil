
#include "config.hpp"
#include <iostream>

using namespace std;

int main(int argv, char * args[]){
    
    //case1
    config f("test.cfg");
    f.parse();

    //case2
    //config f2;
    //f2.parse("test.cfg");
    //f2.set("bool_key1", true);
    //f2.set("string_key1","string val");
    //f2.set("number_key1",2333);
    //f2.save();
    
    f.print();
    
    cout << f.get("test1") << endl;
    cout << f.get("test2") << endl;
    cout << f.get("test3") << endl;
    
    cout << f.get_int("test2") << endl;
    cout << f.get_bool("test4") << endl;
    return 0;
}
