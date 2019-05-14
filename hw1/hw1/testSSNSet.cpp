#include <iostream>
#include <cassert>
#include "SSNSet.h"
using namespace std;

int main() {
	SSNSet s; 
	assert(s.size() == 0);
	s.add(24653784);
	s.add(83566754);
	s.add(24653784);
	s.add(43533784);
	assert(s.size() == 3);
	s.print();
	cout << "Passed all tests" << endl;
}