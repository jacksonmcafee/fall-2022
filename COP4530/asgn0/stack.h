#ifndef STACK_H
#define STACK_H
// Created by David A Gaitros on 10/15/19.
// ********************************************************************
// * Name: Stack Class                                                *
// * Description: A template Stack class designed to be used with     *
// * any simple C++ type to include floating point, double            *
// * floating point, character, and Boolean.                          *
// * The stack pointer, as is the convention, points to the last      *
// * or highest element in the array. So if you allocate 100          *
// * elements of type "T" then the first empty element will be 99.    *
// * Author: Dr. David A. Gaitros                                     *
// * Date: January 19, 2019                                           *
// ********************************************************************
#include <iostream>
using namespace std;

const int DEFAULTSIZE=100;
template <typename T> class Stack;
template <typename T> ostream & operator <<(ostream & os,  Stack<T> &obj);
template <typename T>
class Stack {
public:
    Stack();                    // Default Constructor, stack is size 100.
    Stack(const int size);      // Constructor, creates stack of size "size"
    Stack(const Stack & Obj);   // Copy constructor
    ~Stack();                   // Destructor
    bool Full();                // Return true if the stack is full
    bool Empty();               // Return true if the stack is empty
    int Size();                 // Return the size of the stack
    int Number();               // Return the number of elements stored
    T Top();                    // Returns the top element, does not pop it
    bool Push (const T item);   // Put an item on the stack
    bool Pop();                 // Pop an item off and display to std out
    Stack<T> &operator = (Stack<T> & s); // = operator overload.
    friend ostream &operator << <T>(ostream & os, Stack<T> &s);

protected:
    T * _stack;                 // The "stack"
    int _size;                  // The number of elements the stack can hold
    int _top;                   // Points to the first empty node
    int _number;                // The number of elements in the stack.
};

template < class T >
Stack<T>::Stack() {
	// default constructor of size 100
	_size = DEFAULTSIZE;
	_number = 0;
	_top = 0;

	_stack = new T[_size];
	}	

template < class T >
Stack<T>::Stack(const int size) {
	// constructor of size size
	if (size > 0) { _size = size; }
	else { _size = DEFAULTSIZE; }
	_number = 0;
	_top = 0;

	_stack = new T[_size];
	}

template < class T >
Stack<T>::Stack(const Stack & Obj) {
	// copy constructor from Obj
	_size = Obj._size;
	_number = Obj._number;
	_top = Obj._top;

	delete[] _stack;
	_stack = new T[_size];

	// copies all values from Obj
	for(int i = 0; i < _number; i++) {
		_stack[i] = Obj._stack[i];
		}
	}

template < class T >
Stack<T>::~Stack() {
	// _stack is dynamically allocated, free w/ delete[]
	delete[] _stack;
	}

template < class T >
bool Stack<T>::Full() {
	if (_top == _size) {
		// if the _top node is the same as the size, the stack is full
		// because _top is the first AVAILABLE node, if it == _size, pushing
		// another object would actually be the 101st node because _stack
		// is 0-indexed
		return true;
		}
	return false;
	}

template < class T >
bool Stack<T>::Empty() {
	if (_number > 0) {
		// stack is not empty if there _number is nonzero, return false
		return false;
		}
	return true;
	}

template < class T >
int Stack<T>::Size() { return _size; }

template < class T >
int Stack<T>::Number() { return _number; }

template < class T >
T Stack<T>::Top() {
	// returns the (_top - 1) item because _top is a free node 
	return _stack[_top - 1];
	}

template < class T >
bool Stack<T>::Push(const T item) {
	if(Full() != true) {
		_stack[_top] = item;
		_top++;
		_number++;
		return true;
		}
	else {
		std::cout << "Stack is full, failed to push." << std::endl;
		return false;
		}
	}

template < class T >
bool Stack<T>::Pop() {
	if (Empty() != true) {
		std::cout << _stack[_top - 1] << std::endl;
		_number--;
		_top--;
		return true;
		}
	else {
		std::cout << "Stack is empty, nothing to pop!" << std::endl;
		return false;
		}
	}

template < class T >
Stack<T>& Stack<T>::operator = (Stack<T> &s) {
	_size = s._size;
	_number = s._number;
	_top = s._top;

	// resizes stack to match
	delete[] _stack;
	_stack = new T[_size];
	
	for(int i = 0; i < _number; i++) {
		_stack[i] = s._stack[i];
		}

	return *this;
	}	

template < class T >
ostream& operator<< (ostream &os, Stack<T> &obj) {
	os << "Status: " << endl;
	os << "Empty: " << obj.Empty() << endl;
	os << "Full: " << obj.Full() << endl;
	os << "Stack Size: " << obj.Size() << endl;
	os << "Number of items on Stack: " << obj.Number() << endl;
	os << "The top element is " << obj.Top() << endl;
 
	if (obj.Empty() == true) {
		return os;
	}
	else {
		os << "Pops -> ";
		obj.Pop();
		for(int i = obj._number - 1; i > -1; i--) {
			os << obj._stack[i] << endl;
		}
	}
	return os;
}

#endif
