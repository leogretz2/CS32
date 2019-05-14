#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;

private:
	struct Child;

	// Each Node has a vector of values and children
	struct Node {
		std::vector<ValueType> values;
		std::vector<Child> children;
	};

	// Each child has a label and a pointer to a node
	struct Child {
		Child() { np = nullptr; }
		Child(char lab, Node* node) { label = lab; np = node; }
		char label;
		Node* np;
	};

	Node* rootp;
	void cleanUp(Node* p);
	void insertionHelper(const std::string& key, Node* p, bool endWord, const ValueType& value);
	bool checkExact(Node*& p, const std::string& key) const;
	bool checkInexact(std::vector<Node*>& nodes, Node*& p, const std::string& key, int wrong, bool exists, bool& oneTrue) const;
};

#endif // TRIE_INCLUDED

// Default constructor creates a root node with no children
template<typename ValueType>
Trie<ValueType>::Trie() {
	rootp = new Node;
}

// Destructor destroys all dynamically created Nodes
template<typename ValueType>
Trie<ValueType>::~Trie() {
	cleanUp(rootp);
}

// Reset destroys the current trie and creates a new empty one
template<typename ValueType>
void Trie<ValueType>::reset() {
	~Trie();
	Trie();
}

// Inserts a new Trie node
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
	Node* p = rootp;
	bool endWord = false;

	insertionHelper(key, p, endWord, value);
}

// Recursively inserts a key into the trie
template<typename ValueType>
void Trie<ValueType>::insertionHelper(const std::string& key, Node* p, bool endWord, const ValueType& value) {
	bool endVec = false;
	if (0 == key.size() - 1) endWord = true;
	typename std::vector<Child>::iterator j = p->children.begin();
	if (j == p->children.end()) endVec = true;
	for (; j != p->children.end(); j++) {	// Iterates through the children of each node
		if ((*j).label == key[0]) {			// If the label already exists
			p = (*j).np;					// Moves to the next node
			if (endWord) {
				p->values.push_back(value);	// If reached the end of the key, push the value onto the values vector
				return;
			} else insertionHelper(key.substr(1, key.size() - 1), p, endWord, value);
			break;
		}
		if (j + 1 == p->children.end()) endVec = true;
	}
	if (endVec) {					// If the label doesn't exist yet
		Node* newOne = new Node;			// Make a new Node and a child
		p->children.push_back(Child(key[0], newOne));
		p = newOne;
		if (endWord) {
			p->values.push_back(value);
			return;
		}
		else insertionHelper(key.substr(1, key.size() - 1), p, endWord, value);
	}
}


// Finds a key within the Trie (either exact or a SNiP) and returns a vector of all matches
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
	std::vector<ValueType> allValues;
	if (key.size() == 0) return allValues;
	Node* p = rootp;
	std::vector<Node*> nodes;
	std::string first(1, key[0]);
	int wrong = 0;
	bool exists = false;
	bool oneTrue = false;
	if (exactMatchOnly) {			// If we're looking for an exact match
		if (checkExact(p, key)) allValues = p->values;
	}
	else {							// If we're looking for exact matches and SNiPs
		if (checkExact(p, first) && checkInexact(nodes, p, key.substr(1, key.size() -1), wrong, exists, oneTrue))
			for (int i = 0; i < nodes.size(); i++)
				for (int j = 0; j < nodes[i]->values.size(); j++)
					allValues.push_back(nodes[i]->values[j]);	// Push the values of all the nodes with matches and SNiPs
	}
	return allValues;
}

template<typename ValueType>
bool Trie<ValueType>::checkExact(Node*& p, const std::string& key) const {
	bool endVec = false;
	if (key.size() == 0) return true;
	typename std::vector<Child>::iterator i = p->children.begin();
	if (i == p->children.end()) endVec = true;	// Notes if the children vector is empty
	for (; i != p->children.end(); i++) {		// Iterates through the children vector
		if ((*i).label == key[0]) {				// If label match found, move to the next node
			p = (*i).np;
			return checkExact(p, key.substr(1, key.size() - 1));
		}
		if (i + 1 == p->children.end()) endVec = true;
	}
	return !endVec;
}

template<typename ValueType>
bool Trie<ValueType>::checkInexact(std::vector<Node*>& nodes, Node*& p, const std::string& key, int wrong, bool exists, bool& oneTrue) const {
	if (wrong >= 2) return false;				// If there are two incorrect nodes, there is no match
	if (key.size() == 0) {						// If the key is size 0, we have reached a match with the key, push back to successful nodes
		nodes.push_back(p);
		oneTrue = true;							// There is at least one match, so the function returns true
		return true;
	}
	int tempWrong = wrong;
	typename std::vector<Child>::iterator i = p->children.begin();
	typename std::vector<Child>::iterator end = p->children.end();
	for (; i != end; i++) {
		wrong = tempWrong;						// Reference number of wrong nodes
		p = (*i).np;							// Move to the next node
		if ((*i).label != key[0])				// If the label doesn't match there is an additional wrong value
			wrong++;
		exists = checkInexact(nodes, p, key.substr(1, key.size() - 1), wrong, exists, oneTrue);
	}
	return oneTrue;
}


template<typename ValueType>
void Trie<ValueType>::cleanUp(Node* p) {
	if (p == nullptr)			// If the children vector is empty, then delete the delete the node
		return;
	for (typename std::vector<Child>::iterator i = p->children.begin(); i != p->children.end(); i++) {
		cleanUp((*i).np);			// Loop through remaining children pointers
	}
	delete p;
	//p = nullptr;
}















//Node* p = rootp;
//bool endWord = false;
//bool endVec = false;
//for (int i = 0; i < key.size(); i++) {		// Iterates through the key to be added
//	if (i == key.size() - 1) endWord = true;
//	typename std::vector<Child>::iterator j = p->children.begin();
//	if (j == p->children.end()) endVec = true;
//	for (; j != p->children.end(); j++) {	// Iterates through the children of each node
//		if ((*j).label == key[i]) {			// If the label already exists
//			p = (*j).np;					// Moves to the next node
//			if (endWord) p->values.push_back(value);	// If reached the end of the key, push the value onto the values vector
//			break;
//		}
//		if (j + 1 == p->children.end()) endVec = true;
//	}
//	if (endVec) {					// If the label doesn't exist yet
//		Node* newOne = new Node;			// Make a new Node and a child
//		p->children.push_back(Child(key[i], newOne));
//		p = newOne;
//		if (endWord) p->values.push_back(value);
//	}
//}


//template<typename ValueType>
//bool Trie<ValueType>::checkFirst(Node*& p, const std::string& key) const {
//	bool endVec = false;
//	typename std::vector<Child>::iterator i = p->children.begin();
//	if (i == p->children.end()) endVec = true;
//	for (; i != p->children.end(); i++) {
//		if ((*i).label == key[0]) {
//			p = (*i).np;
//			return true;
//		}
//		if (i + 1 == p->children.end()) endVec = true;
//	}
//	return !endVec;
//}



//template<typename ValueType>
//void Trie<ValueType>::print(Node* p, std::string word) {
//	if (p->children.empty()) {
//		word += (*i).label;
//		cout << word << endl;
//		word = "";
//	}
//	else {
//		for (vector<Child>::iterator i = p->children.begin(); i != p->children.end(); i++) {
//			print((*i).np, word);
//			word += (*i).label;
//		}
//	}
//}



