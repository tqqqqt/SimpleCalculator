#include "programmistsettingswindow.h"
#include "ui_programmistsettingswindow.h"

ProgrammistSettingsWindow::ProgrammistSettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgrammistSettingsWindow)
{
    ui->setupUi(this);

    QSettings settings("tqqqqt","calculator");
    ui->spinBox_count->setValue(settings.value("progr/count",5).toInt());

    this->connect(ui->pushButton_accept,SIGNAL(clicked()),this,SLOT(buttonAccept()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(buttonClose()));
}

ProgrammistSettingsWindow::~ProgrammistSettingsWindow()
{
    delete ui;
}

// Save new settings and emit signal to calculator
void ProgrammistSettingsWindow::buttonAccept(){
    // open PC settings and save changes
    QSettings settings("tqqqqt","calculator");
    settings.setValue("progr/count",ui->spinBox_count->value());

    // emit signal to main window to load new settings
    emit acceptSettings();
    this->close();
}

// Regect change settings and close window
void ProgrammistSettingsWindow::buttonClose(){
    this->close();
}
