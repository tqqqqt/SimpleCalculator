#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curentText="";
    flagAfterResult=false;
    countOpenBracket=0;
    typeLastSymbol=0;
    calculatorMathObject=new CalculatorMath();
    ui->label->setText(curentText);
    this->connect(ui->pushButton_n0,&QPushButton::clicked,[this]{ PressNumberButton('0');});
    this->connect(ui->pushButton_n1,&QPushButton::clicked,[this]{ PressNumberButton('1');});
    this->connect(ui->pushButton_n2,&QPushButton::clicked,[this]{ PressNumberButton('2');});
    this->connect(ui->pushButton_n3,&QPushButton::clicked,[this]{ PressNumberButton('3');});
    this->connect(ui->pushButton_n4,&QPushButton::clicked,[this]{ PressNumberButton('4');});
    this->connect(ui->pushButton_n5,&QPushButton::clicked,[this]{ PressNumberButton('5');});
    this->connect(ui->pushButton_n6,&QPushButton::clicked,[this]{ PressNumberButton('6');});
    this->connect(ui->pushButton_n7,&QPushButton::clicked,[this]{ PressNumberButton('7');});
    this->connect(ui->pushButton_n8,&QPushButton::clicked,[this]{ PressNumberButton('8');});
    this->connect(ui->pushButton_n9,&QPushButton::clicked,[this]{ PressNumberButton('9');});
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(ButtonDot()));
    this->connect(ui->pushButton_pluss,&QPushButton::clicked,[this]{ PressOperButton('+');});
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ PressOperButton('-');});
    this->connect(ui->pushButton_mull,&QPushButton::clicked,[this]{ PressOperButton('*');});
    this->connect(ui->pushButton_devide,&QPushButton::clicked,[this]{ PressOperButton('/');});
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(ButtonClear()));
    this->connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(ButtonOpenBrackets()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(ButtonCloseBrackets()));
    this->connect(ui->pushButton_res,SIGNAL(clicked()),this,SLOT(ButtonResult()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(ButtonZnak()));
    this->connect(ui->pushButton_history,SIGNAL(clicked()),this,SLOT(ButtonHistory()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(ButtonDeleteLast()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PressNumberButton(QChar buttonNum){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText=buttonNum;
        flagAfterResult=false;
    }
    else curentText+=buttonNum;
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::PressOperButton(QChar buttonOper){
    if(typeLastSymbol!=1 && typeLastSymbol!=4) return;
    curentText+=buttonOper;
    typeLastSymbol=5;
    if(flagAfterResult) flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonDot(){
    if(typeLastSymbol!=1) return;
    curentText+=',';
    typeLastSymbol=6;
    ui->label->setText(curentText);
}

void MainWindow::ButtonClear(){
    curentText="";
    countOpenBracket=0;
    typeLastSymbol=0;
    flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonOpenBrackets(){
    if(typeLastSymbol==4 || flagAfterResult) return;
    if(typeLastSymbol==1) curentText+="*(";
    else curentText+='(';
    countOpenBracket++;
    typeLastSymbol=3;
    ui->label->setText(curentText);
}

void MainWindow::ButtonCloseBrackets(){
    if(!countOpenBracket) return;
    curentText+=')';
    countOpenBracket--;
    typeLastSymbol=4;
    ui->label->setText(curentText);
}

void MainWindow::ButtonZnak(){
    if(curentText.length()==0 || flagAfterResult){
        curentText="(-";
        countOpenBracket++;
        typeLastSymbol=2;
        flagAfterResult=false;
    }
    else if(typeLastSymbol==3 || typeLastSymbol==5){
        curentText+="(-";
        countOpenBracket++;
        typeLastSymbol=2;
    }
    ui->label->setText(curentText);
}

void MainWindow::ButtonResult(){
    QString tempResult="";
    if(calculatorMathObject->SetString(curentText.toStdString())) tempResult="Error input.";
    else tempResult=QString::fromStdString(calculatorMathObject->GetResult());
    historyArr.push_back(curentText+"="+tempResult);
    emit PressResult();
    ui->label->setText(tempResult);
    if(tempResult[0]=='E'){
        curentText="";
        flagAfterResult=false;
        countOpenBracket=0;
        typeLastSymbol=0;
        return;
    }
    curentText=tempResult;
    flagAfterResult=true;
    typeLastSymbol=1;
    countOpenBracket=0;
}

void MainWindow::ButtonHistory(){
    HistoryWindow* historyWindow=new HistoryWindow(&historyArr);
    historyWindow->show();
    connect(this,SIGNAL(PressResult()),historyWindow,SLOT(UpdateHis()));
}

void MainWindow::ButtonDeleteLast(){
    curentText.remove(curentText.length()-1,1);
    ui->label->setText(curentText);
    if(typeLastSymbol==2) typeLastSymbol=3;
    else if(curentText.length()==0) typeLastSymbol=0;
    else{
        if(typeLastSymbol==3) countOpenBracket--;
        else if(typeLastSymbol==4) countOpenBracket++;
        QChar temp=curentText.back();
        if(temp>='0' && temp<='9') typeLastSymbol=1;
        else if(temp=='(') typeLastSymbol=3;
        else if(temp==')') typeLastSymbol=4;
        else if(temp=='-' || temp=='+' || temp=='*' || temp=='/') typeLastSymbol=5;
    }
    if(flagAfterResult) flagAfterResult=false;
}
