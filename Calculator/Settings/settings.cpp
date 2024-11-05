#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->connect(ui->pushButton_accept,SIGNAL(clicked()),this,SLOT(buttonAccept()));
    this->connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(buttonClose()));

    QSettings settings("tqqqqt","calculator");
    ui->spinBox->setValue(settings.value("calc/acuracy").toInt());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::buttonAccept(){
    QSettings settings("tqqqqt","calculator");
    settings.setValue("calc/acuracy",ui->spinBox->value());
    emit acceptSettings();
    this->close();
}

void Settings::buttonClose(){
    this->close();
}
