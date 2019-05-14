#include <iostream>
#include "Voicemail.h"
#include "MV.h"

using namespace std;

int main() {
	Voicemail vm(3);
	vm.say();
	cout << vm.numVMs + 1 << endl;

	Voicemail* vm2 = &vm;
	MV mv(3);
	mv.action(vm2);
	cout << endl << endl;

	int m = 1;
	if (++m == 1)
		cout << m;
	cout << m;
}