#include <iostream>
#include "Stack.h"

using namespace cop4530;

int main() {
	Stack<int> intStack;
	
	for (int i = 0; i < 10; ++i) {
		intStack.push(i);
	}

	std::cout << intStack << std::endl;

	return 0;
}