#ifndef TIMING_DIAGRAM_H
#define TIMING_DIAGRAM_H

#include <vector>
#include <string>

class TimingDiagram {

public:

	TimingDiagram() : editPre(false), stallNextJ(false), stallL(false), stallL2(false), stallL3(false) {}

	void editPreviousInstructions() {
		editPre = true;
	}

	void stallNextJump() {
        if (!stallNextJ && !stallL && !stallL2 && !stallL3) {
			stallNextJ = true;
			countStallNextJ = 0;
		}
	}

	void stallNextLW() {
        if (!stallNextJ && !stallL2 && !stallL3) {
			stallL = true;
			countStallL = 0;
		}
	}

	void stallNext2LW() {
        if (!stallNextJ && !stallL3) {
			stallL2 = true;
			countStallL2 = 0;
		}
	}

	void stallNextNextLW() {
		stallL3 = true;
		countStallL3 = 0;
	}

	std::vector<std::string> getTimingDiagrams() {
		std::vector<std::string> ret;
		if (editPre) {
			editPre = false;
			stallNextJ = false;
			stallL = false;
			stallL2 = false;
			stallL3 = false;
			ret.push_back("FDNNN");
			ret.push_back("FNNNN");
			return ret;
		}
		else if (stallNextJ) {
			if (countStallNextJ == 0) {
				++countStallNextJ;
				ret.push_back("FDEMW");
				return ret;
			}
			else {
				stallNextJ = false;
				ret.push_back("FNNNN");
				return ret;
			}
		}
		else if (stallL) {
			if (countStallL == 0) {
				++countStallL;
				ret.push_back("FDEMW");
				return ret;
			}
			else {
				stallL = false;
				ret.push_back("FDNNN");
				return ret;
			}
		}
		else if (stallL2) {
			if (countStallL2 == 0) {
				++countStallL2;
				ret.push_back("FDEMW");
				return ret;
			}
			else if (countStallL2 == 1) {
				++countStallL2;
				ret.push_back("FDNNN");
				return ret;
			}
			else {
				stallL2 = false;
				ret.push_back("FDNNN");
				return ret;
			}
		}
		else if (stallL3) {
			if (countStallL3 == 0) {
				++countStallL3;
				ret.push_back("FDEMW");
				return ret;
			}
			else if (countStallL3 == 1) {
				++countStallL3;
				ret.push_back("FDEMW");
				return ret;
			}
			else {
				stallL3 = false;
				ret.push_back("FDNNN");
				return ret;
			}
		}
		else {
			ret.push_back("FDEMW");
			return ret;
		}
	}

private:

	bool editPre;

	bool stallNextJ;

	int countStallNextJ;

	bool stallL;

	int countStallL;

	bool stallL2;

	int countStallL2;

	bool stallL3;

	int countStallL3;
};

#endif
