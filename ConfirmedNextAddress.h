#ifndef CONFIRMED_NEXT_ADDRESS_H
#define CONFIRMED_NEXT_ADDRESS_H

#include "ProgramCounter.h"

class ConfirmedNextAddress {

public:

    ConfirmedNextAddress() : address(0) {}

	void setAddress(int a) {
		address = a;
		set = true;
	}

	void execute() {
		if (set) {
			programCounter->setPC(address);
			set = false;
		}
	}

	void setProgramCounter(ProgramCounter* pc) {
		programCounter = pc;
	}

private:

	bool set;

	int address;

	ProgramCounter* programCounter;
};

#endif
