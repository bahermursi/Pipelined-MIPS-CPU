#ifndef BUFFER_4_H
#define BUFFER_4_H

#include "Mux2.h"
#include "RegFile.h"
#include "Mux3.h"
#include "MIPSInstruction.h"
#include "ForwardingUnit.h"

class Buffer4  {

public:

	Buffer4() : regWrite(0) {}

	void setMemOut(int m) {
		memOut = m;
	}

	void setALUOut(int o) {
		aluOut = o;
	}

	void setTAOrDA(int td) {
		taOrDa = td;
	}

	void setFinalMux(Mux2* m2) {
		finalMux = m2;
	}

	void setRegFile(RegFile* rf) {
		regFile = rf;
	}

	void setTD(int td) {
		tD = td;
	}

	void execute() {
		finalMux->setI0(aluOut);
		finalMux->setI1(memOut);
		finalMux->setS(memToReg);
		source1Mux->setI2(aluOut);
		source2Mux->setI2(aluOut);
		dataMemoryMux->setI1(memOut);
		regFile->setAddress(taOrDa);
		regFile->setRegWrite(regWrite && !dontWrite && !dontWrite2 && !dontWrite3 && !dontWrite4);
		forwardingUnit->setPreviousPreviousInstruction(mipsInstruction);
		forwardingUnit->setPreviousPreviousRegWrite(regWrite && !dontWrite && !dontWrite2 && !dontWrite3 && !dontWrite4);
		mux3_2->setI2(aluOut);
		mux2_8->setI1(memOut);
		mux2_9->setI1(memOut);
	}


	void setSource1Mux(Mux3* m3) {
		source1Mux = m3;
	}

	void setSource2Mux(Mux3* m3) {
		source2Mux = m3;
	}

	void setDataMemoryMux(Mux2* m2) {
		dataMemoryMux = m2;
	}

	void setMIPSInstruction(const MIPSInstruction& instr) {
		mipsInstruction = instr;
	}

	void setForwardingUnit(ForwardingUnit* fu) {
		forwardingUnit = fu;
	}

	void setRegWrite(int rw) {
		regWrite = rw;
	}

	void setMux3_2(Mux3* m3) {
		mux3_2 = m3;
	}

	void setMemToReg(int m) {
		memToReg = m;
	}

	void setDontWrite(int dw) {
		dontWrite = dw;
	}

	void setMux2_8(Mux2* m2) {
		mux2_8 = m2;
	}

	void setMux2_9(Mux2* m2) {
		mux2_9 = m2;
	}

	void setDontWrite2(int dw) {
		dontWrite2 = dw;
	}

	void setDontWrite3(int dw) {
		dontWrite3 = dw;
	}

	void setDontWrite4(int dw) {
		dontWrite4 = dw;
	}

private:

	MIPSInstruction mipsInstruction;

	int memOut, aluOut, taOrDa, memToReg;

	int regWrite;

	int tD;

	int dontWrite, dontWrite2, dontWrite3, dontWrite4;

	Mux2* finalMux;

	RegFile* regFile;

	Mux3* source1Mux;

	Mux3* source2Mux;

	Mux2* dataMemoryMux;

	ForwardingUnit* forwardingUnit;

	Mux3* mux3_2;

	Mux2* mux2_8;

	Mux2* mux2_9;
};

#endif