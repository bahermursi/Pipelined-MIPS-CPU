#include "DataMemory.h"

void DataMemory::execute() {
	if (address >= 0 && address < 32) {
		if (memWrite)
			memory[address] = writeData;
		buffer4->setMemOut(memory[address]);
	}
}

void DataMemory::setWriteData(int wr){
    writeData = wr;
}

void DataMemory::setAddress(int a){
    address = a;
}

void DataMemory::setMemWrite(int mw){
	memWrite = mw;
}