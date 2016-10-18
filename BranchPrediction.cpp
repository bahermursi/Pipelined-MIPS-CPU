#include "BranchPrediction.h"
#include "Buffer1.h"
#include "Buffer2.h"
#include "Jump.h"
#include "TimingDiagram.h"
#include "MIPSInstruction.h"
#include "Mux2.h"
#include "ConfirmedNextAddress.h"

void BranchPrediction::nextInstruction(const MIPSInstruction& instr, int pc) {
	if (instr.getInstructionName() == MIPSInstruction::BEQ || instr.getInstructionName() == MIPSInstruction::BNE || instr.getInstructionName() == MIPSInstruction::BLE) {
		if (btb.find(pc) == btb.end()) {
			btb[pc] = std::make_pair(instr.getImm(), 0);
			mux2_0->setS(0);
		}
		else {
			if (btb[pc].second == 0 || btb[pc].second == 1)
				mux2_0->setS(0);
			else {
				mux2_0->setI1(instr.getImm());
				mux2_0->setS(1);
			}
		}
	}
	else
		mux2_0->setS(0);
}

void BranchPrediction::confirmPrediction(int pc, bool taken) {
	this->pc = pc;
	this->taken = taken;
}

void BranchPrediction::execute() {
	if (write && btb.find(pc) != btb.end()) {
		int state = btb[pc].second;
		switch (state)
		{
		case 0:
			if (taken)
				state = 1;
			break;
		case 1:
			if (taken)
				state = 2;
			else
				state = 0;
			break;
		case 2:
			if (taken)
				state = 3;
			else
				state = 1;
			break;
		default:
			if (!taken)
				state = 2;
			break;
		}
		if ((btb[pc].second == 0 || btb[pc].second == 1) && taken) {
			confirmedNextAddress->setAddress(btb[pc].first);
			buffer1->setDontWrite3(1);
			buffer2->setDontWrite4(1);
			buffer1->setStop(true);
			jump->STOP();
			timingDiagram->editPreviousInstructions();
		}
		else if ((btb[pc].second == 2 || btb[pc].second == 3) && !taken) {
			confirmedNextAddress->setAddress(pc + 1);
			buffer1->setDontWrite3(1);
			buffer2->setDontWrite4(1);
			buffer1->setStop(true);
			jump->STOP();
			timingDiagram->editPreviousInstructions();
		}
		else {
			buffer1->setDontWrite3(0);
			buffer2->setDontWrite4(0);
			buffer1->setStop(false);
		}
		btb[pc].second = state;
	}
	else {
		buffer1->setDontWrite3(0);
		buffer2->setDontWrite4(0);
		buffer1->setStop(false);
	}
}

void BranchPrediction::setMux2_0(Mux2* m2) {
	mux2_0 = m2;
}

void BranchPrediction::setConfirmedNextAddress(ConfirmedNextAddress* next) {
	confirmedNextAddress = next;
}

void BranchPrediction::setBuffer1(Buffer1* b1) {
	buffer1 = b1;
}

void BranchPrediction::setBuffer2(Buffer2* b2) {
	buffer2 = b2;
}

void BranchPrediction::setJump(Jump* j) {
	jump = j;
}

std::map<int, std::pair<int, int> > BranchPrediction::getTable() const {
	return btb;
}

void BranchPrediction::setTimingDiagram(TimingDiagram* td) {
	timingDiagram = td;
}

void BranchPrediction::setWrite(bool w) {
	write = w;
}