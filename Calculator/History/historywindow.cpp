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

    memory=_history;

    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(*memory)));
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

// Update history list when get signal from calculator
void HistoryWindow::UpdateHis(){
    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(*memory)));
}

// Close window when calculcator window mode change
void HistoryWindow::closeWindow(){
    this->close();
}
