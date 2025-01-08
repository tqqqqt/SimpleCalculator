#include "graphicspainterwindow.h"
#include "ui_graphicspainterwindow.h"

GraphicsPainterWindow::GraphicsPainterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsPainterWindow)
{
    ui->setupUi(this);
}

GraphicsPainterWindow::GraphicsPainterWindow(QVector<GraphicsInfoObject> *_arr, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::GraphicsPainterWindow)
{
    ui->setupUi(this);

    curent_scale=1;
    info_objects=_arr;
    paintMainOrd();
    paintPoints();

    ui->label->setPixmap(curent_ord);

    // pluss and minus buttons
    this->connect(ui->pushButton_pluss,SIGNAL(clicked()),this,SLOT(addScale()));
    this->connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(minusScale()));

    // signals
    this->connect(this,SIGNAL(needPaintOrd()),this,SLOT(paintMainOrd()));
    this->connect(this,SIGNAL(needPaintPoints()),this,SLOT(paintPoints()));
    this->connect(this,SIGNAL(needUpdatePicture()),this,SLOT(updatePicture()));
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

void GraphicsPainterWindow::paintMainOrd(){
    int window_height=height(),buttons_height=ui->frame->height()+20;
    int height=window_height-buttons_height, width=QWidget::width()-8;

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black,1));

    // X ord
    painter.drawLine(0,height/2,width,height/2);
    painter.drawLine(width,height/2,width-10,height/2-10);
    painter.drawLine(width,height/2,width-10,height/2+10);

    // Y ord
    painter.drawLine(width/2,0,width/2,height);
    painter.drawLine(width/2,0,width/2-10,10);
    painter.drawLine(width/2,0,width/2+10,10);

    curent_ord=pixmap;
}

void GraphicsPainterWindow::paintPoints(){
    QPainter painter(&curent_ord);
    painter.setPen(QPen(Qt::black,1));
    int points_space=30, width=curent_ord.width(), height=curent_ord.height();
    // points on X ord
    for(int i=points_space;i<width/2;i+=points_space){
        // right points
        painter.drawLine(width/2+i,height/2-5,width/2+i,height/2+5);
        painter.drawText(width/2+i-4,height/2+16,QString::fromStdString(std::to_string((i/points_space)*curent_scale)));
        //left points
        painter.drawLine(width/2-i,height/2-5,width/2-i,height/2+5);
        painter.drawText(width/2-i-4,height/2+16,QString::fromStdString(std::to_string(((i/points_space)*curent_scale)*-1)));
    }

    // point on Y ord
    for(int i=points_space;i<height/2;i+=points_space){
        // upper points
        painter.drawLine(width/2-5,height/2-i,width/2+5,height/2-i);
        painter.drawText(width/2-17,height/2-i+4,QString::fromStdString(std::to_string((i/points_space)*curent_scale)));
        //bottom points
        painter.drawLine(width/2-5,height/2+i,width/2+5,height/2+i);
        painter.drawText(width/2-17,height/2+i+4,QString::fromStdString(std::to_string(((i/points_space)*curent_scale)*-1)));
    }
}

void GraphicsPainterWindow::updatePicture(){
    emit needPaintOrd();
    emit needPaintPoints();

    ui->label->setPixmap(curent_ord);
}

void GraphicsPainterWindow::addScale(){
    if(curent_scale>=20) return;
    curent_scale+=1;

    emit needUpdatePicture();
}

void GraphicsPainterWindow::minusScale(){
    if(curent_scale<=1) return;
    curent_scale-=1;

    emit needUpdatePicture();
}

void GraphicsPainterWindow::paintGraphics(){
    emit needUpdatePicture();

    if(info_objects->size()==0) return;

}
