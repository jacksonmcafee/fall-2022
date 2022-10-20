#ifndef STACK_H
#define STACK_H

namespace cop4530 {

	template <typename T>
	class Stack {
		public:
			Stack();
			~Stack();
			Stack (const Stack<T>&);
			Stack (Stack<T>&&);

			Stack<T>& operator= (const Stack &);
			Stack<T>& operator= (Stack &&);
			
			bool empty() const;
			void clear();
			
			void push(const T& x);
			void push(T && x);
			void pop();

			T& top();
			const T& top() const;

			int size() const;
			void print(std::ostream& os, char ofc = ' ') const;

		private:
			T* _stack;
			int thesize;
			int max_size;

			T dummy;
	};

	template <typename T>
	std::ostream& operator<< (std::ostream& os, const Stack<T>& a);
	
	template <typename T>
	bool operator== (const Stack<T>&, const Stack<T>&);
	
	template <typename T>
	bool operator!= (const Stack<T>&, const Stack<T>&);
	
	template <typename T>
	bool operator<= (const Stack<T>& a, const Stack<T>& b);

#include "Stack.hpp"

}

#endif