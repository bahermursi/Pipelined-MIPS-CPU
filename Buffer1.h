#ifndef BUFFER_1_H
#define BUFFER_1_H

#include "MIPSInstruction.h"
#include "Buffer2.h"
#include "ControlUnit.h"
#include "Mux2.h"
#include "RegFile.h"
#include "Jump.h"
#include "HazardDetection.h"

class Buffer1 {

public:

	void setMipsInstruction(const MIPSInstruction& instr) {
		mipsInstruction = instr;
	}

	void setPCPlus4(int pc) {
		pcPlus4 = pc;
	}

	void execute() {
		buffer2->setMipsInstruction(mipsInstruction);
		buffer2->setPCPlus4(pcPlus4);
		buffer2->setDontWrite(dontWrite);
		buffer2->setDontWrite3(dontWrite3);
		controlUnit->set(mipsInstruction.getInstructionName());
		taOrDaMux->setI0(mipsInstruction.getTA());
		taOrDaMux->setI1(mipsInstruction.getDA());
		regFile->setSA(mipsInstruction.getSA());
		regFile->setTA(mipsInstruction.getTA());
		jump->setMipsInstruction(mipsInstruction);
		jump->setPCPlus4(pcPlus4);
		if (stop)
			jump->STOP();
		hazardDetection->setCurrentInstruction(mipsInstruction);
	}

	void setBuffer2(Buffer2* b2) {
		buffer2 = b2;
	}

	void setControlUnit(ControlUnit* cu) {
		controlUnit = cu;
	}

	void setTAOrDAMux(Mux2* td) {
		taOrDaMux = td;
	}

	void setRegFile(RegFile* rf) {
		regFile = rf;
	}

	void setDontWrite(int dw) {
		dontWrite = dw;
	}

	void setJump(Jump* j) {
		jump = j;
	}

	void setHazardDetection(HazardDetection* hd) {
		hazardDetection = hd;
	}

	void setDontWrite3(int dw) {
		dontWrite3 = dw;
	}

	void setStop(bool s) {
		stop = s;
	}

private:

	MIPSInstruction mipsInstruction;

	int pcPlus4;

	int dontWrite, dontWrite3;

	bool stop;

	Buffer2* buffer2;

	ControlUnit* controlUnit;

	Mux2* taOrDaMux;

	RegFile* regFile;

	Jump* jump;

	HazardDetection* hazardDetection;
};

#endif
