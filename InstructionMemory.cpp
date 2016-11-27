#include "InstructionMemory.h"
#include "BranchPrediction.h"
#include <iostream>

void InstructionMemory:: execute() {
	if (address < instructions.size()) {
		buffer1->setMipsInstruction(instructions[address]);
		//std::cout << instructions[address].getLine() << std::endl;
		branchPrediction->nextInstruction(instructions[address], address);
		if (instructions[address].getInstructionName() == MIPSInstruction::J || instructions[address].getInstructionName() == MIPSInstruction::JAL || instructions[address].getInstructionName() == MIPSInstruction::JR || instructions[address].getInstructionName() == MIPSInstruction::JUMP_PROCEDURE || instructions[address].getInstructionName() == MIPSInstruction::RETURN_PROCEDURE)
			timingDiagram->stallNextJump();
		else if (instructions[address].getInstructionName() == MIPSInstruction::LW) {
			if (address + 1 < instructions.size()) {
				if (instructions[address + 1].getInstructionName() == MIPSInstruction::JR && instructions[address + 1].getSA() == instructions[address].getTA())
					timingDiagram->stallNext2LW();
				else if ((instructions[address + 1].getInstructionName() == MIPSInstruction::ADD || instructions[address + 1].getInstructionName() == MIPSInstruction::SUB || instructions[address + 1].getInstructionName() == MIPSInstruction::OR || instructions[address + 1].getInstructionName() == MIPSInstruction::XOR || instructions[address + 1].getInstructionName() == MIPSInstruction::SLT || instructions[address + 1].getInstructionName() == MIPSInstruction::BEQ || instructions[address + 1].getInstructionName() == MIPSInstruction::BNE || instructions[address + 1].getInstructionName() == MIPSInstruction::BLE) && (instructions[address + 1].getSA() == instructions[address].getTA() || instructions[address + 1].getTA() == instructions[address].getTA()))
					timingDiagram->stallNextLW();
				else if ((instructions[address + 1].getInstructionName() == MIPSInstruction::ADDI || instructions[address + 1].getInstructionName() == MIPSInstruction::LW) && instructions[address + 1].getSA() == instructions[address].getTA())
					timingDiagram->stallNextLW();
			}
			else if (address + 2 < instructions.size()) {
				if (instructions[address + 2].getInstructionName() == MIPSInstruction::JR && instructions[address + 1].getSA() == instructions[address].getTA())
					timingDiagram->stallNextNextLW();
			}
		}
	}
	else {
		MIPSInstruction temp;
		temp.setRType("nop", MIPSInstruction::ADD, 0);
		buffer1->setMipsInstruction(temp);
		++counter;
	}
}

void InstructionMemory::setAddress(int a){
    address = a;
}
