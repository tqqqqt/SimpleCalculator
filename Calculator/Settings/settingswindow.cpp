#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->connect(ui->pushButton_accept,SIGNAL(clicked()),this,SLOT(buttonAccept()));
    this->connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(buttonClose()));

    QSettings settings("tqqqqt","calculator");
    ui->spinBox->setValue(settings.value("calc/acuracy").toInt());
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::buttonAccept(){
    QSettings settings("tqqqqt","calculator");
    settings.setValue("calc/acuracy",ui->spinBox->value());
    emit acceptSettings();
    this->close();
}

void SettingsWindow::buttonClose(){
    this->close();
}
