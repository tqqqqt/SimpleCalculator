#include <QtTest>

#include "./../Calculator/source/programmistobject.h"

class programmistobject : public QObject
{
    Q_OBJECT

public:
    programmistobject();
    ~programmistobject();

private slots:
    void test_addNum_2_correct();
    void test_addNum_2_out_of_count_symbols();
    void test_addNum_8_correct();
    void test_addNum_8_out_of_count_symbols();
    void test_addNum_10_correct();
    void test_addNum_10_out_of_count_symbols();
    void test_addNum_16_correct();
    void test_addNum_16_out_of_count_symbols();

    void test_addMinus_empty_num();
    void test_addMinus_zero_in_num();
    void test_addMinus_correct();
    void test_addMinus_from_negative_to_positive();

    void test_deleteLastSymbol_2_empty();
    void test_deleteLastSymbol_2_correct();
    void test_deleteLastSymbol_8_empty();
    void test_deleteLastSymbol_8_correct();
    void test_deleteLastSymbol_10_empty();
    void test_deleteLastSymbol_10_negative_num();
    void test_deleteLastSymbol_10_correct();
    void test_deleteLastSymbol_16_empty();
    void test_deleteLastSymbol_16_correct();

    void test_changeSystem_exception_incorect_system();
    void test_changeSystem_correct();

    void test_setCount_exception_incorect_count();
    void test_setCount_correct();

    void test_moveLeft_empty();
    void test_moveLeft_full_count_nums();
    void test_moveLeft_correct();

    void test_moveRight_empty();
    void test_moveRight_one_num();
    void test_moveRight_correct();
};

programmistobject::programmistobject(){ }
programmistobject::~programmistobject(){ }

void programmistobject::test_addNum_2_correct(){
    ProgrammistObject object;
    QString result="1", curent_result="";

    object.changeSystem(2);
    object.addNum('1');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_2_out_of_count_symbols(){
    ProgrammistObject object;
    QString result="1111", curent_result="";

    object.changeSystem(2);
    object.setCount(1);
    object.addNum('1');
    object.addNum('1');
    object.addNum('1');
    object.addNum('1');
    object.addNum('1');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_8_correct(){
    ProgrammistObject object;
    QString result="2", curent_result="";

    object.changeSystem(8);
    object.addNum('2');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_8_out_of_count_symbols(){
    ProgrammistObject object;
    QString result="7", curent_result="";

    object.changeSystem(8);
    object.setCount(1);
    object.addNum('7');
    object.addNum('1');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_10_correct(){
    ProgrammistObject object;
    QString result="3", curent_result="";

    object.changeSystem(10);
    object.addNum('3');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_10_out_of_count_symbols(){
    ProgrammistObject object;
    QString result="7", curent_result="";

    object.changeSystem(10);
    object.setCount(1);
    object.addNum('7');
    object.addNum('1');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_16_correct(){
    ProgrammistObject object;
    QString result="4", curent_result="";

    object.changeSystem(16);
    object.addNum('4');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addNum_16_out_of_count_symbols(){
    ProgrammistObject object;
    QString result="7", curent_result="";

    object.changeSystem(16);
    object.setCount(1);
    object.addNum('7');
    object.addNum('1');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addMinus_empty_num(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.addMinus();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addMinus_zero_in_num(){
    ProgrammistObject object;
    QString result="0", curent_result="";

    object.addNum('0');
    object.addMinus();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addMinus_correct(){
    ProgrammistObject object;
    QString result="-2", curent_result="";

    object.addNum('2');
    object.addMinus();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_addMinus_from_negative_to_positive(){
    ProgrammistObject object;
    QString result="2", curent_result="";

    object.addNum('2');
    object.addMinus();
    object.addMinus();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_2_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.changeSystem(2);
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_2_correct(){
    ProgrammistObject object;
    QString result="1", curent_result="";

    object.changeSystem(2);
    object.addNum('1');
    object.addNum('0');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_8_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.changeSystem(8);
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_8_correct(){
    ProgrammistObject object;
    QString result="2", curent_result="";

    object.changeSystem(8);
    object.addNum('2');
    object.addNum('3');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_10_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.changeSystem(10);
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_10_negative_num(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.changeSystem(10);
    object.addNum('2');
    object.addMinus();
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_10_correct(){
    ProgrammistObject object;
    QString result="5", curent_result="";

    object.changeSystem(10);
    object.addNum('5');
    object.addNum('6');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_16_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.changeSystem(16);
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_deleteLastSymbol_16_correct(){
    ProgrammistObject object;
    QString result="6", curent_result="";

    object.changeSystem(16);
    object.addNum('6');
    object.addNum('6');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_changeSystem_exception_incorect_system(){
    ProgrammistObject object;
    QString result="use only 2, 8, 10, 16 systems";

    try{
        object.changeSystem(24);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void programmistobject::test_changeSystem_correct(){
    ProgrammistObject object;
    QString result="A", curent_result="";

    object.changeSystem(16);
    object.addNum('A');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_setCount_exception_incorect_count(){
    ProgrammistObject object;
    QString result="count <= 0";

    try{
        object.setCount(-2);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void programmistobject::test_setCount_correct(){
    ProgrammistObject object;
    QString result="1111", curent_result="";

    object.changeSystem(2);
    object.setCount(1);
    object.addNum('1');
    object.addMinus();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveLeft_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.moveLeft();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveLeft_full_count_nums(){
    ProgrammistObject object;
    QString result="1111", curent_result="";

    object.setCount(1);
    object.changeSystem(2);
    object.addNum('1');
    object.addMinus();
    object.moveLeft();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveLeft_correct(){
    ProgrammistObject object;
    QString result="24", curent_result="";

    object.addNum('1');
    object.addNum('2');
    object.moveLeft();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveRight_empty(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.moveRight();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveRight_one_num(){
    ProgrammistObject object;
    QString result="", curent_result="";

    object.addNum('1');
    object.moveRight();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void programmistobject::test_moveRight_correct(){
    ProgrammistObject object;
    QString result="6", curent_result="";

    object.changeSystem(10);
    object.addNum('1');
    object.addNum('2');
    object.moveRight();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(programmistobject)

#include "tst_programmistobject.moc"
