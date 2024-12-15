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
    void test_polishEntry_and_getResult_1();
    void test_polishEntry_and_getResult_2();
    void test_polishEntry_and_getResult_3();
    void test_polishEntry_and_getResult_4();
    void test_polishEntry_and_getResult_5();
    void test_polishEntry_and_getResult_6();
    void test_polishEntry_and_getResult_7();
    void test_polishEntry_and_getResult_8();
};

calculatormath::calculatormath(){ }

calculatormath::~calculatormath(){ }

void calculatormath::test_polishEntry_and_getResult_1(){
    CalculatorObject plus, num_2, num_3;
    plus.addSymbol("+");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());
    QCOMPARE(calculator.GetResult().toString(),"5");
}

void calculatormath::test_polishEntry_and_getResult_2(){
    CalculatorObject plus, mull;
    CalculatorObject num_2, num_3;
    plus.addSymbol("+");
    mull.addSymbol("*");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,plus,num_2,mull,num_2};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());
    QCOMPARE(calculator.GetResult().toString(),"6");
}

void calculatormath::test_polishEntry_and_getResult_3(){
    CalculatorObject minus, num_2, num_3;
    minus.addSymbol("-");
    num_2.setFullNum("2");
    num_3.setFullNum("3");
    QVector<CalculatorObject> temp{num_2,minus,num_3};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());
    QCOMPARE(calculator.GetResult().toString(),"(-1)");
}

void calculatormath::test_polishEntry_and_getResult_4(){
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
    QCOMPARE(calculator.GetResult().toString(),"11");
}

void calculatormath::test_polishEntry_and_getResult_5(){
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
    QCOMPARE(calculator.GetResult().toString(),"7");
}

void calculatormath::test_polishEntry_and_getResult_6(){
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
    QCOMPARE(calculator.GetResult().toString(),"25");
}

void calculatormath::test_polishEntry_and_getResult_7(){
    CalculatorObject open_bracket, close_bracket, mull, div, num_2;
    open_bracket.addSymbol("(");
    close_bracket.addSymbol(")");
    mull.addSymbol("*");
    div.addSymbol("/");
    num_2.setFullNum("2");
    QVector<CalculatorObject> temp{open_bracket,open_bracket,num_2,mull,num_2,close_bracket,div,num_2,close_bracket};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());
    QCOMPARE(calculator.GetResult().toString(),"2");
}

void calculatormath::test_polishEntry_and_getResult_8(){
    CalculatorObject plus, mull, num_02;
    plus.addSymbol("+");
    mull.addSymbol("*");
    num_02.setFullNum("0,2");
    QVector<CalculatorObject> temp{num_02,plus,num_02,mull,num_02,plus,num_02,mull,num_02,plus,num_02};

    CalculatorMath calculator;
    calculator.setVector(temp.toStdVector());
    QCOMPARE(calculator.GetResult().toString(),"0,48");
}

QTEST_APPLESS_MAIN(calculatormath)

#include "tst_calculatormath.moc"
