#include "Mux2.h"
#include "ProgramCounter.h"
#include "Buffer2.h"
#include "Mux3.h"
#include "DataMemory.h"
#include "RegFile.h"
#include "ALU.h"

void Mux2::setMux2_1(Mux2* m2) {
	mux2_1 = m2;
}

void Mux2::setProgramCounter(ProgramCounter* pc) {
	programCounter = pc;
}

void Mux2::setBuffer2(Buffer2* b2) {
	buffer2 = b2;
}

void Mux2::setMux3_1(Mux3* m3) {
	mux3_1 = m3;
}

void Mux2::setDataMemory(DataMemory* dm) {
	dataMemory = dm;
}

void Mux2::setRegFile(RegFile* rf) {
	regFile = rf;
}

void Mux2::setMux2_6(Mux2* m2) {
	mux2_6 = m2;
}

void Mux2::setBuffer3(Buffer3* b3) {
	buffer3 = b3;
}

void Mux2::setALU(ALU* a) {
	alu = a;
}

void Mux2::execute() {
	if (idx == 7)
		I1 = 31;
	int out = S ? I1 : I0;
	switch (idx)
	{
	case 0:
		mux2_1->setI0(out);
		break;
	case 1:
		programCounter->setPC(out);
		break;
	case 2:
		mux2_6->setI0(out);
		break;
	case 3:
		mux3_1->setI0(out);
		break;
	case 4:
		dataMemory->setWriteData(out);
		break;
	case 5:
		regFile->setData(out);
		break;
	case 6:
		buffer2->setTaOrDa(out);
		break;
	case 7:
		buffer3->setALUOut(out);
		break;
	case 8:
		alu->setSource1(out);
		break;
	case 9:
		alu->setSource2(out);
		break;
	}
}