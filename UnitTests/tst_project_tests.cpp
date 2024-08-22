#include <QtTest>

#include "../Calculator/source/calculatormath.h"
#include "../Calculator/source/numbermath.h"

class project_tests : public QObject
{
    Q_OBJECT

public:
    project_tests();
    ~project_tests();

private slots:
    void test_mathSum_data();
    void test_mathSum();
    void test_mathNeg_data();
    void test_mathNeg();
    void test_mathMul_data();
    void test_mathMul();
    void test_polish_entry1();
    void test_polish_entry2();

};

project_tests::project_tests()
{
}

project_tests::~project_tests()
{

}

void project_tests::test_mathSum_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("row1")<<"0"<<"0"<<"0";
    QTest::newRow("row2")<<"1"<<"0"<<"1";
    QTest::newRow("row3")<<"0"<<"2"<<"2";
    QTest::newRow("row4")<<"2"<<"2"<<"4";
    QTest::newRow("row5")<<"16"<<"14"<<"30";
    QTest::newRow("row6")<<"61"<<"41"<<"102";
    QTest::newRow("row7")<<"123456789987654321"<<"2"<<"123456789987654323";
    QTest::newRow("row8")<<"123456789987654321"<<"3"<<"123456789987654324";
    QTest::newRow("row9")<<"123456789987654321"<<"4"<<"123456789987654325";
    QTest::newRow("row10")<<"99999999"<<"88888888"<<"188888887";
    QTest::newRow("row11")<<"123456789"<<"987654321"<<"1111111110";
    QTest::newRow("row12")<<"9999999999"<<"100"<<"10000000099";
    QTest::newRow("row13")<<"123456789987654321"<<"123456789987654321"<<"246913579975308642";
}

void project_tests::test_mathNeg_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("row1")<<"0"<<"0"<<"0";
    QTest::newRow("row2")<<"1"<<"0"<<"1";
    QTest::newRow("row3")<<"0"<<"2"<<"-2";
    QTest::newRow("row4")<<"2"<<"2"<<"0";
    QTest::newRow("row5")<<"16"<<"14"<<"2";
    QTest::newRow("row6")<<"61"<<"41"<<"20";
    QTest::newRow("row7")<<"123456789987654321"<<"2"<<"123456789987654319";
    QTest::newRow("row8")<<"123456789987654321"<<"3"<<"123456789987654318";
    QTest::newRow("row9")<<"123456789987654321"<<"4"<<"123456789987654317";
    QTest::newRow("row10")<<"99999999"<<"88888888"<<"11111111";
    QTest::newRow("row11")<<"123456789"<<"987654321"<<"-864197532";
    QTest::newRow("row12")<<"9999999999"<<"100"<<"9999999899";
    QTest::newRow("row13")<<"123456789987654321"<<"123456789987654321"<<"0";
}

void project_tests::test_mathMul_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("row1")<<"0"<<"0"<<"0";
    QTest::newRow("row2")<<"1"<<"0"<<"0";
    QTest::newRow("row3")<<"0"<<"2"<<"0";
    QTest::newRow("row4")<<"2"<<"2"<<"4";
    QTest::newRow("row5")<<"16"<<"14"<<"224";
    QTest::newRow("row6")<<"61"<<"41"<<"2501";
    QTest::newRow("row7")<<"123456789987654321"<<"2"<<"246913579975308642";
    QTest::newRow("row8")<<"123456789987654321"<<"3"<<"370370369962962963";
    QTest::newRow("row9")<<"123456789987654321"<<"4"<<"493827159950617284";
    QTest::newRow("row10")<<"99999999"<<"88888888"<<"8888888711111112";
    QTest::newRow("row11")<<"123456789"<<"987654321"<<"121932631112635269";
    QTest::newRow("row12")<<"9999999999"<<"100"<<"999999999900";
    QTest::newRow("row13")<<"1234567899"<<"1234567899"<<"1524157897241274201";
    QTest::newRow("row14")<<"123456789987654321"<<"123456789987654321"<<"15241578994055784200731595789971041";
}

void project_tests::test_mathSum(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);
    QCOMPARE(MathSum(firstNum.toStdString(),secondNum.toStdString()),result.toStdString());
}

void project_tests::test_mathNeg(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);
    QCOMPARE(MathNeg(firstNum.toStdString(),secondNum.toStdString()),result.toStdString());
}

void project_tests::test_mathMul(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);
    QCOMPARE(MathMul(firstNum.toStdString(),secondNum.toStdString()),result.toStdString());
}

void project_tests::test_polish_entry1()
{
    CalculatorMath* creatorEntry=new CalculatorMath();
    QCOMPARE(creatorEntry->SetString("2+(2-2+(4*8))"),0);
}

void project_tests::test_polish_entry2(){
    CalculatorMath* creatorEntry=new CalculatorMath();
    QCOMPARE(creatorEntry->SetString("2+(2-2+(4*8)"),2);
}

QTEST_APPLESS_MAIN(project_tests)

#include "tst_project_tests.moc"
