#include <QtTest>

#include "../Calculator/source/calculatorobject.h"
#include "../Calculator/source/calculatormath.h"
#include "../Calculator/source/numbermath.h"

#include <QVector>

class calculatormath : public QObject
{
    Q_OBJECT

public:
    calculatormath();
    ~calculatormath();

private slots:
    void test_setVector_getPolishEntry();

    void test_getResult_1();
    void test_getResult_2();
    void test_getResult_3();
    void test_getResult_4();
    void test_getResult_5();
    void test_getResult_6();
    void test_getResult_7();
    void test_getResult_8();

    void test_setPolighEntry();

    void test_simplifyExpression();

    void test_getResultWithVariable_1();
    void test_getResultWithVariable_2();
    void test_getResultWithVariable_3();
};

calculatormath::calculatormath(){ }

calculatormath::~calculatormath(){ }

void calculatormath::test_setVector_getPolishEntry(){
    CalculatorObject plus, num_2, num_3;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    temp.clear();
    temp={num_2,num_3,plus};

    std::vector<CalculatorObject> curent_result=calculator.getPolishEntry();
    size_t curent_size=curent_result.size(), result_size=temp.size();

    QCOMPARE(curent_size,result_size);

    QString curent_element="", result_element="";
    for(size_t i=0;i<result_size;i++){
        curent_element=QString::fromStdString(curent_result[i].toString());
        result_element=QString::fromStdString(temp[i].toString());
        QCOMPARE(curent_element,result_element);
    }
}

void calculatormath::test_getResult_1(){
    CalculatorObject plus, num_2, num_3;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="5";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_2(){
    CalculatorObject plus, mull;
    CalculatorObject num_2, num_3;
    plus.addSymbol("+");
    mull.addSymbol("*");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,num_2,mull,num_2};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="6";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_3(){
    CalculatorObject minus, num_2, num_3;
    minus.addSymbol("-");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,minus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="(-1)";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_4(){
    CalculatorObject plus, minus, open_bracket, close_bracket, mull;
    CalculatorObject num_2, num_3;
    plus.addSymbol("+");
    minus.addSymbol("-");
    open_bracket.addSymbol("(");
    close_bracket.addSymbol(")");
    mull.addSymbol("*");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,open_bracket,num_2,minus,num_2,plus,open_bracket,num_3,mull,num_3,close_bracket,close_bracket};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="11";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_5(){
    CalculatorObject plus, minus, open_bracket, close_bracket, mull;
    CalculatorObject num_2, num_3;
    plus.addSymbol("+");
    minus.addSymbol("-");
    open_bracket.addSymbol("(");
    close_bracket.addSymbol(")");
    mull.addSymbol("*");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{open_bracket,open_bracket,num_2,plus,num_3,close_bracket,mull,num_2,close_bracket,minus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="7";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_6(){
    CalculatorObject plus, open_bracket, close_bracket, mull;
    CalculatorObject num_2, num_3;
    plus.addSymbol("+");
    open_bracket.addSymbol("(");
    close_bracket.addSymbol(")");
    mull.addSymbol("*");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{open_bracket,num_2,plus,num_3,close_bracket,mull,open_bracket,num_3,plus,num_2,close_bracket};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="25";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_7(){
    CalculatorObject open_bracket, close_bracket, mull, div, num_2;
    open_bracket.addSymbol("(");
    close_bracket.addSymbol(")");
    mull.addSymbol("*");
    div.addSymbol("/");
    num_2.setFullNum("2");
    QVector<CalculatorObject> temp{open_bracket,open_bracket,num_2,mull,num_2,close_bracket,div,num_2,close_bracket};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="2";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResult_8(){
    CalculatorObject plus, mull, num_02;
    plus.addSymbol("+");
    mull.addSymbol("*");
    num_02.setFullNum("0,2");
    QVector<CalculatorObject> temp{num_02,plus,num_02,mull,num_02,plus,num_02,mull,num_02,plus,num_02};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    CalculatorObject result_object;
    QString curent_result, result="0,48";
    result_object=calculator.GetResult();
    curent_result=QString::fromStdString(result_object.toString());
    QCOMPARE(curent_result,result);
}

void calculatormath::test_setPolighEntry(){
    CalculatorObject plus, num_2, num_3;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,num_3,plus};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());

    std::vector<CalculatorObject> curent_result=calculator.getPolishEntry();
    size_t curent_size=curent_result.size(), result_size=temp.size();

    QCOMPARE(curent_size,result_size);

    QString curent_element="", result_element="";
    for(size_t i=0;i<result_size;i++){
        curent_element=QString::fromStdString(curent_result[i].toString());
        result_element=QString::fromStdString(temp[i].toString());
        QCOMPARE(curent_element,result_element);
    }
}

void calculatormath::test_simplifyExpression(){
    CalculatorObject plus, num_2;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    std::vector<CalculatorObject> temp{num_2,num_2,plus,num_2,plus};

    CalculatorMath calculator;
    calculator.setPolishEntry(temp);
    calculator.simplifyExpression();

    std::vector<CalculatorObject> curent_result=calculator.getPolishEntry();
    temp.clear();
    num_2.setFullNum("6");
    temp={num_2};

    size_t curent_size=curent_result.size(), result_size=temp.size();
    QCOMPARE(curent_size,result_size);

    QString curent_element="", result_element="";
    for(size_t i=0;i<result_size;i++){
        curent_element=QString::fromStdString(curent_result[i].toString());
        result_element=QString::fromStdString(temp[i].toString());
        QCOMPARE(curent_element,result_element);
    }
}

void calculatormath::test_getResultWithVariable_1(){
    CalculatorObject plus, num_2, variable;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    variable.addVariable();
    std::vector<CalculatorObject> temp{num_2,variable,plus};

    CalculatorMath calculator;
    calculator.setPolishEntry(temp);

    CalculatorObject curent_object=calculator.getResultWithVariable("2");
    QString curent_result=QString::fromStdString(curent_object.toString()), result="4";

    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResultWithVariable_2(){
    CalculatorObject mull, num_2, variable;
    mull.addSymbol("*");
    num_2.setFullNum("2");
    variable.addVariable();
    std::vector<CalculatorObject> temp{num_2,variable,mull};

    CalculatorMath calculator;
    calculator.setPolishEntry(temp);

    CalculatorObject curent_object=calculator.getResultWithVariable("3");
    QString curent_result=QString::fromStdString(curent_object.toString()), result="6";

    QCOMPARE(curent_result,result);
}

void calculatormath::test_getResultWithVariable_3(){
    CalculatorObject plus, num_2, variable;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    variable.addVariable();
    std::vector<CalculatorObject> temp{num_2,variable,plus,variable,plus};

    CalculatorMath calculator;
    calculator.setPolishEntry(temp);

    CalculatorObject curent_object=calculator.getResultWithVariable("6");
    QString curent_result=QString::fromStdString(curent_object.toString()), result="14";

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(calculatormath)

#include "tst_calculatormath.moc"
