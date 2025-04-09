#include <QtTest>

#include "../Calculator/source/valueobject.h"

class valueobject : public QObject
{
    Q_OBJECT

public:
    valueobject();
    ~valueobject();

private slots:
    void test_addNum_exception_incorect_symbol();
    void test_addNum_incorect_add_dot();
    void test_addNum_double_zero();
    void test_addNum_change_first_zero();
    void test_addNum_double_dot();
    void test_addNum_correct();

    void test_deleleLastSymbol_empty_num();
    void test_deleleLastSymbol_dot_last();
    void test_deleleLastSymbol_zero_last();

    void test_setFullNum_exception_empty_num();
    void test_setFullNum_exception_only_minus();
    void test_setFullNum_exception_incorect_symbol();
    void test_setFullNum_exception_count_dot();
    void test_setFullNum_correct();
};

valueobject::valueobject(){ }
valueobject::~valueobject(){ }

void valueobject::test_addNum_exception_incorect_symbol(){
    ValueObject object;
    QString result="input not a num or dot";

    try{
        object.addNum('a');
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void valueobject::test_addNum_incorect_add_dot(){
    ValueObject object;
    QString result="", curent_result="";

    object.addNum(',');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_addNum_double_zero(){
    ValueObject object;
    QString result="0", curent_result="";

    object.addNum('0');
    object.addNum('0');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_addNum_change_first_zero(){
    ValueObject object;
    QString result="2", curent_result="";

    object.addNum('0');
    object.addNum('2');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_addNum_double_dot(){
    ValueObject object;
    QString result="0,", curent_result="";

    object.addNum('0');
    object.addNum(',');
    object.addNum(',');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_addNum_correct(){
    ValueObject object;
    QString result="2", curent_result="";

    object.addNum('2');
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_deleleLastSymbol_empty_num(){
    ValueObject object;
    QString result="", curent_result="";

    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_deleleLastSymbol_dot_last(){
    ValueObject object;
    QString result="0", curent_result="";

    object.addNum('0');
    object.addNum(',');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_deleleLastSymbol_zero_last(){
    ValueObject object;
    QString result="", curent_result="";

    object.addNum('0');
    object.deleteLastSymbol();
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

void valueobject::test_setFullNum_exception_empty_num(){
    ValueObject object;
    QString result="empty string";

    try{
        object.setFullNum("");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void valueobject::test_setFullNum_exception_only_minus(){
    ValueObject object;
    QString result="num have only minus";

    try{
        object.setFullNum("-");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void valueobject::test_setFullNum_exception_incorect_symbol(){
    ValueObject object;
    QString result="incorect symbol in num";

    try{
        object.setFullNum("12a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void valueobject::test_setFullNum_exception_count_dot(){
    ValueObject object;
    QString result="incorect count dot";

    try{
        object.setFullNum("0,0,0");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void valueobject::test_setFullNum_correct(){
    ValueObject object;
    QString result="-2,2", curent_result="";

    object.setFullNum("-2,2");
    curent_result=QString::fromStdString(object.toString());

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(valueobject)

#include "tst_valueobject.moc"
