#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "MIPSInstruction.h"
#include "Buffer2.h"
#include "Mux2.h"

class ControlUnit {

public:

	ControlUnit() : receivedInfo(0) {}

    void set(MIPSInstruction::InstructionName);

	void execute();

	void setBuffer2(Buffer2* b2) {
		buffer2 = b2;
	}

	void setTAOrDAMux(Mux2* m2) {
		taOrDaMux = m2;
	}

private:

	MIPSInstruction::InstructionName instructionName;

	Buffer2* buffer2;

	Mux2* taOrDaMux;

	int receivedInfo;
};
#endif
