#ifndef CPU_H
#define CPU_H
#include "ProgramCounter.h"
#include "ALU.h"
#include "Jump.h"
#include "HazardDetection.h"
#include "ConfirmedNextAddress.h"
#include "BranchPrediction.h"
#include "TimingDiagram.h"
#include "MIPSParser.h"

class CPU {

public:

    CPU();

    void execute();

    void setParser(MIPSParser);

    Mux2 mux2_0, mux2_1, mux2_2, mux2_3, mux2_4, mux2_5, mux2_6, mux2_7, mux2_8, mux2_9;

    Mux3 mux3_0, mux3_1, mux3_2;

    ProgramCounter programCounter;

    InstructionMemory instructionMemory;

    Buffer1 buffer1;

    Buffer2 buffer2;

    Buffer3 buffer3;

    Buffer4 buffer4;

    RegFile regFile;

    ControlUnit controlUnit;

    ForwardingUnit forwardingUnit;

    ALU alu;

    DataMemory dataMemory;

    Jump jump;

    HazardDetection hazardDetection;

    BranchPrediction branchPrediction;

    ConfirmedNextAddress confirmedNextAddress;

    TimingDiagram timingDiagram;
};

#endif
