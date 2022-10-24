/*
The structure of this program is based on a personal practice stack 
implementation, which is why it includes max_size and resizing checks
within both push and pop.

While I am aware that resizing by a factor of 2 might not be the most
space efficient when you are using large numbers of values, I thought it might
be more time efficient than expanding it every iteration of push().
*/

#ifndef STACK_HPP
#define STACK_HPP

#include "Stack.h"

using namespace cop4530;

template <typename T>
Stack<T>::Stack() {
	thesize = 0;
	max_size = 2;

	_stack = new T[max_size];
}

template <typename T>
Stack<T>::Stack(const Stack& s) {
	thesize = 0;
	max_size = 2;
	_stack = new T[s.thesize];

	while (thesize != s.thesize) {
		push(s._stack[thesize]);
		thesize++;
	}
} 

template <typename T>
// move constructor
Stack<T>::Stack(Stack && s) {
	thesize = s.thesize;
	max_size = s.max_size;

	_stack = new T[max_size];

	T* temp = _stack;
	_stack = s._stack;
	s._stack = temp;
}

template <typename T>
Stack<T>::~Stack() {
	delete[] _stack;
}

template <typename T>
bool Stack<T>::empty() const {
	return (thesize == 0);
}

template <typename T>
// clears _stack by popping every value until thesize == 0
void Stack<T>::clear() {
	while (!empty()) {
		pop();
	}
}

// push function
template <typename T>
void Stack<T>::push(const T& x) {
	// if size is less than the max size, push to stack 
	if (thesize < max_size) {
		_stack[thesize] = x;
		thesize++;
	}

	// if size is equal to max_size, double stack size 
	else {
		// store pointer to _stack
		T* old_stack = _stack;
		// double _stack size
		max_size *= 2;

		// assign new memory to _stack
		_stack = new T[max_size]; 

		// copy values from old array
		for (int i = 0; i < thesize; i++) {
			_stack[i] = old_stack[i];
		}

		_stack[thesize] = x;
		thesize++;

		delete[] old_stack;
	}
}

template <typename T>
// replace top element of stack with x
void Stack<T>::push(T && x) {
	_stack[thesize] = x;
  thesize++;
}

template <typename T>
// removes the top object and returns it
void Stack<T>::pop() {
	if (thesize != 0) {
		thesize--;

		if (thesize < max_size / 2) {
			// store pointer to _stack
			T* old_stack = _stack;

			// resize max_size based on scale factor
			max_size /= 2;

			// assign new memory to _stack
			_stack = new T[max_size];

			// copy values from old array
			for (int i = 0; i < thesize; i++) {
				_stack[i] = old_stack[i];
			}
					
			delete[] old_stack;	
		}
	}
}

template <typename T>
T& Stack<T>::top() {
	if (thesize != 0) { return _stack[thesize - 1]; }
	else { return dummy; }
}

// could fail...
template <typename T>
const T& Stack<T>::top() const {
	if (thesize != 0) { return &_stack[thesize - 1]; }
	else { return dummy; }
}

template <typename T>
int Stack<T>::size() const {
	return thesize;
}

template <typename T>
// copy operator overload
Stack<T>& Stack<T>::operator= (const Stack& s) {
	if (this != &s) {
		// set default values
		thesize = s.thesize;
		max_size = s.max_size;

		// delete old stack
		delete[] _stack;

		// assign memory to _stack
		_stack = new T[max_size];

		// copy values from d._stack to _stack
		for (int i = 0; i < max_size; i++) {
			_stack[i] = s._stack[i];
		}
	}
	return *this;
}

template <typename T>
// move operator overload
Stack<T>& Stack<T>::operator= (Stack && s) {
	if (this != &s) {
		// set default values
		thesize = s.thesize;
		max_size = s.max_size;

		// swap _stacks
		T* temp = _stack;
		_stack = s._stack;
		s._stack = temp;
	}
	return *this;
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
	// iterate through stack
	for(int i = 0; i < thesize; ++i) {
		// pass _stack[i] to os and delim
		os << _stack[i] << ofc;
	}
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a) {
	if(a.empty()) {
		os << "This stack is empty!" << std::endl;
		return os;
	}
	else {
		a.print(os);
		return os;
	}
}

// equivalence operator overloads
template <typename T>
bool operator== (const Stack<T>& a, const Stack<T>& b) {
	if (a.thesize != b.thesize) { return false; }
	else {
		for (int i = 0; i < a.thesize; ++i) {
			if (a._stack[i] != b._stack[i]) {
				return false;
			}
		}
	}
	return true;
}

template <typename T>
bool operator!= (const Stack<T>& a, const Stack<T>& b) {
	return !(a == b);
}

template <typename T>
bool operator<= (const Stack<T>& a, const Stack<T>& b) {
	if (a.thesize != b.thesize) { return false; }
	else {
		for (int i = 0; i < a.thesize; ++i) {
			if (a._stack[i] > b._stack[i]) {
				return false;
			}
		}
	}
	return true;
}

#endif