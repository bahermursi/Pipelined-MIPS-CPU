#ifndef FORWARDING_UNIT_H
#define FORWARDING_UNIT_H

#include "MIPSInstruction.h"
#include "Mux3.h"
#include "Mux2.h"

class Buffer3;
class ForwardingUnit {

public:

	void setCurrentInstruction(MIPSInstruction mipsInstruction) {
		currentInstruction = mipsInstruction;
	}

	void setPreviousInstruction(MIPSInstruction mipsInstruction) {
		previousInstruction = mipsInstruction;
	}

	void setPreviousPreviousInstruction(MIPSInstruction mipsInstruction) {
		previousPreviousInstruction = mipsInstruction;
	}

	void execute();

	void setMux3_0(Mux3* m3) {
		mux3_0 = m3;
	}

	void setMux3_1(Mux3* m3) {
		mux3_1 = m3;
	}

	void setMux3_2(Mux3* m3) {
		mux3_2 = m3;
	}

	void setBuffer3(Buffer3*);

	void setPreviousRegWrite(int rw) {
		previousRegWrite = rw;
	}

	void setPreviousPreviousRegWrite(int rw) {
		previousPreviousRegWrite = rw;
	}

	void setMux2_8(Mux2* m2) {
		mux2_8 = m2;
	}

	void setMux2_9(Mux2* m2) {
		mux2_9 = m2;
	}

private:

	MIPSInstruction currentInstruction, previousInstruction, previousPreviousInstruction;

	int previousRegWrite, previousPreviousRegWrite;

	Mux3* mux3_0;
	
	Mux3* mux3_1;

	Buffer3* buffer3;

	Mux3* mux3_2;

	Mux2* mux2_8;

	Mux2* mux2_9;
};

#endif