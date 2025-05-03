#include <QtTest>

#include "../Calculator/source/calculatorobject.h"

class calculatorobject : public QObject
{
    Q_OBJECT

public:
    calculatorobject();
    ~calculatorobject();

private slots:
    void test_addNum_exception_input();
    void test_addNum_no_add_object_type();
    void test_addNum_no_change_zero();
    void test_addNum_cange_zero();
    void test_addNum_no_add_dot();

    void test_addSymbol_exception_input();
    void test_addSymbol_not_none();
    void test_addSymbol_minus_bracket();
    void test_addSymbol_open_bracket();
    void test_addSymbol_close_bracket();
    void test_addSymbol_operator();
    void test_addSymbol_mod();

    void test_addFunction_exception_input();
    void test_addFunction_not_none();
    void test_addFunction_correct();

    void test_addSpecialFunction_exception_input();
    void test_addSpecialFunction_not_none();
    void test_addSpecialFunction_degree();
    void test_addSpecialFunction_factorial();

    void test_addVariable_not_none();
    void test_addVariable_correct();

    void test_getOnlyNum_incorect_type();
    void test_getOnlyNum_negative_num();
    void test_getOnlyNum_positive_num();

    void test_setFullNum_empty_num();
    void test_setFullNum_only_minus();
    void test_setFullNum_incorect_symbol();
    void test_setFullNum_incorect_count_dot();
    void test_setFullNum_correct();

    void test_checkNum_incorect_type();
    void test_checkNum_already_check();
    void test_checkNum_delete_first_zeros();
    void test_checkNum_save_nums_after_dot();
    void test_checkNum_delete_nums_after_dot();

    void test_deleteLastSymbol_empty_text();
    void test_deleteLastSymbol_not_num();
    void test_deleteLastSymbol_minus_bracket();
    void test_deleteLastSymbol_end_dot();
    void test_deleteLastSymbol_end_clear();
    void test_deleteLastSymbol_change_type();
};

calculatorobject::calculatorobject(){ }
calculatorobject::~calculatorobject(){ }

void calculatorobject::test_addNum_exception_input(){
    CalculatorObject object;
    QString result="input not in [0-9] and ','";

    try{
        object.addNum('a');
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_addNum_no_add_object_type(){
    CalculatorObject object;
    QString result="Sin(", curent_result="";

    object.addFunction("Sin(");
    object.addNum('2');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addNum_no_change_zero(){
    CalculatorObject object;
    QString result="0", curent_result="";

    object.addNum('0');
    object.addNum('0');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addNum_cange_zero(){
    CalculatorObject object;
    QString result="2", curent_result="";

    object.addNum('0');
    object.addNum('2');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addNum_no_add_dot(){
    CalculatorObject object;
    QString result="1,", curent_result="";

    object.addNum('1');
    object.addNum(',');
    object.addNum(',');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_exception_input(){
    CalculatorObject object;
    QString result="input not a {+, -, *, /, (-, (, ), mod }";

    try{
        object.addSymbol("a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_addSymbol_not_none(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(");
    object.addSymbol(")");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_minus_bracket(){
    CalculatorObject object;
    QString result="(-", curent_result="";

    object.addSymbol("(-");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_open_bracket(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_close_bracket(){
    CalculatorObject object;
    QString result=")", curent_result="";

    object.addSymbol(")");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_operator(){
    CalculatorObject object;
    QString result="+", curent_result="";

    object.addSymbol("+");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSymbol_mod(){
    CalculatorObject object;
    QString result="mod", curent_result="";

    object.addSymbol("mod");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addFunction_exception_input(){
    CalculatorObject object;
    QString result="input not a {Sin, Cos, Tan, Ctan, Module, Round, ^( }";

    try{
        object.addFunction("a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_addFunction_not_none(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(");
    object.addFunction("Sin(");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addFunction_correct(){
    CalculatorObject object;
    QString result="Sin(", curent_result="";

    object.addFunction("Sin(");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSpecialFunction_exception_input(){
    CalculatorObject object;
    QString result="input not a { !, °, % }";

    try{
        object.addSpecialFunction("a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_addSpecialFunction_not_none(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(");
    object.addSpecialFunction("!");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSpecialFunction_degree(){
    CalculatorObject object;
    QString result="°", curent_result="";

    object.addSpecialFunction("°");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addSpecialFunction_factorial(){
    CalculatorObject object;
    QString result="!", curent_result="";

    object.addSpecialFunction("!");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addVariable_not_none(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(");
    object.addVariable();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_addVariable_correct(){
    CalculatorObject object;
    QString result="x", curent_result="";

    object.addVariable();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_getOnlyNum_incorect_type(){
    CalculatorObject object;
    QString result="object is not num", curent_result;

    try{
        object.addSymbol("(");
        curent_result=QString::fromStdString(object.getOnlyNum().toString());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_getOnlyNum_negative_num(){
    CalculatorObject object, curent_object;
    QString result="-2", curent_result="";

    object.setFullNum("-2");
    curent_object=object.getOnlyNum();
    curent_result=QString::fromStdString(curent_object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_getOnlyNum_positive_num(){
    CalculatorObject object, curent_object;
    QString result="2", curent_result="";

    object.addNum('2');
    curent_object=object.getOnlyNum();
    curent_result=QString::fromStdString(curent_object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_setFullNum_empty_num(){
    CalculatorObject object;
    QString result="length == 0", curent_result="";

    try{
        object.setFullNum("");
        curent_result=QString::fromStdString(object.getOnlyNum().toString());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_setFullNum_only_minus(){
    CalculatorObject object;
    QString result="only minus in num", curent_result="";

    try{
        object.setFullNum("-");
        curent_result=QString::fromStdString(object.getOnlyNum().toString());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_setFullNum_incorect_symbol(){
    CalculatorObject object;
    QString result="incorect symbol in num", curent_result="";

    try{
        object.setFullNum("a");
        curent_result=QString::fromStdString(object.getOnlyNum().toString());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_setFullNum_incorect_count_dot(){
    CalculatorObject object;
    QString result="count dot in num more then one", curent_result="";

    try{
        object.setFullNum("0,0,0");
        curent_result=QString::fromStdString(object.getOnlyNum().toString());
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void calculatorobject::test_setFullNum_correct(){
    CalculatorObject object;
    QString result="-2,3", curent_result="";

    object.setFullNum("-2,3");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_checkNum_incorect_type(){
    CalculatorObject object;
    QString result="Sin(", curent_result="";

    object.addFunction("Sin(");
    object.checkNum();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_checkNum_already_check(){
    CalculatorObject object;
    QString result="1", curent_result="";

    object.addNum('1');
    object.checkNum();
    object.checkNum();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_checkNum_delete_first_zeros(){
    CalculatorObject object;
    QString result="21", curent_result="";

    object.setFullNum("0021");
    object.checkNum();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_checkNum_save_nums_after_dot(){
    CalculatorObject object;
    QString result="0,02", curent_result="";

    object.setFullNum("0,02");
    object.checkNum();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_checkNum_delete_nums_after_dot(){
    CalculatorObject object;
    QString result="2", curent_result="";

    object.setFullNum("2,00");
    object.checkNum();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_empty_text(){
    CalculatorObject object;
    QString result="", curent_result="";

    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_not_num(){
    CalculatorObject object;
    QString result="", curent_result="";

    object.addFunction("Sin(");
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_minus_bracket(){
    CalculatorObject object;
    QString result="(", curent_result="";

    object.addSymbol("(-");
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_end_dot(){
    CalculatorObject object;
    QString result="2", curent_result="";

    object.addNum('2');
    object.addNum(',');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_end_clear(){
    CalculatorObject object;
    QString result="", curent_result="";

    object.addNum('1');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void calculatorobject::test_deleteLastSymbol_change_type(){
    CalculatorObject object;
    QString result="(-", curent_result="";
    CalculatorObject::ObjectsTypes result_type=CalculatorObject::ObjectsTypes::MinusBracket, curent_result_type;

    object.addSymbol("(-");
    object.addNum('2');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());
    curent_result_type=object.getObjectType();

    QCOMPARE(curent_result_type,result_type);
    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(calculatorobject)

#include "tst_calculatorobject.moc"
