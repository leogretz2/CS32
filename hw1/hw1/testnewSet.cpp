#include "newSet.h"
#include <iostream>
#include <cassert>

int main() {
	Set a(10);   // a can hold at most 10 distinct items
	Set b(5);      // b can hold at most 5 distinct items
	Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
	ItemType v[6] = { "bleh", "blah", "bluh", "blgh", "blesdafh" , "blyh" };
	for (int k = 0; k < 5; k++)
		assert(b.insert(v[k]));
	assert(!b.insert(v[5]));
	b.dump();

	a.swap(b);
	assert(!a.insert(v[5]) && b.insert(v[5]));
	a.dump();
	b.dump();
	std::cout << a.size() << " " << b.size() << std::endl;

	std::cout << "passed" << std::endl;
}