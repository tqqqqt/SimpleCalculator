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

    // clear_ord it's pixmap for display ord and points without graphics
    // curent_ord it's pixmap with graphics
    clear_ord=curent_ord;
    ui->label->setPixmap(curent_ord);
    paintGraphics();

    // pluss and minus buttons
    this->connect(ui->pushButton_pluss,SIGNAL(clicked()),this,SLOT(addScale()));
    this->connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(minusScale()));

    // signals
    this->connect(this,SIGNAL(needPaintOrd()),this,SLOT(paintMainOrd()));
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
    emit closeWindow();
    event->accept();
}

// paint X and Y ord without points num
void GraphicsPainterWindow::paintMainOrd(){
    // get window and buttons height to calculate free space for pixmap
    int window_height=height(), buttons_height=ui->frame->height()+20;
    // picture size
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
    emit needPaintOrd();
    emit needPaintPoints();

    clear_ord=curent_ord;
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

    emit needClearGraphics();
    emit needUpdatePicture();
}

// change picture scale to minus one
void GraphicsPainterWindow::minusScale(){
    if(curent_scale<=1) return; // don't use dot nums like 0.5
    curent_scale-=1;

    emit needClearGraphics();
    emit needUpdatePicture();
}

// paint all graphics in elements on screen or create and save graphics on element and display on screen
void GraphicsPainterWindow::paintGraphics(){
    curent_ord=clear_ord;
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
            painter.drawPixmap(curent_ord.rect(),element.getGraphic(),element.getGraphic().rect());
            continue;
        }

        std::vector<std::string> result_left, result_right; // maybe need rewrite to save memory?
        CalculatorObject temp_result;
        math_object.setPolishEntry(element.getPolishEntry());

        // move to right X ord
        double curent_point=0;
        for(int i=0;i<width/2;i+=POINT_SPACE/10){
            try{
                if(i%POINT_SPACE==0) curent_point=round(curent_point);
                temp_result=math_object.getResultWithVariable(curent_point);
                result_right.push_back(temp_result.toString());
            }
            catch(std::exception){
                // skip exception and point
            }
            curent_point+=0.1*curent_scale;
        }

        // move to left X ord
        curent_point=0;
        for(int i=0;i<width/2;i+=POINT_SPACE/10){
            try{
                if(i%POINT_SPACE==0) curent_point=round(curent_point);
                temp_result=math_object.getResultWithVariable(curent_point);
                result_left.push_back(temp_result.toString());
            }
            catch(std::exception){
                // skip exception and point
            }
            curent_point-=0.1*curent_scale;
        }

        // prepate pixmap
        QPixmap new_graphic(width,height);
        new_graphic.fill(Qt::transparent);
        QPainter temp_painter(&new_graphic);
        temp_painter.setPen(QPen(Qt::black,1));

        // paint new graphic
        double next_point=0.0, curent_y=0.0, next_y=0.0;
        // paint right part X ord
        curent_point=0.0;
        for(int i=0;i<result_right.size()-1;i++){
            // check if curent or next point is skip point
            if(result_right[i]=="S" || result_right[i+1]=="S") continue;

            // change ',' to '.' for stod
            if(result_right[i].find(',')!=std::string::npos) result_right[i][result_right[i].find(',')]='.';
            if(result_right[i+1].find(',')!=std::string::npos) result_right[i+1][result_right[i+1].find(',')]='.';

            next_point=curent_point+POINT_SPACE/10;
            curent_y=(POINT_SPACE*std::stod(result_right[i]))/curent_scale;
            next_y=(POINT_SPACE*std::stod(result_right[i+1]))/curent_scale;
            temp_painter.drawLine(width/2+curent_point,height/2-curent_y,width/2+next_point,height/2-next_y);
            curent_point+=POINT_SPACE/10;
        }

        // paint left part X ord
        curent_point=0.0;
        for(int i=0;i<result_left.size()-1;i++){
            // check if curent or next point is skip point
            if(result_left[i]=="S" || result_left[i+1]=="S") continue;

            // change ',' to '.' for stod
            if(result_left[i].find(',')!=std::string::npos) result_left[i][result_left[i].find(',')]='.';
            if(result_left[i+1].find(',')!=std::string::npos) result_left[i+1][result_left[i+1].find(',')]='.';

            next_point=curent_point-POINT_SPACE/10;
            curent_y=(POINT_SPACE*std::stod(result_left[i]))/curent_scale;
            next_y=(POINT_SPACE*std::stod(result_left[i+1]))/curent_scale;
            temp_painter.drawLine(width/2+curent_point,height/2-curent_y,width/2+next_point,height/2-next_y);
            curent_point-=POINT_SPACE/10;
        }

        // added to element and window
        element.setGraphic(new_graphic);
        painter.drawPixmap(curent_ord.rect(),new_graphic,new_graphic.rect());
    }

    // set complete picture on screen
    ui->label->setPixmap(curent_ord);
}
