#include "ControlUnit.h"

void ControlUnit::set(MIPSInstruction:: InstructionName instr){
	instructionName = instr;
	++receivedInfo;
}

void ControlUnit::execute() {
	if (receivedInfo > 1) {
		bool regDst = (instructionName == MIPSInstruction::ADD || instructionName == MIPSInstruction::SUB || instructionName == MIPSInstruction::XOR || instructionName == MIPSInstruction::SLT || instructionName == MIPSInstruction::JR || instructionName == MIPSInstruction::OR);
		bool branch = (instructionName == MIPSInstruction::BLE || instructionName == MIPSInstruction::BEQ || instructionName == MIPSInstruction::BNE);
		bool memToReg = (instructionName == MIPSInstruction::LW);
		bool memWrite = (instructionName == MIPSInstruction::SW);
		bool aluSrc = (instructionName == MIPSInstruction::ADDI || instructionName == MIPSInstruction::LW || instructionName == MIPSInstruction::SW);
		bool regWrite = !(instructionName == MIPSInstruction::J || instructionName == MIPSInstruction::BLE || instructionName == MIPSInstruction::JR || instructionName == MIPSInstruction::SW || instructionName == MIPSInstruction::BEQ || instructionName == MIPSInstruction::BNE || instructionName == MIPSInstruction::JUMP_PROCEDURE || instructionName == MIPSInstruction::RETURN_PROCEDURE);
		taOrDaMux->setS(regDst);
		buffer2->setBranch(branch);
		buffer2->setMemToReg(memToReg);
		buffer2->setMemWrite(memWrite);
		buffer2->setAluSrc(aluSrc);
		buffer2->setRegWrite(regWrite);
	}
	else {
		buffer2->setBranch(0);
		buffer2->setMemToReg(0);
		buffer2->setMemWrite(0);
		buffer2->setAluSrc(0);
		buffer2->setRegWrite(0);
	}
}