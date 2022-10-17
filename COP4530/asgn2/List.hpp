#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"

using namespace cop4530;

template <typename T>
List<T>::const_iterator::const_iterator() {
	this->current = nullptr;
}

// * op overload, just needs to call retrieve to get val
template <typename T>
const T& List<T>::const_iterator::operator*() const {
	return retrieve();
}

// increment/decrement operators
template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++() {
	current = current->next;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
	const_iterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
	current = current->prev;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
	const_iterator temp = *this;
	--(*this);
	return temp;
}

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
	return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
	return !(*this == rhs);
}

// get val of current 
template <typename T>
T& List<T>::const_iterator::retrieve() const {
	return current->data;
}

// constructor, get iterator at p
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) {
	current = p;
}					

// iterator default constructor
template <typename T>
List<T>::iterator::iterator() { }

// * op overload, just needs to call retrieve to get val
template <typename T>
T& List<T>::iterator::operator*() {
	return const_iterator::retrieve();
}

template <typename T>
const T& List<T>::iterator::operator*() const {
	return const_iterator::operator*();
}

// increment/decrement operators
template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++() {
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
	iterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--() {
	this->current = this->current->prev;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
	iterator temp = *this;
	--(*this);
	return temp;
}

template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p}{}

// default constructor
template <typename T>
List<T>::List() {
	init();
}

// copy constructor
template <typename T>
List<T>::List(const List &rhs) {
	init();
	for(auto &x : rhs)
		push_back(x);
}

// move constructor
template <typename T>
List<T>::List(List && rhs) {
	theSize = rhs.theSize;
	head = rhs.head;
	tail = rhs.tail;
	rhs.theSize = 0;
	rhs.head = rhs.tail = nullptr;
}

// val constructor
template <typename T>
List<T>::List(int num, const T& val) {
	init();
	for(int i = 0; i < num; i++) {
		this->push_back(val);
	}
}

// iterator constructor
template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
	init();
	while(start != end) {
		this->push_back(*start);
		start++;
	}	
}

// destructor definition
template <typename T>
List<T>::~List() {
	clear(); 
	delete head; 
	delete tail;
}

// copy assignment operator
template <typename T>
const List<T> &List<T>::operator=(const List &rhs) {
	List copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// move assignment operator
template <typename T>
List<T> &List<T>::operator=(List && rhs) {
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

// return size&e <typename T>
void List<T>::clear() {
	while (!empty()) { 
		pop_front(); 
	}
}

// == operator override
template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs) {
	// check if size ==
	return (lhs.size()==rhs.size());
};

// != operator override
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
	// checks if size !=
	return (lhs.size()!=rhs.size());
};

// << operator override
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
	l.print(os);
	return os;
};

template <typename T>
void List<T>::reverse() {
	// create alt list, push everything to it in reverse
	// assign list to this
	List<T> list;
	int size = theSize;
	for(int i = 0; i < size; i++) {
		list.push_front(this->back());
		this->pop_back();
	}

	// wish I could this = list 

	for(int j = 0; j < size; j++) {
		this->push_front(list.front());
		list.pop_front();
	}
}

template <typename T>
T& List<T>::front() {
	return *begin();
}

template <typename T>
const T& List<T>::front() const {
	return *begin();
}

template <typename T>
T& List<T>::back() {
	return *--end();
}

template <typename T>
const T& List<T>::back() const {
	return *--end();
} 

// push to front of list
template <typename T>
void List<T>::push_front(const T & val) {
	insert(begin(), val);
}

// push to front of list w move
template <typename T>
void List<T>::push_front(T && val) {
	insert(begin(), std::move(val));
}

// push to back of list
template <typename T>
void List<T>::push_back(const T & val) {
	insert(this->end(), val);
}

// push to back of list w/ move
template <typename T>
void List<T>::push_back(T && val) {
	insert(this->end(), std::move(val));
}

// remove node from front of list
template <typename T>
void List<T>::pop_front() {
	erase(begin());
}

// remove node from back of list
template <typename T>
void List<T>::pop_back() {
	erase(--end());
}

// iList constructor
template <typename T>
List<T>::List(std::initializer_list<T> iList) {
	init();
	// iterate through iList and push each val
	for(const auto& it: iList) 
       push_back(it);
}

// iList operator= override
template <typename T>
List<T>& List<T>::operator= (std::initializer_list<T> iList) {
	// empty this
	clear();
	// iterate through iList and push each val
	for(const auto& it: iList) 
       push_back(it);
	return *this;
}

template <typename T>
void List<T>::remove(const T &val) {
	// create iterator at beginning of obj
	iterator itr = this->begin();
	// iterate thrpugh list
	for(itr; itr != this->end(); ++itr) {
		if(*itr == val) {
			this->erase(itr);
			itr = this->begin();
		}
	}
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
	// create iterator at beginning of obj
	const_iterator itr = this->begin();
	// iterate through list
	for(itr; itr != this->end(); itr++) {
		// pass itr val to os and delim
		os << *itr << ofc;
	}
} 

// not sure if this is too messy or not w/ template declarations
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
	iterator itr = this->begin();
		// iterate through list
        for (itr; itr != this->end(); itr++) {   
            auto x = *itr;
            // if pred(x) == true, erase at that location
            if (pred(x)) {
                erase(itr);
            }
		}
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
	return this->head->next;
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
	return this->head->next;
}

template <typename T>
typename List<T>::iterator List<T>::end() {
	return this->tail;
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
	return this->tail;
} 

// normal insert
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
	Node *p = itr.current;
	theSize++;
	return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}

// move insert
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) {
	Node *p = itr.current;
	theSize++;
	return { p->prev = p->prev->next = new Node(std::move(val), p->prev, p) };
}

// normal erase
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
	Node *p = itr.current;
	iterator retVal{p->next};
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	return retVal;
}


// erases from [start, end)
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
	for(iterator itr = start; itr != end;)
		itr = erase(itr);
	return end;
}

// initializes vals
template <typename T>
void List<T>::init() {
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

#endif