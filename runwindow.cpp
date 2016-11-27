#include "runwindow.h"
#include "mainwindow.h"
#include "ui_runwindow.h"
#include <QPrinter>
#include <QFile>
#include <QtWidgets>
#include <QtGui>
#include <QMessageBox>
RunWindow::RunWindow(CPU* c, const vector <MIPSInstruction> &v, string d ,MainWindow* m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunWindow),parentPointer(m)
{
    ui->setupUi(this);

    cpu = c;
    instructions = v;

    rowCount = 0;
    offset = 0;
    Running = true;
    const int column = 100;
    data = d;

    QStringList myHeader;
    ui->TimeDiagram->setColumnCount(column);
    myHeader << "Instructions";
    for( int i=0; i<= column; ++i)
        myHeader << QString::number(i+1);

    ui->TimeDiagram->setHorizontalHeaderLabels(myHeader);
}

RunWindow::~RunWindow()
{
    delete ui;
}

void RunWindow::on_startButton_clicked()
{
    connect( ui->stopButton, SIGNAL( clicked() ),
             this, SLOT( ) );

    ind = 0;
    while(Running){
        cpu->execute();
        string jumpError = cpu->jump.errorHandling();
        if (jumpError != "") {
                 QMessageBox::information(NULL,"",QString::fromStdString(jumpError));
                 Running = false;
        }
        regs = cpu->regFile.getRegisters();
        mem = cpu->dataMemory.getMemory();

        parentPointer->getDataPointers(regs, mem);

        instr = QString::fromStdString(cpu->instructionMemory.getInstruction());

        vector <string> tDiagrams = cpu->timingDiagram.getTimingDiagrams();

        lines.push_back(instr);

        if(tDiagrams.size() == 1) addNewInstruction(tDiagrams[0]);
        else {
            editPrevInstruction(tDiagrams[0]);
            addNewInstruction(tDiagrams[1]);
        }

        ++ind;
        QApplication::processEvents();
        if(!Running){
            break;
        }
    }

    ui->TimeDiagram->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void RunWindow::addNewInstruction(string str){
    for(int i = 1; i <= offset; ++i){
        ui->TimeDiagram->setItem(rowCount,i, new QTableWidgetItem(" "));
    }

    ui->TimeDiagram->insertRow(ui->TimeDiagram->rowCount());

    ui->TimeDiagram->setItem(rowCount,0, new QTableWidgetItem(lines[ind]));

    for( int i = 0 + offset; i < str.length() + offset; ++i){
        ui->TimeDiagram->setItem(rowCount,i+1, new QTableWidgetItem(QString::fromStdString(getStage(str[i-offset]))));
        ui->TimeDiagram->resizeColumnsToContents();

    }

    ++rowCount;
    ++offset;
}
void RunWindow::editPrevInstruction(string str){
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
string RunWindow::getStage(char st){
    if( st == 'F') return "F";
    else if(st == 'D') return "D";
    else if (st == 'E') return "E";
    else if(st == 'M') return "M";
    else if( st == 'W') return "W";
    else if( st == 'N') return " ";
    return "";
}

void RunWindow::on_saveButton_clicked()
{
    QString fileStart = "Code Section:\n\n\n\n";
    QString code = QString::fromStdString(data);
    QString tDiagram = "1 - Time Diagram:";
    QString bDiagram = "2 - Branch Table:";
    QString memString = "4 - Memory:";
    QPixmap pixmap(ui->TimeDiagram->size());
    ui->TimeDiagram->render(&pixmap);

    QString path = "/Users/bahermursi/Desktop/MyReport.pdf";
    QPdfWriter writer(path);
    writer.setResolution(QPrinter::ScreenResolution);
    QPainter painter(&writer);

    int diagrampos = 500;

    QFont font;
    font.setBold(true);
    font.setPointSize(16);


    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageOrientation(QPageLayout::Portrait);
    painter.setPen(Qt::black);

    painter.drawPixmap(QRect(0,0,writer.logicalDpiX()*7.8,writer.logicalDpiY()*9.5), QPixmap(":/Images/Pic/Untitled.jpg"));
    writer.newPage();
    painter.setFont(font);
    painter.drawText(100,100,fileStart);
    for(int i = 0; i < lines.size(); ++i)
        painter.drawText(300, 700 + 300*i, lines[i]);
    writer.newPage();

    painter.drawText(100,100,tDiagram);
    painter.drawPixmap(500,diagrampos,writer.width()- 100, writer.height()/2,pixmap);
    writer.newPage();

//    painter.drawText(100,100,bDiagram);
//    painter.drawPixmap(500,diagrampos,writer.width()- 100, writer.height()/2,pixmap);
//    writer.newPage();

    painter.drawText(700,1200 + 300,"Registers:"); painter.drawText(4000,1200 + 300,"Memory:");
    for(int i = 0; i < 32; ++i){
        registers = "reg $" + QString::number(i) + " = " + QString::number(regs[i]);
        painter.drawText(700,2000 + 300*i,registers);
        memory = "mem["+ QString::number(i)+"]" + " = " +QString::number(mem[i]);
        painter.drawText(4500,2000 + 300*i,memory);
    }

    QMessageBox::information(NULL,"Hi!","Report have been generated successfully!");
}

void RunWindow::on_stopButton_clicked()
{
    Running = false;
}


