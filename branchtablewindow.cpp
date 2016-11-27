#include "branchtablewindow.h"
#include "ui_branchtablewindow.h"
#include <iostream>
using namespace std;
BranchTableWindow::BranchTableWindow(const std::map<int, std::pair<int, int> >& b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BranchTableWindow)
{
    ui->setupUi(this);
    QStringList myHeader;
    ui->BranchDiagram->setColumnCount(3);
    myHeader << "PC Address"<<"Target Address" <<"States";
    ui->BranchDiagram->resizeRowsToContents();

    ui->BranchDiagram->setHorizontalHeaderLabels(myHeader);

    std::map<int, std::pair<int, int> >::const_iterator it = b.begin();
    int i = 0;
    for(it; it != b.end(); ++it){
        ui->BranchDiagram->insertRow(ui->BranchDiagram->rowCount());
        ui->BranchDiagram->setItem(i, 0,new QTableWidgetItem(QString::number((*it).first)));
        std::pair<int,int> p = (*it).second;
        ui->BranchDiagram->setItem(i, 1,new QTableWidgetItem( QString::number(p.first) ));
        ui->BranchDiagram->setItem(i, 2,new QTableWidgetItem( QString::number(p.second) ));
        ++i;
    }
      ui->BranchDiagram->update();

}

BranchTableWindow::~BranchTableWindow()
{
    delete ui;
}
