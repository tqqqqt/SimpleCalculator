#include "programmistsettingswindow.h"
#include "ui_programmistsettingswindow.h"

ProgrammistSettingsWindow::ProgrammistSettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgrammistSettingsWindow)
{
    ui->setupUi(this);

    QSettings settings("tqqqqt","calculator");
    ui->spinBox_acu->setValue(settings.value("progr/acuracy",10).toInt());
    ui->spinBox_count->setValue(settings.value("progr/count",5).toInt());

    this->connect(ui->pushButton_accept,SIGNAL(clicked()),this,SLOT(buttonAccept()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(buttonClose()));
}

ProgrammistSettingsWindow::~ProgrammistSettingsWindow()
{
    delete ui;
}

void ProgrammistSettingsWindow::buttonAccept(){
    QSettings settings("tqqqqt","calculator");
    settings.setValue("progr/acuracy",ui->spinBox_acu->value());
    settings.setValue("progr/count",ui->spinBox_count->value());
    emit acceptSettings();
    this->close();
}

void ProgrammistSettingsWindow::buttonClose(){
    this->close();
}
