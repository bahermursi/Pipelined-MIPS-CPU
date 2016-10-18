#include "ProgramCounter.h"

void ProgramCounter::execute(){
    instructiomMemory->setAddress(PC);
	buffer1->setPCPlus4(PC + 1);
	branchMux->setI0(PC + 1);
	//Add jump set
}

void ProgramCounter::setPC(int counter) {
	previousPC = PC;
    PC = counter;
}
