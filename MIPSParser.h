#ifndef MIPS_PARSER_H
#define MIPS_PARSER_H

#include <string>
#include <vector>
#include "MIPSInstruction.h"

class MIPSParser {

public:

	MIPSParser();

    std::vector<int> parse(const std::string& fileName);

	std::vector<MIPSInstruction> getInstructions() const {
		return instructions;
	}

private:

	int regNameToNumber(const std::string& name);

	std::string regNum, regName, reg, immDec, immHex, imm, instr[MIPSInstruction::NUMBER_OR_INSTRUCTIONS];

	std::vector<MIPSInstruction> instructions;
};

#endif
