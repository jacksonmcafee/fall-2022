#include <iostream>
#include "passserver.h"

using namespace std;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main() { 
  // create essential variables
  char ch;
  char* input1 = nullptr;
  string s1, s2, s3;
  PassServer ps = PassServer();

  while(true) {
    // get user input
    Menu();
    cin >> ch;

    switch (ch) {
      case 'l':
        // get filename
        cin >> input1;
        ps.load(input1);
        break;

      case 'a':
        // get username and password
        cin >> s1 >> s2;
        ps.addUser(make_pair(s1, s2));
        break;
      
      case 'r':
        // get username
        cin >> input1;
        ps.removeUser(input1);
        break;

      case 'c':
        cin >> s1 >> s2 >> s3;
        ps.changePassword(make_pair(s1, s2), s3);
        break;

      case 'f':
        cin >> s1;
        ps.find(s1);
        break;

      case 'd':
        ps.dump();
        break;

      case 's':
        cout << ps.getSize() << endl;
        break;
      
      case 'w':
        cin >> input1;
        ps.write_to_file(input1);

      case 'x':
        return 0;
    }
  }
  return 0;
}