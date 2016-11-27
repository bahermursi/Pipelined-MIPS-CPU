#ifndef STEPWINDOW_H
#define STEPWINDOW_H

#include <QDialog>
#include <CPU.h>
#include <MIPSInstruction.h>
#include <vector>
#include <string>
using namespace std;
class MainWindow;
namespace Ui {
class StepWindow;
}

class StepWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StepWindow(CPU*,const vector <MIPSInstruction>&,MainWindow*, QWidget *parent = 0);
    ~StepWindow();

private slots:
    void on_stepWindow_clicked();


private:
    void addNewInstruction(string);
    void editPrevInstruction(string);
    string getStage(char);
    Ui::StepWindow *ui;
    CPU *cpu;
    vector <MIPSInstruction> instructions;
    MainWindow *parentPointer;
     QString instr ;
    int rowCount;
    int offset;

};

#endif // STEPWINDOW_H
