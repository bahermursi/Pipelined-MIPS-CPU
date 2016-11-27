#ifndef ENTRYSTACKWINDOW_H
#define ENTRYSTACKWINDOW_H

#include <QDialog>
#include <CPU.h>
namespace Ui {
class EntryStackWindow;
}

class EntryStackWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EntryStackWindow(CPU*,QWidget *parent = 0);
    ~EntryStackWindow();

private:
    Ui::EntryStackWindow *ui;

};

#endif // ENTRYSTACKWINDOW_H
