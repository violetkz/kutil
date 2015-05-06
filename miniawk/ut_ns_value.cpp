
#include "ns_value.h"
#include <iostream>

void constructor_test () {
    ns_value n(99);     std::cout << n;
    ns_value nb(false);  std::cout << nb;
    ns_value ns("Test~");  std::cout << ns;
    
    ns_value xn(NSVAL_ILLEGAL); std::cout << xn;
    ns_value xn2(NSVAL_UNINITIALIZED); std::cout << xn2; 
    ns_value n1 = -222; std::cout << n1;
    ns_value n2 = true; std::cout << n2;
    ns_value n3 = "wwewtpetept"; std::cout << n3;
    ns_value n4 = NSVAL_UNINITIALIZED; std::cout << n4;
}

void assign_test() {
    ns_value ns(99);
    ns_value nx; 
    
    nx = ns;    std::cout << nx;

    ns_value nss("assign_test-----");
    ns_value nss_1 = "initialized string";
    ns_value nss_2 = nss;
    ns_value nss_3 = nss;
    ns_value nss_4 = nss_2;
    nss_2 = nss;

    ns_value *nvp = new ns_value("1234567890");
    
    std::cout << *nvp ;
    delete nvp;
}

int main() {
    constructor_test();
    assign_test();
}
