#include "Mux3.h"
#include "ALU.h"
#include "Buffer3.h"

void Mux3::setMux2_8(Mux2* m2) {
	mux2_8 = m2;
}

void Mux3::setMux2_9(Mux2* m2) {
	mux2_9 = m2;
}

void Mux3::execute() {
	int out = (S == 2) ? I2 : (S == 1) ? I1 : I0;
	switch (idx)
	{
	case 0:
		mux2_8->setI0(out);
		break;
	case 1:
		mux2_9->setI0(out);
		break;
	default:
		buffer3->setTD(out);
	}
}

void Mux3::setBuffer3(Buffer3* b3) {
	buffer3 = b3;
}