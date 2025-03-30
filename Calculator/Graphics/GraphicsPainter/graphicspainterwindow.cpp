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
    loadStyle();
    ui->setupUi(this);

    curent_new_color=0;
    curent_scale=1;
    info_objects=_arr;

    // clear_ord it's pixmap for display only ord
    // clear_ord_with_point it's pixmap ord and point then always update when change scale
    // curent_ord it's pixmap with graphics

    // create clean main ord
    clear_ord=paintMainOrd();
    // set clean ord as curent and add points
    curent_ord=clear_ord;
    paintPoints();
    // save ord with points in variable
    clear_ord_with_point=curent_ord;
    ui->label->setPixmap(curent_ord);
    paintGraphics();

    // set minimum size to move graphics size
    ui->label->setMinimumSize(1,1);

    // pluss and minus buttons
    this->connect(ui->pushButton_pluss,SIGNAL(clicked()),this,SLOT(addScale()));
    this->connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(minusScale()));

    // signals
    this->connect(this,SIGNAL(needPaintPoints()),this,SLOT(paintPoints()));
    this->connect(this,SIGNAL(needUpdatePicture()),this,SLOT(updatePicture()));
    this->connect(this,SIGNAL(needClearGraphics()),this,SLOT(clearGraphics()));
}

GraphicsPainterWindow::~GraphicsPainterWindow()
{
    delete ui;
}

// function close window if close main graphics window
void GraphicsPainterWindow::needClose(){
    this->close();
}

// function do something before close window
void GraphicsPainterWindow::closeEvent(QCloseEvent *event){
    // close all child windows
    emit closeWindow();
    event->accept();
}

// function do something after resize window
void GraphicsPainterWindow::resizeEvent(QResizeEvent *event){
    event->accept();

    // rewrite clear ord
    clear_ord=paintMainOrd();
    // add points and draw graphics
    emit needClearGraphics();
    emit needUpdatePicture();
}

// load window style
void GraphicsPainterWindow::loadStyle(){
    QFile file(":/Graphics/GraphicsPainter/style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();

    this->setStyleSheet(content);
}

// paint X and Y ord without points num
QPixmap GraphicsPainterWindow::paintMainOrd(){
    // get window and buttons height to calculate free space for pixmap
    int window_height=height(), buttons_height=ui->frame->height()+20;
    // picture size
    int height=window_height-buttons_height, width=QWidget::width()-8;

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black,1));

    // main ord
    // X ord
    painter.drawLine(0,height/2,width,height/2);
    painter.drawLine(width,height/2,width-10,height/2-10);
    painter.drawLine(width,height/2,width-10,height/2+10);

    // Y ord
    painter.drawLine(width/2,0,width/2,height);
    painter.drawLine(width/2,0,width/2-10,10);
    painter.drawLine(width/2,0,width/2+10,10);

    // points hiden lines
    for(int i=0;i<width/2;i+=POINT_SPACE/10){
        // more thick line on 0.5, thin on 0.1
        if(i%(POINT_SPACE/2)==0) painter.setPen(QPen(Qt::gray,0.3));
        else painter.setPen(QPen(Qt::gray,0.1));
        // x right side
        painter.drawLine(width/2+i,0,width/2+i,height);
        // x left side
        painter.drawLine(width/2-i,0,width/2-i,height);
        // y up side
        painter.drawLine(0,height/2-i,width,height/2-i);
        // y down side
        painter.drawLine(0,height/2+i,width,height/2+i);
    }

    return pixmap;
}

// paint points on already done ord
void GraphicsPainterWindow::paintPoints(){
    QPainter painter(&curent_ord);
    painter.setPen(QPen(Qt::black,1));
    int width=curent_ord.width(), height=curent_ord.height();

    // points on X ord
    for(int i=POINT_SPACE;i<width/2;i+=POINT_SPACE){
        // right points
        painter.drawLine(width/2+i,height/2-5,width/2+i,height/2+5);
        painter.drawText(width/2+i-4,height/2+16,QString::fromStdString(std::to_string((i/POINT_SPACE)*curent_scale)));
        //left points
        painter.drawLine(width/2-i,height/2-5,width/2-i,height/2+5);
        painter.drawText(width/2-i-4,height/2+16,QString::fromStdString(std::to_string(((i/POINT_SPACE)*curent_scale)*-1)));
    }

    // point on Y ord
    for(int i=POINT_SPACE;i<height/2;i+=POINT_SPACE){
        // upper points
        painter.drawLine(width/2-5,height/2-i,width/2+5,height/2-i);
        painter.drawText(width/2-17,height/2-i+4,QString::fromStdString(std::to_string((i/POINT_SPACE)*curent_scale)));
        // bottom points
        painter.drawLine(width/2-5,height/2+i,width/2+5,height/2+i);
        painter.drawText(width/2-17,height/2+i+4,QString::fromStdString(std::to_string(((i/POINT_SPACE)*curent_scale)*-1)));
    }
}

// update picture when change scale
void GraphicsPainterWindow::updatePicture(){
    curent_ord=clear_ord;

    emit needPaintPoints();

    clear_ord_with_point=curent_ord;
    ui->label->setPixmap(curent_ord);
    paintGraphics();
}

// clear elements graphics when change scale
void GraphicsPainterWindow::clearGraphics(){
    for(GraphicsInfoObject& element: *info_objects){
        element.clearGraphic();
    }
}

// change picture scale to pluss one
void GraphicsPainterWindow::addScale(){
    if(curent_scale>=20) return; // more then 20 scale it's big nums
    curent_scale+=1;

    // emit signal to delete graphics in all info objects
    emit needClearGraphics();
    // emit signal to draw new paint whis new scale
    emit needUpdatePicture();
}

// change picture scale to minus one
void GraphicsPainterWindow::minusScale(){
    if(curent_scale<=1) return; // don't use dot nums like 0.5
    curent_scale-=1;

    // emit signal to delete graphics in all info objects
    emit needClearGraphics();
    // emit signal to draw new paint whis new scale
    emit needUpdatePicture();
}

// return color for new graphics
Qt::GlobalColor GraphicsPainterWindow::getNewColor(){
    curent_new_color=(curent_new_color+1)%7;
    switch (curent_new_color) {
    default: case 0:
        return Qt::GlobalColor::darkRed;
    case 1:
        return Qt::GlobalColor::darkBlue;
    case 2:
        return Qt::GlobalColor::darkGray;
    case 3:
        return Qt::GlobalColor::darkGreen;
    case 4:
        return Qt::GlobalColor::darkMagenta;
    case 5:
        return Qt::GlobalColor::darkCyan;
    case 6:
        return Qt::GlobalColor::darkYellow;
    }
}

// paint all graphics in elements on screen or create and save graphics on element and display on screen
void GraphicsPainterWindow::paintGraphics(){
    // set pixmap with points as curent ord
    curent_ord=clear_ord_with_point;
    // if no objects in graphics
    if(info_objects->size()==0){
        ui->label->setPixmap(curent_ord);
        return;
    }

    // paint size
    int width=curent_ord.width(), height=curent_ord.height();
    QPainter painter(&curent_ord);
    CalculatorMath math_object;
    math_object.setFunctionAccuracy(10); // if set more can freez
    math_object.SetDivAccuracy(4); // no need very big accuracy, not seen in graphics
    math_object.setFunctionRadianFlag(true); // all points already in radian

    // paint graphics of all elements
    for(GraphicsInfoObject& element: *info_objects){
        // if graphics already paint do not rewrite and set on screen
        if(element.getGraphicFlag()==true){
            painter.setPen(QPen(element.getGraphicsColor(),1));
            painter.drawPixmap(curent_ord.rect(),element.getGraphic(),element.getGraphic().rect());
            continue;
        }

        // object to collect results after calculate
        CalculatorObject temp_result;
        math_object.setPolishEntry(element.getPolishEntry());

        // create new pixmap
        QPixmap new_graphic(width,height);
        new_graphic.fill(Qt::transparent);
        Qt::GlobalColor new_color;
        // if color already set in object use or set new color
        if(element.getColorFlag()==false) new_color=getNewColor();
        else new_color=element.getGraphicsColor();
        QPainter temp_painter(&new_graphic);
        temp_painter.setPen(QPen(new_color,1));

        // save last known point
        int last_x=0.0, last_y=0.0;
        int curent_y=0;
        // create two part of num becouse double have trouble with accuracy
        // trouble like 2.0000000001 or 1.999999999999
        int whole_num_part=0, fractional_num_part=0, curent_step=1*curent_scale;
        // full num use to set in math
        std::string full_num="";
        // move to right X ord
        for(int curent_x=0, count_points=0;curent_x<width/2;curent_x+=POINT_SPACE/10){
            try{
                // collect two variable in one num
                if(fractional_num_part==0) full_num=std::to_string(whole_num_part);
                else full_num=std::to_string(whole_num_part)+','+std::to_string(fractional_num_part);
                // calculate result
                temp_result=math_object.getResultWithVariable(full_num);

                std::string string_result=temp_result.toString();
                // change to dot becouse std::stod dont know what is it
                if(string_result.find(',')!=std::string::npos) string_result[string_result.find(',')]='.';
                curent_y=static_cast<int>(std::round((POINT_SPACE*std::stod(string_result))/curent_scale));

                // need count point > 0 for not draw line from 0,0 point in ord
                if(count_points>0){
                    temp_painter.drawLine(width/2+last_x,height/2-last_y,width/2+curent_x,height/2-curent_y);
                }

                // save last coords
                last_x=curent_x;
                last_y=curent_y;
                // count curent points
                count_points+=1;
            }
            catch(std::exception){
                // skip exception and point
            }
            fractional_num_part+=curent_step;
            // round num, nums only one digit after dot
            if(fractional_num_part>=10){
                whole_num_part+=1;
                fractional_num_part%=10;
            }
        }

        last_x=0;
        last_y=0;
        whole_num_part=0;
        fractional_num_part=0;
        // move to left X ord
        for(int curent_x=0, count_points=0;curent_x<width/2;curent_x+=POINT_SPACE/10){
            try{
                // collect all num
                if(fractional_num_part==0) full_num='-'+std::to_string(whole_num_part);
                else full_num='-'+std::to_string(whole_num_part)+','+std::to_string(fractional_num_part);
                // calculate result
                temp_result=math_object.getResultWithVariable(full_num);

                std::string string_result=temp_result.toString();
                // change becouse std::stod
                if(string_result.find(',')!=std::string::npos) string_result[string_result.find(',')]='.';
                curent_y=static_cast<int>(std::round((POINT_SPACE*std::stod(string_result))/curent_scale));

                // need count point > 0 for not draw line from 0,0 point in ord
                if(count_points>0){
                    temp_painter.drawLine(width/2-last_x,height/2-last_y,width/2-curent_x,height/2-curent_y);
                }

                // save last coords
                last_x=curent_x;
                last_y=curent_y;
                // count points
                count_points+=1;
            }
            catch(std::exception){
                // skip exception and point
            }
            fractional_num_part+=curent_step;
            // num have only one num after dote
            if(fractional_num_part>=10){
                whole_num_part+=1;
                fractional_num_part%=10;
            }
        }

        // added pixmap to element and window
        element.setGraphic(new_graphic);
        element.setGraphicsColor(new_color);
        painter.drawPixmap(curent_ord.rect(),new_graphic,new_graphic.rect());
    }

    // set complete picture on screen
    ui->label->setPixmap(curent_ord);
}
