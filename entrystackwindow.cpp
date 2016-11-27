#include "entrystackwindow.h"
#include "ui_entrystackwindow.h"
#include <iostream>
EntryStackWindow::EntryStackWindow(CPU *cpu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryStackWindow)
{
    ui->setupUi(this);

    QStringList myHeader;
    ui->stackTable->setColumnCount(1);
    myHeader << "Address";
    ui->stackTable->setHorizontalHeaderLabels(myHeader);

   std::stack<int> eStack = cpu->jump.getStack();

    for( int i = 0; i < eStack.size() ; ++i){
        ui->stackTable->insertRow(ui->stackTable->rowCount());
        int x = eStack.top();
        ui->stackTable->setItem(i,0, new QTableWidgetItem(QString::number(x)));
                eStack.pop();
        ui->stackTable->resizeColumnsToContents();
        std::cout << "Entered";
    }

}

EntryStackWindow::~EntryStackWindow()
{
    delete ui;
}
