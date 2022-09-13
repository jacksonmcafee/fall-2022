template <class T>
TList<T>::TList() {
	// create head/tail node
	Node<T>* current = new Node(0);

	// assign default values
	first = last = current;
	size = 0;
}

/* ! check in post if size is accurate to # of nodes in list ! */
template <class T>
TList<T>::TList(T val, int num) {
	// create first node, d = val
	Node<T>* current = new Node(val);
	
	// set current node to head, point prev to nullptr
	first = current;
	first->prev = nullptr;

	// increment size
	size++;

	// loop to create num - 1 new nodes and connect w/ node
	for (int i = 0; i < num - 1; i++) {
		// create new node, d = val
		Node<T>* node = new Node(val); 
		
		// point current->next to new node, node->prev to current
		current->next = node;
		node->prev = current;

		// increment size
		size++;

		// set current to node, loop
		current = node;
	}

	// set current node to tail, point next to nullptr
	last = current;
	last->next = nullptr;
}

/* !  check later by saving tail memory loc! */
template <class T>	
TList<T>::~TList() {
	// create iterator node, step through list until next->nullptr
	Node<T>* current = new Node(0);
	current = first;
	
	while(current->next != nullptr) {
		// delete last node after stepping to next
		delete current->prev;
		current = current->next;
	}

	// delete iterator node
	delete current;

	// clear first/last ptrs
	first = last = nullptr;
	size = 0;
}

/* on god this might not work, could be razing all of L.List */
// copy constructor, deep copy
template <class T>	
TList<T>::TList(const TList& L) {
	// create first node, d = L.head->data
	Node<T>* current = new Node(L.head->data);

	// create iterator node on L, set it to L.head
	Node<T>* L_iterator = new Node(0);
	L_iterator = L.first;
	
	// set head to current node, head->prev to nullptr
	first = current;
	first->prev = nullptr;

	// copy L.size over
	size = L.size;

	// create size # of deep copies
	// size doesn't get incremented because it's already L.size
	for (int i = 0; i < size; i++) {
		// create new node, d = L.iterator->data
		Node<T> node = new Node(L.iterator->data);
		current->next = *node;
		node->prev = *current;

		// move L.iterator to next node in L
		L_iterator = L_iterator->next;

		// move current to node
		current = node;
	}

	// delete iterator node
	delete L_iterator;

	// assign vals to last
	last = *current;
	last->next = nullptr;
}

/* currently a hard copy of above, refactor later please... */
template <class T>
TList<T>& TList<T>::operator=(const TList& L) {
	// create first node, d = L.head->data
	Node<T>* current = new Node(L.head->data);

	// create iterator node on L, set it to L.head
	Node<T>* L_iterator = new Node(0);
	L_iterator = L.first;
	
	// set head to current node, head->prev to nullptr
	first = *current;
	first->prev = nullptr;

	// copy L.size over
	size = L.size;

	// create size # of deep copies
	// size doesn't get incremented because it's already L.size
	for (int i = 0; i < size; i++) {
		// create new node, d = L.iterator->data
		Node<T>* node = new Node(L.iterator->data);
		current->next = *node;
		node->prev = *current;

		// move L.iterator to next node in L
		L_iterator = L_iterator->next;

		// move current to node
		current = node;
	}

	// delete iterator node
	delete L_iterator;

	// assign vals to last
	last = *current;
	last->next = nullptr;
}

// BOTH UNFINISHED

// move constructor, soft copy
template <class T>
TList<T>::TList(TList && L) {
	// do something
	std::cout << "do something" << std::endl;
}

// move operator, soft copy, can just point head to L
template <class T>	
TList<T>& TList<T>::operator=(TList && L)  {
	// do something
	std::cout << "do something" << std::endl;
	return *this;
}

// THESE MIGHT WORK!!

template <class T>	
bool TList<T>::IsEmpty() const { return (size == 0 ? true : false); }

/* might not work lol !!! */
template <class T>	
void TList<T>::Clear() {
// create iterator node, step through list until next->nullptr
	Node<T>* current = new Node(0);
	current = first;
	
	while(current->next != nullptr) {
		// delete last node after stepping to next
		delete current->prev;
		current = current->next;
	}

	// delete iterator node
	delete current;

	// clear first/last ptrs
	first = last = nullptr;
	size = 0;
}

template <class T>
int TList<T>::GetSize() const { return size; }

// ALL UNTOUCHED BELOW THIS LINE 

template <class T>
void TList<T>::InsertFront(const T& d) {
	std::cout << "do something" << std::endl;
}

template <class T>
void TList<T>::InsertBack(const T& d) {
	std::cout << "do something" << std::endl;
}

template <class T>
void TList<T>::RemoveFront() {
	std::cout << "do something" << std::endl;
}

template <class T>
void TList<T>::RemoveBack() {
	std::cout << "do something" << std::endl;
}

template <class T>
T& TList<T>::GetFirst() const {
	std::cout << "do something" << std::endl;
	T temp;
	return temp;
}

template <class T>
T& TList<T>::GetLast() const {
	std::cout << "do something" << std::endl;
	T temp;
	return temp;
}
