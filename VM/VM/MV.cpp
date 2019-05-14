#include "Voicemail.h"
#include "MV.h"

MV::MV(int mv) {
	m_mv = mv;
}

void MV::action(Voicemail* vm) {
	vm->say();
}

