#include "graphicsinfowindow.h"
#include "ui_graphicsinfowindow.h"

GraphicsInfoWindow::GraphicsInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsInfoWindow)
{
    ui->setupUi(this);

    painter_window_open=false;
    curent_text="";
    count_open_bracket=0;
    count_oper=0;

    //nums buttons
    this->connect(ui->pushButton_n0,&QPushButton::clicked,[this]{ pressNumberButton('0'); });
    this->connect(ui->pushButton_n1,&QPushButton::clicked,[this]{ pressNumberButton('1'); });
    this->connect(ui->pushButton_n2,&QPushButton::clicked,[this]{ pressNumberButton('2'); });
    this->connect(ui->pushButton_n3,&QPushButton::clicked,[this]{ pressNumberButton('3'); });
    this->connect(ui->pushButton_n4,&QPushButton::clicked,[this]{ pressNumberButton('4'); });
    this->connect(ui->pushButton_n5,&QPushButton::clicked,[this]{ pressNumberButton('5'); });
    this->connect(ui->pushButton_n6,&QPushButton::clicked,[this]{ pressNumberButton('6'); });
    this->connect(ui->pushButton_n7,&QPushButton::clicked,[this]{ pressNumberButton('7'); });
    this->connect(ui->pushButton_n8,&QPushButton::clicked,[this]{ pressNumberButton('8'); });
    this->connect(ui->pushButton_n9,&QPushButton::clicked,[this]{ pressNumberButton('9'); });

    //dot, minus and variable (X) buttons
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(buttonDot()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(buttonZnak()));
    this->connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(pressVariableButton()));

    //operator buttons and result
    this->connect(ui->pushButton_pluss,&QPushButton::clicked,[this]{ pressOperButton("+"); });
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ pressOperButton("-"); });
    this->connect(ui->pushButton_mull,&QPushButton::clicked,[this]{ pressOperButton("*"); });
    this->connect(ui->pushButton_devide,&QPushButton::clicked,[this]{ pressOperButton("/"); });
    this->connect(ui->pushButton_pow,&QPushButton::clicked,[this]{ pressOperButton("^("); });
    this->connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(buttonAdd()));

    //clear and delete last
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(buttonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(buttonDeleteLast()));

    //bracket buttons
    this->connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(buttonOpenBrackets()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(buttonCloseBrackets()));

    // delete list element, mode and functions button
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));
    this->connect(ui->pushButton_functions,SIGNAL(clicked()),this,SLOT(pressFunctionsButton()));
    this->connect(ui->pushButton_del_element,SIGNAL(clicked()),this,SLOT(deleteListElement()));

    // options and re-open painter
    this->connect(ui->action_open_painter,SIGNAL(triggered()),this,SLOT(openPainter()));

    // signals
    this->connect(this,SIGNAL(needUpdateList()),this,SLOT(updateListWidget()));
}

GraphicsInfoWindow::~GraphicsInfoWindow()
{
    delete ui;
}

void GraphicsInfoWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    event->accept();
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
    painter_window=new GraphicsPainterWindow(&info_objects);
    painter_window_open=true;

    this->connect(this,SIGNAL(closeWindow()),painter_window,SLOT(needClose()));
    this->connect(painter_window,SIGNAL(closeWindow()),this,SLOT(updatePainterWindowState()));
    this->connect(this,SIGNAL(needUpdateList()),painter_window,SLOT(paintGraphics()));

    painter_window->show();
}

void GraphicsInfoWindow::setFullText(){
    curent_text="";
    for(auto element:objects){
        curent_text+=QString::fromStdString(element.toString());
    }
    curent_text+=QString::fromStdString(curent_object.toString());
    ui->label->setText(curent_text);
}

void GraphicsInfoWindow::pressNumberButton(QChar buttonNum){
    if(curent_object.getObjectType()>CalculatorObject::ObjectsTypes::Num){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addNum(buttonNum.toLatin1());
    setFullText();
}

void GraphicsInfoWindow::pressOperButton(QString buttonOper){
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::None || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::MinusBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Operators || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Functins) return;
    if(buttonOper=='-' && curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBrackets){
        curent_object.addSymbol("-");
        setFullText();
        return;
    }
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addSymbol(buttonOper.toStdString());
    count_oper+=1;
    if(buttonOper=="^(") count_open_bracket+=1;
    setFullText();
}

void GraphicsInfoWindow::pressVariableButton(){
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Factorial || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None) objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addVariable();
    setFullText();
}

void GraphicsInfoWindow::pressFunctionsButton(){
    if(function_window_show==true) return;
    FunctionsWindow *functions_window=new FunctionsWindow();
    this->connect(functions_window,SIGNAL(pressFunction(QString)),this,SLOT(addedFunction(QString)));
    this->connect(functions_window,SIGNAL(pressSpecialFunction(QString)),this,SLOT(addedSpecialFunction(QString)));
    this->connect(this,SIGNAL(closeWindow()),functions_window,SLOT(needCloseWindow()));
    this->connect(functions_window,SIGNAL(updateWindowState()),this,SLOT(updateFunctionWindowState()));
    functions_window->show();
    function_window_show=true;
}

void GraphicsInfoWindow::addedFunction(QString _function){
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addFunction(_function.toStdString());
    count_oper+=1;
    count_open_bracket+=1;
    setFullText();
}

void GraphicsInfoWindow::addedSpecialFunction(QString _function){
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets) return;
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addFunction(_function.toStdString());
    count_oper+=1;
    setFullText();
}

void GraphicsInfoWindow::buttonDot(){
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num) return;
    curent_object.addNum(',');
    setFullText();
}

void GraphicsInfoWindow::buttonClear(){
    curent_text="";
    objects.clear();
    curent_object.clear();
    count_oper=0;
    count_open_bracket=0;
    setFullText();
}

void GraphicsInfoWindow::buttonOpenBrackets(){
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Factorial || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addSymbol("(");
    count_open_bracket+=1;
    setFullText();
}

void GraphicsInfoWindow::buttonCloseBrackets(){
    if(count_open_bracket==0) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::MinusBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::X_variable) return;
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol(")");
    count_open_bracket--;
    setFullText();
}

void GraphicsInfoWindow::buttonAdd(){
    if(curent_text.length()==0 || (curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Factorial && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::X_variable)) return;
    if(count_open_bracket || count_oper==0) return;
    QString save_text=curent_text;
    std::vector<CalculatorObject> save_polish;
    try {
        objects.push_back(curent_object);
        info_math.setVector(objects.toStdVector());
        info_math.simplifyExpression();
        save_polish=info_math.getPolishEntry();
        objects.clear();
        curent_object.clear();
        setFullText();
    }
    catch (std::exception &exp) {
        curent_text="";
        curent_object.clear();
        ui->label->setText(exp.what());
    }
    GraphicsInfoObject new_object;
    new_object.setDisplayText(save_text.toStdString());
    new_object.setPolishEntry(save_polish);
    info_objects.push_back(new_object);
    emit needUpdateList();
    count_open_bracket=0;
    count_oper=0;
}

void GraphicsInfoWindow::buttonZnak(){
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::MinusBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None) objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol("(-");
    count_open_bracket++;
    setFullText();
}

void GraphicsInfoWindow::buttonDeleteLast(){
    if(curent_object.getLength()==0){
        int size=objects.size()-1;
        while(size>=0){
            if(objects[size].getLength()==0){
                objects.pop_back();
                continue;
            }
            objects[size].deleteLastSymbol();
            if(objects[size].getLength()==0) objects.pop_back();
            break;
        }
        if(size>=0){
            curent_object=objects.back();
            objects.pop_back();
        }
        return;
    }
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Operators) count_oper--;
    else if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets) count_open_bracket++;
    else if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBrackets) count_open_bracket--;
    curent_object.deleteLastSymbol();
    if(curent_object.getLength()==0){
        if(objects.size()==0) curent_object.clear();
        else{
            curent_object=objects.back();
            objects.pop_back();
        }
    }
    setFullText();
}

void GraphicsInfoWindow::deleteListElement(){
    int curent_element=ui->listWidget_expressions->currentRow();
    if(curent_element<0 || curent_element>info_objects.size()) return;
    info_objects.erase(info_objects.begin()+curent_element);
    emit needUpdateList();
}

void GraphicsInfoWindow::updateFunctionWindowState(){
    function_window_show=false;
}

void GraphicsInfoWindow::updateListWidget(){
    ui->listWidget_expressions->clear();
    for(GraphicsInfoObject elem:info_objects){
        ui->listWidget_expressions->addItem(QString::fromStdString(elem.getDisplayText()));
    }
}
