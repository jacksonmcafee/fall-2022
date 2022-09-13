#include <iostream>
#include <string>

#include "tlist.h"

using namespace std;

template <typename T> 
void PrintList(const TList<T>& L, string label)
{
   cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = "; 
   L.Print(cout);
   cout << "\n\n";
}

int main()
{

   TList<int> int_list(1, 10);
   std::cout << int_list.GetSize() << std::endl;
   std::cout << int_list.IsEmpty() << std::endl;
   int_list.Clear();

   std::cout << int_list.GetSize() << std::endl;
   std::cout << int_list.IsEmpty() << std::endl;

   std::cout << "do something" << std::endl;
   return 0;
}
