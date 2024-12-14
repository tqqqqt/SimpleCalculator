#include <QtTest>

#include "../Calculator/source/valueobject.h"

class valueobject : public QObject
{
    Q_OBJECT

public:
    valueobject();
    ~valueobject();

private slots:
    void test_toString_data();
    void test_toString();
    void test_getLength_data();
    void test_getLength();
    void test_addNum_data();
    void test_addNum();
    void test_deleteLastSymbol_data();
    void test_deleteLastSymbol();
    void test_setFullNum_data();
    void test_setFullNum();
    void test_clear();

};

valueobject::valueobject(){ }

valueobject::~valueobject(){ }

void valueobject::test_toString_data(){
    QTest::addColumn<QString>("num");

    QTest::newRow("test_1")<<"0";
    QTest::newRow("test_2")<<"768";
    QTest::newRow("test_3")<<"0,234";
    QTest::newRow("test_4")<<"-234";
    QTest::newRow("test_5")<<"-0,01";
    QTest::newRow("test_6")<<"234235,234234";
    QTest::newRow("test_6")<<"-987,654";
}

void valueobject::test_toString(){
    QFETCH(QString,num);

    ValueObject object;
    object.setFullNum(num.toStdString());
    QCOMPARE(object.toString(),num.toStdString());
}

void valueobject::test_getLength_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("result");

    QTest::newRow("test_1")<<"0"<<1;
    QTest::newRow("test_2")<<"0,23"<<4;
    QTest::newRow("test_3")<<"234"<<3;
    QTest::newRow("test_4")<<"-123456"<<7;
    QTest::newRow("test_5")<<"342,234"<<7;
    QTest::newRow("test_6")<<"-13,456"<<7;
    QTest::newRow("test_7")<<"-0,00000001"<<11;
}

void valueobject::test_getLength(){
    QFETCH(QString,num);
    QFETCH(int,result);

    ValueObject object;
    object.setFullNum(num.toStdString());
    QCOMPARE(object.getLength(),result);
}

void valueobject::test_addNum_data(){
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
    QTest::newRow("test_11")<<','<<"";
}

void valueobject::test_addNum(){
    QFETCH(char,input);
    QFETCH(QString,result);

    ValueObject object;
    object.addNum(input);
    QCOMPARE(object.toString(),result.toStdString());
}

void valueobject::test_deleteLastSymbol_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"0"<<"";
    QTest::newRow("test_2")<<"123"<<"12";
    QTest::newRow("test_3")<<"0,0123"<<"0,012";
    QTest::newRow("test_4")<<"123,123"<<"123,12";
    QTest::newRow("test_5")<<"-12"<<"-1";
}

void valueobject::test_deleteLastSymbol(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    ValueObject object;
    object.setFullNum(num.toStdString());
    object.deleteLastSymbol();
    QCOMPARE(object.toString(),result.toStdString());
}

void valueobject::test_setFullNum_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"0"<<"0";
    QTest::newRow("test_2")<<"234"<<"234";
    QTest::newRow("test_3")<<"0,0001"<<"0,0001";
    QTest::newRow("test_4")<<"-123"<<"-123";
    QTest::newRow("test_5")<<"-0,002"<<"-0,002";
    QTest::newRow("test_6")<<"-123456789,987654321"<<"-123456789,987654321";
    QTest::newRow("test_7")<<""<<"incorect num";
    QTest::newRow("test_8")<<"-"<<"incorect num";
    QTest::newRow("test_9")<<"(-2)"<<"incorect num";
    QTest::newRow("test_10")<<"2+2"<<"incorect num";
    QTest::newRow("test_11")<<"2,2,2"<<"incorect num";
}

void valueobject::test_setFullNum(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    ValueObject object;
    try {
        object.setFullNum(num.toStdString());
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch (std::exception &exp) {
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void valueobject::test_clear(){
    ValueObject object;
    object.setFullNum("123,456");
    object.clear();
    QCOMPARE(object.toString(),"");
    QCOMPARE(object.getLength(),0);
}

QTEST_APPLESS_MAIN(valueobject)

#include "tst_valueobject.moc"
