#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeWindow)
{
    ui->setupUi(this);
    this->connect(ui->pushButton_calc,&QPushButton::clicked,[this]{ buttonMode(1); });
    this->connect(ui->pushButton_val,&QPushButton::clicked,[this]{ buttonMode(2); });
    this->connect(ui->pushButton_prog,&QPushButton::clicked,[this]{ buttonMode(3); });
}

ModeWindow::~ModeWindow()
{
    delete ui;
}

// Save and send to calculator selected mode
void ModeWindow::buttonMode(int _mode){
    QSettings settings("tqqqqt","calculator");
    settings.setValue("calc/mode",_mode);

    emit changeMode(_mode);
    this->close();
}
