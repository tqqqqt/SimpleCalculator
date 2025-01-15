#include "graphicsinfowindow.h"
#include "ui_graphicsinfowindow.h"

GraphicsInfoWindow::GraphicsInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicsInfoWindow)
{
    loadStyles();
    ui->setupUi(this);
    loadIcons();

    painter_window_open=false;
    function_window_show=false;
    curent_text="";
    count_open_bracket=0;

    // connects
    // nums buttons
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

    // dot, minus and variable (X) buttons
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(buttonDot()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(buttonZnak()));
    this->connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(pressVariableButton()));

    // operator, pow and add buttons
    this->connect(ui->pushButton_pluss,&QPushButton::clicked,[this]{ pressOperButton("+"); });
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ pressOperButton("-"); });
    this->connect(ui->pushButton_mull,&QPushButton::clicked,[this]{ pressOperButton("*"); });
    this->connect(ui->pushButton_devide,&QPushButton::clicked,[this]{ pressOperButton("/"); });
    this->connect(ui->pushButton_pow,&QPushButton::clicked,[this]{ pressOperButton("^("); });
    this->connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(buttonAdd()));

    // clear and delete last
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(buttonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(buttonDeleteLast()));

    // bracket buttons
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

// load all need icons and set in buttons
void GraphicsInfoWindow::loadIcons(){
    QPixmap pixmap(":/menu-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size()/2);

    pixmap.load(":/Graphics/GraphicsInfo/enter-icon.png");
    button_icon.addPixmap(pixmap);
    ui->pushButton_add->setIcon(button_icon);
    ui->pushButton_add->setIconSize(pixmap.rect().size()/2);
}

// load styles use in window
void GraphicsInfoWindow::loadStyles(){

}

// emit signal before close window
void GraphicsInfoWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    event->accept();
}

// open mode window and wait result
void GraphicsInfoWindow::buttonChangeMode(){
    ModeWindow *mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));

    mode_window->exec();
}

// change curent window mode if it not 4 couse 4 is graphics
void GraphicsInfoWindow::updateMode(int _mode){
    if(_mode==4) return;

    // set false to window state
    function_window_show=false;
    painter_window_open=false;

    // emit signal to close child window like function or painter
    emit closeWindow();
    // emit signal to main to change curent calculator mode
    emit changeWindow(_mode);
    this->hide();
}

// change flag to enable open new window
void GraphicsInfoWindow::updatePainterWindowState(){
    painter_window_open=false;
}

// open painter window if no one open
void GraphicsInfoWindow::openPainter(){
    if(painter_window_open==true) return;
    painter_window=new GraphicsPainterWindow(&info_objects);
    painter_window_open=true;

    // connects signals with painter window
    this->connect(this,SIGNAL(closeWindow()),painter_window,SLOT(needClose()));
    this->connect(this,SIGNAL(addNewElement()),painter_window,SLOT(paintGraphics()));
    this->connect(painter_window,SIGNAL(closeWindow()),this,SLOT(updatePainterWindowState()));

    painter_window->show();
}

// collect text from all objects and display on screen
void GraphicsInfoWindow::setFullText(){
    curent_text="";

    // collect all texts
    for(auto element:objects){
        curent_text+=QString::fromStdString(element.toString());
    }
    curent_text+=QString::fromStdString(curent_object.toString());

    ui->label->setText(curent_text);
}

// added pressed num to curent object
void GraphicsInfoWindow::pressNumberButton(QChar buttonNum){
    // drop curent object in vector if it's not a num
    if(curent_object.getObjectType()>CalculatorObject::ObjectsTypes::Num){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addNum(buttonNum.toLatin1());

    setFullText();
}

// added operator to curent object
void GraphicsInfoWindow::pressOperButton(QString buttonOper){
    // rules for use operator
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::None || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::MinusBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Operators || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Functins) return;

    // change object to minus bracket without drop in vector
    if(buttonOper=='-' && curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBrackets){
        curent_object.addSymbol("-");
        setFullText();
        return;
    }

    // drop object in vector if it's not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    curent_object.addSymbol(buttonOper.toStdString());
    if(buttonOper=="^(") count_open_bracket+=1;

    // display curent text
    setFullText();
}

// added X variable to curent object
void GraphicsInfoWindow::pressVariableButton(){
    // variable use rules
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Factorial || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;

    // drop objects in vector if it's not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None) objects.push_back(curent_object);

    curent_object.clear();
    curent_object.addVariable();

    // display curent text
    setFullText();
}

// open function window if it's not open
void GraphicsInfoWindow::pressFunctionsButton(){
    // if already open don't open again
    if(function_window_show==true) return;

    FunctionsWindow *functions_window=new FunctionsWindow();

    // connects signals
    this->connect(functions_window,SIGNAL(pressFunction(QString)),this,SLOT(addedFunction(QString)));
    this->connect(functions_window,SIGNAL(pressSpecialFunction(QString)),this,SLOT(addedSpecialFunction(QString)));
    this->connect(functions_window,SIGNAL(updateWindowState()),this,SLOT(updateFunctionWindowState()));
    this->connect(this,SIGNAL(closeWindow()),functions_window,SLOT(needCloseWindow()));

    functions_window->show();
    function_window_show=true;
}

// react to press function in function window and added function to curent object
void GraphicsInfoWindow::addedFunction(QString _function){
    // function use rules
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;

    // drop object in vector if it's not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    curent_object.addFunction(_function.toStdString());
    count_open_bracket+=1;

    // display text
    setFullText();
}

// some function with more arguments then 1 (mod)
void GraphicsInfoWindow::addedSpecialFunction(QString _function){
    // special function use rules
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::X_variable) return;

    // always drop curetn object in vector
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSpecialFunction(_function.toStdString());

    // display text
    setFullText();
}

// added dot for curent object
void GraphicsInfoWindow::buttonDot(){
    // dot use rulles
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num) return;

    curent_object.addNum(',');

    // display text
    setFullText();
}

// clear all states
void GraphicsInfoWindow::buttonClear(){
    curent_text="";
    objects.clear();
    curent_object.clear();
    count_open_bracket=0;

    // update display text after changes
    setFullText();
}

// added open bracket to curent object
void GraphicsInfoWindow::buttonOpenBrackets(){
    // open bracket rules use
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Factorial || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;

    // drop curent object in vector
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    curent_object.addSymbol("(");
    count_open_bracket+=1;

    // display text
    setFullText();
}

// added close bracket to curent object
void GraphicsInfoWindow::buttonCloseBrackets(){
    // no need close bracket if dont have open bracket
    if(count_open_bracket==0) return;

    // rules to use close bracket
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::MinusBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::X_variable) return;

    // always drop curent object in vector
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol(")");
    count_open_bracket--;

    // display text
    setFullText();
}

// added full object to list and display in window
void GraphicsInfoWindow::buttonAdd(){
    // rules to add input to list
    if(curent_text.length()==0 || count_open_bracket!=0) return;
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBrackets && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Factorial && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::X_variable) return;

    // save text and polish entry to add in info object
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

    // create new info object
    GraphicsInfoObject new_object;
    new_object.setDisplayText(save_text.toStdString());
    new_object.setPolishEntry(save_polish);

    // added in list
    info_objects.push_back(new_object);

    // emit signal to update diplay list
    emit needUpdateList();
    // emit signal to pointer window to paint graphics for new element
    emit addNewElement();

    // clear states
    count_open_bracket=0;
}

// added minus in curent object
void GraphicsInfoWindow::buttonZnak(){
    // rules for use minus bracket
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::MinusBrackets || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::X_variable) return;

    // drop object in vector if his not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None) objects.push_back(curent_object);

    curent_object.clear();
    curent_object.addSymbol("(-");
    count_open_bracket++;

    // display text
    setFullText();
}

// delete last input symbol or function
void GraphicsInfoWindow::buttonDeleteLast(){
    // check what curent object length is null
    if(curent_object.getLength()==0){
        int size=objects.size()-1;
        // while have objects in vector check them all
        while(size>=0){
            // if length null delete object
            if(objects[size].getLength()==0){
                objects.pop_back();
                continue;
            }
            // delete last symbol if length not null
            objects[size].deleteLastSymbol();

            // pop if after delete symbol length == 0
            if(objects[size].getLength()==0) objects.pop_back();

            // break cause we found object with no null length
            break;
        }
        // set find object as curent object
        if(size>=0){
            curent_object=objects.back();
            objects.pop_back();
        }
        return;
    }
    // if curent object length not null
    // some checks for change count brackets and operators
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBrackets) count_open_bracket++;
    else if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBrackets) count_open_bracket--;

    curent_object.deleteLastSymbol();
    // check curent length and change curent object if can
    if(curent_object.getLength()==0){
        if(objects.size()==0) curent_object.clear();
        else{
            curent_object=objects.back();
            objects.pop_back();
        }
    }

    // display text
    setFullText();
}

// delete element in list
void GraphicsInfoWindow::deleteListElement(){
    int curent_element=ui->listWidget_expressions->currentRow();

    // check for bound
    if(curent_element<0 || curent_element>info_objects.size()) return;
    info_objects.erase(info_objects.begin()+curent_element);

    emit needUpdateList();
    emit addNewElement();
}

// set flag to false for open new function window
void GraphicsInfoWindow::updateFunctionWindowState(){
    function_window_show=false;
}

// update widget to display all elements
void GraphicsInfoWindow::updateListWidget(){
    // clear list widget for added elements
    ui->listWidget_expressions->clear();
    for(GraphicsInfoObject elem:info_objects){
        ui->listWidget_expressions->addItem(QString::fromStdString(elem.getDisplayText()));
    }
}
