#include "stepwindow.h"
#include "ui_stepwindow.h"
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>
StepWindow::StepWindow(CPU* c,const vector <MIPSInstruction> &v ,MainWindow* m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StepWindow),parentPointer(m)
{
    ui->setupUi(this);

    cpu = c;
    instructions = v;

    rowCount = 0;
    offset = 0;
    const int column = 100;


    QStringList myHeader;
    ui->TimeDiagram->setColumnCount(column);
    myHeader << "Instructions";
    for( int i=0; i<= column; ++i){
        myHeader << QString::number(i+1);
    }
    ui->TimeDiagram->resizeRowsToContents();

    ui->TimeDiagram->setHorizontalHeaderLabels(myHeader);
}

StepWindow::~StepWindow()
{
    delete ui;
}

void StepWindow::on_stepWindow_clicked()
{
    cpu->execute();
    string jumpError = cpu->jump.errorHandling();
    if (jumpError != "") {
             QMessageBox::information(NULL,"",QString::fromStdString(jumpError));
             ui->stepWindow->setEnabled(false);
    }
    vector <string> tDiagrams = cpu->timingDiagram.getTimingDiagrams();
    parentPointer->getDataPointers(cpu->regFile.getRegisters(), cpu->dataMemory.getMemory());
    instr = QString::fromStdString(cpu->instructionMemory.getInstruction());
    ui->instNameLabel->setText(instr);
    if(tDiagrams.size() == 1) addNewInstruction(tDiagrams[0]);
    else {
        editPrevInstruction(tDiagrams[0]);
        addNewInstruction(tDiagrams[1]);
    }


    ui->TimeDiagram->update();
}

void StepWindow::addNewInstruction(string str){
    for(int i = 1; i <= offset; ++i){
        ui->TimeDiagram->setItem(rowCount,i, new QTableWidgetItem(" "));
    }

    ui->TimeDiagram->insertRow(ui->TimeDiagram->rowCount());
    ui->TimeDiagram->setItem(rowCount,0, new QTableWidgetItem(instr));

    for( int i = 0 + offset; i < str.length() + offset; ++i){
        ui->TimeDiagram->setItem(rowCount,i+1, new QTableWidgetItem(QString::fromStdString(getStage(str[i-offset]))));
        ui->TimeDiagram->resizeColumnsToContents();
    }

    ++rowCount;
    ++offset;
}
void StepWindow::editPrevInstruction(string str){
    int tempOff = offset - 1;
    int count = rowCount - 1;
    for(int i = 1; i <= tempOff; ++i){
        ui->TimeDiagram->setItem(count,i, new QTableWidgetItem(" "));
    }

    for( int i = 0 + tempOff; i < str.length() + tempOff; ++i){
        ui->TimeDiagram->setItem(count,i+1, new QTableWidgetItem(QString::fromStdString(getStage(str[i-tempOff]))));
        ui->TimeDiagram->resizeColumnsToContents();
    }

}

string StepWindow::getStage(char st){
    if( st == 'F') return "F";
    else if(st == 'D') return "D";
    else if (st == 'E') return "E";
    else if(st == 'M') return "M";
    else if( st == 'W') return "W";
    else if( st == 'N') return " ";
    return "";
}
