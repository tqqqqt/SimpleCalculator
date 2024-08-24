#include "historywindow.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
}

HistoryWindow::HistoryWindow(const QVector<QString>& _history, QWidget* parent):QMainWindow (parent),ui(new Ui::HistoryWindow){
    ui->setupUi(this);
    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(_history)));
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}
