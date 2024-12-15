#include <QtTest>

#include "../Calculator/source/calculatorobject.h"

class calculatorobject : public QObject
{
    Q_OBJECT

public:
    calculatorobject();
    ~calculatorobject();

private slots:
    void test_toString_data();
    void test_toString();
    void test_getLength_data();
    void test_getLength();
    void test_getObjectType_data();
    void test_getObjectType();
    void test_addNum_data();
    void test_addNum();
    void test_addSymbol_data();
    void test_addSymbol();
    void test_deleteLastSymbol_data();
    void test_deleteLastSymbol();
    void test_setFullNum_data();
    void test_setFullNum();
    void test_getOnlyNum_data();
    void test_getOnlyNum();
};

calculatorobject::calculatorobject(){ }

calculatorobject::~calculatorobject(){ }

void calculatorobject::test_toString_data(){
    QTest::addColumn<QString>("num");

    QTest::newRow("test_1")<<"0";
    QTest::newRow("test_2")<<"24";
    QTest::newRow("test_3")<<"(-2,22)";
    QTest::newRow("test_4")<<"2,00000001";
    QTest::newRow("test_5")<<"(-2)";
    QTest::newRow("test_6")<<"(-123,456)";
}

void calculatorobject::test_toString(){
    QFETCH(QString,num);

    CalculatorObject object;
    object.setFullNum(num.toStdString());
    QCOMPARE(object.toString(),num.toStdString());
}

void calculatorobject::test_getLength_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("length");

    QTest::newRow("test_1")<<"0"<<1;
    QTest::newRow("test_2")<<"123"<<3;
    QTest::newRow("test_3")<<"0,00000001"<<10;
    QTest::newRow("test_4")<<"(-24)"<<5;
    QTest::newRow("test_5")<<"(-2)"<<4;
    QTest::newRow("test_6")<<"(-2,1918)"<<9;
}

void calculatorobject::test_getLength(){
    QFETCH(QString,num);
    QFETCH(int,length);

    CalculatorObject object;
    object.setFullNum(num.toStdString());
    QCOMPARE(object.getLength(),length);
}

void calculatorobject::test_getObjectType_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<int>("input_type");
    QTest::addColumn<int>("type");

    QTest::newRow("test_1")<<"0"<<1<<1;
    QTest::newRow("test_2")<<"9"<<1<<1;
    QTest::newRow("test_3")<<"3"<<1<<1;
    QTest::newRow("test_4")<<"-"<<2<<5;
    QTest::newRow("test_5")<<"+"<<2<<5;
    QTest::newRow("test_6")<<"*"<<2<<5;
    QTest::newRow("test_7")<<"/"<<2<<5;
    QTest::newRow("test_8")<<"(-"<<2<<2;
    QTest::newRow("test_9")<<"("<<2<<3;
    QTest::newRow("test_10")<<")"<<2<<4;
}

void calculatorobject::test_getObjectType(){
    QFETCH(QString,input);
    QFETCH(int,input_type);
    QFETCH(int,type);

    CalculatorObject object;
    if(input_type==1) object.addNum(input.toStdString()[0]);
    else object.addSymbol(input.toStdString());
    QCOMPARE(object.getObjectType(),type);
}

void calculatorobject::test_addNum_data(){
    QTest::addColumn<char>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<'0'<<"0";
    QTest::newRow("test_2")<<'1'<<"1";
    QTest::newRow("test_3")<<'2'<<"2";
    QTest::newRow("test_4")<<'3'<<"3";
    QTest::newRow("test_5")<<'4'<<"4";
    QTest::newRow("test_6")<<'5'<<"5";
    QTest::newRow("test_7")<<'6'<<"6";
    QTest::newRow("test_8")<<'7'<<"7";
    QTest::newRow("test_9")<<'8'<<"8";
    QTest::newRow("test_10")<<'9'<<"9";
    QTest::newRow("test_11")<<'+'<<"input not a num";
    QTest::newRow("test_12")<<'-'<<"input not a num";
    QTest::newRow("test_13")<<'*'<<"input not a num";
    QTest::newRow("test_14")<<'/'<<"input not a num";
    QTest::newRow("test_15")<<'('<<"input not a num";
    QTest::newRow("test_16")<<')'<<"input not a num";
    QTest::newRow("test_17")<<' '<<"input not a num";
}

void calculatorobject::test_addNum(){
    QFETCH(char,input);
    QFETCH(QString,result);

    CalculatorObject object;
    try {
        object.addNum(input);
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch (std::exception &exp) {
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void calculatorobject::test_addSymbol_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"0"<<"input not a oper or bracket";
    QTest::newRow("test_2")<<"1"<<"input not a oper or bracket";
    QTest::newRow("test_3")<<"2"<<"input not a oper or bracket";
    QTest::newRow("test_4")<<"3"<<"input not a oper or bracket";
    QTest::newRow("test_5")<<"4"<<"input not a oper or bracket";
    QTest::newRow("test_6")<<"5"<<"input not a oper or bracket";
    QTest::newRow("test_7")<<"6"<<"input not a oper or bracket";
    QTest::newRow("test_8")<<"7"<<"input not a oper or bracket";
    QTest::newRow("test_9")<<"8"<<"input not a oper or bracket";
    QTest::newRow("test_10")<<"9"<<"input not a oper or bracket";
    QTest::newRow("test_11")<<"+"<<"+";
    QTest::newRow("test_12")<<"-"<<"-";
    QTest::newRow("test_13")<<"*"<<"*";
    QTest::newRow("test_14")<<"/"<<"/";
    QTest::newRow("test_15")<<"("<<"(";
    QTest::newRow("test_16")<<")"<<")";
    QTest::newRow("test_17")<<""<<"input not a oper or bracket";
    QTest::newRow("test_18")<<" "<<"input not a oper or bracket";
}

void calculatorobject::test_addSymbol(){
    QFETCH(QString,input);
    QFETCH(QString,result);

    CalculatorObject object;
    try {
        object.addSymbol(input.toStdString());
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch (std::exception &exp) {
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void calculatorobject::test_deleteLastSymbol_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<int>("type_input");
    QTest::addColumn<int>("type_object");
    QTest::addColumn<int>("length");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"1"<<1<<0<<0<<"";
    QTest::newRow("test_2")<<"4"<<1<<0<<0<<"";
    QTest::newRow("test_3")<<"8"<<1<<0<<0<<"";
    QTest::newRow("test_4")<<"+"<<2<<0<<0<<"";
    QTest::newRow("test_5")<<"-"<<2<<0<<0<<"";
    QTest::newRow("test_6")<<"/"<<2<<0<<0<<"";
    QTest::newRow("test_7")<<"*"<<2<<0<<0<<"";
    QTest::newRow("test_8")<<"(-"<<2<<3<<1<<"(";
    QTest::newRow("test_9")<<"("<<2<<0<<0<<"";
    QTest::newRow("test_10")<<")"<<2<<0<<0<<"";
    QTest::newRow("test_11")<<"1234253"<<3<<1<<6<<"123425";
    QTest::newRow("test_12")<<"(-1,00000001)"<<3<<1<<12<<"(-1,00000001";
    QTest::newRow("test_13")<<"(-2)"<<3<<1<<3<<"(-2";
    QTest::newRow("test_14")<<"(-123)"<<3<<1<<5<<"(-123";
}

void calculatorobject::test_deleteLastSymbol(){
    QFETCH(QString,input);
    QFETCH(int,type_input);
    QFETCH(int,type_object);
    QFETCH(int,length);
    QFETCH(QString,result);

    CalculatorObject object;
    if(type_input==1) object.addNum(input.toStdString()[0]);
    else if(type_input==2) object.addSymbol(input.toStdString());
    else object.setFullNum(input.toStdString());
    object.deleteLastSymbol();
    QCOMPARE(object.getObjectType(),type_object);
    QCOMPARE(object.getLength(),length);
    QCOMPARE(object.toString(),result.toStdString());
}

void calculatorobject::test_setFullNum_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"123"<<"123";
    QTest::newRow("test_2")<<"-3435,01"<<"-3435,01";
    QTest::newRow("test_3")<<"1,0000000000001"<<"1,0000000000001";
    QTest::newRow("test_4")<<"(-223)"<<"(-223)";
    QTest::newRow("test_5")<<"2+"<<"incorect num";
    QTest::newRow("test_6")<<"-234"<<"-234";
    QTest::newRow("test_7")<<"/*"<<"incorect num";
    QTest::newRow("test_8")<<""<<"incorect num";
    QTest::newRow("test_9")<<"2,2,2"<<"incorect num";
}

void calculatorobject::test_setFullNum(){
    QFETCH(QString,input);
    QFETCH(QString,result);

    CalculatorObject object;
    try{
        object.setFullNum(input.toStdString());
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void calculatorobject::test_getOnlyNum_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<int>("input_type");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"10"<<1<<"10";
    QTest::newRow("test_2")<<"0,00001"<<1<<"0,00001";
    QTest::newRow("test_3")<<"(-234,43)"<<1<<"-234,43";
    QTest::newRow("test_4")<<"(-0,01)"<<1<<"-0,01";
    QTest::newRow("test_5")<<"+"<<2<<"object is not num";
    QTest::newRow("test_6")<<"*"<<2<<"object is not num";
    QTest::newRow("test_7")<<"/"<<2<<"object is not num";
    QTest::newRow("test_8")<<"(-"<<2<<"object is not num";
}

void calculatorobject::test_getOnlyNum(){
    QFETCH(QString,input);
    QFETCH(int,input_type);
    QFETCH(QString,result);

    CalculatorObject object;
    if(input_type==1) object.setFullNum(input.toStdString());
    else object.addSymbol(input.toStdString());
    try{
        QCOMPARE(object.getOnlyNum().toString(),result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

QTEST_APPLESS_MAIN(calculatorobject)

#include "tst_calculatorobject.moc"
