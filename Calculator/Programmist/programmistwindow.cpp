#include "programmistwindow.h"
#include "ui_programmistwindow.h"

ProgrammistWindow::ProgrammistWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammistWindow)
{
    ui->setupUi(this);
}

ProgrammistWindow::~ProgrammistWindow()
{
    delete ui;
}
