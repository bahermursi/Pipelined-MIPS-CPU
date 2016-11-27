#ifndef BRANCHTABLEWINDOW_H
#define BRANCHTABLEWINDOW_H

#include <QDialog>

namespace Ui {
class BranchTableWindow;
}

class BranchTableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BranchTableWindow(const std::map<int, std::pair<int, int> >&, QWidget *parent = 0);
    ~BranchTableWindow();

private:
    Ui::BranchTableWindow *ui;
    std::map<int, std::pair<int, int> > branchTable;
};

#endif // BRANCHTABLEWINDOW_H
