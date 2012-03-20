
#include "config.hpp"

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

    return 0;
}
