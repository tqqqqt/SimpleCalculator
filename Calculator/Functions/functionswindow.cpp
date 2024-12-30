#include "functionswindow.h"
#include "ui_functionswindow.h"

FunctionsWindow::FunctionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionsWindow)
{
    ui->setupUi(this);

    this->connect(ui->pushButton_sin,&QPushButton::clicked,[this]{ pressButtons("Sin("); });
    this->connect(ui->pushButton_cos,&QPushButton::clicked,[this]{ pressButtons("Cos("); });
    this->connect(ui->pushButton_tng,&QPushButton::clicked,[this]{ pressButtons("Tng("); });
    this->connect(ui->pushButton_ctng,&QPushButton::clicked,[this]{ pressButtons("Ctng("); });
}

FunctionsWindow::~FunctionsWindow()
{
    delete ui;
}

void FunctionsWindow::pressButtons(QString _function){
    emit pressFunction(_function);
}

void FunctionsWindow::closeWindow(){
    this->close();
}
