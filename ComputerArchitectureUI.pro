#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T12:54:15
#
#-------------------------------------------------
QT += core gui
QT += widgets
QT += printsupport
QT += sql
CONFIG += c++11
INCLUDEPATH += /usr/include/c++/4.3

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerArchitectureUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    runwindow.cpp \
    mipstexthighlighter.cpp \
    MIPSParser.cpp \
    ALU.cpp \
    ControlUnit.cpp \
    CPU.cpp \
    DataMemory.cpp \
    ForwardingUnit.cpp \
    HazardDetection.cpp \
    InstructionMemory.cpp \
    Jump.cpp \
    Mux2.cpp \
    Mux3.cpp \
    ProgramCounter.cpp \
    RegFile.cpp \
    stepwindow.cpp \
    branchtablewindow.cpp \
    BranchPrediction.cpp \
    aboutwindow.cpp \
    entrystackwindow.cpp

HEADERS  += mainwindow.h \
    runwindow.h \
    mipstexthighlighter.h \
    MIPSInstruction.h \
    MIPSParser.h \
    ALU.h \
    BranchPrediction.h \
    Buffer1.h \
    Buffer2.h \
    Buffer3.h \
    Buffer4.h \
    ConfirmedNextAddress.h \
    ControlUnit.h \
    CPU.h \
    DataMemory.h \
    ForwardingUnit.h \
    HazardDetection.h \
    InstructionMemory.h \
    Jump.h \
    Mux2.h \
    Mux3.h \
    ProgramCounter.h \
    RegFile.h \
    stepwindow.h \
    branchtablewindow.h \
    aboutwindow.h \
    TimingDiagram.h \
    entrystackwindow.h

FORMS    += mainwindow.ui \
    runwindow.ui \
    stepwindow.ui \
    branchtablewindow.ui \
    aboutwindow.ui \
    entrystackwindow.ui

RESOURCES += \
    resources.qrc
