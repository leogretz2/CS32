#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	Set s;
	s.insert("yo");
	s.insert("jo");
	assert(!s.insert("yo"));
	assert(!s.erase("po"));
	s.dump();
	s.erase("yo");
	s.erase("jo");
	assert(s.empty());
	ItemType x = "arepa";
	assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
	/*s.insert("chapati");
	assert(s.size() == 1);
	assert(s.get(0, x) && x == "chapati");*/
	s.insert("y");
	s.insert("d");
	s.insert("c");
	s.insert("e");
	s.insert("b");
	/*s.insert("g");
	s.insert("q");*/
	s.insert("c");
	s.insert("p");
	s.get(0, x);
	assert(x == "b");
	Set s2; 
	s2.insert("a");
	s2.insert("b");
	s2.insert("c");
	s2.insert("d");
	s2.insert("e");
	s2.insert("f");
	s2.insert("g");
	s2.insert("h");
	//s2.dump();
	Set s3;
	s.swap(s2);
	s.dump();
	s2.dump();
	s.swap(s3);
	s.dump();
	s3.dump();
	cout << "Passed all tests" << endl;
}