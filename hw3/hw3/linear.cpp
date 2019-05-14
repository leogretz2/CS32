#include <iostream>
#include <cassert>

using namespace std;


bool somePredicate(double x) {
	return x < 0;
}

// Return true if the somePredicate function returns true for at
	  // least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
	if (n <= 0)
		return false;
	if (somePredicate(a[n - 1]))
		return true;
	else 
		return anyTrue(a, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
	int count = 0;
	if (n <= 0)
		return 0;
	if (somePredicate(a[n - 1]))
		count++;
	count += countTrue(a, n - 1);
	return count; 
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	int index = 0;
	if (n <= 0)
		return -1;
	if (somePredicate(a[0])) 
		return index;
	index++;
	index += firstTrue(a + 1, n - 1);
	if (index <= 0)
		return -1;
	return index;  // This is incorrect.
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no 
// elements, return -1.
int positionOfMin(const double a[], int n)
{
	int index = 0;
	if (n == 0)
		return -1;
	if (n == 1)
		return index;
	int tempMin = positionOfMin(a, n - 1);
	if (a[tempMin] < a[n - 1])
		return tempMin;
	else
		return n - 1;
	return -1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return false;
	if (n2 == 0 && n1 >= 0)
		return true;
	if (n1 == 0 && n2 != 0)
		return false;
	if (a1[0] == a2[0])
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		return includes(a1 + 1, n1 - 1, a2, n2);

}

//int main() {
//	const double a[] = { 1,2,3,4,5 };
//	const double b[] = { -1,2,3,4,5 };
//	const double c[] = { 1,2,-3,4,5 };
//	const double d[] = { 1,2,3,4,-5 };
//	const double e[] = { 1,-2,3,-4,-5 };
//
//	const double a1[] = { 10, 50, 40, 20, 50, 40, 30 };
//	const double a2[] = { 50, 40, 40, 40 };
//
//	//anyTrue
//	assert(!anyTrue(a, 5));
//	assert(anyTrue(b, 5));
//	assert(anyTrue(c, 5));
//	assert(anyTrue(d, 5));
//	assert(!anyTrue(a, 0));
//
//	//countTrue
//	assert(countTrue(a, 5) == 0);
//	assert(countTrue(b, 5) == 1);
//	assert(countTrue(e, 5) == 3);
//	assert(countTrue(a, 0) == 0);
//
//	//firstTrue
//	assert(firstTrue(a, 5) == -1);
//	assert(firstTrue(b, 5) == 0);
//	assert(firstTrue(c, 5) == 2);
//	assert(firstTrue(d, 5) == 4);
//	assert(firstTrue(e, 5) == 1);
//
//	//positionOfMin
//	assert(positionOfMin(a, 5) == 0);
//	assert(positionOfMin(c, 5) == 2);
//	assert(positionOfMin(e, 5) == 4);
//	assert(positionOfMin(a, 0) == -1);
//
//	//includes
//	assert(includes(a1, 7, a2, 3) == 1);
//	assert(includes(a1, 7, a2, 4) == 0);
//	assert(includes(a1, 7, a2, 0) == 1);
//	assert(includes(a1, 3, a2, 4) == 0);
//	assert(includes(a1, 0, a2, 0) == 1);
//
//	cout << "All Tests Passed (ADFADFGDSGSDFGASDFASDF" << endl;
//}