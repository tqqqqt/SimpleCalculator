#include "programmistwindow.h"
#include "ui_programmistwindow.h"

ProgrammistWindow::ProgrammistWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammistWindow)
{
    loadStyle();
    ui->setupUi(this);
    loadIcons();

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
    this->connect(ui->pushButton_A,&QPushButton::clicked,[this]{ pressNumberButton('A'); });
    this->connect(ui->pushButton_B,&QPushButton::clicked,[this]{ pressNumberButton('B'); });
    this->connect(ui->pushButton_C,&QPushButton::clicked,[this]{ pressNumberButton('C'); });
    this->connect(ui->pushButton_D,&QPushButton::clicked,[this]{ pressNumberButton('D'); });
    this->connect(ui->pushButton_E,&QPushButton::clicked,[this]{ pressNumberButton('E'); });
    this->connect(ui->pushButton_F,&QPushButton::clicked,[this]{ pressNumberButton('F'); });
    this->connect(ui->pushButton_dot,&QPushButton::clicked,[this]{ pressNumberButton(','); });
    this->connect(ui->pushButton_znak,&QPushButton::clicked,[this]{ pressNumberButton('-'); });
    this->connect(ui->pushButton_move_left,&QPushButton::clicked,[this]{ pressMoveButton(-1); });
    this->connect(ui->pushButton_move_right,&QPushButton::clicked,[this]{ pressMoveButton(1); });
    this->connect(ui->pushButton_clear,&QPushButton::clicked,[this]{ buttonClear(); });
    this->connect(ui->pushButton_delLast,&QPushButton::clicked,[this]{ buttonDeleteLast(); });
    this->connect(ui->pushButton_hex,&QPushButton::clicked,[this]{ buttonChangeSystem(16); });
    this->connect(ui->pushButton_dec,&QPushButton::clicked,[this]{ buttonChangeSystem(10); });
    this->connect(ui->pushButton_oct,&QPushButton::clicked,[this]{ buttonChangeSystem(8); });
    this->connect(ui->pushButton_bin,&QPushButton::clicked,[this]{ buttonChangeSystem(2); });
}

ProgrammistWindow::~ProgrammistWindow()
{
    delete ui;
}

void ProgrammistWindow::loadStyle(){

}

void ProgrammistWindow::loadIcons(){
    QPixmap pixmap(":/menu-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size()/2);
}

void ProgrammistWindow::pressNumberButton(QChar){

}

void ProgrammistWindow::pressMoveButton(int){

}

void ProgrammistWindow::buttonClear(){

}

void ProgrammistWindow::buttonDeleteLast(){

}

void ProgrammistWindow::buttonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));
    mode_window->exec();
}

void ProgrammistWindow::updateMode(int _mode){
    if(_mode==3) return;
    emit changeWindow(_mode);
    this->hide();
}

void ProgrammistWindow::buttonChangeSystem(int){

}
