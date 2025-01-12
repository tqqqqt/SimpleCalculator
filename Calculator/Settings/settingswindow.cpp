#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    // open PC settings and load curent settings
    QSettings settings("tqqqqt","calculator");
    ui->spinBox_div_acuracy->setValue(settings.value("calc/acuracy").toInt());
    ui->spinBox_function_acuracy->setValue(settings.value("calc/func_acuracy").toInt());

    // buttons connect
    this->connect(ui->pushButton_accept,SIGNAL(clicked()),this,SLOT(buttonAccept()));
    this->connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(buttonClose()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

// Save in settings new value and emit signal to calculator
void SettingsWindow::buttonAccept(){
    // open settings and load changes
    QSettings settings("tqqqqt","calculator");
    settings.setValue("calc/acuracy",ui->spinBox_div_acuracy->value());
    settings.setValue("calc/func_acuracy",ui->spinBox_function_acuracy->value());

    // emit signal to main window to load new settings
    emit acceptSettings();
    this->close();
}

// Regect change settings
void SettingsWindow::buttonClose(){
    this->close();
}
