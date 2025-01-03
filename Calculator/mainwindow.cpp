#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loadStyle();
    ui->setupUi(this);
    loadIcons();

    settings=new QSettings("tqqqqt","calculator");
    calculatorMathObject=new CalculatorMath();
    curentText="";
    flagAfterResult=false;
    countOpenBracket=0;
    countOper=0;
    function_window_show=false;
    history_window_show=false;

    if(settings->contains("calc/acuracy")==false) settings->setValue("calc/acuracy",10);
    if(settings->contains("calc/func_acuracy")==false) settings->setValue("calc/func_acuracy",10);
    curent_acuracy=settings->value("calc/acuracy",10).toInt();
    function_acuracy=settings->value("calc/func_acuracy",10).toInt();
    calculatorMathObject->SetDivAccuracy(curent_acuracy);
    calculatorMathObject->setFunctionAccuracy(function_acuracy);
    ui->label->setText(curentText);

    //nums buttons
    this->connect(ui->pushButton_n0,&QPushButton::clicked,[this]{ PressNumberButton('0'); });
    this->connect(ui->pushButton_n1,&QPushButton::clicked,[this]{ PressNumberButton('1'); });
    this->connect(ui->pushButton_n2,&QPushButton::clicked,[this]{ PressNumberButton('2'); });
    this->connect(ui->pushButton_n3,&QPushButton::clicked,[this]{ PressNumberButton('3'); });
    this->connect(ui->pushButton_n4,&QPushButton::clicked,[this]{ PressNumberButton('4'); });
    this->connect(ui->pushButton_n5,&QPushButton::clicked,[this]{ PressNumberButton('5'); });
    this->connect(ui->pushButton_n6,&QPushButton::clicked,[this]{ PressNumberButton('6'); });
    this->connect(ui->pushButton_n7,&QPushButton::clicked,[this]{ PressNumberButton('7'); });
    this->connect(ui->pushButton_n8,&QPushButton::clicked,[this]{ PressNumberButton('8'); });
    this->connect(ui->pushButton_n9,&QPushButton::clicked,[this]{ PressNumberButton('9'); });

    //dot and minus buttons
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(ButtonDot()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(ButtonZnak()));

    //operator buttons and result
    this->connect(ui->pushButton_pluss,&QPushButton::clicked,[this]{ PressOperButton("+"); });
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ PressOperButton("-"); });
    this->connect(ui->pushButton_mull,&QPushButton::clicked,[this]{ PressOperButton("*"); });
    this->connect(ui->pushButton_devide,&QPushButton::clicked,[this]{ PressOperButton("/"); });
    this->connect(ui->pushButton_pow,&QPushButton::clicked,[this]{ PressOperButton("^("); });
    this->connect(ui->pushButton_res,SIGNAL(clicked()),this,SLOT(ButtonResult()));

    //button clear and delete last
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(ButtonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(ButtonDeleteLast()));

    //bracket buttons
    this->connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(ButtonOpenBrackets()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(ButtonCloseBrackets()));

    //history, mode and fucntions buttons
    this->connect(ui->pushButton_history,SIGNAL(clicked()),this,SLOT(ButtonHistory()));
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(ButtonChangeMode()));
    this->connect(ui->pushButton_functions,SIGNAL(clicked()),this,SLOT(pressFunctionsButton()));

    //options
    this->connect(ui->action_settings,SIGNAL(triggered()),this,SLOT(ButtonSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Close all windows before close calculator window
void MainWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    event->accept();
}

// Load css style from main_style.css file
void MainWindow::loadStyle(){
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
    curentText="";
    for(auto element:objects) curentText+=QString::fromStdString(element.toString());
    curentText+=QString::fromStdString(curent_object.toString());
    ui->label->setText(curentText);
}

// Added num in the object
void MainWindow::PressNumberButton(QChar buttonNum){
    if(curent_object.getObjectType()>2){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    if(flagAfterResult){
        curent_object.clear();
        flagAfterResult=false;
    }
    curent_object.addNum(buttonNum.toLatin1());
    setFullText();
}

// Added operator in the object
void MainWindow::PressOperButton(QString buttonOper){
    if(curent_object.getObjectType()==0 || curent_object.getObjectType()==2 || curent_object.getObjectType()==5) return;
    if(buttonOper=='-' && curent_object.getObjectType()==3){
        curent_object.addSymbol("-");
        if(flagAfterResult) flagAfterResult=false;
        setFullText();
        return;
    }
    if(curent_object.getObjectType()==1 || curent_object.getObjectType()==4){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addSymbol(buttonOper.toStdString());
    countOper++;
    if(buttonOper=="^(") countOpenBracket++;
    if(flagAfterResult) flagAfterResult=false;
    setFullText();
}

// Open function window
void MainWindow::pressFunctionsButton(){
    if(function_window_show==true) return;
    FunctionsWindow *functions_window=new FunctionsWindow();
    this->connect(functions_window,SIGNAL(pressFunction(QString)),this,SLOT(addedFunction(QString)));
    this->connect(this,SIGNAL(closeWindow()),functions_window,SLOT(closeWindow()));
    functions_window->show();
    function_window_show=true;
}

// Added function in the object
void MainWindow::addedFunction(QString _function){
    if(curent_object.getObjectType()==1 || curent_object.getObjectType()==4 || flagAfterResult==true) return;
    if(curent_object.getObjectType()==5 || curent_object.getObjectType()==3 || curent_object.getObjectType()==7){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addFunction(_function.toStdString());
    countOper+=1;
    countOpenBracket+=1;
    setFullText();
}

// Added dot in the object
void MainWindow::ButtonDot(){
    if(curent_object.getObjectType()!=1) return;
    curent_object.addNum(',');
    if(flagAfterResult) flagAfterResult=false;
    setFullText();
}

// Clear all states
void MainWindow::ButtonClear(){
    curentText="";
    objects.clear();
    curent_object.clear();
    countOper=0;
    countOpenBracket=0;
    flagAfterResult=false;
    setFullText();
}

// Added open brackets in the object
void MainWindow::ButtonOpenBrackets(){
    if(curent_object.getObjectType()!=5 && curent_object.getObjectType()!=0) return;
    if(curent_object.getObjectType()!=0){
        objects.push_back(curent_object);
        curent_object.clear();
    }
    curent_object.addSymbol("(");
    countOpenBracket++;
    setFullText();
}

// Added close brackets in the object
void MainWindow::ButtonCloseBrackets(){
    if(countOpenBracket==0) return;
    if(curent_object.getObjectType()!=1 && curent_object.getObjectType()!=2 && curent_object.getObjectType()!=4) return;
    objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol(")");
    countOpenBracket--;
    setFullText();
}

// Added minus oper after num to negative num
void MainWindow::ButtonZnak(){
    if(curent_object.getObjectType()==4 || curent_object.getObjectType()==1 || curent_object.getObjectType()==2) return;
    if(curent_object.getObjectType()!=0) objects.push_back(curent_object);
    curent_object.clear();
    curent_object.addSymbol("(-");
    countOpenBracket++;
    if(flagAfterResult) flagAfterResult=false;
    setFullText();
}

// Calculate result and display on the screen
void MainWindow::ButtonResult(){
    if(curentText.length()==0 || (curent_object.getObjectType()!=1 && curent_object.getObjectType()!=4)) return;
    if(countOpenBracket || countOper==0) return;
    QString save_calculator_text=curentText;
    try {
        objects.push_back(curent_object);
        calculatorMathObject->setVector(objects.toStdVector());
        objects.clear();
        curent_object=calculatorMathObject->GetResult();
        if(curent_object.toString()[0]=='('){
            curent_object.deleteLastSymbol();
            objects.push_back(curent_object);
            curent_object.clear();
            curent_object.addSymbol(")");
        }
        setFullText();
        flagAfterResult=true;
    }
    catch (std::exception &exp) {
        curentText="";
        curent_object.clear();
        ui->label->setText(exp.what());
        flagAfterResult=false;
    }
    historyArr.push_back(save_calculator_text+'='+ui->label->toPlainText());
    emit PressResult();
    countOpenBracket=0;
    countOper=0;
}

// Open history window
void MainWindow::ButtonHistory(){
    if(history_window_show==true) return;
    HistoryWindow* historyWindow=new HistoryWindow(&historyArr);
    connect(this,SIGNAL(PressResult()),historyWindow,SLOT(UpdateHis()));
    connect(this,SIGNAL(closeWindow()),historyWindow,SLOT(closeWindow()));
    historyWindow->show();
    history_window_show=true;
}

// Open options window
void MainWindow::ButtonSettings(){
    SettingsWindow* settings_window=new SettingsWindow(this);
    this->connect(settings_window,SIGNAL(acceptSettings()),this,SLOT(UpdateSettings()));
    settings_window->exec();
}

// Update settings after pressed accept in settings window
void MainWindow::UpdateSettings(){
    curent_acuracy=settings->value("calc/acuracy",10).toInt();
    function_acuracy=settings->value("calc/func_acuracy",10).toInt();

    calculatorMathObject->SetDivAccuracy(curent_acuracy);
    calculatorMathObject->setFunctionAccuracy(function_acuracy);
}

// Open mode window
void MainWindow::ButtonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(UpdateMode(int)));
    mode_window->exec();
}

// Change window after change calculator mode
void MainWindow::UpdateMode(int _mode){
    if(_mode==1) return;

    function_window_show=false;
    history_window_show=false;

    emit closeWindow();
    emit changeWindow(_mode);
    this->hide();
}

// Delete last symbol in object
void MainWindow::ButtonDeleteLast(){
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
    if(curent_object.getObjectType()==5) countOper--;
    else if(curent_object.getObjectType()==4) countOpenBracket++;
    else if(curent_object.getObjectType()==3) countOpenBracket--;
    curent_object.deleteLastSymbol();
    if(curent_object.getLength()==0){
        if(objects.size()==0) curent_object.clear();
        else{
            curent_object=objects.back();
            objects.pop_back();
        }
    }
    if(flagAfterResult) flagAfterResult=false;
    setFullText();
}
