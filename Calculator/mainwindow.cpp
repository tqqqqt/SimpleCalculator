#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loadStyle();
    ui->setupUi(this);
    loadIcons();

    QSettings *settings=new QSettings("tqqqqt","calculator");
    calculator_math_object=CalculatorMath();
    curent_text="";
    flag_after_result=false;
    count_open_bracket=0;
    count_oper=0;
    function_window_show=false;
    history_window_show=false;

    // check setting or set default value
    if(settings->contains("calc/acuracy")==false) settings->setValue("calc/acuracy",10);
    if(settings->contains("calc/func_acuracy")==false) settings->setValue("calc/func_acuracy",10);
    // load settings
    curent_acuracy=settings->value("calc/acuracy",10).toInt();
    function_acuracy=settings->value("calc/func_acuracy",10).toInt();
    // set settings in calculator object
    calculator_math_object.setDivAccuracy(curent_acuracy);
    calculator_math_object.setFunctionAccuracy(function_acuracy);
    ui->label->setText(curent_text);

    delete settings;

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

    //dot and minus buttons
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(buttonDot()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(buttonZnak()));

    //operator buttons
    this->connect(ui->pushButton_pluss,&QPushButton::clicked,[this]{ pressOperButton("+"); });
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ pressOperButton("-"); });
    this->connect(ui->pushButton_mull,&QPushButton::clicked,[this]{ pressOperButton("*"); });
    this->connect(ui->pushButton_devide,&QPushButton::clicked,[this]{ pressOperButton("/"); });
    this->connect(ui->pushButton_pow,&QPushButton::clicked,[this]{ pressOperButton("^("); });

    // result button
    this->connect(ui->pushButton_res,SIGNAL(clicked()),this,SLOT(buttonResult()));

    //button clear and delete last
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(buttonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(buttonDeleteLast()));

    //bracket buttons
    this->connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(buttonOpenBrackets()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(buttonCloseBrackets()));

    //history, mode and fucntions buttons
    this->connect(ui->pushButton_history,SIGNAL(clicked()),this,SLOT(buttonHistory()));
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));
    this->connect(ui->pushButton_functions,SIGNAL(clicked()),this,SLOT(pressFunctionsButton()));

    //options
    this->connect(ui->action_settings,SIGNAL(triggered()),this,SLOT(buttonSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Close all windows before close calculator window
void MainWindow::closeEvent(QCloseEvent *event){
    // emit signal to close child windows like history, functions
    emit closeWindow();

    event->accept();
}

// Load css style from main_style.css file
void MainWindow::loadStyle(){
    // main style for window
    QFile file(":/main_style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();

    this->setStyleSheet(content);
}

// Load icons for buttons
void MainWindow::loadIcons(){
    QPixmap pixmap(":/history-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_history->setIcon(button_icon);
    ui->pushButton_history->setIconSize(pixmap.rect().size()/2);

    pixmap.load(":/menu-icon.png");
    button_icon.addPixmap(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size()/2);
}

// Collect text from all objects and display it on the screen
void MainWindow::setFullText(){
    curent_text.clear();
    // collect all text from objects
    for(CalculatorObject element:objects){
        curent_text+=QString::fromStdString(element.toString());
    }
    curent_text+=QString::fromStdString(curent_object.toString());

    ui->label->setText(curent_text);
}

// Added num in the object
void MainWindow::pressNumberButton(const QChar& button_num){
    // rules to use number button
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBracket || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::SpecialFunction) return;
    if(curent_object.getObjectType()>CalculatorObject::ObjectsTypes::Num){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    // clear text if it calculator result
    if(flag_after_result==true){
        curent_object.clear();
        flag_after_result=false;
    }

    curent_object.addNum(button_num.toLatin1());
    // update display text
    setFullText();
}

// Added operator in the object
void MainWindow::pressOperButton(const QString& button_oper){
    // rules for use operators button
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBracket && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::SpecialFunction) return;
    // change curent object type on minus bracket
    if(button_oper=='-' && curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBracket){
        curent_object.addSymbol("-");
        if(flag_after_result==true) flag_after_result=false;
        // update display text
        setFullText();
        return;
    }
    // drop curent object in vector if it no none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    if(button_oper=="^("){
        curent_object.addFunction(button_oper.toStdString());
        count_open_bracket+=1;
    }
    else curent_object.addSymbol(button_oper.toStdString());
    count_oper+=1;
    // change flag after result
    if(flag_after_result==true) flag_after_result=false;
    // update display text
    setFullText();
}

// Open function window
void MainWindow::pressFunctionsButton(){
    // do not open if already open
    if(function_window_show==true) return;

    FunctionsWindow *functions_window=new FunctionsWindow();
    this->connect(functions_window,SIGNAL(pressFunction(QString)),this,SLOT(addedFunction(QString)));
    this->connect(functions_window,SIGNAL(pressSpecialFunction(QString)),this,SLOT(addedSpecialFunction(QString)));
    this->connect(functions_window,SIGNAL(pressOperator(QString)),this,SLOT(pressOperButton(QString)));
    this->connect(functions_window,SIGNAL(updateWindowState()),this,SLOT(updateFunctionWindowState()));
    this->connect(this,SIGNAL(closeWindow()),functions_window,SLOT(needCloseWindow()));

    functions_window->show();
    function_window_show=true;
}

// Added function in the object
void MainWindow::addedFunction(const QString& _function){
    // rules for use functions
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBracket || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::SpecialFunction || flag_after_result==true) return;
    // drop curent object in vector if his no none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    curent_object.addFunction(_function.toStdString());
    count_oper+=1;
    count_open_bracket+=1;
    // update display text after changes
    setFullText();
}

// Added mod and factorial functions
void MainWindow::addedSpecialFunction(const QString& _function){
    // rules for use special functions
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBracket) return;
    // always drop curent object in vector
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSpecialFunction(_function.toStdString());
    count_oper+=1;
    // update display text after changes
    setFullText();
}

// Added dot in the object
void MainWindow::buttonDot(){
    // rules for use dot button
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num) return;
    curent_object.addNum(',');
    // change flag
    if(flag_after_result==true) flag_after_result=false;
    // update display text after changes
    setFullText();
}

// Clear all states
void MainWindow::buttonClear(){
    curent_text="";
    objects.clear();
    curent_object.clear();
    count_oper=0;
    count_open_bracket=0;
    flag_after_result=false;
    // update dispaly text after changes
    setFullText();
}

// Added open brackets in the object
void MainWindow::buttonOpenBrackets(){
    // rules for use open bracket
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::SpecialFunction) return;
    // drop curent object in vector if his not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None){
        objects.push_back(curent_object);
        curent_object.clear();
    }

    curent_object.addSymbol("(");
    count_open_bracket++;
    // update display text after changes
    setFullText();
}

// Added close brackets in the object
void MainWindow::buttonCloseBrackets(){
    // no need close bracket if no have open bracket
    if(count_open_bracket==0) return;
    // rules for use close bracket
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::SpecialFunction && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBracket) return;
    // always drop curent object in vector
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol(")");
    count_open_bracket--;
    // update display text after changes
    setFullText();
}

// Added minus oper after num to negative num
void MainWindow::buttonZnak(){
    // rules for use minus button
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBracket || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Num || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::MinusBracket) return;
    // drop curent object in vector if his not none
    if(curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::None) objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol("(-");
    count_open_bracket++;
    // change flag
    if(flag_after_result==true) flag_after_result=false;
    // update display text after changes
    setFullText();
}

// Calculate result and display on the screen
void MainWindow::buttonResult(){
    // rules for get result
    if(curent_text.length()==0 || (curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::Num && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::CloseBracket && curent_object.getObjectType()!=CalculatorObject::ObjectsTypes::SpecialFunction)) return;
    if(count_open_bracket || count_oper==0) return;
    // save display text to set in history
    QString save_calculator_text=curent_text;
    try {
        objects.push_back(curent_object);
        calculator_math_object.setVector(objects.toStdVector());
        objects.clear();
        curent_object=calculator_math_object.getResult();
        // get brackets from object and make 3 different objects in vector
        if(curent_object.toString()[0]=='-'){
            // save num from result
            std::string temp_num=curent_object.toString();
            temp_num=temp_num.erase(0,1);
            // add minus bracket
            curent_object.clear();
            curent_object.addSymbol("(-");
            objects.push_back(curent_object);
            // add num
            curent_object.clear();
            curent_object.setFullNum(temp_num);
            objects.push_back(curent_object);
            // set curent object ass close bracket
            curent_object.clear();
            curent_object.addSymbol(")");
        }
        // update display text
        setFullText();
        flag_after_result=true;
    }
    catch (std::exception &exp) {
        curent_text="";
        curent_object.clear();
        ui->label->setText(exp.what());
        flag_after_result=false;
    }
    // make hostory string
    history_arr.push_back(save_calculator_text+'='+ui->label->toPlainText());
    // emit signal to update history list in history window if his open
    emit pressResult();

    count_open_bracket=0;
    count_oper=0;
}

// Open history window
void MainWindow::buttonHistory(){
    // no open window if hi already open
    if(history_window_show==true) return;

    HistoryWindow* historyWindow=new HistoryWindow(&history_arr);
    connect(this,SIGNAL(pressResult()),historyWindow,SLOT(updateHis()));
    connect(this,SIGNAL(closeWindow()),historyWindow,SLOT(needCloseWindow()));
    connect(historyWindow,SIGNAL(updateWindowState()),this,SLOT(updateHistoryWindowState()));

    historyWindow->show();
    history_window_show=true;
}

// Open options window
void MainWindow::buttonSettings(){
    SettingsWindow* settings_window=new SettingsWindow(this);
    this->connect(settings_window,SIGNAL(acceptSettings()),this,SLOT(updateSettings()));

    settings_window->exec();
}

// Update settings after pressed accept in settings window
void MainWindow::updateSettings(){
    QSettings *settings=new QSettings("tqqqqt","calculator");
    curent_acuracy=settings->value("calc/acuracy",10).toInt();
    function_acuracy=settings->value("calc/func_acuracy",10).toInt();
    delete settings;

    calculator_math_object.setDivAccuracy(curent_acuracy);
    calculator_math_object.setFunctionAccuracy(function_acuracy);
}

// Open mode window
void MainWindow::buttonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));

    mode_window->exec();
}

// Change window after change calculator mode
void MainWindow::updateMode(const int& _mode){
    // curent calculator is 1 mode, no need change
    if(_mode==1) return;

    // update flags before close
    function_window_show=false;
    history_window_show=false;

    // emit signal to close child windows like history and function
    emit closeWindow();
    // emit signal to main to change calculator mode
    emit changeWindow(_mode);

    this->hide();
}

// Delete last symbol in object
void MainWindow::buttonDeleteLast(){
    // if curent object clear need find no clear object in vector
    if(curent_object.getLength()==0){
        int size=objects.size()-1;
        while(size>=0){
            // delete all object then length null
            if(objects[size].getLength()==0){
                objects.pop_back();
                continue;
            }
            // delete last symbol in no null object
            objects[size].deleteLastSymbol();
            if(objects[size].getLength()==0) objects.pop_back();
            // break if size == 0 or find no null object after delete last symbol
            break;
        }
        // if we find object in vector
        if(size>=0){
            curent_object=objects.back();
            objects.pop_back();
        }
        return;
    }
    // if curent object not null check type for special types
    if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Operator) count_oper--;
    else if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::CloseBracket) count_open_bracket++;
    else if(curent_object.getObjectType()==CalculatorObject::ObjectsTypes::OpenBracket || curent_object.getObjectType()==CalculatorObject::ObjectsTypes::Function) count_open_bracket--;
    curent_object.deleteLastSymbol();
    // check what curent object not null and change on no null object in vector
    if(curent_object.getLength()==0){
        if(objects.size()==0) curent_object.clear();
        else{
            curent_object=objects.back();
            objects.pop_back();
        }
    }
    // change result emit disable result flag
    if(flag_after_result==true) flag_after_result=false;
    // update dispaly text after changes
    setFullText();
}

// update function window flag after function window close
void MainWindow::updateFunctionWindowState(){
    function_window_show=false;
}

// update history window flag after history window close
void MainWindow::updateHistoryWindowState(){
    history_window_show=false;
}
