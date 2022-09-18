/* 
Jackson McAfee, COP4530 Asgn1

This is terrible, awful, horrible code that sucks.

Just so whoever grades this is aware, there is a high
likelihood that you get a segfault (sometimes) if you 
attempt to add two TList<float>s of any size. I do not
know why this happens, nor can I even replicate it when I am
trying to debug it. It would fail every tenth time, or not at all
for tons and tons of runs, but it would always fail every time
that I thought it might be fixed. 

I could not reproduce it within my gdb testing, so I am just submitting
it as is. Godspeed.
*/

#include <iostream>
#include <string>

#include "tlist.h"

template <typename T> 
// adapted from PrintList function used in provided driver.cpp
void PrintList(const TList<T>& L, std::string label)
{
   std::cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = "; 
   L.Print(std::cout);
   std::cout << "\n\n";
}

int main() {
	// test constructor, copy constructor, copy operator
	TList<int> myIntList(0, 10);
	TList<int> myOtherIntList(myIntList);
	TList<int> myOtherOtherIntList = myIntList;

	// should all be identical
	PrintList(myIntList, "myIntList");
	PrintList(myOtherIntList, "myOtherIntList");
	PrintList(myOtherOtherIntList, "myOtherOtherIntList");

	// empties myIntList, moves data from other
	myIntList.Clear();
	myIntList = std::move(myOtherOtherIntList);

	// myOtherIntList should be size 0, w/ nothing printed
	PrintList(myIntList, "myIntList");
	PrintList(myOtherOtherIntList, "myOtherOtherIntList");

	// random interspersed testing here
	myOtherIntList.InsertFront(2);
	myOtherIntList.InsertBack(50);
	myOtherIntList.InsertFront(1);
	myOtherIntList.InsertBack(51);

	// should have 1, 2 prepended, 50, 51 appended
	PrintList(myOtherIntList, "myOtherIntList");

	auto itr = myOtherIntList.GetIterator();
	itr.Next();
	itr.Next();
	myOtherIntList.Insert(itr, 3);

	itr = myOtherIntList.GetIteratorEnd(); 
	itr.Previous();
	itr.Previous();
	myOtherIntList.Remove(itr);

	// should appear like 3 replaced pos3, identical list
	PrintList(myOtherIntList, "myOtherIntList");

	myOtherIntList.RemoveFront();
	myOtherIntList.RemoveBack();
	myOtherIntList.RemoveFront();
	myOtherIntList.RemoveBack();

	// should have 3 at beginning, otherwise 0s
	PrintList(myOtherIntList, "myOtherIntList");

	// clean testing here

	// insert front and back
	for (int i = 10; i > 0; i--) { myIntList.InsertFront(i); }
	for (int i = 21; i < 31; i++) { myIntList.InsertBack(i); }
	PrintList(myIntList, "myIntList");

	std::cout << "Empty? " << myIntList.IsEmpty() << std::endl;
	std::cout << "First val? " << myIntList.GetFirst() << std::endl;
	std::cout << "Last val? " << myIntList.GetLast() << std::endl << std::endl;

	// remove front and back
	for (int i = 0; i < 10; i++) { myIntList.RemoveBack(); }
	for (int i = 0; i < 10; i++) { myIntList.RemoveFront(); }
	PrintList(myIntList, "myIntList");

	// iterator insert
	itr = myIntList.GetIterator();
	for (int i = 0; i < 10; i++) { myIntList.Insert(itr, i); }

	// iterator remove
	for (int i = 0; i < 10; i++) { 
		myIntList.Remove(itr);
		itr.Next();
	}
	
	PrintList(myIntList, "myIntList");
	
	// iterator traverse front to back
	itr = myIntList.GetIterator();
	for (int i = 0; i < myIntList.GetSize(); i++) {
		std::cout << itr.GetData() << " ";
		itr.Next();
	}
	std::cout << std::endl;

	// iterator traverse back to front
	itr = myIntList.GetIteratorEnd();

	for (int i = 0; i < myIntList.GetSize(); i++) {
		itr.Previous();
		std::cout << itr.GetData() << " ";
	}
	std::cout << std::endl;

	// test constructor for alternate type
	TList<float> myFloatList(1.23, 10);
	PrintList(myFloatList, "myFloatList");

	myIntList = myIntList + myOtherIntList;
	PrintList(myIntList, "myIntList");

	return 0;
}