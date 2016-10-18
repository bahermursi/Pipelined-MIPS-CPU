#include "ALU.h"
#include "BranchPrediction.h"

void ALU:: execute() {
	int result = 0, zero = 0;
	if (instruction == MIPSInstruction::XOR)
		result = source1 ^ source2;
	else if (instruction == MIPSInstruction::OR)
		result = source1 | source2;
	else if (instruction == MIPSInstruction::BEQ)
		zero = source1 == source2;
	else if (instruction == MIPSInstruction::BNE)
		zero = source1 != source2;
	else if (instruction == MIPSInstruction::BLE)
		zero = source1 <= source2;
	else if (instruction == MIPSInstruction::SUB)
		result = source1 - source2;
	else if (instruction == MIPSInstruction::SLT)
		result = source1 < source2;
	else
		result = source1 + source2;
	mux2_7->setI0(result);
	branchPrediction->confirmPrediction(pc, zero);
}

void ALU::setInstruction(MIPSInstruction::InstructionName inst) {
    instruction = inst;
}

void ALU::setSource1(int s) {
	source1 = s;
}

void ALU::setSource2(int s) {
	source2 = s;
}

void ALU::setMux2_7(Mux2* m2) {
	mux2_7 = m2;
}