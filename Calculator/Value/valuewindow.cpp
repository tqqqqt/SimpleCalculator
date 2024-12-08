#include "valuewindow.h"
#include "ui_valuewindow.h"

ValueWindow::ValueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ValueWindow)
{
    QFile file(":/main_style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();
    this->setStyleSheet(content);

    ui->setupUi(this);

    QPixmap pixmap(":/menu-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size());



    curent_field=0;
    value_info=new ValueInfo();
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_upp->setEnabled(false);

    std::vector<std::string> main_info=value_info->getMain();
    for(auto x:main_info) ui->comboBox->addItem(QString::fromStdString(x));
    fillLeftRightBox();

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
    this->connect(ui->pushButton_upp,&QPushButton::clicked,[this]{ buttonChangeField(1); });
    this->connect(ui->pushButton_down,&QPushButton::clicked,[this]{ buttonChangeField(2); });
    this->connect(ui->pushButton_dot,&QPushButton::clicked,[this]{ pressNumberButton(','); });
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(buttonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(buttonDeleteLast()));
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));
    this->connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ buttonClear(); fillLeftRightBox(); });
    this->connect(ui->comboBox_left,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ emit getResult(); });
    this->connect(ui->comboBox_right,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ emit getResult(); });

    this->connect(this,SIGNAL(getResult()),this,SLOT(updateResult()));
    this->connect(this,SIGNAL(refreshText()),this,SLOT(updateText()));

    buttonChangeField(1);
}

ValueWindow::~ValueWindow()
{
    delete ui;
}

void ValueWindow::pressNumberButton(QChar button_num){
    if(curent_field==1){
        up_object.addNum(button_num.toLatin1());
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    }
    else{
        bottom_object.addNum(button_num.toLatin1());
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
    }
    emit getResult();
}

void ValueWindow::buttonChangeField(int _field){
    if(_field==curent_field) return;
    if(_field==1){
        curent_field=1;
        ui->textEdit_left->setFontWeight(QFont::Bold);
        ui->textEdit_right->setFontWeight(QFont::Normal);
        ui->pushButton_upp->setEnabled(false);
        ui->pushButton_down->setEnabled(true);
    }
    else{
        curent_field=2;
        ui->textEdit_right->setFontWeight(QFont::Bold);
        ui->textEdit_left->setFontWeight(QFont::Normal);
        ui->pushButton_upp->setEnabled(true);
        ui->pushButton_down->setEnabled(false);
    }
    emit refreshText();
}

void ValueWindow::buttonClear(){
    up_object.clear();
    bottom_object.clear();
    ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
}

void ValueWindow::updateText(){
    ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
}

void ValueWindow::buttonDeleteLast(){
    if(curent_field==1){
        up_object.deleteLastSymbol();
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    }
    else{
        bottom_object.deleteLastSymbol();
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
    }
    emit getResult();
}

void ValueWindow::buttonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));
    mode_window->exec();
}

void ValueWindow::updateMode(int _mode){
    if(_mode==2) return;
    emit changeWindow(_mode);
    this->hide();
}

void ValueWindow::updateResult(){
    if(curent_field==1 && up_object.toString()==""){
        bottom_object.clear();
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
        return;
    }
    if(curent_field==2 && bottom_object.toString()==""){
        up_object.clear();
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
        return;
    }
    std::string main=ui->comboBox->currentText().toStdString(), left=ui->comboBox_left->currentText().toStdString();
    std::string right=ui->comboBox_right->currentText().toStdString();
    std::string value=(curent_field==1)?up_object.toString():bottom_object.toString();
    QString temp="";
    if(curent_field==1){
        temp=QString::fromStdString(value_info->getMullNum(main,left,right,value));
        bottom_object.setFullNum(temp.toStdString());
        ui->textEdit_right->setText(temp);
    }
    else{
        temp=QString::fromStdString(value_info->getMullNum(main,right,left,value));
        up_object.setFullNum(temp.toStdString());
        ui->textEdit_left->setText(temp);
    }
}

void ValueWindow::fillLeftRightBox(){
    ui->comboBox_left->clear();
    ui->comboBox_right->clear();
    std::vector<std::string> temp=value_info->getSecond(ui->comboBox->currentText().toStdString());
    for(auto x:temp){
        ui->comboBox_left->addItem(QString::fromStdString(x));
        ui->comboBox_right->addItem(QString::fromStdString(x));
    }
}
