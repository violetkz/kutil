/*
 * ============================================================================
 *       Filename:  map_test.cpp
 *    Description:  the test file of std::map
 *
 *        Version:  1.0
 *        Created:  2012/4/24 10:36:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   
 *   Organization:  
 *
 * ============================================================================
 */
#include <cstdio>
#include <map>
#include <string>
using namespace std;


int main(){
    typedef pair<int, string>  map_item;
    map<int, string> test_map;
    test_map.insert(map_item(1, "1"));
    test_map.insert(map_item(2, "2"));
    test_map.insert(map_item(4, "4"));
    test_map.insert(map_item(5, "5"));
    test_map.insert(map_item(6, "6"));
    test_map.insert(map_item(3, "3"));
    
    for (auto it = test_map.begin(); it != test_map.end(); ++it){
        printf(" %d ==> %s \n", it->first, it->second.c_str());
    }
    return 0;
}

