#include "programmistwindow.h"
#include "ui_programmistwindow.h"

ProgrammistWindow::ProgrammistWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammistWindow)
{
    loadStyle();
    ui->setupUi(this);
    ui->pushButton_dot->setStyleSheet(disable_button_style); // not used in with mode
    loadIcons();

    object=ProgrammistObject();
    buttonChangeSystem(10); // in default curent system is 10
    QSettings *settings=new QSettings("tqqqqt","calculator");
    if(!settings->contains("progr/count")) settings->setValue("progr/count",5);
    object.setCount(settings->value("progr/count",5).toInt());
    delete settings;

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

    // symbol buttons
    this->connect(ui->pushButton_A,&QPushButton::clicked,[this]{ pressNumberButton('A'); });
    this->connect(ui->pushButton_B,&QPushButton::clicked,[this]{ pressNumberButton('B'); });
    this->connect(ui->pushButton_C,&QPushButton::clicked,[this]{ pressNumberButton('C'); });
    this->connect(ui->pushButton_D,&QPushButton::clicked,[this]{ pressNumberButton('D'); });
    this->connect(ui->pushButton_E,&QPushButton::clicked,[this]{ pressNumberButton('E'); });
    this->connect(ui->pushButton_F,&QPushButton::clicked,[this]{ pressNumberButton('F'); });

    // minus button
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(pressMinusButton()));

    // move buttons
    this->connect(ui->pushButton_move_left,&QPushButton::clicked,[this]{ pressMoveButton(-1); });
    this->connect(ui->pushButton_move_right,&QPushButton::clicked,[this]{ pressMoveButton(1); });

    // clear and delete last symbol buttons
    this->connect(ui->pushButton_clear,&QPushButton::clicked,[this]{ buttonClear(); });
    this->connect(ui->pushButton_delLast,&QPushButton::clicked,[this]{ buttonDeleteLast(); });

    // system buttons
    this->connect(ui->pushButton_hex,&QPushButton::clicked,[this]{ buttonChangeSystem(16); });
    this->connect(ui->pushButton_dec,&QPushButton::clicked,[this]{ buttonChangeSystem(10); });
    this->connect(ui->pushButton_oct,&QPushButton::clicked,[this]{ buttonChangeSystem(8); });
    this->connect(ui->pushButton_bin,&QPushButton::clicked,[this]{ buttonChangeSystem(2); });

    // mode button
    this->connect(ui->pushButton_mode,SIGNAL(clicked()),this,SLOT(buttonChangeMode()));

    // signals
    this->connect(this,SIGNAL(getResult()),this,SLOT(updateResult()));
    this->connect(ui->action_settings,SIGNAL(triggered()),this,SLOT(openSettings()));
}

ProgrammistWindow::~ProgrammistWindow()
{
    delete ui;
}

// load styles for buttons and future use
void ProgrammistWindow::loadStyle(){
    // window style
    QFile file(":/Programmist/programmist_style.css");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str(&file);
    QString content=file_str.readAll();
    file.close();

    // style for disable buttons
    QFile file2(":/Programmist/programmist_disable_button.css");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str2(&file2);
    disable_button_style=file_str2.readAll();
    file2.close();

    // style for enables buttons
    QFile file3(":/Programmist/programmist_enable_button.css");
    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str3(&file3);
    enable_button_style=file_str3.readAll();
    file3.close();

    // style for curent chose system
    QFile file4(":/Programmist/programmist_curent_system.css");
    file4.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file_str4(&file4);
    curent_system_button_style=file_str4.readAll();
    file4.close();

    this->setStyleSheet(content);
}

// load and set icons on buttons
void ProgrammistWindow::loadIcons(){
    QPixmap pixmap(":/menu-icon.png");
    QIcon button_icon(pixmap);
    ui->pushButton_mode->setIcon(button_icon);
    ui->pushButton_mode->setIconSize(pixmap.rect().size()/2);
}

// display nums in all systems
void ProgrammistWindow::updateResult(){
    // display num in curent system
    ui->textEdit_input->setText(QString::fromStdString(object.toString()));
    // display nums in all systems
    ui->lineEdit_bin->setText(QString::fromStdString(object.toString2()));
    ui->lineEdit_oct->setText(QString::fromStdString(object.toString8()));
    ui->lineEdit_dec->setText(QString::fromStdString(object.toString10()));
    ui->lineEdit_hex->setText(QString::fromStdString(object.toString16()));
}

// added num to object
void ProgrammistWindow::pressNumberButton(const QChar& _num){
    try {
        object.addNum(_num.toLatin1());
        // display new text in all systems
        emit getResult();
    }
    catch (std::exception &exp) {
        object.clear();
        ui->textEdit_input->setText(exp.what());
    }
}

// add minus to num
void ProgrammistWindow::pressMinusButton(){
    // add minus to num
    object.addMinus();

    // display all nums in systems after changes
    emit getResult();
}

// move bin bite in left or right order
void ProgrammistWindow::pressMoveButton(const int& _direction){
    // if object text is null
    if(object.getLength()==0) return;
    // move bit in left (-1) order or right (1) order
    if(_direction==-1) object.moveLeft();
    else object.moveRight();
    // display new nums in all systems after changes
    emit getResult();
}

// clear all states in window
void ProgrammistWindow::buttonClear(){
    ui->textEdit_input->clear();
    ui->lineEdit_hex->clear();
    ui->lineEdit_dec->clear();
    ui->lineEdit_oct->clear();
    ui->lineEdit_bin->clear();

    object.clear();
}

// delete last input symbol
void ProgrammistWindow::buttonDeleteLast(){
    // if no symbol in object
    if(object.getLength()==0) return;

    object.deleteLastSymbol();
    // display new nums in all systems after changes
    emit getResult();
}

// open mode window
void ProgrammistWindow::buttonChangeMode(){
    ModeWindow* mode_window=new ModeWindow(this);
    this->connect(mode_window,SIGNAL(changeMode(int)),this,SLOT(updateMode(int)));

    mode_window->exec();
}

// update curent window mode
void ProgrammistWindow::updateMode(const int& _mode){
    // if chose curent programmist mode
    if(_mode==3) return;

    // signal to main what need change curent main window
    emit changeWindow(_mode);
    this->hide();
}

// change curent system
void ProgrammistWindow::buttonChangeSystem(const int& _system){
    // change system in object and display system text
    object.changeSystem(_system);
    ui->textEdit_input->setText(QString::fromStdString(object.toString()));

    // set enable buttons for curent system
    switch(_system){
    case 2:
        setSymbolButtonsEnable(false,disable_button_style);
        setNumsButtonsEnable(false,disable_button_style);
        setSystemButtonsEnable();

        ui->pushButton_n0->setEnabled(true);
        ui->pushButton_n0->setStyleSheet(enable_button_style);
        ui->pushButton_n1->setEnabled(true);
        ui->pushButton_n1->setStyleSheet(enable_button_style);

        ui->pushButton_bin->setEnabled(false);
        ui->pushButton_bin->setStyleSheet(curent_system_button_style);
        break;
    case 8:
        setSymbolButtonsEnable(false,disable_button_style);
        setNumsButtonsEnable(true,enable_button_style);
        setSystemButtonsEnable();

        ui->pushButton_n9->setEnabled(false);
        ui->pushButton_n9->setStyleSheet(disable_button_style);
        ui->pushButton_n8->setEnabled(false);
        ui->pushButton_n8->setStyleSheet(disable_button_style);

        ui->pushButton_oct->setEnabled(false);
        ui->pushButton_oct->setStyleSheet(curent_system_button_style);
        break;
    case 10:
        setSymbolButtonsEnable(false,disable_button_style);
        setNumsButtonsEnable(true,enable_button_style);
        setSystemButtonsEnable();

        ui->pushButton_dec->setEnabled(false);
        ui->pushButton_dec->setStyleSheet(curent_system_button_style);
        break;
    case 16:
        setSymbolButtonsEnable(true,enable_button_style);
        setNumsButtonsEnable(true,enable_button_style);
        setSystemButtonsEnable();

        ui->pushButton_hex->setEnabled(false);
        ui->pushButton_hex->setStyleSheet(curent_system_button_style);
        break;
    }
}

// set all symbol buttons enable flag and enable style string
void ProgrammistWindow::setSymbolButtonsEnable(const bool& _flag, const QString& _style){
    ui->pushButton_A->setEnabled(_flag);
    ui->pushButton_B->setEnabled(_flag);
    ui->pushButton_C->setEnabled(_flag);
    ui->pushButton_D->setEnabled(_flag);
    ui->pushButton_E->setEnabled(_flag);
    ui->pushButton_F->setEnabled(_flag);

    ui->pushButton_A->setStyleSheet(_style);
    ui->pushButton_B->setStyleSheet(_style);
    ui->pushButton_C->setStyleSheet(_style);
    ui->pushButton_D->setStyleSheet(_style);
    ui->pushButton_E->setStyleSheet(_style);
    ui->pushButton_F->setStyleSheet(_style);
}

// set all num buttons enable flag and enable style string
void ProgrammistWindow::setNumsButtonsEnable(const bool& _flag, const QString& _style){
    ui->pushButton_n0->setEnabled(_flag);
    ui->pushButton_n1->setEnabled(_flag);
    ui->pushButton_n2->setEnabled(_flag);
    ui->pushButton_n3->setEnabled(_flag);
    ui->pushButton_n4->setEnabled(_flag);
    ui->pushButton_n5->setEnabled(_flag);
    ui->pushButton_n6->setEnabled(_flag);
    ui->pushButton_n7->setEnabled(_flag);
    ui->pushButton_n8->setEnabled(_flag);
    ui->pushButton_n9->setEnabled(_flag);

    ui->pushButton_n0->setStyleSheet(_style);
    ui->pushButton_n1->setStyleSheet(_style);
    ui->pushButton_n2->setStyleSheet(_style);
    ui->pushButton_n3->setStyleSheet(_style);
    ui->pushButton_n4->setStyleSheet(_style);
    ui->pushButton_n5->setStyleSheet(_style);
    ui->pushButton_n6->setStyleSheet(_style);
    ui->pushButton_n7->setStyleSheet(_style);
    ui->pushButton_n8->setStyleSheet(_style);
    ui->pushButton_n9->setStyleSheet(_style);
}

// set all system buttons enable and enable style
void ProgrammistWindow::setSystemButtonsEnable(){
    ui->pushButton_hex->setEnabled(true);
    ui->pushButton_dec->setEnabled(true);
    ui->pushButton_oct->setEnabled(true);
    ui->pushButton_bin->setEnabled(true);

    ui->pushButton_hex->setStyleSheet(enable_button_style);
    ui->pushButton_dec->setStyleSheet(enable_button_style);
    ui->pushButton_oct->setStyleSheet(enable_button_style);
    ui->pushButton_bin->setStyleSheet(enable_button_style);
}

// open settings window and wait result
void ProgrammistWindow::openSettings(){
    ProgrammistSettingsWindow *settings_window=new ProgrammistSettingsWindow(this);
    this->connect(settings_window,SIGNAL(acceptSettings()),this,SLOT(updateSettings()));
    settings_window->exec();
}

// load new settings after accept changes in settings window
void ProgrammistWindow::updateSettings(){
    QSettings *settings=new QSettings("tqqqqt","calculator");
    object.setCount(settings->value("progr/count",5).toInt());
    delete settings;
}
