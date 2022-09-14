template <class T>
TList<T>::TList() {
	// blank list has no content
	first = last = nullptr;
	size = 0;
}

template <class T>
TList<T>::TList(T val, int num) {
	// create first node, then for loop the rest of the nodes
	Node<T>* node = new Node(val);
	first = last = node;
	for (int i = 0; i < num - 1; i++) {
		InsertBack(val);
	}
}
 
template <class T>
TList<T>::~TList() {
	// create iterator, step through nodes and delete prev

}

template <class T>
void TList<T>::InsertFront(const T& d) {
	// create node to insert
	Node<T>* node = new Node(d);

	// set prev, next for new first node
	node->prev = nullptr;
	node->next = first;

	// set prev for old first node
	first->prev = node;

	// set first to new first node
	first = node;
	size++;
}

template <class T>
void TList<T>::InsertBack(const T& d) {
	// create node to insert
	Node<T>* node = new Node(d);
	
	// set prev, next for new last node
	node->prev = last;
	node->next = nullptr;

	// set next for old last node
	last->next = node;

	// set last to new last node
	last = node;
	size++;
}

template <class T>
void TList<T>::RemoveFront() {
	// set node to first node
	Node<T>* node = first;

	// set prev for new first node, assign it to first node
	node->next->prev = nullptr;
	first = node->next;

	// delete old first node
	delete node;
	size--;
}

template <class T>
void TList<T>::RemoveBack() {
	// set node to last node
	Node<T>* node = last;

	// set next for new last node, assign it to last node
	node->prev->next = nullptr;
	last = node->prev;

	// delete old last node
	delete node;
	size--;
}

template <class T>
void TList<T>::Clear() {

}

template <class T>
int TList<T>::GetSize() const {	return size; }

// returns data from first node
template <class T>
T& TList<T>::GetFirst() const {
	if (size == 0) { return dummy; }
	else { return first->data; }
}	

// returns data from last node
template <class T>
T& TList<T>::GetLast() const {
	if (size == 0) { return dummy; }
	else { return last->data; }
}	

template <class T>
TListIterator<T> TList<T>::GetIterator() const {
	TListIterator<T> itr = new TListIterator();
	itr->ptr = first;
	return itr;
}

template <class T>
TListIterator<T> TList<T>::GetIteratorEnd() const {
	TListIterator<T> itr = new TListITerator();
	itr->ptr = last;
	return itr;
}

// TListIterator definitions below
template <class T>
TListIterator<T>::TListIterator() {	ptr = nullptr; }

// returns true if next node exists
template <class T>
bool TListIterator<T>::HasNext() const {
	if (ptr->next != nullptr) {	return true; }
	else { return false; }
}

// returns true if prev node exists
template <class T>
bool TListIterator<T>::HasPrevious() const {
	if (ptr->prev != nullptr) {	return true; }
	else { return false; }
}

// returns iterator to next node
template <class T>
TListIterator TListIterator<T>::Next() {
	TListIterator<T> itr = ptr->next;
	return itr;
}

// returns iterator to previous node
template <class T>
TListIterator TListIterator<T>::Previous() {
	TListIterator<T> itr = ptr->prev;
	return itr;
}

// returns data of current node
template <class T>
T& TListIterator<T>::GetData() const { 
	if (ptr != nullptr) { return ptr->data; }
	else { return dummy; }
}