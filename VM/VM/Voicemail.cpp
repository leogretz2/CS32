#include "Voicemail.h"
#include <iostream>

using namespace std;

Voicemail::Voicemail(int num) {
	numVMs = num;
}

void Voicemail::say() {
	cout << "Sup bitch. " << numVMs << endl;
}