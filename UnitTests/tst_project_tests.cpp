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
    void test_mathDiv_data();
    void test_mathDiv();
    void test_polish_entry_noError_data();
    void test_polish_entry_noError();
    void test_polish_entry_error_data();
    void test_polish_entry_error();
    void test_full_calculate_data();
    void test_full_calculate();
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
    QTest::newRow("test_1")<<"0"<<"0"<<"0";
    QTest::newRow("test_2")<<"1"<<"0"<<"1";
    QTest::newRow("test_3")<<"0"<<"2"<<"2";
    QTest::newRow("test_4")<<"2"<<"2"<<"4";
    QTest::newRow("test_5")<<"91"<<"10"<<"101";
    QTest::newRow("test_6")<<"16"<<"14"<<"30";
    QTest::newRow("test_7")<<"61"<<"41"<<"102";
    QTest::newRow("test_8")<<"109"<<"1"<<"110";
    QTest::newRow("test_9")<<"123456789987654321"<<"2"<<"123456789987654323";
    QTest::newRow("test_10")<<"123456789987654321"<<"3"<<"123456789987654324";
    QTest::newRow("test_11")<<"123456789987654321"<<"4"<<"123456789987654325";
    QTest::newRow("test_12")<<"99999999"<<"88888888"<<"188888887";
    QTest::newRow("test_13")<<"123456789"<<"987654321"<<"1111111110";
    QTest::newRow("test_14")<<"9999999999"<<"100"<<"10000000099";
    QTest::newRow("test_15")<<"123456789987654321"<<"123456789987654321"<<"246913579975308642";
}

void project_tests::test_mathNeg_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("test_1")<<"0"<<"0"<<"0";
    QTest::newRow("test_2")<<"1"<<"0"<<"1";
    QTest::newRow("test_3")<<"0"<<"2"<<"-2";
    QTest::newRow("test_4")<<"2"<<"2"<<"0";
    QTest::newRow("test_5")<<"16"<<"14"<<"2";
    QTest::newRow("test_6")<<"40"<<"39"<<"1";
    QTest::newRow("test_7")<<"61"<<"41"<<"20";
    QTest::newRow("test_8")<<"102"<<"41"<<"61";
    QTest::newRow("test_9")<<"123456789987654321"<<"2"<<"123456789987654319";
    QTest::newRow("test_10")<<"123456789987654321"<<"3"<<"123456789987654318";
    QTest::newRow("test_11")<<"123456789987654321"<<"4"<<"123456789987654317";
    QTest::newRow("test_12")<<"99999999"<<"88888888"<<"11111111";
    QTest::newRow("test_13")<<"123456789"<<"987654321"<<"-864197532";
    QTest::newRow("test_14")<<"9999999999"<<"100"<<"9999999899";
    QTest::newRow("test_15")<<"123456789987654321"<<"123456789987654321"<<"0";
}

void project_tests::test_mathMul_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("test_1")<<"0"<<"0"<<"0";
    QTest::newRow("test_2")<<"1"<<"0"<<"0";
    QTest::newRow("test_3")<<"0"<<"2"<<"0";
    QTest::newRow("test_4")<<"2"<<"2"<<"4";
    QTest::newRow("test_5")<<"8"<<"2"<<"16";
    QTest::newRow("test_6")<<"16"<<"14"<<"224";
    QTest::newRow("test_7")<<"61"<<"41"<<"2501";
    QTest::newRow("test_8")<<"123456789987654321"<<"2"<<"246913579975308642";
    QTest::newRow("test_9")<<"123456789987654321"<<"3"<<"370370369962962963";
    QTest::newRow("test_10")<<"123456789987654321"<<"4"<<"493827159950617284";
    QTest::newRow("test_11")<<"99999999"<<"88888888"<<"8888888711111112";
    QTest::newRow("test_12")<<"123456789"<<"987654321"<<"121932631112635269";
    QTest::newRow("test_13")<<"9999999999"<<"100"<<"999999999900";
    QTest::newRow("test_14")<<"1234567899"<<"1234567899"<<"1524157897241274201";
    QTest::newRow("test_15")<<"123456789987654321"<<"123456789987654321"<<"15241578994055784200731595789971041";
}

void project_tests::test_mathDiv_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");
    QTest::newRow("test_1")<<"2"<<"0"<<"Error div 0";
    QTest::newRow("test_2")<<"0"<<"2"<<"0";
    QTest::newRow("test_3")<<"8"<<"2"<<"4";
    QTest::newRow("test_4")<<"8"<<"4"<<"2";
    QTest::newRow("test_5")<<"24"<<"25"<<"0";
    QTest::newRow("test_6")<<"144"<<"14"<<"10";
    QTest::newRow("test_7")<<"144"<<"12"<<"12";
    QTest::newRow("test_8")<<"9999"<<"9"<<"1111";
    QTest::newRow("test_9")<<"48954"<<"246"<<"199";
    QTest::newRow("test_10")<<"999999999"<<"3"<<"333333333";
    QTest::newRow("test_11")<<"151658732170"<<"1231546"<<"123145";
    QTest::newRow("test_12")<<"121932631112635269"<<"123456789"<<"987654321";
    QTest::newRow("test_13")<<"5252683697925751630154898"<<"42546738"<<"123456789987654321";
    QTest::newRow("test_14")<<"137174211083676268890260631"<<"1111111111"<<"123456789987654321";
    QTest::newRow("test_15")<<"15241578994055784200731595789971041"<<"123456789987654321"<<"123456789987654321";
}

void project_tests::test_polish_entry_noError_data(){
    QTest::addColumn<QString>("expression");
    QTest::addColumn<int>("result");
    QTest::newRow("test_1")<<"2+2"<<0;
    QTest::newRow("test_2")<<"0+0"<<0;
    QTest::newRow("test_3")<<"2+(2-2)"<<0;
    QTest::newRow("test_4")<<"2+(2-(4*8))"<<0;
    QTest::newRow("test_5")<<"2+(3*(4*(5*(6*(7*(8+9))))))"<<0;
}

void project_tests::test_polish_entry_error_data(){
    QTest::addColumn<QString>("expression");
    QTest::addColumn<int>("result");
    QTest::newRow("test_1")<<"-2+2"<<3;
    QTest::newRow("test_2")<<"(-2+2"<<2;
    QTest::newRow("test_3")<<"2+(-2"<<2;
    QTest::newRow("test_4")<<"2+-2"<<4;
    QTest::newRow("test_5")<<"2+(3-(4*5)"<<2;
}

void project_tests::test_full_calculate_data(){
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::newRow("test_1")<<"2+2"<<"4";
    QTest::newRow("test_2")<<"2-2"<<"0";
    QTest::newRow("test_3")<<"2-4"<<"(-2)";
    QTest::newRow("test_4")<<"2+2*2"<<"6";
    QTest::newRow("test_5")<<"2+(2-2+(4*8))"<<"34";
    QTest::newRow("test_6")<<"2*(3*(4*(5*(6*(7*(8+9))))))"<<"85680";
    QTest::newRow("test_7")<<"(413*826)+(795*234)"<<"527168";
    QTest::newRow("test_8")<<"2*(4*(3+2)+(5+4)*6)"<<"148";
    QTest::newRow("test_9")<<"((12*12)/12)+((13*13)/13)"<<"25";
    QTest::newRow("test_10")<<"((((16*14)/2)/2)/2)/2"<<"14";
    QTest::newRow("test_11")<<"((((30*49)-70)/(4+(14*14)))*10)/((46+4)/(10/2))"<<"7";
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

void project_tests::test_mathDiv(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);
    QCOMPARE(MathDiv(firstNum.toStdString(),secondNum.toStdString()),result.toStdString());
}

void project_tests::test_polish_entry_noError()
{
    CalculatorMath* creatorEntry=new CalculatorMath();
    QFETCH(QString,expression);
    QFETCH(int,result);
    QCOMPARE(creatorEntry->SetString(expression.toStdString()),result);
}

void project_tests::test_polish_entry_error(){
    CalculatorMath* creatorEntry=new CalculatorMath();
    QFETCH(QString,expression);
    QFETCH(int,result);
    QCOMPARE(creatorEntry->SetString(expression.toStdString()),result);
}

void project_tests::test_full_calculate(){
    CalculatorMath* creatorEntry=new CalculatorMath();
    QFETCH(QString,input);
    QFETCH(QString,result);
    creatorEntry->SetString(input.toStdString());
    QCOMPARE(creatorEntry->GetResult(),result.toStdString());
}

QTEST_APPLESS_MAIN(project_tests)

#include "tst_project_tests.moc"
