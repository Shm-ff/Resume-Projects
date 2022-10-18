// @author Mohammed Abdulaziz
// @date 10/02/22
// @brief Primitive search engine which mimics the process of early 2000's search engines
//        as well as uses an inverted index in order to make searching much more optimized.

#include <iostream>
#include "search.h"
#include <fstream>
using namespace std;

int main() {
    // Uncomment line below to start test cases
    // map<string, set<string>> index;
    // Test Case for Milestone 3
    
    // buildIndex("cplusplus.txt", index);
    // for ( auto x : index) {
    //     cout << x.first << " ";
    //     for (string websites : x.second) {
    //         cout << websites << " ";
    //     }
    //     cout << endl;
    // }
    
    // Test case for Milestone 4
    
    // set<string> result = findQueryMatches(index, "vector +container");
    // for (string str : result) {
    //     cout << str << endl;
    // }
    
    searchEngine("cplusplus.txt");
    return 0;
}

