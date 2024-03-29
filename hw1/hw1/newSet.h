#ifndef NEWSET_H
#define NEWSET_H

#include <string>
#include <iostream>

//using ItemType = unsigned long;
using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:

	Set(int max = DEFAULT_MAX_ITEMS);         // Create an empty set (i.e., one with no items).

	Set(const Set& other);

	~Set();

	Set& operator=(const Set& rhs);

	bool empty() const;  // Return true if the set is empty, otherwise false.

	int size() const;    // Return the number of items in the set.

	void dump() const;

	bool insert(const ItemType& value);
	// Insert value into the set if it is not already present.  Return
	// true if the value was actually inserted.  Leave the set unchanged
	// and return false if the value was not inserted (perhaps because it
	// was already in the set or because the set has a fixed capacity and
	// is full).

	bool erase(const ItemType& value);
	// Remove the value from the set if present.  Return true if the
	// value was removed; otherwise, leave the set unchanged and
	// return false.

	bool contains(const ItemType& value) const;
	// Return true if the value is in the set, otherwise false.

	bool get(int i, ItemType& value) const;
	// If 0 <= i < size(), copy into value the item in the set that is
	// strictly greater than exactly i items in the set and return true.
	// Otherwise, leave value unchanged and return false.

	void swap(Set& other);
	// Exchange the contents of this set with the other one.
private:

	//ItemType m_arr[DEFAULT_MAX_ITEMS];
	int m_max;
	int m_size;
	ItemType* m_arr_d;
	int findVal(const ItemType* a, ItemType val, int n) const;

};

#endif