#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mipstexthighlighter.h"
#include "MIPSParser.h"
#include "MIPSInstruction.h"
#include "CPU.h"
#include "stepwindow.h"
#include "runwindow.h"
#include "branchtablewindow.h"
#include "AboutWindow.h"
#include "entrystackwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  void getDataPointers(int* r, int* m);
    string myData;
private slots:
    void on_pushButton_clicked();

    void on_runButton_clicked();

    void on_helpButton_clicked();

    void on_checkSyntaxButton_clicked();

    void on_highlightLine(int);

   void setRegs();

   void setMem();
   void on_stepButton_clicked();


   void on_branchTableButton_clicked();

   void on_aboutButton_clicked();

   void on_clearButton_clicked();

   void on_entryStackButton_clicked();

private:
    Ui::MainWindow *ui;
    MIPSParser parser;
    vector <string>  s;
    vector <string>  l;
    vector <int> linesIndex;
    vector <MIPSInstruction> instructions;
    bool isCorrect;
    MipsTextHighlighter *highlighter;
    int regs[32];
    int mem[32];
    CPU *cpu;
    string instName;
    StepWindow *stepWindow;
    RunWindow *runWindow;
    AboutWindow *aboutWindow;
    BranchTableWindow *branchWindow;
    EntryStackWindow *entryWindow;
    bool openedFile;
};

#endif // MAINWINDOW_H
