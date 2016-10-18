#ifndef JUMP_H
#define JUMP_H

#include "Mux2.h"
#include "MIPSInstruction.h"
#include <stack>

class Buffer1;
class Buffer2;
class Jump {

public:

    Jump() : stop(false), error1(false), error2(false) {}

	void setBuffer1(Buffer1* b1) {
		buffer1 = b1;
	}

	void setBuffer2(Buffer2* b2) {
		buffer2 = b2;
	}

	void setMux2_6(Mux2* m2) {
		mux2_6 = m2;
	}

	void setMux2_1(Mux2* m2) {
		mux2_1 = m2;
	}

	void setMipsInstruction(const MIPSInstruction& instr) {
		mipsInstruction = instr;
	}

	void setSD(int sd) {
		sD = sd;
	}

	void setPCPlus4(int pc) {
		pcPlus4 = pc;
	}

	void execute();

	void STOP() {
		stop = true;
	}

	std::stack<int> getStack() const {
		return st;
	}

    std::string errorHandling() const {
        if (error1)
            return "4-entry stack size exceeded";
        else if (error2)
            return "4-entry stack is empty";
        else
            return "";
    }

private:

    bool error1, error2;

	bool stop;

	MIPSInstruction mipsInstruction;

	int sD;

	int pcPlus4;

	Buffer1* buffer1;

	Buffer2* buffer2;

	Mux2* mux2_6;

	Mux2* mux2_1;

	std::stack<int> st;
};

#endif
