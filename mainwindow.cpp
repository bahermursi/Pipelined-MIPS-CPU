#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <Qfile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QString>
#include <QFont>
#include <QDebug>
#include <iostream>
#include "MIPSParser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isCorrect = false;
    ui->runButton->setEnabled(isCorrect);
    ui->stepButton->setEnabled(isCorrect);
    ui->branchTableButton->setEnabled(isCorrect);
    ui->aboutButton->setEnabled(isCorrect);
    ui->correctLabel->setVisible(false);
    ui->wrongLabel->setVisible(false);
   ui->checkSyntaxButton->setEnabled(false);
    setRegs();
    setMem();
    openedFile = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->codeBrowser->setFont(font);


    highlighter = new MipsTextHighlighter(ui->codeBrowser->document());
    QFileDialog qdialog;
    QString path = qdialog.getOpenFileName(this, tr("Open File"), "/Users","Text File(*.txt)" );
    QFile mfile(path);

    if (!mfile.open(QFile::ReadOnly | QFile::Text)){
        openedFile = false;
        qDebug() << "Error in opening file!";
        QMessageBox::information(NULL,"Hi!","Error in opening file!");
    } else{

        openedFile = true;
       ui->checkSyntaxButton->setEnabled(true);
    }

    ui->pathLabel->setText(path);
    linesIndex = parser.parse(path.toStdString());
    instructions = parser.getInstructions();

    cpu = new CPU();
    cpu->setParser(parser);
    int *r = cpu->regFile.getRegisters();
    int *m = cpu->dataMemory.getMemory();

    for( int i = 0; i< 32; ++i){
        regs[i] = r[i];
        mem[i] = m[i];
    }
    setRegs();
    setMem();

    instName = cpu->instructionMemory.getInstruction();

    myData = mfile.readAll().toStdString();
    ui->codeBrowser->setPlainText(QString::fromStdString(myData));
    highlighter->rehighlight();
    QTextCursor cursor = ui->codeBrowser->textCursor();
    ui->codeBrowser->selectAll();
    ui->codeBrowser->setFontPointSize(16);

    ui->codeBrowser->setTextCursor( cursor );
    mfile.close();
}


void MainWindow::on_runButton_clicked()
{
    runWindow = new RunWindow(cpu,instructions,myData,this,this);
    runWindow->exec();
}

void MainWindow::on_helpButton_clicked()
{
}

void MainWindow::on_checkSyntaxButton_clicked()
{
    isCorrect = (linesIndex.size() == 0) && openedFile;
    if(isCorrect){
        ui->correctLabel->setVisible(true);
        ui->wrongLabel->setVisible(false);
        ui->syntaxLabel->setText("Syntax checked");
    }
    else{

        ui->wrongLabel->setVisible(true);
        ui->correctLabel->setVisible(false);
        for(int i = 0; i < linesIndex.size(); ++i){
            ui->syntaxLabel->setText("Syntax Error Found");
        }
    }
    ui->runButton->setEnabled(isCorrect);
    ui->stepButton->setEnabled(isCorrect);
    ui->branchTableButton->setEnabled(isCorrect);
    ui->aboutButton->setEnabled(isCorrect);

    //int count = 0;
    //    int pos =  myData.find("add $s9, $t11, $s2");
    //    for( int i=0; i< pos; ++i )
    //        if(myData[i] == '\n') ++count;
    //    on_highlightLine(1);

}

void MainWindow::on_highlightLine(int x)
{
    QTextCursor c = ui->codeBrowser->textCursor();
    QTextCharFormat fmt;
    fmt.setBackground(Qt::red);
    fmt.setFontPointSize(16);
    c.setPosition(0);

    c.setPosition(50 /*+prev.Lines.length()*/, QTextCursor::MoveAnchor);
    c.setPosition(60 /* + line.length()*/, QTextCursor::KeepAnchor);

    c.setPosition(5/*+prev.Lines.length()*/, QTextCursor::MoveAnchor);
    c.setPosition(10/* + line.length()*/, QTextCursor::KeepAnchor);

    c.setCharFormat(fmt);
}

void MainWindow::setRegs(){
    ui->r0Label->setText(QString::number(regs[0]));
    ui->r1Label->setText(QString::number(regs[1]));
    ui->r2Label->setText(QString::number(regs[2]));
    ui->r3Label->setText(QString::number(regs[3]));
    ui->r4Label->setText(QString::number(regs[4]));
    ui->r5Label->setText(QString::number(regs[5]));
    ui->r6Label->setText(QString::number(regs[6]));
    ui->r7Label->setText(QString::number(regs[7]));
    ui->r8Label->setText(QString::number(regs[8]));
    ui->r9Label->setText(QString::number(regs[9]));
    ui->r10Label->setText(QString::number(regs[10]));
    ui->r11Label->setText(QString::number(regs[11]));
    ui->r12Label->setText(QString::number(regs[12]));
    ui->r13Label->setText(QString::number(regs[13]));
    ui->r14Label->setText(QString::number(regs[14]));
    ui->r15Label->setText(QString::number(regs[15]));
    ui->r16Label->setText(QString::number(regs[16]));
    ui->r17Label->setText(QString::number(regs[17]));
    ui->r18Label->setText(QString::number(regs[18]));
    ui->r19Label->setText(QString::number(regs[19]));
    ui->r20Label->setText(QString::number(regs[20]));
    ui->r21Label->setText(QString::number(regs[21]));
    ui->r22Label->setText(QString::number(regs[22]));
    ui->r23Label->setText(QString::number(regs[23]));
    ui->r24Label->setText(QString::number(regs[24]));
    ui->r25Label->setText(QString::number(regs[25]));
    ui->r26Label->setText(QString::number(regs[26]));
    ui->r27Label->setText(QString::number(regs[27]));
    ui->r28Label->setText(QString::number(regs[28]));
    ui->r29Label->setText(QString::number(regs[29]));
    ui->r30Label->setText(QString::number(regs[30]));
    ui->r31Label->setText(QString::number(regs[31]));
}
void MainWindow::setMem(){
    ui->m0Label->setText(QString::number(mem[0]));
    ui->m1Label->setText(QString::number(mem[1]));
    ui->m2Label->setText(QString::number(mem[2]));
    ui->m3Label->setText(QString::number(mem[3]));
    ui->m4Label->setText(QString::number(mem[4]));
    ui->m5Label->setText(QString::number(mem[5]));
    ui->m6Label->setText(QString::number(mem[6]));
    ui->m7Label->setText(QString::number(mem[7]));
    ui->m8Label->setText(QString::number(mem[8]));
    ui->m9Label->setText(QString::number(mem[9]));
    ui->m10Label->setText(QString::number(mem[10]));
    ui->m11Label->setText(QString::number(mem[11]));
    ui->m12Label->setText(QString::number(mem[12]));
    ui->m13Label->setText(QString::number(mem[13]));
    ui->m14Label->setText(QString::number(mem[14]));
    ui->m15Label->setText(QString::number(mem[15]));
    ui->m16Label->setText(QString::number(mem[16]));
    ui->m17Label->setText(QString::number(mem[17]));
    ui->m18Label->setText(QString::number(mem[18]));
    ui->m19Label->setText(QString::number(mem[19]));
    ui->m20Label->setText(QString::number(mem[20]));
    ui->m21Label->setText(QString::number(mem[21]));
    ui->m22Label->setText(QString::number(mem[22]));
    ui->m23Label->setText(QString::number(mem[23]));
    ui->m24Label->setText(QString::number(mem[24]));
    ui->m25Label->setText(QString::number(mem[25]));
    ui->m26Label->setText(QString::number(mem[26]));
    ui->m27Label->setText(QString::number(mem[27]));
    ui->m28Label->setText(QString::number(mem[28]));
    ui->m29Label->setText(QString::number(mem[29]));
    ui->m30Label->setText(QString::number(mem[30]));
    ui->m31Label->setText(QString::number(mem[31]));
}

void MainWindow::on_stepButton_clicked()
{
    stepWindow = new StepWindow(cpu,instructions,this,this);
    stepWindow->exec();
}

void MainWindow::getDataPointers(int* r, int* m)
{

    for( int i = 0; i< 32; ++i){
        regs[i] = r[i];
        mem[i] = m[i];
    }

    setRegs();
    setMem();
    ui->centralWidget->update();
}

void MainWindow::on_branchTableButton_clicked()
{
    branchWindow = new BranchTableWindow(cpu->branchPrediction.getTable(), this);
    branchWindow->exec();
}

void MainWindow::on_aboutButton_clicked()
{
    aboutWindow = new AboutWindow( this);
    aboutWindow->exec();
}

void MainWindow::on_clearButton_clicked()
{
    cpu = NULL;
    for(int i=0; i<32; ++i){
        regs[i] = 0;
        mem[i] = 0;
    }
    ui->codeBrowser->clear();
    ui->syntaxLabel->clear();
    ui->wrongLabel->setVisible(false);
    ui->correctLabel->setVisible(false);
    isCorrect = false;
    ui->runButton->setEnabled(isCorrect);
    ui->stepButton->setEnabled(isCorrect);
    ui->branchTableButton->setEnabled(isCorrect);
    ui->aboutButton->setEnabled(isCorrect);

}

void MainWindow::on_entryStackButton_clicked()
{
 entryWindow = new EntryStackWindow(cpu,this);
 entryWindow->exec();
}
