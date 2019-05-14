#include "SSNSet.h"

SSNSet::SSNSet() {
	m_SSNsize = s.size();
}

bool SSNSet::add(ItemType ssn) {
	return(s.insert(ssn));
}

int SSNSet::size() const {
	return s.size();
}

void SSNSet::print() const {
	for (int i = 0; i < size(); i++) {
		ItemType curr = 0;
		s.get(i, curr);
		std::cout << curr << std::endl;
	}
}
