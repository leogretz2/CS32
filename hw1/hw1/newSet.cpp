#include "newSet.h"
#include <algorithm>


Set::Set(int max) {
	if (max < 0)
		exit(1);
	m_size = 0;
	m_max = max;
	m_arr_d = new ItemType[m_max];
}

Set::Set(const Set& other) {
	m_max = other.m_max;
	m_size = other.m_size;
	m_arr_d = new ItemType[m_max];
	for (int i = 0; i < m_size; i++) {
		m_arr_d[i] = other.m_arr_d[i];
	}
}

Set::~Set() {
	delete[] m_arr_d;
}

Set& Set::operator=(const Set& rhs) {
	if (this != &rhs) {
		delete[] m_arr_d;
		m_max = rhs.m_max;
		m_size = rhs.m_size;
		m_arr_d = new ItemType[m_max];
		for (int i = 0; i < m_size; i++) {
			m_arr_d[i] = rhs.m_arr_d[i];
		}
	}
	return *this;
}

bool Set::empty() const {
	if (size() == 0) return true;
	return false;
}

int Set::size() const {
	return m_size;
}

void Set::dump() const {
	for (int i = 0; i < size(); i++) {
		std::cerr << m_arr_d[i] << " ";
	}
	std::cerr << std::endl;
}

bool Set::insert(const ItemType& value) {
	if (contains(value) || m_size == m_max)
		return false;
	m_arr_d[m_size] = value;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value) {
	if (contains(value)) {
		int loc = findVal(m_arr_d, value, m_size);
		for (int i = loc; i < m_size - 1; i++) {
			m_arr_d[i] = m_arr_d[i + 1];
		}
		m_size--;
		return true;
	}
	return false;
}

bool Set::contains(const ItemType& value) const {
	int loc = findVal(m_arr_d, value, m_size);
	if (loc >= 0 && loc < m_size) {
		return true;
	}
	return false;
}

int Set::findVal(const ItemType* a, ItemType val, int n) const {
	for (int i = 0; i < n; i++) {
		if (a[i] == val)
			return i;
	}
	return -1;
}

bool Set::get(int i, ItemType& value) const {
	if (0 <= i && i < size()) {
		int j = 0, count;
		for (j = 0; j < m_size; j++) {
			count = 0;
			for (int k = 0; k < m_size; k++) {
				if (k != j && m_arr_d[j] > m_arr_d[k])
					count++;
			}
			if (count == i)
				break;
		}
		value = m_arr_d[j];
		return true;
	}
	return false;
}

void Set::swap(Set& other) {
	/*int s = std::max(m_size, other.m_size);
	for (int i = 0; i < s; i++) {
		ItemType temp = m_arr_d[i];
		m_arr_d[i] = other.m_arr_d[i];
		other.m_arr_d[i] = temp;
	}
	int temp_s = m_size;
	m_size = other.m_size;
	other.m_size = temp_s;

	int temp_m = m_max;
	m_max = other.m_max;
	other.m_max = temp_m;*/
	Set temp(other);
	other = *this;
	*this = temp;
}