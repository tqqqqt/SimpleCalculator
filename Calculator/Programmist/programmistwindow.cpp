#include "programmistwindow.h"
#include "ui_programmistwindow.h"

ProgrammistWindow::ProgrammistWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammistWindow)
{
    loadStyle();
    ui->setupUi(this);
    loadIcons();

    object=new ProgrammistObject();
    buttonChangeSystem(10);
    settings=new QSettings("tqqqqt","calculator");
    if(!settings->contains("progr/acuracy")) settings->setValue("progr/acuracy",10);
    if(!settings->contains("progr/count")) settings->setValue("progr/count",5);
    object->setAccuracy(settings->value("progr/acuracy",10).toInt());
    object->setCount(settings->value("progr/count",5).toInt());

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
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));

    this->connect(this,SIGNAL(getResult()),this,SLOT(updateResult()));
    this->connect(ui->action_settings,SIGNAL(triggered()),this,SLOT(openSettings()));
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

void ProgrammistWindow::updateResult(){
    ui->textEdit_input->setText(QString::fromStdString(object->toString()));
    ui->lineEdit_bin->setText(QString::fromStdString(object->toString2()));
    ui->lineEdit_oct->setText(QString::fromStdString(object->toString8()));
    ui->lineEdit_dec->setText(QString::fromStdString(object->toString10()));
    ui->lineEdit_hex->setText(QString::fromStdString(object->toString16()));
}

void ProgrammistWindow::pressNumberButton(QChar _num){
    try {
        object->addNum(_num.toLatin1());
        emit getResult();
    }
    catch (std::exception &exp) {
        object->clear();
        ui->textEdit_input->setText(exp.what());
    }
}

void ProgrammistWindow::pressMoveButton(int _direction){
    if(object->getLength()==0) return;
    if(_direction==-1) object->moveLeft();
    else object->moveRight();
    emit getResult();
}

void ProgrammistWindow::buttonClear(){
    ui->textEdit_input->clear();
    ui->lineEdit_hex->clear();
    ui->lineEdit_dec->clear();
    ui->lineEdit_oct->clear();
    ui->lineEdit_bin->clear();
    object->clear();
}

void ProgrammistWindow::buttonDeleteLast(){
    if(object->getLength()==0) return;
    object->deleteLastSymbol();
    emit getResult();
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

void ProgrammistWindow::buttonChangeSystem(int _system){
    object->changeSystem(_system);
    ui->textEdit_input->setText(QString::fromStdString(object->toString()));
    switch(_system){
    case 2:
        setButtonsEnable(false,false);
        ui->pushButton_n0->setEnabled(true);
        ui->pushButton_n1->setEnabled(true);
        ui->pushButton_bin->setEnabled(false);
        break;
    case 8:
        setButtonsEnable(false,true);
        ui->pushButton_n9->setEnabled(false);
        ui->pushButton_n8->setEnabled(false);
        ui->pushButton_oct->setEnabled(false);
        break;
    case 10:
        setButtonsEnable(false,true);
        ui->pushButton_dec->setEnabled(false);
        ui->pushButton_znak->setEnabled(true);
        break;
    case 16:
        setButtonsEnable(true,true);
        ui->pushButton_hex->setEnabled(false);
        break;
    }
}

void ProgrammistWindow::setButtonsEnable(bool _flag_symbol, bool _flag_num){
    ui->pushButton_A->setEnabled(_flag_symbol);
    ui->pushButton_B->setEnabled(_flag_symbol);
    ui->pushButton_C->setEnabled(_flag_symbol);
    ui->pushButton_D->setEnabled(_flag_symbol);
    ui->pushButton_E->setEnabled(_flag_symbol);
    ui->pushButton_F->setEnabled(_flag_symbol);

    ui->pushButton_n0->setEnabled(_flag_num);
    ui->pushButton_n1->setEnabled(_flag_num);
    ui->pushButton_n2->setEnabled(_flag_num);
    ui->pushButton_n3->setEnabled(_flag_num);
    ui->pushButton_n4->setEnabled(_flag_num);
    ui->pushButton_n5->setEnabled(_flag_num);
    ui->pushButton_n6->setEnabled(_flag_num);
    ui->pushButton_n7->setEnabled(_flag_num);
    ui->pushButton_n8->setEnabled(_flag_num);
    ui->pushButton_n9->setEnabled(_flag_num);

    ui->pushButton_znak->setEnabled(false);

    ui->pushButton_hex->setEnabled(true);
    ui->pushButton_dec->setEnabled(true);
    ui->pushButton_oct->setEnabled(true);
    ui->pushButton_bin->setEnabled(true);
}

void ProgrammistWindow::openSettings(){
    ProgrammistSettingsWindow *settings_window=new ProgrammistSettingsWindow();
    this->connect(settings_window,SIGNAL(acceptSettings()),this,SLOT(updateSettings()));
    settings_window->exec();
}

void ProgrammistWindow::updateSettings(){
    object->setAccuracy(settings->value("progr/acuracy",10).toInt());
    object->setCount(settings->value("progr/count",5).toInt());
}
