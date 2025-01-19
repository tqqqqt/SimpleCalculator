#include <QtTest>

#include "./../Calculator/source/graphicsinfoobject.h"

class graphicsinnfoobject : public QObject
{
    Q_OBJECT

private:
    int argc=0;

public:
    graphicsinnfoobject();
    ~graphicsinnfoobject();

private slots:
    void test_setDisplayText();

    void test_getDisplayText();

    void test_setPolishEntry();

    void test_getPolishEntry();

    void test_setGraphics();

    void test_clearGraphic();

    void test_setGraphicsColor();

    void test_getGraphicsColor();

    void test_getGraphicsFlag();

    void test_getColorFlag();

};

graphicsinnfoobject::graphicsinnfoobject(){ }

graphicsinnfoobject::~graphicsinnfoobject(){ }

void graphicsinnfoobject::test_setDisplayText(){
    QGuiApplication app(argc,nullptr);

    GraphicsInfoObject object;
    std::string input_str="2+x";
    QString curent_str="", result_str="y = 2+x";

    object.setDisplayText(input_str);
    curent_str=QString::fromStdString(object.getDisplayText());

    QCOMPARE(curent_str,result_str);
}

void graphicsinnfoobject::test_getDisplayText(){
    QGuiApplication app(argc,nullptr);

    GraphicsInfoObject object;
    std::string input_str="2+x";
    QString curent_str_1="", curent_str_2="";
    QString result_str_1="y = ", result_str_2="y = 2+x";

    curent_str_1=QString::fromStdString(object.getDisplayText());
    object.setDisplayText(input_str);
    curent_str_2=QString::fromStdString(object.getDisplayText());

    QCOMPARE(curent_str_1,result_str_1);
    QCOMPARE(curent_str_2,result_str_2);
}

void graphicsinnfoobject::test_setPolishEntry(){
    QGuiApplication app(argc,nullptr);

    GraphicsInfoObject object;
    CalculatorObject calculator_object;
    std::vector<CalculatorObject> curent_polish_entry, temp_polish_entry;
    size_t curent_size=0, result_size=0;
    QString curent_element="", result_element="";

    calculator_object.addNum('1');
    temp_polish_entry.push_back(calculator_object);
    calculator_object.clear();
    calculator_object.addSymbol("+");
    temp_polish_entry.push_back(calculator_object);
    calculator_object.clear();
    calculator_object.addNum('1');
    temp_polish_entry.push_back(calculator_object);

    object.setPolishEntry(temp_polish_entry);

    curent_polish_entry=object.getPolishEntry();

    curent_size=curent_polish_entry.size();
    result_size=temp_polish_entry.size();

    QCOMPARE(curent_size,result_size);
    for(size_t i=0;i<result_size;i++){
        curent_element=QString::fromStdString(curent_polish_entry[i].toString());
        result_element=QString::fromStdString(temp_polish_entry[i].toString());
        QCOMPARE(curent_element,result_element);
    }
}

void graphicsinnfoobject::test_getPolishEntry(){
    QGuiApplication app(argc,nullptr);

    GraphicsInfoObject object;
    CalculatorObject calculator_object;
    std::vector<CalculatorObject> curent_polish_entry, temp_polish_entry;
    size_t curent_size=0, result_size=0;
    QString curent_element="", result_element="";

    curent_polish_entry=object.getPolishEntry();
    curent_size=curent_polish_entry.size();

    QCOMPARE(curent_size,result_size);

    calculator_object.addNum('1');
    temp_polish_entry.push_back(calculator_object);
    calculator_object.clear();
    calculator_object.addSymbol("+");
    temp_polish_entry.push_back(calculator_object);
    calculator_object.clear();
    calculator_object.addNum('1');
    temp_polish_entry.push_back(calculator_object);

    object.setPolishEntry(temp_polish_entry);

    curent_polish_entry=object.getPolishEntry();

    curent_size=curent_polish_entry.size();
    result_size=temp_polish_entry.size();

    QCOMPARE(curent_size,result_size);
    for(size_t i=0;i<result_size;i++){
        curent_element=QString::fromStdString(curent_polish_entry[i].toString());
        result_element=QString::fromStdString(temp_polish_entry[i].toString());
        QCOMPARE(curent_element,result_element);
    }
}

void graphicsinnfoobject::test_setGraphics(){
    QGuiApplication app(argc,nullptr);

    QPixmap pixmap(1,1);
    GraphicsInfoObject object;
    bool curent_flag=false, result_flag=true;

    object.setGraphic(pixmap);

    curent_flag=object.getGraphicFlag();

    QCOMPARE(curent_flag,result_flag);
}

void graphicsinnfoobject::test_clearGraphic(){
    QGuiApplication app(argc,nullptr);

    QPixmap pixmap(1,1);
    GraphicsInfoObject object;
    bool curent_flag=false;
    bool result_1=false, result_2=true, result_3=false;

    curent_flag=object.getGraphicFlag();
    QCOMPARE(curent_flag,result_1);

    object.setGraphic(pixmap);
    curent_flag=object.getGraphicFlag();
    QCOMPARE(curent_flag,result_2);

    object.clearGraphic();
    curent_flag=object.getGraphicFlag();
    QCOMPARE(curent_flag,result_3);
}

void graphicsinnfoobject::test_setGraphicsColor(){
    QGuiApplication app(argc,nullptr);

    Qt::GlobalColor curent_color=Qt::transparent, result_color=Qt::red;
    GraphicsInfoObject object;

    object.setGraphicsColor(Qt::red);
    curent_color=object.getGraphicsColor();

    QCOMPARE(curent_color,result_color);
}

void graphicsinnfoobject::test_getGraphicsColor(){
    QGuiApplication app(argc,nullptr);

    Qt::GlobalColor curent_color=Qt::transparent;
    Qt::GlobalColor result_color_1=Qt::black, result_color_2=Qt::red;
    GraphicsInfoObject object;

    curent_color=object.getGraphicsColor();
    QCOMPARE(curent_color,result_color_1);

    object.setGraphicsColor(Qt::red);
    curent_color=object.getGraphicsColor();

    QCOMPARE(curent_color,result_color_2);
}

void graphicsinnfoobject::test_getGraphicsFlag(){
    QGuiApplication app(argc,nullptr);

    QPixmap pixmap(1,1);
    GraphicsInfoObject object;
    bool curent_flag=false;
    bool result_1=false, result_2=true;

    curent_flag=object.getGraphicFlag();
    QCOMPARE(curent_flag,result_1);

    object.setGraphic(pixmap);
    curent_flag=object.getGraphicFlag();
    QCOMPARE(curent_flag,result_2);
}

void graphicsinnfoobject::test_getColorFlag(){
    QGuiApplication app(argc,nullptr);

    Qt::GlobalColor color=Qt::red;
    GraphicsInfoObject object;
    bool curent_flag=false;
    bool result_1=false, result_2=true;

    curent_flag=object.getColorFlag();
    QCOMPARE(curent_flag,result_1);

    object.setGraphicsColor(color);
    curent_flag=object.getColorFlag();
    QCOMPARE(curent_flag,result_2);
}

QTEST_APPLESS_MAIN(graphicsinnfoobject)

#include "tst_graphicsinnfoobject.moc"
