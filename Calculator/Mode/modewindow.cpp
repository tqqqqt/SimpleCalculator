#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeWindow)
{
    ui->setupUi(this);

    // buttons connect
    // calculator mode
    this->connect(ui->pushButton_calc,&QPushButton::clicked,[this]{ buttonMode(1); });
    // value mode
    this->connect(ui->pushButton_val,&QPushButton::clicked,[this]{ buttonMode(2); });
    // programmist mode
    this->connect(ui->pushButton_prog,&QPushButton::clicked,[this]{ buttonMode(3); });
    // graphics mode
    this->connect(ui->pushButton_graphics,&QPushButton::clicked,[this]{ buttonMode(4); });
}

ModeWindow::~ModeWindow()
{
    delete ui;
}

// Save and send to calculator selected mode
void ModeWindow::buttonMode(const int& _mode){
    // open PC settings and save changes
    QSettings settings("tqqqqt","calculator");
    settings.setValue("calc/mode",_mode);

    // emit signal to main window to change mode in window
    emit changeMode(_mode);
    this->close();
}
