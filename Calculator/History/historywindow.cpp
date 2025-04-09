#include "historywindow.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
}

HistoryWindow::HistoryWindow(QVector<QString>* _history, QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);

    // save address of vector to show in window
    memory=_history;

    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(*memory)));
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

// Update history list when get signal from calculator
void HistoryWindow::updateHis(){
    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(*memory)));
}

// Close window when calculcator window mode change
void HistoryWindow::needCloseWindow(){
    this->close();
}

// Send signal to calculator for change state and close window
void HistoryWindow::closeEvent(QCloseEvent *event){
    // emit signal to main window to change window state
    emit updateWindowState();

    event->accept();
}
