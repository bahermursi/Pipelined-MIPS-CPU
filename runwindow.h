#ifndef RUNWINDOW_H
#define RUNWINDOW_H
#include <QDialog>
#include <CPU.h>
#include <MIPSInstruction.h>
#include <vector>
#include <string>

using namespace std;
class MainWindow;

namespace Ui {
class RunWindow;
}

class RunWindow : public QDialog
{
    Q_OBJECT
enum UNITS {FETCH, DECODE, EXECUTE,MEMORY,WRITEBACK,NOP};
public:
explicit RunWindow(CPU* c, const vector <MIPSInstruction> &v , string, MainWindow* m,QWidget *parent = 0);
    ~RunWindow();
    QWidget* p;

private slots:
    void on_saveButton_clicked();
    void on_stopButton_clicked();
    void on_startButton_clicked();

private:
    void addNewInstruction(string);
    void editPrevInstruction(string str);
    string getStage(char);

    Ui::RunWindow *ui;
    CPU *cpu;
    vector <MIPSInstruction> instructions;
    MainWindow *parentPointer;
    QString instr;
    bool Running;
    int rowCount, *regs, *mem;
    int offset;
    QString memory,registers;
    vector<QString> lines;
    string data;
    int ind;
    bool b= false;

};

#endif // RUNWINDOW_H
