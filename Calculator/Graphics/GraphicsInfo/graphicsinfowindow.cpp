#include "graphicsinfowindow.h"
#include "ui_graphicsinfowindow.h"

GraphicsInfoWindow::GraphicsInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsInfoWindow)
{
    ui->setupUi(this);

    painter_window=new GraphicsPainterWindow();
    painter_window->show();
    painter_window_open=true;

    // painter window connects
    this->connect(this,SIGNAL(closeWindow()),painter_window,SLOT(needClose()));
    this->connect(painter_window,SIGNAL(closeWindow()),this,SLOT(updatePainterWindowState()));

    // mode button
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));

    // options and re-open painter
    this->connect(ui->action_open_painter,SIGNAL(triggered()),this,SLOT(openPainter()));
}

GraphicsInfoWindow::~GraphicsInfoWindow()
{
    delete ui;
}

void GraphicsInfoWindow::buttonChangeMode(){
    ModeWindow *mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));
    mode_window->exec();
}

void GraphicsInfoWindow::updateMode(int _mode){
    if(_mode==4) return;

    //

    emit closeWindow();
    emit changeWindow(_mode);
    this->hide();
}

void GraphicsInfoWindow::updatePainterWindowState(){
    painter_window_open=false;
}

void GraphicsInfoWindow::openPainter(){
    if(painter_window_open==true) return;
    painter_window=new GraphicsPainterWindow();
    painter_window_open=true;

    this->connect(this,SIGNAL(closeWindow()),painter_window,SLOT(needClose()));
    this->connect(painter_window,SIGNAL(closeWindow()),this,SLOT(updatePainterWindowState()));

    painter_window->show();
}
