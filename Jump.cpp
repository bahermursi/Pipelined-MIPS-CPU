#include "Jump.h"
#include "Buffer1.h"
#include "Buffer2.h"
#include <exception>

void Jump::execute() {
	if (!stop) {
		if (mipsInstruction.getInstructionName() == MIPSInstruction::J) {
			mux2_1->setI1(mipsInstruction.getImm());
			mux2_1->setS(1);
			buffer1->setDontWrite(1);
			this->STOP();
		}
		else if (mipsInstruction.getInstructionName() == MIPSInstruction::JAL) {
			mux2_1->setI1(mipsInstruction.getImm());
			mux2_1->setS(1);
			buffer1->setDontWrite(1);
			mux2_6->setS(1);
			buffer2->setSelectPCPlus4(1);
			this->STOP();
		}
		else if (mipsInstruction.getInstructionName() == MIPSInstruction::JR) {
			mux2_1->setI1(sD);
			mux2_1->setS(1);
			buffer1->setDontWrite(1);
			this->STOP();
		}
		else if (mipsInstruction.getInstructionName() == MIPSInstruction::JUMP_PROCEDURE) {
			if (st.size() < 4)
				st.push(pcPlus4);
			else
                error1 = true;
			mux2_1->setI1(mipsInstruction.getImm());
			mux2_1->setS(1);
			buffer1->setDontWrite(1);
			this->STOP();
		}
		else if (mipsInstruction.getInstructionName() == MIPSInstruction::RETURN_PROCEDURE) {
			int address;
			if (st.size() > 0) {
				address = st.top();
				st.pop();
			}
			else
                error2 = true;
			mux2_1->setI1(address);
			mux2_1->setS(1);
			buffer1->setDontWrite(1);
			this->STOP();
		}
		else {
			mux2_1->setS(0);
			buffer1->setDontWrite(0);
			mux2_6->setS(0);
			buffer2->setSelectPCPlus4(0);
		}
	}
	else {
		mux2_1->setS(0);
		buffer1->setDontWrite(0);
		mux2_6->setS(0);
		buffer2->setSelectPCPlus4(0);
		stop = false;
	}
}
