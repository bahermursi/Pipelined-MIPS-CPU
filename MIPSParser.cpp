#include "MIPSParser.h"
#include <fstream>
#include <exception>
#include <regex>
#include <sstream>
#include <iostream>
using namespace std;

MIPSParser::MIPSParser() {
    ifstream cin("/Users/bahermursi/Desktop/ComputerArchitectureUI/Regular Expressions.rgx");
	getline(cin, regNum);
	getline(cin, regName);
	reg = "(\\$(" + regNum + "|" + regName + "))";
	getline(cin, immDec);
	getline(cin, immHex);
	imm = "(" + immHex + "|" + immDec + ")";
	for (int i = 0; i < MIPSInstruction::NUMBER_OR_INSTRUCTIONS; ++i) {
		getline(cin, instr[i]);
		int idx = 0;
		while ((idx = instr[i].find("REG")) != -1)
			instr[i].replace(idx, 3, reg);
		while ((idx = instr[i].find("IMM")) != -1)
			instr[i].replace(idx, 3, imm);
	}
    cin.close();
}

std::vector<int> MIPSParser::parse(const string& fileName) {
	vector<int>ret;
	int lineNumber = -1;
	ifstream cin{ fileName };
    if (cin.fail()){
        cout<< "Failed to open: " + fileName;
    return ret;
    }
	string line;
    regex regRgx( reg ), immRgx( imm ), immDecimalRgx( immDec );
	bool lineIsEmpty, matchesRgx;
	while (!cin.eof()) {
		++lineNumber;
		MIPSInstruction instruction;
		getline(cin, line);
		lineIsEmpty = true;
		for (int i = 0; i < line.length(); ++i) {
			if (line[i] != ' ' && line[i] != '\t') {
				lineIsEmpty = false;
				break;
			}
		}
		if (lineIsEmpty)
			continue;
		matchesRgx = false;
		for (MIPSInstruction::InstructionName i = MIPSInstruction::ADD; i <= MIPSInstruction::SLT; i = (MIPSInstruction::InstructionName)(i + 1)) {
            if (regex_match(line, regex( instr[i] ))) {
                sregex_iterator it( line.begin(), line.end(), regRgx );
				int s, t, d;
				d = regNameToNumber((*(it++))[0]);
				s = regNameToNumber((*(it++))[0]);
				t = regNameToNumber((*it)[0]);
				instruction.setRType(line, i, s, t, d);
				instructions.push_back(instruction);
				matchesRgx = true;
				break;
			}
		}
		if (matchesRgx)
			continue;
        if (regex_match(line, regex( instr[MIPSInstruction::JR] ))) {
            sregex_iterator it( line.begin(), line.end(), regRgx );
			int s;
			s = regNameToNumber((*it)[0]);
			instruction.setRType(line, MIPSInstruction::JR, s);
			instructions.push_back(instruction);
			continue;
		}
		for (MIPSInstruction::InstructionName i = MIPSInstruction::ADDI; i <= MIPSInstruction::BLE; i = (MIPSInstruction::InstructionName)(i + 1)) {
            if (regex_match(line, regex( instr[i] ))) {
                sregex_iterator it1( line.begin(), line.end(), regRgx );
				int s, t, immediate;
				t = regNameToNumber((*(it1++))[0]);
				s = regNameToNumber((*it1)[0]);
				int comma = line.length() - 1;
				while (line[comma] != ',')
					--comma;
				string immStr = line.substr(comma + 1, line.length() - comma - 1);
                sregex_iterator it2( immStr.begin(), immStr.end(), immRgx );
				immStr = (*it2)[0];
				if (regex_match(immStr, immDecimalRgx))
					immediate = atoi(immStr.c_str());
				else {
					stringstream ss;
					ss << hex << immStr.substr(2, immStr.length() - 2);
					ss >> immediate;
				}
				instruction.setIType(line, i, s, t, immediate);
				instructions.push_back(instruction);
				matchesRgx = true;
				break;
			}
		}
		if (matchesRgx)
			continue;
		for (MIPSInstruction::InstructionName i = MIPSInstruction::LW; i <= MIPSInstruction::SW; i = (MIPSInstruction::InstructionName)(i + 1)) {
            if (regex_match(line, regex( instr[i] ))) {
				sregex_iterator it1{ line.begin(), line.end(), regRgx };
				int s, t, immediate;
				t = regNameToNumber((*(it1++))[0]);
				s = regNameToNumber((*it1)[0]);
				int comma = line.find(','), bracket = line.find('(');
				string immStr = line.substr(comma + 1, bracket - comma - 1);
                sregex_iterator it2( immStr.begin(), immStr.end(), immRgx );
				immStr = (*it2)[0];
				if (regex_match(immStr, immDecimalRgx))
					immediate = atoi(immStr.c_str());
				else {
					stringstream ss;
					ss << hex << immStr.substr(2, immStr.length() - 2);
					ss >> immediate;
				}
				instruction.setIType(line, i, s, t, immediate);
				instructions.push_back(instruction);
				matchesRgx = true;
				break;
			}
		}
		if (matchesRgx)
			continue;
		for (MIPSInstruction::InstructionName i = MIPSInstruction::J; i <= MIPSInstruction::JUMP_PROCEDURE; i = (MIPSInstruction::InstructionName)(i + 1)) {
            if (regex_match(line, regex( instr[i] ))) {
                sregex_iterator it( line.begin(), line.end(), immRgx );
				int immediate;
				string immStr = (*it)[0];
				if (regex_match(immStr, immDecimalRgx))
					immediate = atoi(immStr.c_str());
				else {
					stringstream ss;
					ss << hex << immStr.substr(2, immStr.length() - 2);
					ss >> immediate;
				}
				instruction.setJType(line, i, immediate);
				instructions.push_back(instruction);
				matchesRgx = true;
				break;
			}
		}
		if (matchesRgx)
			continue;
        if (regex_match(line, regex( instr[MIPSInstruction::RETURN_PROCEDURE] ))) {
			instruction.setJType(line, MIPSInstruction::RETURN_PROCEDURE);
			instructions.push_back(instruction);
			matchesRgx = true;
		}
		if (!matchesRgx)
			ret.push_back(lineNumber);
	}
    cin.close();
	return ret;
}

int MIPSParser::regNameToNumber(const string& name) {
    if (regex_match(name, regex( "\\$" + regNum )))
		return atoi(name.substr(1, name.length() - 1).c_str());
	else {
		if (name[1] == 'z')
			return 0;
		else if (name == "$at")
			return 1;
		else if (name[1] == 'v')
			return name[2] - '0' + 2;
		else if (name[1] == 'a')
			return name[2] - '0' + 4;
		else if (name[1] == 't' && name[2] <= '7')
			return name[2] - '0' + 8;
		else if (name[1] == 's')
			return name[2] - '0' + 16;
		else if (name[1] == 't')
			return name[2] - '0' + 16;
		else if (name[1] == 'k')
			return name[2] - '0' + 26;
		else if (name[1] == 'g')
			return 28;
		else if (name[1] == 's')
			return 29;
		else if (name[1] == 'f')
			return 30;
		else
			return 31;
	}
}
