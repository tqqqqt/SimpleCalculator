#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curentText="";
    flagAfterResult=false;
    curentTextLength=0;
    countOpenBracket=0;
    typeLastSymbol=0;
    calculatorMathObject=new CalculatorMath();
    ui->label->setText(curentText);
    this->connect(ui->pushButton_n0,SIGNAL(clicked()),this,SLOT(ButtonN0()));
    this->connect(ui->pushButton_n1,SIGNAL(clicked()),this,SLOT(ButtonN1()));
    this->connect(ui->pushButton_n2,SIGNAL(clicked()),this,SLOT(ButtonN2()));
    this->connect(ui->pushButton_n3,SIGNAL(clicked()),this,SLOT(ButtonN3()));
    this->connect(ui->pushButton_n4,SIGNAL(clicked()),this,SLOT(ButtonN4()));
    this->connect(ui->pushButton_n5,SIGNAL(clicked()),this,SLOT(ButtonN5()));
    this->connect(ui->pushButton_n6,SIGNAL(clicked()),this,SLOT(ButtonN6()));
    this->connect(ui->pushButton_n7,SIGNAL(clicked()),this,SLOT(ButtonN7()));
    this->connect(ui->pushButton_n8,SIGNAL(clicked()),this,SLOT(ButtonN8()));
    this->connect(ui->pushButton_n9,SIGNAL(clicked()),this,SLOT(ButtonN9()));
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(ButtonClear()));
    this->connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(ButtonOpenBrackets()));
    this->connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(ButtonCloseBrackets()));
    this->connect(ui->pushButton_devide,SIGNAL(clicked()),this,SLOT(ButtonDevide()));
    this->connect(ui->pushButton_mull,SIGNAL(clicked()),this,SLOT(ButtonMull()));
    this->connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(ButtonMinus()));
    this->connect(ui->pushButton_pluss,SIGNAL(clicked()),this,SLOT(ButtonPlus()));
    this->connect(ui->pushButton_res,SIGNAL(clicked()),this,SLOT(ButtonResult()));
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(ButtonZnak()));
    this->connect(ui->pushButton_history,SIGNAL(clicked()),this,SLOT(ButtonHistory()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(ButtonDeleteLast()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonN0(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='0';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='0';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN1(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='1';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='1';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN2(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='2';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='2';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN3(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='3';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='3';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN4(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='4';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='4';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN5(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='5';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='5';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN6(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='6';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='6';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN7(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='7';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='7';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN8(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='8';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='8';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonN9(){
    if(typeLastSymbol==4) return;
    if(flagAfterResult){
        curentText='9';
        flagAfterResult=false;
        curentTextLength=1;
    }
    else{
        curentText+='9';
        curentTextLength++;
    }
    typeLastSymbol=1;
    ui->label->setText(curentText);
}

void MainWindow::ButtonClear(){
    curentText="";
    curentTextLength=0;
    countOpenBracket=0;
    typeLastSymbol=0;
    flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonOpenBrackets(){
    if(typeLastSymbol==4 || flagAfterResult) return;
    if(typeLastSymbol==1){
        curentText+="*(";
        curentTextLength+=2;
    }
    else{
        curentText+='(';
        curentTextLength++;
    }
    countOpenBracket++;
    typeLastSymbol=3;
    ui->label->setText(curentText);
}

void MainWindow::ButtonCloseBrackets(){
    if(!countOpenBracket) return;
    curentText+=')';
    curentTextLength++;
    countOpenBracket--;
    typeLastSymbol=4;
    ui->label->setText(curentText);
}

void MainWindow::ButtonDevide(){
    if(typeLastSymbol!=1 && typeLastSymbol!=4) return;
    curentText+='/';
    curentTextLength++;
    typeLastSymbol=5;
    if(flagAfterResult) flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonMull(){
    if(typeLastSymbol!=1 && typeLastSymbol!=4) return;
    curentText+='*';
    curentTextLength++;
    typeLastSymbol=5;
    if(flagAfterResult) flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonMinus(){
    if(typeLastSymbol!=1 && typeLastSymbol!=4) return;
    curentText+='-';
    curentTextLength++;
    typeLastSymbol=5;
    if(flagAfterResult) flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonPlus(){
    if(typeLastSymbol!=1 && typeLastSymbol!=4) return;
    curentText+='+';
    curentTextLength++;
    typeLastSymbol=5;
    if(flagAfterResult) flagAfterResult=false;
    ui->label->setText(curentText);
}

void MainWindow::ButtonZnak(){
    if(curentTextLength==0 || flagAfterResult){
        curentText="(-";
        curentTextLength=2;
        countOpenBracket++;
        typeLastSymbol=2;
        flagAfterResult=false;
    }
    else if(typeLastSymbol==3 || typeLastSymbol==5){
        curentText+="(-";
        curentTextLength+=2;
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
    ui->label->setText(tempResult);
    if(tempResult[0]=='E'){
        curentText="";
        flagAfterResult=false;
        countOpenBracket=0;
        typeLastSymbol=0;
        curentTextLength=0;
        return;
    }
    curentText=tempResult;
    flagAfterResult=true;
    curentTextLength=curentText.length();
    typeLastSymbol=1;
    countOpenBracket=0;
}

void MainWindow::ButtonHistory(){
    HistoryWindow* historyWindow=new HistoryWindow(historyArr);
    historyWindow->show();
}

void MainWindow::ButtonDeleteLast(){
    curentText.remove(curentTextLength-1,1);
    if(curentTextLength) curentTextLength--;
    ui->label->setText(curentText);
    if(typeLastSymbol==2) typeLastSymbol=3;
    else if(curentTextLength==0) typeLastSymbol=0;
    else{
        QChar temp=curentText.back();
        if(temp>='0' && temp<='9') typeLastSymbol=1;
        else if(temp=='(') typeLastSymbol=3;
        else if(temp==')') typeLastSymbol=4;
        else if(temp=='-' || temp=='+' || temp=='*' || temp=='/') typeLastSymbol=5;
    }
    if(flagAfterResult) flagAfterResult=false;
}
