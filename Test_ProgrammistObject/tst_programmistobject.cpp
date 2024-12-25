#include <QtTest>

#include "./../Calculator/source/programmistobject.h"

class programmistobject : public QObject
{
    Q_OBJECT

public:
    programmistobject();
    ~programmistobject();

private slots:
    void test_toString2_data();
    void test_toString2();
    void test_toString8_data();
    void test_toString8();
    void test_toString10_data();
    void test_toString10();
    void test_toString16_data();
    void test_toString16();
    void test_toString_data();
    void test_toString();
    void test_getLength_data();
    void test_getLength();
    void test_addNum_data();
    void test_addNum();
    void test_addMinus_data();
    void test_addMinus();
    void test_deleteLastSymbol_data();
    void test_deleteLastSymbol();
    void test_changeSystem_data();
    void test_changeSystem();
    void test_clear_data();
    void test_clear();
    void test_moveLeft_data();
    void test_moveLeft();
    void test_moveRight_data();
    void test_moveRight();
};

programmistobject::programmistobject(){ }

programmistobject::~programmistobject(){ }

void programmistobject::test_toString2_data(){
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<QVector<char>{'1'}<<"1";
    QTest::newRow("test_2")<<QVector<char>{'0'}<<"0";
    QTest::newRow("test_3")<<QVector<char>{'1','0','1'}<<"101";
    QTest::newRow("test_4")<<QVector<char>{'1','1','1','1','1'}<<"11111";
    QTest::newRow("test_5")<<QVector<char>{'0','1','1'}<<"11";
    QTest::newRow("test_6")<<QVector<char>{'1','1','0'}<<"110";
}

void programmistobject::test_toString2(){
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(2);
    for(auto x:input) object.addNum(x);
    QCOMPARE(object.toString2(),result.toStdString());
}

void programmistobject::test_toString8_data(){
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<QVector<char>{'1'}<<"1";
    QTest::newRow("test_2")<<QVector<char>{'7'}<<"7";
    QTest::newRow("test_3")<<QVector<char>{'4','5','6'}<<"456";
    QTest::newRow("test_4")<<QVector<char>{'1','0','1','0','1'}<<"10101";
    QTest::newRow("test_5")<<QVector<char>{'0','2','3'}<<"23";
    QTest::newRow("test_6")<<QVector<char>{'7','7','7'}<<"777";
}

void programmistobject::test_toString8(){
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(8);
    for(auto x:input) object.addNum(x);
    QCOMPARE(object.toString8(),result.toStdString());
}

void programmistobject::test_toString10_data(){
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<QVector<char>{'1'}<<"1";
    QTest::newRow("test_2")<<QVector<char>{'0'}<<"0";
    QTest::newRow("test_3")<<QVector<char>{'2','3'}<<"23";
    QTest::newRow("test_4")<<QVector<char>{'1','4','8','8','6'}<<"14886";
    QTest::newRow("test_5")<<QVector<char>{'0','4','4'}<<"44";
    QTest::newRow("test_6")<<QVector<char>{'7','9','9'}<<"799";
}

void programmistobject::test_toString10(){
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(10);
    for(auto x:input) object.addNum(x);
    QCOMPARE(object.toString10(),result.toStdString());
}

void programmistobject::test_toString16_data(){
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<QVector<char>{'1'}<<"1";
    QTest::newRow("test_2")<<QVector<char>{'F'}<<"F";
    QTest::newRow("test_3")<<QVector<char>{'2','F','1'}<<"2F1";
    QTest::newRow("test_4")<<QVector<char>{'B','1','1','0'}<<"B110";
    QTest::newRow("test_5")<<QVector<char>{'0','A','5'}<<"A5";
    QTest::newRow("test_6")<<QVector<char>{'2','2','A'}<<"22A";
}

void programmistobject::test_toString16(){
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(16);
    for(auto x:input) object.addNum(x);
    QCOMPARE(object.toString16(),result.toStdString());
}

void programmistobject::test_toString_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<2<<QVector<char>{'1','0','0'}<<"100";
    QTest::newRow("test_2")<<8<<QVector<char>{'2','0','7'}<<"207";
    QTest::newRow("test_3")<<10<<QVector<char>{'4','8','9'}<<"489";
    QTest::newRow("test_4")<<16<<QVector<char>{'2','E','0'}<<"2E0";
    QTest::newRow("test_5")<<16<<QVector<char>{'0','E','9'}<<"E9";
    QTest::newRow("test_6")<<10<<QVector<char>{'0','9','9'}<<"99";
    QTest::newRow("test_7")<<8<<QVector<char>{'0','4','7'}<<"47";
    QTest::newRow("test_8")<<2<<QVector<char>{'0','1','0'}<<"10";
}

void programmistobject::test_toString(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(system);
    for(auto x:input) object.addNum(x);
    QCOMPARE(object.toString(),result.toStdString());
}

void programmistobject::test_getLength_data(){

}

void programmistobject::test_getLength(){

}

void programmistobject::test_addNum_data(){

}

void programmistobject::test_addNum(){

}

void programmistobject::test_addMinus_data(){

}

void programmistobject::test_addMinus(){

}

void programmistobject::test_deleteLastSymbol_data(){

}

void programmistobject::test_deleteLastSymbol(){

}

void programmistobject::test_changeSystem_data(){

}

void programmistobject::test_changeSystem(){

}

void programmistobject::test_clear_data(){

}

void programmistobject::test_clear(){

}

void programmistobject::test_moveLeft_data(){

}

void programmistobject::test_moveLeft(){

}

void programmistobject::test_moveRight_data(){

}

void programmistobject::test_moveRight(){

}

QTEST_APPLESS_MAIN(programmistobject)

#include "tst_programmistobject.moc"
