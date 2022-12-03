#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/*
Jackson McAfee
Asgn7 Word/Number Counting Program

I chose to use maps because they have O(log(n)) complexity which was
about as quick as I thought I might be able to make it.
*/

void storeInMap(std::map<std::string, int> &, std::string);
void printMap(std::map<std::string, int>);
bool comparePairs(std::pair<std::string, int>, std::pair<std::string, int>);

int main() {
  // create map and string objects
  std::map<std::string, int> valMap;
  std::string in_str = "";
  std::string store_str = "";
  std::string temp_str = "";

  std::string specChars = "!@#$%^&*()-=_+[]{}/.,<>|";

  // create int to determine what the previous char was
  // 1 for alpha, 2 for numeric, 3 for {" ", "\t", "\n"}
  int prev_char;

  // TODO: might need to swap to NOT getline depending on file input
  // get string as input then transform it to all lowercase w/ transform
  while (std::getline(std::cin, temp_str)) {
    in_str = in_str + "\n" + temp_str;
  }
  std::transform(in_str.begin(), in_str.end(), in_str.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (std::isalpha(in_str[0])) {
    prev_char = 1;
  } else if (std::isdigit(in_str[0])) {
    prev_char = 2;
  } else {
    prev_char = 3;
  }

  // iterate through string
  for (int i = 0; i < in_str.size(); ++i) {
    switch (prev_char) {
    case 1:
      // check if current char is numeric
      if (std::isdigit(in_str[i])) {
        // update prev_char immediately
        prev_char = 2;

        // current is NOT the same as previous, we need to check and store
        // this string
        storeInMap(valMap, store_str);

        // clear storage string, then append current char as first
        store_str.clear();
      }
      // check if current char is alt char
      else if (in_str[i] == '\n' || in_str[i] == '\t' || in_str[i] == ' ' ||
               std::find(specChars.begin(), specChars.end(), in_str[i]) !=
                   specChars.end()) {
        // update prev_char immediately
        prev_char = 3;

        // current is NOT the same as previous, we need to check and store
        // this string
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

        // current is NOT the same as previous, we need to check and store
        // this string
        storeInMap(valMap, store_str);

        // clear storage string, then append current char as first
        store_str.clear();
      }
      // check if current char is alt char

      else if (in_str[i] == '\n' || in_str[i] == '\t' || in_str[i] == ' ' ||
               std::find(specChars.begin(), specChars.end(), in_str[i]) !=
                   specChars.end()) {
        // update prev_char immediately
        prev_char = 3;

        // current is NOT the same as previous, we need to check and store
        // this string
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

        // current is NOT the same as previous, we need to check and store
        // this string
        storeInMap(valMap, store_str);

        // clear storage string, then append current char as first
        store_str.clear();
      }
      // check if current char is numeric
      else if (std::isdigit(in_str[i])) {
        // update prev_char immediately
        prev_char = 2;

        // current is NOT the same as previous, we need to check and store
        // this string
        storeInMap(valMap, store_str);

        // clear storage string, then append current char as first
        store_str.clear();
      }
      store_str += in_str[i];
      break;

    default:
      // EOL/EOF reached, exit loop
      std::cout << "End of file located. Exiting program." << std::endl;
      i = in_str.size() - 1;
    }
  }
  // store final word in string
  storeInMap(valMap, store_str);
  printMap(valMap);
}

void storeInMap(std::map<std::string, int> &map, std::string str) {
  // take map and string as input, all storage should be identical
  if (map.find(str) == map.end()) {
    map.insert(std::pair<std::string, int>(str, 1));
  } else {
    map[str]++;
  }
}

void printMap(std::map<std::string, int> map) {
  std::cout << "Printing the map..." << std::endl;

  std::vector<std::pair<std::string, int>> wordVec;
  std::vector<std::pair<std::string, int>> intVec;
  std::vector<std::pair<std::string, int>> charVec;

  for (const auto &pair : map) {
    if (std::isalpha(pair.first[0])) {
      wordVec.push_back(make_pair(pair.first, pair.second));
    } else if (std::isdigit(pair.first[0])) {
      intVec.push_back(make_pair(pair.first, pair.second));
    } else {
      charVec.push_back(make_pair(pair.first, pair.second));
    }
  }

  std::sort(wordVec.begin(), wordVec.end(), comparePairs);
  std::sort(intVec.begin(), intVec.end(), comparePairs);
  std::sort(charVec.begin(), charVec.end(), comparePairs);

  std::cout << "Strings in map..." << std::endl;
  if (wordVec.size() > 10) {
    for (int i = 0; i < 10; ++i) {
      std::cout << wordVec[i].first << " - " << wordVec[i].second << std::endl;
    }
  } else {
    for (auto &x : wordVec) {
      std::cout << x.first << " - " << x.second << std::endl;
    }
  }

  std::cout << "Ints in map..." << std::endl;
  if (intVec.size() > 10) {
    for (int i = 0; i < 10; ++i) {
      std::cout << intVec[i].first << " - " << intVec[i].second << std::endl;
    }
  } else {
    for (auto &x : intVec) {
      std::cout << x.first << " - " << x.second << std::endl;
    }
  }

  std::cout << "Characters in map..." << std::endl;
  if (charVec.size() > 10) {
    for (int i = 0; i < 10; ++i) {
      if (charVec[i].first == " ") {
        std::cout << "space - " << charVec[i].second << std::endl;
      } else if (charVec[i].first == "\n") {
        std::cout << "newline - " << charVec[i].second << std::endl;
      } else if (charVec[i].first == "\t") {
        std::cout << "tab - " << charVec[i].second << std::endl;
      }
    }
  } else {
    for (auto &x : charVec) {
      if (x.first == " ") {
        std::cout << "space - " << x.second << std::endl;
      } else if (x.first == "\n") {
        std::cout << "newline - " << x.second << std::endl;
      } else if (x.first == "\t") {
        std::cout << "tab - " << x.second << std::endl;
      }
    }
  }
}

bool comparePairs(std::pair<std::string, int> lhs,
                  std::pair<std::string, int> rhs) {
  // compare ints to see which is greater
  return lhs.second > rhs.second;
}
