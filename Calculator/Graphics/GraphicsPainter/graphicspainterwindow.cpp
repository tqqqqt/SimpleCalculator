#include "graphicspainterwindow.h"
#include "ui_graphicspainterwindow.h"

GraphicsPainterWindow::GraphicsPainterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsPainterWindow)
{
    ui->setupUi(this);
}

GraphicsPainterWindow::~GraphicsPainterWindow()
{
    delete ui;
}

void GraphicsPainterWindow::needClose(){
    this->close();
}

void GraphicsPainterWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    event->accept();
}
