#include <QtTest>

#include "../Calculator/source/numbermath.h"

class numbermath : public QObject
{
    Q_OBJECT

public:
    numbermath();
    ~numbermath();

private slots:
    void test_maxNum_data();
    void test_maxNum();

    void test_findMultiplier_data();
    void test_findMultiplier();

    void test_mathSum_data();
    void test_mathSum();

    void test_mathNeg_data();
    void test_mathNeg();

    void test_mathMul_data();
    void test_mathMul();

    void test_mathDiv_data();
    void test_mathDiv();

    void test_mathPow_data();
    void test_mathPow();

    void test_mathSin_data();
    void test_mathSin();

    void test_mathCos_data();
    void test_mathCos();

    void test_mathTng_data();
    void test_mathTng();

    void test_mathCtng_data();
    void test_mathCtng();

    void test_mathFactorial_data();
    void test_mathFactorial();

    void test_mathMod_data();
    void test_mathMod();

    void test_mathModule_data();
    void test_mathModule();

    void test_mathRoundUp_data();
    void test_mathRoundUp();

    void test_mathRoundDown_data();
    void test_mathRoundDown();
};

numbermath::numbermath(){ }

numbermath::~numbermath(){ }

void numbermath::test_maxNum_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<int>("result");

    QTest::newRow("test_1")<<"0"<<"0"<<0;
    QTest::newRow("test_2")<<"2"<<"0"<<-1;
    QTest::newRow("test_3")<<"0"<<"2"<<1;
    QTest::newRow("test_4")<<"0,01"<<"0,001"<<-1;
    QTest::newRow("test_5")<<"-2"<<"0"<<1;
    QTest::newRow("test_6")<<"0"<<"-2"<<-1;
    QTest::newRow("test_7")<<"-2,41"<<"2,41"<<1;
    QTest::newRow("test_8")<<"0,0000001"<<"0,0000001"<<0;
    QTest::newRow("test_9")<<"-2,000001"<<"-2,000001"<<0;
    QTest::newRow("test_10")<<"0,01"<<"0,010"<<0;
    QTest::newRow("test_11")<<"5,99"<<"5,98"<<-1;
    QTest::newRow("test_12")<<"2,001"<<"2,0010000000001"<<1;
    QTest::newRow("test_13")<<"-432"<<"-432"<<0;
    QTest::newRow("test_14")<<"-12"<<"-13"<<-1;
    QTest::newRow("test_15")<<"2,000000001"<<"2,000000002"<<1;
}

void numbermath::test_maxNum(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(int,result);

    int curent_result=MaxNumber(firstNum.toStdString(),secondNum.toStdString());

    QCOMPARE(curent_result,result);
}

void numbermath::test_findMultiplier_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<int>("result");

    QTest::newRow("test_1")<<"1"<<"1"<<1;
    QTest::newRow("test_2")<<"4"<<"2"<<2;
    QTest::newRow("test_3")<<"13"<<"2"<<6;
    QTest::newRow("test_4")<<"14"<<"13"<<1;
    QTest::newRow("test_5")<<"81"<<"9"<<9;
    QTest::newRow("test_6")<<"4"<<"-2"<<-2;
    QTest::newRow("test_7")<<"-4"<<"2"<<-2;
    QTest::newRow("test_8")<<"-81"<<"-9"<<9;
}

void numbermath::test_findMultiplier(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(int,result);

    int curent_result=FindMultiplier(firstNum.toStdString(),secondNum.toStdString());

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_data(){
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
    QTest::newRow("test_16")<<"0"<<"0,1"<<"0,1";
    QTest::newRow("test_17")<<"0,1"<<"0"<<"0,1";
    QTest::newRow("test_18")<<"4,99"<<"0,01"<<"5,00";
    QTest::newRow("test_19")<<"123456789,2468"<<"987654321,13579"<<"1111111110,38259";
    QTest::newRow("test_20")<<"123456789,987654321"<<"987654321,123456789"<<"1111111111,111111110";
    QTest::newRow("test_21")<<"1,999"<<"0,001"<<"2,000";
    QTest::newRow("test_22")<<"23,456"<<"2,441"<<"25,897";
    QTest::newRow("test_23")<<"2,199199"<<"2,011011"<<"4,210210";
    QTest::newRow("test_24")<<"2"<<"-45"<<"-43";
    QTest::newRow("test_25")<<"0,446"<<"-2,1"<<"-1,654";
    QTest::newRow("test_26")<<"-21,009"<<"0,00078"<<"-21,00822";
    QTest::newRow("test_27")<<"-13,3009"<<"-14,8007"<<"-28,1016";
}

void numbermath::test_mathSum(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);

    std::string curent_result=MathSum(firstNum.toStdString(),secondNum.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathNeg_data(){
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
    QTest::newRow("test_16")<<"0"<<"0,2"<<"-0,2";
    QTest::newRow("test_17")<<"2,2"<<"2,2"<<"0";
    QTest::newRow("test_18")<<"0,1"<<"0,00020003"<<"0,09979997";
    QTest::newRow("test_19")<<"2,23"<<"2,001"<<"0,229";
    QTest::newRow("test_20")<<"2,00001"<<"3,364"<<"-1,36399";
    QTest::newRow("test_21")<<"123456789,123456789"<<"987654321,987654321"<<"-864197532,864197532";
    QTest::newRow("test_22")<<"987654321,123456789"<<"123456789,987654321"<<"864197531,135802468";
    QTest::newRow("test_23")<<"1"<<"0,0099"<<"0,9901";
    QTest::newRow("test_24")<<"2"<<"0,00990099"<<"1,99009901";
    QTest::newRow("test_25")<<"-123,001"<<"2,009"<<"-125,010";
    QTest::newRow("test_26")<<"45,778"<<"-5,222"<<"51,000";
    QTest::newRow("test_27")<<"-82,0009"<<"-17,9991"<<"-64,0018";
    QTest::newRow("test_28")<<"-2,009"<<"7,991"<<"-10,000";
}

void numbermath::test_mathNeg(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);

    std::string curent_result=MathNeg(firstNum.toStdString(),secondNum.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathMul_data(){
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
    QTest::newRow("test_16")<<"0,2"<<"2"<<"0,4";
    QTest::newRow("test_17")<<"0,946"<<"0,228"<<"0,215688";
    QTest::newRow("test_18")<<"23,25"<<"24,26"<<"564,0450";
    QTest::newRow("test_19")<<"123456789,2468"<<"123456789,13579"<<"15241578797423853,937022972";
    QTest::newRow("test_20")<<"123456789987654321,123456789"<<"987654321123456789,987654321"<<"121932632103337905905959456328608443,662094193112635269";
    QTest::newRow("test_21")<<"-23,23"<<"1119"<<"-25994,37";
    QTest::newRow("test_22")<<"221,12"<<"-17"<<"-3759,04";
    QTest::newRow("test_23")<<"-234,21"<<"-13,14"<<"3077,5194";
    QTest::newRow("test_24")<<"-0,001"<<"0,0000001"<<"-0,0000000001";
}

void numbermath::test_mathMul(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);

    std::string curent_result=MathMul(firstNum.toStdString(),secondNum.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathDiv_data(){
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"0"<<"Error div 0";
    QTest::newRow("test_2")<<"0"<<"2"<<"0";
    QTest::newRow("test_3")<<"8"<<"2"<<"4";
    QTest::newRow("test_4")<<"8"<<"4"<<"2";
    QTest::newRow("test_5")<<"24"<<"25"<<"0,96";
    QTest::newRow("test_6")<<"144"<<"14"<<"10,2857142857";
    QTest::newRow("test_7")<<"144"<<"12"<<"12";
    QTest::newRow("test_8")<<"9999"<<"9"<<"1111";
    QTest::newRow("test_9")<<"48954"<<"246"<<"199";
    QTest::newRow("test_10")<<"999999999"<<"3"<<"333333333";
    QTest::newRow("test_11")<<"151658732170"<<"1231546"<<"123145";
    QTest::newRow("test_12")<<"121932631112635269"<<"123456789"<<"987654321";
    QTest::newRow("test_13")<<"5252683697925751630154898"<<"42546738"<<"123456789987654321";
    QTest::newRow("test_14")<<"137174211083676268890260631"<<"1111111111"<<"123456789987654321";
    QTest::newRow("test_15")<<"15241578994055784200731595789971041"<<"123456789987654321"<<"123456789987654321";
    QTest::newRow("test_16")<<"0,2"<<"0"<<"Error div 0";
    QTest::newRow("test_17")<<"0"<<"0,2"<<"0";
    QTest::newRow("test_18")<<"1"<<"10"<<"0,1";
    QTest::newRow("test_19")<<"123456789"<<"345"<<"357845,7652173913";
    QTest::newRow("test_20")<<"1"<<"2345"<<"0,0004264392";
    QTest::newRow("test_21")<<"-324,14"<<"14,15"<<"-22,9074204947";
    QTest::newRow("test_22")<<"21,12"<<"-6,42"<<"-3,2897196262";
    QTest::newRow("test_23")<<"-47,786"<<"-34,623"<<"1,3801808047";
}

void numbermath::test_mathDiv(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(QString,result);

    std::string curent_result="";

    try{
        curent_result=MathDiv(firstNum.toStdString(),secondNum.toStdString(),10);
        QCOMPARE(curent_result,result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void numbermath::test_mathPow_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("pow_num");
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"6"<<10<<"64";
    QTest::newRow("test_2")<<"2"<<"0"<<10<<"1";
    QTest::newRow("test_3")<<"2"<<"1"<<10<<"2";
    QTest::newRow("test_4")<<"3,466"<<"12"<<10<<"3005679,716419116273457363412193535228973056";
    QTest::newRow("test_5")<<"23"<<"10"<<10<<"41426511213649";
    QTest::newRow("test_6")<<"2"<<"-8"<<10<<"0,00390625";
}

void numbermath::test_mathPow(){
    QFETCH(QString,num);
    QFETCH(QString,pow_num);
    QFETCH(int,div_acuracy);
    QFETCH(QString,result);

    std::string curent_result="";

    try{
        curent_result=MathPow(num.toStdString(),pow_num.toStdString(),div_acuracy);
        QCOMPARE(curent_result,result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void numbermath::test_mathSin_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<int>("function_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<10<<10<<"0,0348994966";
}

void numbermath::test_mathSin(){
    QFETCH(QString,num);
    QFETCH(int,div_acuracy);
    QFETCH(int,function_acuracy);
    QFETCH(QString,result);

    std::string curent_result=MathSin(num.toStdString(),div_acuracy,function_acuracy);

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathCos_data(){

}

void numbermath::test_mathCos(){

}

void numbermath::test_mathTng_data(){

}

void numbermath::test_mathTng(){

}

void numbermath::test_mathCtng_data(){

}

void numbermath::test_mathCtng(){

}

void numbermath::test_mathFactorial_data(){

}

void numbermath::test_mathFactorial(){

}

void numbermath::test_mathMod_data(){

}

void numbermath::test_mathMod(){

}

void numbermath::test_mathModule_data(){

}

void numbermath::test_mathModule(){

}

void numbermath::test_mathRoundUp_data(){

}

void numbermath::test_mathRoundUp(){

}

void numbermath::test_mathRoundDown_data(){

}

void numbermath::test_mathRoundDown(){

}

QTEST_APPLESS_MAIN(numbermath)

#include "tst_numbermath.moc"
