#include "valuewindow.h"
#include "ui_valuewindow.h"

ValueWindow::ValueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ValueWindow)
{
    loadStyle();
    ui->setupUi(this);
    loadIcons();

    curent_field=0;
    value_info=ValueInfo();
    // to default curent side is up
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_upp->setEnabled(false);

    std::vector<std::string> main_info=value_info.getMain();
    for(auto x:main_info) ui->comboBox->addItem(QString::fromStdString(x));
    fillUpBottomBox();

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

    // side buttons
    this->connect(ui->pushButton_upp,&QPushButton::clicked,[this]{ buttonChangeField(1); });
    this->connect(ui->pushButton_down,&QPushButton::clicked,[this]{ buttonChangeField(2); });

    // dot button
    this->connect(ui->pushButton_dot,&QPushButton::clicked,[this]{ pressNumberButton(','); });

    // clear and delete last symbol buttons
    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(buttonClear()));
    this->connect(ui->pushButton_delLast,SIGNAL(clicked()),this,SLOT(buttonDeleteLast()));

    // mode button
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));

    // events then user change curent values
    this->connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ buttonClear(); fillUpBottomBox(); });
    this->connect(ui->comboBox_up,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ emit getResult(); });
    this->connect(ui->comboBox_down,QOverload<int>::of(&QComboBox::currentIndexChanged),[this]{ emit getResult(); });

    // signals
    this->connect(this,SIGNAL(getResult()),this,SLOT(updateResult()));
    this->connect(this,SIGNAL(refreshText()),this,SLOT(updateText()));

    buttonChangeField(1);
}

ValueWindow::~ValueWindow()
{
    delete ui;
}

// load styles for window
void ValueWindow::loadStyle(){
    // main window style
    QFile file(":/Value/value_style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();

    // style for disable button
    QFile file2(":/Value/value_disable_button.css");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str2(&file2);
    disable_button_style=file_str2.readAll();
    file2.close();

    // style for enable button
    QFile file3(":/Value/value_enable_button.css");
    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str3(&file3);
    enable_button_style=file_str3.readAll();
    file3.close();

    this->setStyleSheet(content);
}

// load icons for window
void ValueWindow::loadIcons(){
    QPixmap pixmap(":/menu-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size()/2);
}

// add input num to object
void ValueWindow::pressNumberButton(const QChar& button_num){
    // add to up field
    if(curent_field==1){
        up_object.addNum(button_num.toLatin1());
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    }
    // add to down field
    else{
        bottom_object.addNum(button_num.toLatin1());
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
    }

    // update text on another field
    emit getResult();
}

// change curent field and styles
void ValueWindow::buttonChangeField(const int& _field){
    // if no changes
    if(_field==curent_field) return;
    // if chose up field
    if(_field==1){
        curent_field=1;
        ui->textEdit_left->setFontWeight(QFont::Bold);
        ui->textEdit_right->setFontWeight(QFont::Normal);
        ui->pushButton_upp->setEnabled(false);
        ui->pushButton_upp->setStyleSheet(disable_button_style);
        ui->pushButton_down->setEnabled(true);
        ui->pushButton_down->setStyleSheet(enable_button_style);
    }
    // if chose down field
    else{
        curent_field=2;
        ui->textEdit_right->setFontWeight(QFont::Bold);
        ui->textEdit_left->setFontWeight(QFont::Normal);
        ui->pushButton_upp->setEnabled(true);
        ui->pushButton_upp->setStyleSheet(enable_button_style);
        ui->pushButton_down->setEnabled(false);
        ui->pushButton_down->setStyleSheet(disable_button_style);
    }

    emit refreshText();
}

// clear all states
void ValueWindow::buttonClear(){
    up_object.clear();
    bottom_object.clear();

    ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
}

// update display text from objects
void ValueWindow::updateText(){
    ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
}

// delete last symbol
void ValueWindow::buttonDeleteLast(){
    // up field
    if(curent_field==1){
        up_object.deleteLastSymbol();
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
    }
    // bottom field
    else{
        bottom_object.deleteLastSymbol();
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
    }

    // update display text in another field
    emit getResult();
}

// change calculator mode
void ValueWindow::buttonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));

    mode_window->exec();
}

// update window mode if have change
void ValueWindow::updateMode(const int& _mode){
    if(_mode==2) return;
    // signal to main what need change calculator window
    emit changeWindow(_mode);
    this->hide();
}

// update text in field then change text
void ValueWindow::updateResult(){
    // set empty text if curent up object clear
    if(curent_field==1 && up_object.toString()==""){
        bottom_object.clear();
        ui->textEdit_right->setText(QString::fromStdString(bottom_object.toString()));
        return;
    }
    // set empty text if curent bottom object clear
    if(curent_field==2 && bottom_object.toString()==""){
        up_object.clear();
        ui->textEdit_left->setText(QString::fromStdString(up_object.toString()));
        return;
    }
    // get value types
    std::string main=ui->comboBox->currentText().toStdString(), upp=ui->comboBox_up->currentText().toStdString();
    std::string down=ui->comboBox_down->currentText().toStdString();
    // get value in curent field
    std::string value=(curent_field==1)?up_object.toString():bottom_object.toString();
    QString temp="";
    // get result
    if(curent_field==1){
        temp=QString::fromStdString(value_info.getMullNum(main,upp,down,value));
        bottom_object.setFullNum(temp.toStdString());
        bottom_object.checkNum();
        temp=QString::fromStdString(bottom_object.toString());
        ui->textEdit_right->setText(temp);
    }
    else{
        temp=QString::fromStdString(value_info.getMullNum(main,down,upp,value));
        up_object.setFullNum(temp.toStdString());
        up_object.checkNum();
        temp=QString::fromStdString(up_object.toString());
        ui->textEdit_left->setText(temp);
    }
}

// fill child value type then chose main type
void ValueWindow::fillUpBottomBox(){
    ui->comboBox_up->clear();
    ui->comboBox_down->clear();
    // get names of types from value object
    std::vector<std::string> temp=value_info.getSecond(ui->comboBox->currentText().toStdString());
    // set names in combo box
    for(auto x:temp){
        ui->comboBox_up->addItem(QString::fromStdString(x));
        ui->comboBox_down->addItem(QString::fromStdString(x));
    }
}
