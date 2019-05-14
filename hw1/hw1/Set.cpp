#include "Set.h"
#include <algorithm>

Set::Set() {
	m_size = 0;
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
		std::cerr << m_arr[i] << " ";
	}
	std::cerr << std::endl;
}

bool Set::insert(const ItemType& value) {
	if (contains(value) || m_size == DEFAULT_MAX_ITEMS)
		return false;
	m_arr[m_size] = value;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value) {
	if (contains(value)) {
		int loc = findVal(m_arr, value, m_size);
		for (int i = loc; i < m_size - 1; i++) {
			m_arr[i] = m_arr[i + 1];
		}
		m_size--;
		return true;
	}
	return false;
}

bool Set::contains(const ItemType& value) const {
	int loc = findVal(m_arr, value, m_size);
	if (loc >= 0 && loc < m_size) {
		return true;
	}
	return false;
}

int Set::findVal(const ItemType a[], ItemType val, int n) const {
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
				if (k != j && m_arr[j] > m_arr[k])
					count++;
			}
			if (count == i)
				break;
		}
		value = m_arr[j];
		return true;
	}
	return false;
}

void Set::swap(Set& other) {
	int s = std::max(m_size, other.m_size);
	for (int i = 0; i < s; i++) {
		ItemType temp = m_arr[i];
		m_arr[i] = other.m_arr[i];
		other.m_arr[i] = temp;
	}
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;
}
