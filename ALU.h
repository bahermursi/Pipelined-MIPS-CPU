#ifndef ALU_H
#define ALU_H

#include "MIPSInstruction.h"
#include "Mux2.h"

class BranchPrediction;
class ALU {

public:

    void execute();

	void setSource1(int);

	void setSource2(int);

    void setInstruction(MIPSInstruction::InstructionName);

	void setMux2_7(Mux2*);

	void setBranchPrediction(BranchPrediction* branch) {
		branchPrediction = branch;
	}

	void setPC(int a) {
		pc = a;
	}

private:

	int pc;

	int source1, source2;

	MIPSInstruction::InstructionName instruction;

	Mux2* mux2_7;

	BranchPrediction* branchPrediction;
};

#endif