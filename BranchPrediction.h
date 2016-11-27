#ifndef BRANCH_PREDICTION_H
#define BRANCH_PREDICTION_H

#include <map>

class Buffer1;
class Buffer2;
class Jump;
class TimingDiagram;
class Mux2;
class ConfirmedNextAddress;
class MIPSInstruction;
class BranchPrediction {

public:

	void nextInstruction(const MIPSInstruction&, int);

	void confirmPrediction(int, bool);

	void execute();

	void setMux2_0(Mux2*);

	void setConfirmedNextAddress(ConfirmedNextAddress*);

	void setBuffer1(Buffer1*);

	void setBuffer2(Buffer2*);

	void setJump(Jump*);

	std::map<int, std::pair<int, int> > getTable() const;

	void setTimingDiagram(TimingDiagram*);

	void setWrite(bool);

private:

	//pc, pair<branchPc, prediction>
	std::map<int, std::pair<int, int> > btb;

	int pc;

	bool taken;

	bool write;

	Mux2* mux2_0;

	ConfirmedNextAddress* confirmedNextAddress;
	
	Buffer1* buffer1;

	Buffer2* buffer2;

	Jump* jump;

	TimingDiagram* timingDiagram;
};

#endif