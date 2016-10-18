#include "ForwardingUnit.h"
#include "Buffer3.h"

void ForwardingUnit::execute() {
	int f0 = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
	f2 = (currentInstruction.getInstructionName() == MIPSInstruction::SW && previousInstruction.getInstructionName() == MIPSInstruction::LW && currentInstruction.getTA() == previousInstruction.getTA());
	if (currentInstruction.getInstructionName() != MIPSInstruction::J && currentInstruction.getInstructionName() != MIPSInstruction::JAL && currentInstruction.getInstructionName() != MIPSInstruction::JUMP_PROCEDURE && currentInstruction.getInstructionName() != MIPSInstruction::RETURN_PROCEDURE) {
		if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getSA() == previousInstruction.getTA())
			f0 = 1;
		else if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getSA() == 31)
			f0 = 1;
		else if (previousRegWrite && previousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousInstruction.getInstructionName() != MIPSInstruction::JAL && currentInstruction.getSA() == previousInstruction.getDA())
			f0 = 1;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getSA() == previousPreviousInstruction.getTA())
			f0 = 2;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getSA() == 31)
			f0 = 2;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousPreviousInstruction.getInstructionName() != MIPSInstruction::JAL && currentInstruction.getSA() == previousPreviousInstruction.getDA())
			f0 = 2;
		if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::LW && currentInstruction.getSA() == previousPreviousInstruction.getTA())
			f4 = 1;
		if (currentInstruction.getInstructionName() != MIPSInstruction::JR && currentInstruction.getInstructionName() != MIPSInstruction::ADDI && currentInstruction.getInstructionName() != MIPSInstruction::LW && currentInstruction.getInstructionName() != MIPSInstruction::SW) {
			if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getTA() == previousInstruction.getTA())
				f1 = 1;
			else if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getTA() == 31)
				f1 = 1;
			else if (previousRegWrite && previousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousInstruction.getInstructionName() != MIPSInstruction::JAL && currentInstruction.getTA() == previousInstruction.getDA())
				f1 = 1;
			else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getTA() == previousPreviousInstruction.getTA())
				f1 = 2;
			else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getTA() == 31)
				f1 = 2;
			else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousPreviousInstruction.getInstructionName() != MIPSInstruction::JAL && currentInstruction.getTA() == previousPreviousInstruction.getDA())
				f1 = 2;
			if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::LW && currentInstruction.getTA() == previousPreviousInstruction.getTA())
				f5 = 1;
		}
	}
	if (currentInstruction.getInstructionName() == MIPSInstruction::SW) {
		if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getTA() == previousInstruction.getTA())
			f3 = 1;
		else if (previousRegWrite && previousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getTA() == 31)
			f3 = 1;
		else if (previousRegWrite && previousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousInstruction.getInstructionName() != MIPSInstruction::JAL && previousInstruction.getInstructionName() != MIPSInstruction::LW && currentInstruction.getTA() == previousInstruction.getDA())
			f3 = 1;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::ADDI && currentInstruction.getTA() == previousPreviousInstruction.getTA())
			f3 = 2;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() == MIPSInstruction::JAL && currentInstruction.getTA() == 31)
			f3 = 2;
		else if (previousPreviousRegWrite && previousPreviousInstruction.getInstructionName() != MIPSInstruction::ADDI && previousPreviousInstruction.getInstructionName() != MIPSInstruction::JAL && previousPreviousInstruction.getInstructionName() != MIPSInstruction::LW && currentInstruction.getTA() == previousPreviousInstruction.getDA())
			f3 = 2;
	}
	mux3_0->setS(f0);
	mux3_1->setS(f1);
	buffer3->setDataMemoryMuxSelection(f2);
	mux3_2->setS(f3);
	mux2_8->setS(f4);
	mux2_9->setS(f5);
}

void ForwardingUnit::setBuffer3(Buffer3* b3) {
	buffer3 = b3;
}