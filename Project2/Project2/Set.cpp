#include "Set.h"

// Set constructor, creates an empty set
Set::Set() {
	m_size = 0;
	head = &dummy;
	tail = &dummy;
	dummy.next = &dummy;
	dummy.prev = &dummy;
}

// Set copy constructor, creates another set identical to an existing set
Set::Set(const Set& other) {
	m_size = 0;
	head = &dummy;
	tail = &dummy;					// head and tail both point the dummy node
	dummy.next = &dummy;
	dummy.prev = &dummy;
	Node* p = other.dummy.next;
	for (int i = 0; i < other.m_size && p != &other.dummy; i++, p=p->next) {
		insert(p->data);			// inserts every node from the other set into the new one
	}
}

// Set destructor: deletes all the nodes of a set to avoid memory leaks
Set::~Set() {
	Node* p = tail;				// Starts with the tail
	for (; p != head;) {
		p = p->prev;
		delete p->next;			// Loops through backwards and deletes every node until it hits the dummy node
	}
}

// Set assignment operator: makes one set equal to another specified set
Set& Set::operator=(const Set& rhs) {
	if (this != &rhs) {
		Node* p = tail;			// Starts with the tail
		for (; p != &dummy;) {	
			p = p->prev;
			delete p->next;		// Loops through backwards and deletes every node until it hits the dummy node
		}
		m_size = 0;	
		head = &dummy;			
		tail = &dummy;			// head and tail point to the dummy node
		dummy.next = &dummy;
		dummy.prev = &dummy;
		Node* p2 = rhs.dummy.next;	// Points to the first interesting node of the other set
		for (int i = 0; i < rhs.m_size && p2 != &rhs.dummy; i++, p2 = p2->next) {
			insert(p2->data);	// inserts every node from the other set into the new one
		}
	}
	return *this;				// returns a pointer to the new set
}

// Tests if the set is empty or not
bool Set::empty() const {
	if (size() == 0) return true;
	return false;
}

// Returns the size of the set
int Set::size() const {
	return m_size;
}

// Prints out data of every node of the set
void Set::dump() const {
	Node* p;
	int i;
	for (p = head->next, i = 0; p != &dummy && i < size(); p = p->next, i++) {
		std::cerr << p->data << " ";
	}
	std::cerr << std::endl;
}

// Inserts a new value (as part of a node) into the set if it isn't already in the set
bool Set::insert(const ItemType& value) {
	if (contains(value))		// Checks if it contains the value
		return false;
	//Node* loc = findLeastPos(value);
	Node* newOne = new Node;	// Dynamically allocates the new node
	newOne->data = value;		// Assign value to the data of the new node
	newOne->next = &dummy;
	newOne->prev = tail;
	dummy.prev = newOne;
	tail->next = newOne;		// Adjust the set so the new node is on the end and points to the dummy and dummy points back
	/*newOne->next = loc;
	newOne->prev = loc->prev;
	loc->prev->next = newOne;
	loc->prev = newOne;*/
	m_size++;					
	tail = tail->next;			// Adjust the tail to the end
	return true;
}

bool Set::erase(const ItemType& value) {
	Node* loc;
	for (loc = dummy.next; loc != &dummy; loc = loc->next) {	// Loop through the set
		if (loc->data == value)
			break;					// If value exists in the set break the loop, otherwise go to the end
	}
	//Node* loc = findLeastPos(value);
	if (loc == &dummy || loc->data != value)	// If loc is not the value, means value is not in set, return false
		return false;
	loc->prev->next = loc->next;
	loc->next->prev = loc->prev;				// Adjust to remove node from the set
	m_size--;
	if(loc == tail)					// If the value removed is on the end move the tail back, if not tail remains
		tail = tail->prev;
	delete loc;						// Delete the erased node
	return true;
}

// Checks to see if the set contains a value
bool Set::contains(const ItemType& value) const {
	if(findVal(dummy.next, value))
		return true;
	return false;
}

// Loops through the set and returns true if value is contained in the set
bool Set::findVal(Node* a, ItemType val) const {
	int i;
	Node* p;
	for (p = a, i = 0; p != &dummy && i < size(); p = p->next, i++) {
		if (p->data == val)
			return true;
	}
	return false;
}

// Finds the position after where the node should be added in order to keep the set sorted
//Set::Node* Set::findLeastPos(const ItemType& value) const
//{
//	Node* begin = dummy.next;
//	Node* end = tail;
//	while (begin < end)
//	{
//		Node* mid = ((begin - end) / 2) + begin;
//		if (value < mid->data)
//			end = mid;
//		else if (mid->data < value)
//			begin = mid + 1;
//		else
//			return mid;
//	}
//	return begin;
//}

// Assigns the value strictly greater than i values in the set to value, returns true if does, returns false if fails to
bool Set::get(int i, ItemType& value) const {
	/*Node* p = dummy.next;
	if (i < 0 || i > size())
		return false;
	value = (p + i)->data;
	return true;*/

	if (0 <= i && i < size()) {
		int j, k, count;
		Node* p1;
		Node* p2;
		for (p1 = dummy.next, j = 0; p1 != &dummy && j < m_size; p1 = p1->next, j++) {		// Loops through entire set
			count = 0;
			for (p2 = dummy.next, k = 0; p2 != &dummy && k < m_size; p2 = p2->next, k++) {	// Loops through entire set
				if (k != j && p1->data > p2->data)			// If an item in the set is less than the current one from the first loop add to count
					count++;
			}
			if (count == i)		// If the number of items in the set less than the specified node is equal to i, break
				break;
		}
		value = p1->data;		// Assign the correct value to value and return true
		return true;
	}
	return false;
}


// Swaps two sets
void Set::swap(Set& other) {
	//Node* temp = head;
	//Node* temp_n = dummy.next;
	//Node* temp_p = dummy.prev;
	//Node* temp_n_2 = tail->next;
	//Node* temp_p_2 = tail->prev;
	//head = other.head;
	//dummy.next = other.dummy.next;
	//dummy.prev = other.dummy.prev;
	//other.head = temp;
	//other.dummy.next = temp_n;
	//other.dummy.prev = temp_p; // swap dummy nodes

	//Node* temp_2 = tail;
	//tail = other.tail;
	//tail->next = other.tail->next;
	//tail->prev = other.tail->prev;
	//other.tail = temp_2;
	//other.tail->next = temp_n_2;
	//other.tail->prev = temp_p_2;	//swap tails

	Node* temp = head;
	head = other.head;
	other.head = temp;

	Node* temp_2 = tail;
	tail = other.tail;
	other.tail = temp_2;

	int temp_s = m_size;
	m_size = other.m_size;
	other.m_size = temp_s;	//swap sizes
}

// Constructor for a node object, next and previous point to nothing
Set::Node::Node() {
	next = nullptr;
	prev = nullptr;
}

// Unites sets s1 and s2 by including any values s1 doesn't have, that s2 has, in s1
void unite(const Set& s1, const Set& s2, Set& result) {
	result = s1;		// Assign s1 to result to erase any existing nodes in result and set up
	for (int i = 0; i < s2.size(); i++) {
		ItemType temp;
		s2.get(i, temp);
		result.insert(temp);		// Insert any values that result doesn't have, that s2 does, into result.
	}
}

// Subtracts set s2 from s1 by excluding any values that s1 and s2 have in common
void subtract(const Set& s1, const Set& s2, Set& result) {
	result = s1;		// Assign s1 to result to erase any existing nodes in result and set up
	for (int i = 0; i < s2.size(); i++) {
		ItemType temp;
		s2.get(i, temp);
		result.erase(temp);	// Erase any common values between result and s2
	}
}


