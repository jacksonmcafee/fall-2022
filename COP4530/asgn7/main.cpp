#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>

/* 
Jackson McAfee
Asgn7 Word/Number Counting Program

I chose to use maps because they have O(log(n)) complexity which was
about as quick as I thought I might be able to make it. 
*/

int main() {
    // create map and string objects   
    map<string, int> valMap;
    std::string in_str = "";
    std::string store_str = "";

    // create int to determine what the previous char was
    // 1 for alpha, 2 for numeric, 3 for {" ", "\t", "\n"} 
    int prev_char = 0;

    // TODO: might need to swap to NOT getline depending on file input
    // get string as input then transform it to all lowercase w/ transform
    std::getline(std::cin, in_str);
    std::transform(in_str.begin(), in_str.end(), in_str.begin(), [](unsigned char c) { return std::tolower(c); });

    // iterate through string 
    for (int i = 0; i < in_str.size(); ++i) {
        switch (prev_char): 
            case 1:
                // check if current char is numeric 
                if (std::isdigit(in_str[i])) {
                    // update prev_char immediately
                    prev_char = 2;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);
                    
                    // clear storage string, then append current char as first
                    store_str.clear();
                }
                // check if current char is alt char
                else if (in_str[i] == ' ' || in_str[i] == '\t' || in_str[i] == '\n') {
                    // update prev_char immediately
                    prev_char = 3;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);
                    
                    // clear storage string, append current char
                    store_str.clear();
                } 
                store_str += in_str[i];
                break;

            case 2:
                // check if current char is alpha 
                if (std::isalpha(in_str[i])) {
                    // update prev_char immediately
                    prev_char = 1;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);

                    // clear storage string, then append current char as first
                    store_str.clear();
                }
                // check if current char is alt char
                else if (in_str[i] == ' ' || in_str[i] == '\t' || in_str[i] == '\n') {
                    // update prev_char immediately
                    prev_char = 3;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);

                    // clear storage string, then append current char as first
                    store_str.clear();
                }
                store_str += in_str[i];
                break;

            case 3:
                // check if current char is numeric
                if (std::isalpha(in_str[i])) {
                    // update prev_char immediately
                    prev_char = 1;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);

                    // clear storage string, then append current char as first
                    store_str.clear();
                }
                // check if current char is numeric
                else if (std::isdigit(in_str[i])) {
                    // update prev_char immediately
                    prev_char = 2;

                    // current is NOT the same as previous, we need to check and store this string
                    storeInMap(valMap, store_str);

                    // clear storage string, then append current char as first
                    store_str.clear();
                }
                store_str += in_str[i];
                break;

            default:
                // EOL/EOF reached, exit loop
                i = in_str.size() - 1;

    }

}

void storeInMap(std::map<string, int> map, std::string str) {
    // take map and string as input, all storage should be identical
    if (map.find(str) == map.end()) {
        map.insert(std::make_pair(str, 1));
    }
    else {
        map[str]++;    
    }
}