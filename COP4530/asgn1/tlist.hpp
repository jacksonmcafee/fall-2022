template <typename T>
TList<T>::TList() {
	// blank list has no content
	first = last = nullptr;
	size = 0;
}

template <typename T>
TList<T>::TList(T val, int num) {
	// loop all of num nodes, append node(val)
	for (int i = 0; i < num; i++) { InsertBack(val); }
}
 
template <typename T>
TList<T>::~TList() {
	if (size > 0) {
		// create iterator on list
		TListIterator<T> itr;
		itr.ptr = first;

		// move to next ptr, delete previous ptr, rinse & repeat 
		while(itr.HasNext()) {
			itr.Next();
			delete itr.ptr->prev;
		}
		delete itr.ptr;
	}
	/* 	I wasted 4 hours of my life trying to figure out why
	my move operator was segfaulting. It was because I stupidly
	tried to "delete this" at the end of my destructor... */ 
}

template <typename T>
TList<T>::TList(const TList& L) {
	// set default vals
	first = last = nullptr;
	size = 0;

	// create iterator on list passed list L
	TListIterator<T> itr = L.GetIterator();

	for (int i = 0; i < L.GetSize(); i++) {
		// insert itr.ptr->data for each, swap to next
		InsertBack(itr.GetData());
		itr.Next();
	}
}

// copy constructor, deep copy
template <typename T>
TList<T>& TList<T>::operator=(const TList& L) {
	// empty this before copy
	Clear();

	// create iterator on list L
	TListIterator<T> itr = L.GetIterator();

	for (int i = 0; i < L.GetSize(); i++) {
		// insert back b/c Front would reverse list
		InsertBack(itr.GetData());
		itr.Next();
	}

	return *this;
}

// move constructor
template <typename T>
TList<T>::TList(TList && L) {
	// assign vals over
	size = L.size;

	// because L.first and L.last are linked already, we can just write them over
	first = L.first;
	last = L.last;
}

// move operator
template <typename T>
TList<T>& TList<T>::operator=(TList && L) {
	// create temp swap node to use for head/tail swap
    // swap first w/ L.first, L.first w/ swap node
    Node<T>* s_node = first;
    first = L.first; 
    L.first = s_node;
    
    // swap last w/ L.last, L.last w/ swap node
    s_node = last;
    last = L.last;
    L.last = s_node;

    // create temp int to use for size swap
    int temp = size;
    size = L.size;
    L.size = temp;

    return *this;
}

template <typename T>
void TList<T>::InsertFront(const T& d) {
	// create node to insert
	Node<T>* node = new Node<T>(d);

	// check if list is empty
	if (IsEmpty()) { first = last = node; }
	else {
		// set prev for new first node
		node->prev = nullptr;
		
		// set prev for old first node
		first->prev = node;
		
		// set next for new first node
		node->next = first;

		// set first to new first node
		first = node;
	}
	size++;
}

template <typename T>
void TList<T>::InsertBack(const T& d) {
	// create node to insert
	Node<T>* node = new Node<T>(d);
	
	// check if list is empty
	if (IsEmpty()) { first = last = node; }
	else {
		// set prev for new last node
		node->prev = last;
		
		// set next for old last node
		last->next = node;
		
		// set next for new last node
		node->next = nullptr;

		// set last to new last node
		last = node;
	}
	size++;
}

template <typename T>
void TList<T>::RemoveFront() {
	// if empty list, return
	if (size == 0) { ; }
	// if only head node, just delete first and set empty vals
	else if (size == 1) {
		delete first;
		first = last = nullptr;
		size = 0;
	}
	else {
	// set node to first node
	Node<T>* node = first->next;
	node->prev = nullptr;

	// delete first
	delete first;

	// assign first to node
	first = node;

	// decrement size
	size--;
	}
}

template <typename T>
void TList<T>::RemoveBack() {
	// if empty list, return
	if (size == 0) { ; }
	// if only tail node, just delete last and set empty vals
	else if (size == 1) {
		delete last;
		first = last = nullptr;
		size = 0;
	}
	else {
	// set node to last node
	Node<T>* node = last->prev;
	node->next = nullptr;

	// delete first
	delete last;

	// assign first to node
	last = node;

	// decrement size
	size--;
	}
}

template <typename T>
// checks if list is empty
bool TList<T>::IsEmpty() const { return size == 0; }

// just don't delete *this
template <typename T>
void TList<T>::Clear() {
	while (size != 0) {
		RemoveBack();
	}
	// default values
	first = last = nullptr;
}

template <typename T>
// size getter
int TList<T>::GetSize() const {	return size; }

template <typename T>
// returns data from first node
T& TList<T>::GetFirst() const {
	// if there's nothing to get, return dummy
	if (size == 0) { return dummy; }
	// else return data
	else { return first->data; }
}	

// returns data from last node
template <typename T>
T& TList<T>::GetLast() const {
	// if there's nothing to get, return dummy
	if (size == 0) { return dummy; }
	// else return data
	else { return last->data; }
}	

template <typename T>
// gets iterator to first node
TListIterator<T> TList<T>::GetIterator() const {
	// create iterator, asgn ptr to first
	TListIterator<T> itr;
	itr.ptr = first;
	return itr;
}

template <typename T>
// gets iterator to last node
TListIterator<T> TList<T>::GetIteratorEnd() const {
	// create iterator, asgn ptr to last
	TListIterator<T> itr;
	// should honestly have an alternate constructor for this 
	itr.ptr = last;
	return itr;
}


template <typename T>
// inserts node at position pos-1
void TList<T>::Insert(TListIterator<T> pos, const T& d) {
    // create node for prev and pos
    Node<T>* insert = new Node<T>(d);
	Node<T>* node = nullptr;

	// if prev exists, node can be prev
    if(pos.HasPrevious() == true) { node = pos.ptr->prev; }

    // swap
    insert->next = pos.ptr;
    pos.ptr->prev = insert;

    // if node is still null, inserted node is now first
    if (node == nullptr) { first = insert; }
    else {
        node->next = insert;
        insert->prev = node;
    }
    size++;
}

template <typename T>
// removes node as position pos
TListIterator<T> TList<T>::Remove(TListIterator<T> pos) {
    // if empty list OR passed node is null, do nothing & return
    if (first == nullptr || pos.ptr == nullptr) { return pos; }

    // if ptr is the ptr, set first to first+1
    if (first == pos.ptr) { first = pos.ptr->next; }

    // as long as ptr->next isn't null, asgn node+1->prev to node->prev
    if (pos.ptr->next != nullptr) { pos.ptr->next->prev = pos.ptr->prev; }

    // as long as ptr->prev isn't null, asgn node+1->next to node->next
    if (pos.ptr->prev != nullptr) { pos.ptr->prev->next = pos.ptr->next; }

    // delete ptr, decrement size, return pos w/ nullptr
    delete pos.ptr;
    size--;
    return pos;
}

template <typename T>
// prints TList
void TList<T>::Print(std::ostream& os, char delim) const{
	TListIterator<T> itr = GetIterator();
	// iterate on TList, append data + delim to os, shift to next
	for (int i = 0; i < size; i++) {  
		os << itr.GetData() << delim;
		itr.Next();
	}
}

/* TListIterator definitions below */

template <typename T>
// default constructor, asgn to nullptr
TListIterator<T>::TListIterator() { ptr = nullptr; }

template <typename T>
// returns true if next node exists
bool TListIterator<T>::HasNext() const {
	if (ptr->next != nullptr) {	return true; }
	else { return false; }
}

template <typename T>
// returns true if prev node exists
bool TListIterator<T>::HasPrevious() const {
	if (ptr->prev != nullptr) {	return true; }
	else { return false; }
}

template <typename T>
// returns iterator to next node
TListIterator<T> TListIterator<T>::Next() {
	if (HasNext() == true) { ptr = ptr->next; }
	return *this;
}

template <typename T>
// returns iterator to previous node
TListIterator<T> TListIterator<T>::Previous() {
	if (HasPrevious() == true) { ptr = ptr->prev; }
	return *this;
}

template <typename T>
// returns data of current node
T& TListIterator<T>::GetData() const { return ptr->data; }