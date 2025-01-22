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
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"0"<<10<<"div 0";
    QTest::newRow("test_2")<<"0"<<"2"<<10<<"0";
    QTest::newRow("test_3")<<"8"<<"2"<<10<<"4";
    QTest::newRow("test_4")<<"8"<<"4"<<10<<"2";
    QTest::newRow("test_5")<<"24"<<"25"<<10<<"0,96";
    QTest::newRow("test_6")<<"144"<<"14"<<10<<"10,2857142857";
    QTest::newRow("test_7")<<"144"<<"12"<<10<<"12";
    QTest::newRow("test_8")<<"9999"<<"9"<<10<<"1111";
    QTest::newRow("test_9")<<"48954"<<"246"<<10<<"199";
    QTest::newRow("test_10")<<"999999999"<<"3"<<10<<"333333333";
    QTest::newRow("test_11")<<"151658732170"<<"1231546"<<10<<"123145";
    QTest::newRow("test_12")<<"121932631112635269"<<"123456789"<<10<<"987654321";
    QTest::newRow("test_13")<<"5252683697925751630154898"<<"42546738"<<10<<"123456789987654321";
    QTest::newRow("test_14")<<"137174211083676268890260631"<<"1111111111"<<10<<"123456789987654321";
    QTest::newRow("test_15")<<"15241578994055784200731595789971041"<<"123456789987654321"<<10<<"123456789987654321";
    QTest::newRow("test_16")<<"0,2"<<"0"<<10<<"div 0";
    QTest::newRow("test_17")<<"0"<<"0,2"<<10<<"0";
    QTest::newRow("test_18")<<"1"<<"10"<<10<<"0,1";
    QTest::newRow("test_19")<<"123456789"<<"345"<<10<<"357845,7652173913";
    QTest::newRow("test_20")<<"1"<<"2345"<<10<<"0,0004264392";
    QTest::newRow("test_21")<<"-324,14"<<"14,15"<<10<<"-22,9074204947";
    QTest::newRow("test_22")<<"21,12"<<"-6,42"<<10<<"-3,2897196262";
    QTest::newRow("test_23")<<"-47,786"<<"-34,623"<<10<<"1,3801808047";
    QTest::newRow("test_24")<<"5039,84177369508992"<<"5040"<<10<<"0,9999686059";
    QTest::newRow("test_25")<<"5039,84177369508992"<<"5040"<<4<<"1,0000";
}

void numbermath::test_mathDiv(){
    QFETCH(QString,firstNum);
    QFETCH(QString,secondNum);
    QFETCH(int,div_acuracy);
    QFETCH(QString,result);

    std::string curent_result="";

    try{
        curent_result=MathDiv(firstNum.toStdString(),secondNum.toStdString(),div_acuracy);
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

    QTest::newRow("test_1")<<"2"<<10<<20<<"0,0348994966";
    QTest::newRow("test_2")<<"0"<<10<<20<<"0";
    QTest::newRow("test_3")<<"35"<<10<<20<<"0,5735764363";
    QTest::newRow("test_4")<<"2,18"<<10<<20<<"0,0380389982";
    QTest::newRow("test_5")<<"0,001"<<10<<20<<"0,0000174533";
    QTest::newRow("test_6")<<"480"<<10<<20<<"0,8660254038";
    QTest::newRow("test_7")<<"999"<<10<<20<<"-0,9876883404";
    QTest::newRow("test_8")<<"-44"<<10<<20<<"-0,6946583705";
    QTest::newRow("test_9")<<"-0,123"<<10<<20<<"-0,0021467534";
    QTest::newRow("test_10")<<"-189,99"<<10<<20<<"0,1734762936";
    QTest::newRow("test_11")<<"-888"<<10<<20<<"-0,2079116908";
}

void numbermath::test_mathSin(){
    QFETCH(QString,num);
    QFETCH(int,div_acuracy);
    QFETCH(int,function_acuracy);
    QFETCH(QString,result);

    std::string curent_result=MathSin(num.toStdString(),div_acuracy,function_acuracy,false);

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathCos_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<int>("function_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<10<<20<<"0,9993908271";
    QTest::newRow("test_2")<<"0"<<10<<20<<"1";
    QTest::newRow("test_3")<<"0,001"<<10<<20<<"0,9999999998";
    QTest::newRow("test_4")<<"0,024"<<10<<20<<"0,9999999123";
    QTest::newRow("test_5")<<"27"<<10<<20<<"0,8910065242";
    QTest::newRow("test_6")<<"-12"<<10<<20<<"0,9781476008";
    QTest::newRow("test_7")<<"-6,002"<<10<<20<<"0,9945182460";
    QTest::newRow("test_8")<<"-123"<<10<<20<<"-0,5446390351";
    QTest::newRow("test_9")<<"888"<<10<<20<<"-0,9781476008";
    QTest::newRow("test_10")<<"-999"<<10<<20<<"0,1564344650";
}

void numbermath::test_mathCos(){
    QFETCH(QString,num);
    QFETCH(int,div_acuracy);
    QFETCH(int,function_acuracy);
    QFETCH(QString,result);

    std::string curent_result=MathCos(num.toStdString(),div_acuracy,function_acuracy,false);

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathTng_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<int>("function_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<10<<20<<"0,0349207694";
    QTest::newRow("test_2")<<"6"<<10<<20<<"0,1051042352";
    QTest::newRow("test_3")<<"0,01"<<10<<20<<"0,0001745329";
    QTest::newRow("test_4")<<"34,23"<<10<<20<<"0,6803649964";
    QTest::newRow("test_5")<<"-8"<<10<<20<<"-0,1405408347";
    QTest::newRow("test_6")<<"-99,333"<<10<<20<<"6,0846592905";
    QTest::newRow("test_7")<<"-0,00002"<<10<<20<<"-0,0000003491";
    QTest::newRow("test_8")<<"898"<<10<<20<<"-0,0349207695";
    QTest::newRow("test_9")<<"-989"<<10<<20<<"-57,2899617499";
}

void numbermath::test_mathTng(){
    QFETCH(QString,num);
    QFETCH(int,div_acuracy);
    QFETCH(int,function_acuracy);
    QFETCH(QString,result);

    std::string curent_result=MathTng(num.toStdString(),div_acuracy,function_acuracy,false);

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathCtng_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<int>("div_acuracy");
    QTest::addColumn<int>("function_acuracy");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<10<<20<<"28,6362533693";
    QTest::newRow("test_2")<<"8"<<10<<20<<"7,1153697208";
    QTest::newRow("test_3")<<"0,01"<<10<<20<<"5729,5786914673";
    QTest::newRow("test_4")<<"23,32"<<10<<20<<"2,3197447516";
    QTest::newRow("test_5")<<"-43"<<10<<20<<"-1,0723687104";
    QTest::newRow("test_6")<<"-1,123"<<10<<20<<"-51,0137509797";
    QTest::newRow("test_7")<<"-89"<<10<<20<<"-0,0174550649";
    QTest::newRow("test_8")<<"989"<<10<<20<<"0,0174550649";
    QTest::newRow("test_9")<<"-898"<<10<<20<<"28,6362532844";
}

void numbermath::test_mathCtng(){
    QFETCH(QString,num);
    QFETCH(int,div_acuracy);
    QFETCH(int,function_acuracy);
    QFETCH(QString,result);

    std::string curent_result=MathCtng(num.toStdString(),div_acuracy,function_acuracy,false);

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathFactorial_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"2";
    QTest::newRow("test_2")<<"12"<<"479001600";
    QTest::newRow("test_3")<<"20"<<"2432902008176640000";
    QTest::newRow("test_4")<<"6"<<"720";
    QTest::newRow("test_5")<<"-15"<<"dot or minus in num";
    QTest::newRow("test_6")<<"4,23"<<"dot or minus in num";
}

void numbermath::test_mathFactorial(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    std::string curent_result="";

    try{
        curent_result=MathFactorial(num.toStdString());
        QCOMPARE(curent_result,result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString().c_str());
    }
}

void numbermath::test_mathMod_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("mod_num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"5"<<"2";
    QTest::newRow("test_2")<<"12"<<"5"<<"2";
    QTest::newRow("test_3")<<"37"<<"1"<<"0";
    QTest::newRow("test_4")<<"1"<<"0"<<"1";
    QTest::newRow("test_5")<<"-12"<<"5"<<"3";
    QTest::newRow("test_6")<<"-28"<<"3"<<"2";
    QTest::newRow("test_7")<<"-12"<<"-5"<<"3";
    QTest::newRow("test_8")<<"-2"<<"1"<<"0";
}

void numbermath::test_mathMod(){
    QFETCH(QString,num);
    QFETCH(QString,mod_num);
    QFETCH(QString,result);

    std::string curent_result=MathMod(num.toStdString(),mod_num.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathModule_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"23"<<"23";
    QTest::newRow("test_2")<<"2,23"<<"2,23";
    QTest::newRow("test_3")<<"-12"<<"12";
    QTest::newRow("test_4")<<"16"<<"16";
    QTest::newRow("test_5")<<"-0,0001"<<"0,0001";
    QTest::newRow("test_6")<<"-999999"<<"999999";
}

void numbermath::test_mathModule(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    std::string curent_result=MathModule(num.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathRoundUp_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"2";
    QTest::newRow("test_2")<<"12"<<"12";
    QTest::newRow("test_3")<<"2,54"<<"3";
    QTest::newRow("test_4")<<"1,000009"<<"1";
    QTest::newRow("test_5")<<"-12,99"<<"-13";
    QTest::newRow("test_6")<<"-44"<<"-44";
    QTest::newRow("test_7")<<"23,49999"<<"23";
}

void numbermath::test_mathRoundUp(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    std::string curent_result=MathRoundUp(num.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

void numbermath::test_mathRoundDown_data(){
    QTest::addColumn<QString>("num");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"2"<<"2";
    QTest::newRow("test_2")<<"23"<<"23";
    QTest::newRow("test_3")<<"1,009"<<"1";
    QTest::newRow("test_4")<<"-12"<<"-12";
    QTest::newRow("test_5")<<"-4,666"<<"-4";
    QTest::newRow("test_6")<<"-0,01"<<"0";
    QTest::newRow("test_7")<<"0,01"<<"0";
}

void numbermath::test_mathRoundDown(){
    QFETCH(QString,num);
    QFETCH(QString,result);

    std::string curent_result=MathRoundDown(num.toStdString());

    QCOMPARE(curent_result,result.toStdString());
}

QTEST_APPLESS_MAIN(numbermath)

#include "tst_numbermath.moc"
