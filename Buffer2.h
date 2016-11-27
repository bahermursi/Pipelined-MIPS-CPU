#ifndef BUFFER_2_H
#define BUFFER_2_H

#include "MIPSInstruction.h"
#include "Buffer3.h"
#include "Mux2.h"
#include "Mux3.h"
#include "ForwardingUnit.h"
#include "ALU.h"
#include "HazardDetection.h"
#include "BranchPrediction.h"

class Buffer2 {

public:

	Buffer2() : branch(0), memWrite(0), regWrite(0) {}

	void setMipsInstruction(const MIPSInstruction& instr) {
		mipsInstruction = instr;
	}

	void setPCPlus4(int pc) {
		pcPlus4 = pc;
	}

	void setSD(int s) {
		sD = s;
	}

	void setTD(int t) {
		tD = t;
	}

	void setTaOrDa(int td) {
		taOrDa = td;
	}

	void setBranch(int b) {
		branch = b;
	}

	void setMemWrite(int w) {
		memWrite = w;
	}

	void setMemToReg(int r) {
		memToReg = r;
	}

	void setAluSrc(int s) {
		aluSrc = s;
	}

	void setRegWrite(int w) {
		regWrite = w;
	}

	void execute() {
		buffer3->setMipsInstruction(mipsInstruction);
		buffer3->setTaOrDa(taOrDa);
		buffer3->setMemToReg(memToReg);
		buffer3->setMemWrite(memWrite);
		buffer3->setRegWrite(regWrite);
		buffer3->setDontWrite(dontWrite);
		buffer3->setDontWrite2(dontWrite2);
		buffer3->setDontWrite3(dontWrite3);
		buffer3->setDontWrite4(dontWrite4);
		tdOrImmMux->setI0(tD);
		tdOrImmMux->setI1(mipsInstruction.getImm());
		tdOrImmMux->setS(aluSrc);
		source1Mux->setI0(sD);
		forwardingUnit->setCurrentInstruction(mipsInstruction);
		alu->setPC(pcPlus4 - 1);
		alu->setInstruction(mipsInstruction.getInstructionName());
		mux3_2->setI0(tD);
		mux2_7->setI1(pcPlus4);
		mux2_7->setS(selectPCPlus4);
		hazardDetection->setPreviousInstruction(mipsInstruction);
		hazardDetection->setPreviousRegWrite(regWrite && !dontWrite && !dontWrite2 && !dontWrite3 && !dontWrite4);
		branchPrediction->setWrite(!dontWrite && !dontWrite2 && !dontWrite3 && !dontWrite4);
	}

	void setBuffer3(Buffer3* b3) {
		buffer3 = b3;
	}

	void setTDOrImmMux(Mux2* ti) {
		tdOrImmMux = ti;
	}

	void setSource1Mux(Mux3* s1) {
		source1Mux = s1;
	}

	void setForwardingUnit(ForwardingUnit* fu) {
		forwardingUnit = fu;
	}

	void setALU(ALU* a) {
		alu = a;
	}

	void setMux3_2(Mux3* m3) {
		mux3_2 = m3;
	}

	void setDontWrite(int dw) {
		dontWrite = dw;
	}

	void setMux2_7(Mux2* m2) {
		mux2_7 = m2;
	}

	void setSelectPCPlus4(int s) {
		selectPCPlus4 = s;
	}

	void setDontWrite2(int dw) {
		dontWrite2 = dw;
	}

	void setHazardDetection(HazardDetection* hd) {
		hazardDetection = hd;
	}

	void setDontWrite3(int dw) {
		dontWrite3 = dw;
	}

	void setDontWrite4(int dw) {
		dontWrite4 = dw;
	}

	void setBranchPrediction(BranchPrediction* bp) {
		branchPrediction = bp;
	}

private:

	MIPSInstruction mipsInstruction;

	int pcPlus4;

	int sD, tD, taOrDa;

	int branch, memWrite, memToReg, aluSrc, regWrite;

	int dontWrite, selectPCPlus4;

	int dontWrite2, dontWrite3, dontWrite4;

	Buffer3* buffer3;

	Mux2* tdOrImmMux;

	Mux3* source1Mux;

	ForwardingUnit* forwardingUnit;

	ALU* alu;

	Mux3* mux3_2;

	Mux2* mux2_7;

	HazardDetection* hazardDetection;

	BranchPrediction* branchPrediction;
};

#endif