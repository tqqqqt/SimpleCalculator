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
    void test_setVector_simple_operators();
    void test_setVector_special_operators();

    void test_getResult_exception_result();
    void test_getResult_simple_operators();
    void test_getResult_special_operators();
    void test_getResult_functions();
    void test_getResult_other_operators();

    void test_getResultWithVariable_exception_result();
    void test_getResultWithVariable_simple_operators();
    void test_getResultWithVariable_special_operators();
    void test_getResultWithVariable_functions();
    void test_getResultWithVariable_other_operators();
    void test_getResultWithVariable_variable();

    void test_simplifyExpression_simple_operators();
    void test_simplifyExpression_special_operators();
    void test_simplifyExpression_functions();
    void test_simplifyExpression_other_operators();
    void test_simplifyExpression_variable_with_operator();
    void test_simplifyExpression_variable_with_function();

    void test_setPolishEntry_exception_none();
    void test_setPolishEntry_exception_bracket();
    void test_setPolishEntry_exception_operator_no_num();
    void test_setPolishEntry_exception_function_no_num();
    void test_setPolishEntry_correct_operator();
    void test_setPolishEntry_correct_function();
};

calculatormath::calculatormath(){ }
calculatormath::~calculatormath(){ }

void calculatormath::test_setVector_simple_operators(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(5), result(5), curent_result;
    input_vector[0].addNum('3');
    input_vector[1].addSymbol("*");
    input_vector[2].addNum('2');
    input_vector[3].addSymbol("+");
    input_vector[4].addNum('3');
    result[0].addNum('3');
    result[1].addNum('2');
    result[2].addSymbol("*");
    result[3].addNum('3');
    result[4].addSymbol("+");

    calculator.setVector(input_vector.toStdVector());
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result.size());
    QCOMPARE(curent_result[0].toString(),result[0].toString());
    QCOMPARE(curent_result[1].toString(),result[1].toString());
    QCOMPARE(curent_result[2].toString(),result[2].toString());
    QCOMPARE(curent_result[3].toString(),result[3].toString());
    QCOMPARE(curent_result[4].toString(),result[4].toString());
}

void calculatormath::test_setVector_special_operators(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(7), result(4), curent_result;
    input_vector[0].addSymbol("(");
    input_vector[1].addSymbol("(-");
    input_vector[2].addNum('3');
    input_vector[3].addSymbol(")");
    input_vector[4].addSymbol("*");
    input_vector[5].addNum('3');
    input_vector[6].addSymbol(")");
    result[0].addNum('3');
    result[1].addSymbol("(-");
    result[2].addNum('3');
    result[3].addSymbol("*");

    calculator.setVector(input_vector.toStdVector());
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result.size());
    QCOMPARE(curent_result[0].toString(),result[0].toString());
    QCOMPARE(curent_result[1].toString(),result[1].toString());
    QCOMPARE(curent_result[2].toString(),result[2].toString());
    QCOMPARE(curent_result[3].toString(),result[3].toString());
}

void calculatormath::test_getResult_exception_result(){
    CalculatorMath calculator;
    CalculatorObject temp;
    QVector<CalculatorObject> input_vector(4);
    QString result="nums after calculate more then 1";
    input_vector[0].addNum('2');
    input_vector[1].addNum('4');
    input_vector[2].addSymbol("+");
    input_vector[3].addNum('2');

    try{
        calculator.setVector(input_vector.toStdVector());
        temp=calculator.GetResult();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_getResult_simple_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(9);
    result.addNum('2');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("-");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol("+");
    input_vector[4]=input_vector[0];
    input_vector[5].addSymbol("*");
    input_vector[6]=input_vector[0];
    input_vector[7].addSymbol("/");
    input_vector[8]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.GetResult();

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResult_special_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(8);
    result.addNum('5');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("^(");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol(")");
    input_vector[4].addSymbol("+");
    input_vector[5].addNum('3');
    input_vector[6].addSpecialFunction("mod");
    input_vector[7]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.GetResult();

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResult_functions(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(15);
    result.setFullNum("-2,1495654642");
    input_vector[0].addFunction("Sin(");
    input_vector[1].addNum('2');
    input_vector[2].addSymbol(")");
    input_vector[3].addSymbol("+");
    input_vector[4].addFunction("Cos(");
    input_vector[5]=input_vector[1];
    input_vector[6].addSymbol(")");
    input_vector[7].addSymbol("+");
    input_vector[8].addFunction("Tng(");
    input_vector[9]=input_vector[1];
    input_vector[10].addSymbol(")");
    input_vector[11].addSymbol("+");
    input_vector[12].addFunction("Ctng(");
    input_vector[13]=input_vector[1];
    input_vector[14].addSymbol(")");

    calculator.setVector(input_vector.toStdVector());
    calculator.setFunctionAccuracy(5);
    calculator.setFunctionRadianFlag(true);
    curent_result=calculator.GetResult();

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResult_other_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(14);
    result.addNum('9');
    input_vector[0].addNum('3');
    input_vector[1].addSpecialFunction("!");
    input_vector[2].addSymbol("+");
    input_vector[3].addFunction("Module(");
    input_vector[4].addNum('3');
    input_vector[5].addSymbol(")");
    input_vector[6].addSymbol("+");
    input_vector[7].addFunction("RoundUp(");
    input_vector[8].addNum('3');
    input_vector[9].addSymbol(")");
    input_vector[10].addSymbol("-");
    input_vector[11].addFunction("RoundUp(");
    input_vector[12].addNum('3');
    input_vector[13].addSymbol(")");

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.GetResult();

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResultWithVariable_exception_result(){
    CalculatorMath calculator;
    CalculatorObject temp;
    QVector<CalculatorObject> input_vector(4);
    QString result="nums after calculate more then 1";
    input_vector[0].addNum('2');
    input_vector[1].addNum('4');
    input_vector[2].addSymbol("+");
    input_vector[3].addNum('2');

    try{
        calculator.setVector(input_vector.toStdVector());
        temp=calculator.getResultWithVariable("1");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_getResultWithVariable_simple_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(9);
    result.addNum('2');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("-");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol("+");
    input_vector[4]=input_vector[0];
    input_vector[5].addSymbol("*");
    input_vector[6]=input_vector[0];
    input_vector[7].addSymbol("/");
    input_vector[8]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.getResultWithVariable("1");

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResultWithVariable_special_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(8);
    result.addNum('5');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("^(");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol(")");
    input_vector[4].addSymbol("+");
    input_vector[5].addNum('3');
    input_vector[6].addSpecialFunction("mod");
    input_vector[7]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.getResultWithVariable("1");

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResultWithVariable_functions(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(15);
    result.setFullNum("-2,1495654642");
    input_vector[0].addFunction("Sin(");
    input_vector[1].addNum('2');
    input_vector[2].addSymbol(")");
    input_vector[3].addSymbol("+");
    input_vector[4].addFunction("Cos(");
    input_vector[5]=input_vector[1];
    input_vector[6].addSymbol(")");
    input_vector[7].addSymbol("+");
    input_vector[8].addFunction("Tng(");
    input_vector[9]=input_vector[1];
    input_vector[10].addSymbol(")");
    input_vector[11].addSymbol("+");
    input_vector[12].addFunction("Ctng(");
    input_vector[13]=input_vector[1];
    input_vector[14].addSymbol(")");

    calculator.setVector(input_vector.toStdVector());
    calculator.setFunctionAccuracy(5);
    calculator.setFunctionRadianFlag(true);
    curent_result=calculator.getResultWithVariable("1");

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResultWithVariable_other_operators(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(14);
    result.addNum('9');
    input_vector[0].addNum('3');
    input_vector[1].addSpecialFunction("!");
    input_vector[2].addSymbol("+");
    input_vector[3].addFunction("Module(");
    input_vector[4].addNum('3');
    input_vector[5].addSymbol(")");
    input_vector[6].addSymbol("+");
    input_vector[7].addFunction("RoundUp(");
    input_vector[8].addNum('3');
    input_vector[9].addSymbol(")");
    input_vector[10].addSymbol("-");
    input_vector[11].addFunction("RoundUp(");
    input_vector[12].addNum('3');
    input_vector[13].addSymbol(")");

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.getResultWithVariable("1");

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_getResultWithVariable_variable(){
    CalculatorMath calculator;
    CalculatorObject curent_result, result;
    QVector<CalculatorObject> input_vector(3);
    result.addNum('4');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("+");
    input_vector[2].addVariable();

    calculator.setVector(input_vector.toStdVector());
    curent_result=calculator.getResultWithVariable("2");

    QCOMPARE(curent_result.toString(),result.toString());
}

void calculatormath::test_simplifyExpression_simple_operators(){
    CalculatorMath calculator;
    CalculatorObject result;
    QVector<CalculatorObject> input_vector(9), curent_result;
    int result_size=1;
    result.addNum('2');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("-");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol("+");
    input_vector[4]=input_vector[0];
    input_vector[5].addSymbol("*");
    input_vector[6]=input_vector[0];
    input_vector[7].addSymbol("/");
    input_vector[8]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result.toString());
}

void calculatormath::test_simplifyExpression_special_operators(){
    CalculatorMath calculator;
    CalculatorObject result;
    QVector<CalculatorObject> input_vector(8), curent_result;
    int result_size=1;
    result.addNum('5');
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("^(");
    input_vector[2]=input_vector[0];
    input_vector[3].addSymbol(")");
    input_vector[4].addSymbol("+");
    input_vector[5].addNum('3');
    input_vector[6].addSpecialFunction("mod");
    input_vector[7]=input_vector[0];

    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result.toString());
}

void calculatormath::test_simplifyExpression_functions(){
    CalculatorMath calculator;
    CalculatorObject result;
    QVector<CalculatorObject> input_vector(15), curent_result;
    int result_size=1;
    result.setFullNum("-2,1495654642");
    input_vector[0].addFunction("Sin(");
    input_vector[1].addNum('2');
    input_vector[2].addSymbol(")");
    input_vector[3].addSymbol("+");
    input_vector[4].addFunction("Cos(");
    input_vector[5]=input_vector[1];
    input_vector[6].addSymbol(")");
    input_vector[7].addSymbol("+");
    input_vector[8].addFunction("Tng(");
    input_vector[9]=input_vector[1];
    input_vector[10].addSymbol(")");
    input_vector[11].addSymbol("+");
    input_vector[12].addFunction("Ctng(");
    input_vector[13]=input_vector[1];
    input_vector[14].addSymbol(")");

    calculator.setFunctionAccuracy(5);
    calculator.setFunctionRadianFlag(true);
    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result.toString());
}

void calculatormath::test_simplifyExpression_other_operators(){
    CalculatorMath calculator;
    CalculatorObject result;
    QVector<CalculatorObject> input_vector(14), curent_result;
    int result_size=1;
    result.addNum('9');
    input_vector[0].addNum('3');
    input_vector[1].addSpecialFunction("!");
    input_vector[2].addSymbol("+");
    input_vector[3].addFunction("Module(");
    input_vector[4].addNum('3');
    input_vector[5].addSymbol(")");
    input_vector[6].addSymbol("+");
    input_vector[7].addFunction("RoundUp(");
    input_vector[8].addNum('3');
    input_vector[9].addSymbol(")");
    input_vector[10].addSymbol("-");
    input_vector[11].addFunction("RoundUp(");
    input_vector[12].addNum('3');
    input_vector[13].addSymbol(")");

    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result.toString());
}

void calculatormath::test_simplifyExpression_variable_with_operator(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(3), curent_result, result(3);
    int result_size=3;
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("+");
    input_vector[2].addVariable();
    result[0].addNum('2');
    result[1].addVariable();
    result[2].addSymbol("+");

    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result[0].toString());
    QCOMPARE(curent_result[1].toString(),result[1].toString());
    QCOMPARE(curent_result[2].toString(),result[2].toString());
}

void calculatormath::test_simplifyExpression_variable_with_function(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(3), curent_result, result(2);
    int result_size=2;
    input_vector[0].addFunction("Sin(");
    input_vector[1].addVariable();
    input_vector[2].addSymbol(")");
    result[0].addVariable();
    result[1].addFunction("Sin(");

    calculator.setVector(input_vector.toStdVector());
    calculator.simplifyExpression();
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),result[0].toString());
    QCOMPARE(curent_result[1].toString(),result[1].toString());
}

void calculatormath::test_setPolishEntry_exception_none(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(1);
    QString result="none type objects";

    try{
        calculator.setPolishEntry(input_vector.toStdVector());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_setPolishEntry_exception_bracket(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(1);
    QString result="find brackets";
    input_vector[0].addSymbol("(");

    try{
        calculator.setPolishEntry(input_vector.toStdVector());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_setPolishEntry_exception_operator_no_num(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(2);
    QString result="no objects before operator";
    input_vector[0].addNum('2');
    input_vector[1].addSymbol("+");

    try{
        calculator.setPolishEntry(input_vector.toStdVector());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_setPolishEntry_exception_function_no_num(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(1);
    QString result="no nums before function";
    input_vector[0].addFunction("Sin(");

    try{
        calculator.setPolishEntry(input_vector.toStdVector());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatormath::test_setPolishEntry_correct_operator(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(3), curent_result;
    int result_size=3;
    input_vector[0].addNum('2');
    input_vector[1].addNum('2');
    input_vector[2].addSymbol("+");

    calculator.setPolishEntry(input_vector.toStdVector());
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),input_vector[0].toString());
    QCOMPARE(curent_result[1].toString(),input_vector[1].toString());
    QCOMPARE(curent_result[2].toString(),input_vector[2].toString());
}

void calculatormath::test_setPolishEntry_correct_function(){
    CalculatorMath calculator;
    QVector<CalculatorObject> input_vector(2), curent_result;
    int result_size=2;
    input_vector[0].addNum('2');
    input_vector[1].addFunction("Sin(");

    calculator.setPolishEntry(input_vector.toStdVector());
    curent_result=QVector<CalculatorObject>::fromStdVector(calculator.getPolishEntry());

    QCOMPARE(curent_result.size(),result_size);
    QCOMPARE(curent_result[0].toString(),input_vector[0].toString());
    QCOMPARE(curent_result[1].toString(),input_vector[1].toString());
}

QTEST_APPLESS_MAIN(calculatormath)

#include "tst_calculatormath.moc"
