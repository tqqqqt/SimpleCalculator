#include "functionswindow.h"
#include "ui_functionswindow.h"

FunctionsWindow::FunctionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionsWindow)
{
    loadStyle();
    ui->setupUi(this);

    // buttons connects
    this->connect(ui->pushButton_sin,&QPushButton::clicked,[this]{ pressButtons("Sin("); });
    this->connect(ui->pushButton_cos,&QPushButton::clicked,[this]{ pressButtons("Cos("); });
    this->connect(ui->pushButton_tng,&QPushButton::clicked,[this]{ pressButtons("Tng("); });
    this->connect(ui->pushButton_ctng,&QPushButton::clicked,[this]{ pressButtons("Ctng("); });
    this->connect(ui->pushButton_fact,&QPushButton::clicked,[this]{ pressButtons("!"); });
    this->connect(ui->pushButton_mod,&QPushButton::clicked,[this]{ pressButtons("mod"); });
    this->connect(ui->pushButton_module,&QPushButton::clicked,[this]{ pressButtons("Module("); });
    this->connect(ui->pushButton_round_up,&QPushButton::clicked,[this]{ pressButtons("RoundUp("); });
    this->connect(ui->pushButton_round_down,&QPushButton::clicked,[this]{ pressButtons("RoundDown("); });
}

FunctionsWindow::~FunctionsWindow()
{
    delete ui;
}

// Load css style from main_style.css file
void FunctionsWindow::loadStyle(){
    // main style for window
    QFile file(":/Functions/functions_style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();

    this->setStyleSheet(content);
}

// Send to calculator what function selected
void FunctionsWindow::pressButtons(const QString& _function){
    // special functions
    // becouse factorial not need brackets, mod use like operators
    if(_function=="!" || _function=="mod") emit pressSpecialFunction(_function);
    else emit pressFunction(_function);
}

// Close window when calculator window mode change
void FunctionsWindow::needCloseWindow(){
    this->close();
}

// Send signal to calculator to change state and close window
void FunctionsWindow::closeEvent(QCloseEvent *event){
    // signal to main window to change status of window
    emit updateWindowState();

    event->accept();
}
