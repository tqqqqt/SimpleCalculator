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
    for(const char& x:input) object.addNum(x);
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
    for(const char& x:input) object.addNum(x);
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
    for(const char& x:input) object.addNum(x);
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
    for(const char& x:input) object.addNum(x);
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
    for(const char& x:input) object.addNum(x);
    QCOMPARE(object.toString(),result.toStdString());
}

void programmistobject::test_getLength_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<int>("result");

    QTest::newRow("test_1")<<2<<QVector<char>{'1','0','0','1'}<<4;
    QTest::newRow("test_2")<<2<<QVector<char>{'0','1','1','1'}<<3;
    QTest::newRow("test_3")<<8<<QVector<char>{'7','2','2'}<<3;
    QTest::newRow("test_4")<<8<<QVector<char>{'0','0','2','2','6'}<<3;
    QTest::newRow("test_5")<<10<<QVector<char>{'1','9','8','2'}<<4;
    QTest::newRow("test_6")<<10<<QVector<char>{'0','0','0','2','3','4'}<<3;
    QTest::newRow("test_7")<<16<<QVector<char>{'A','B','2'}<<3;
    QTest::newRow("test_8")<<16<<QVector<char>{'0','A','2'}<<2;
}

void programmistobject::test_getLength(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(int,result);

    ProgrammistObject object;
    object.changeSystem(system);
    for(const char& x:input) object.addNum(x);
    QCOMPARE(object.getLength(),static_cast<size_t>(result));
}

void programmistobject::test_addNum_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<char>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<2<<'0'<<"0";
    QTest::newRow("test_2")<<2<<'1'<<"1";
    QTest::newRow("test_3")<<2<<'2'<<"incorect num to 2 system";
    QTest::newRow("test_4")<<2<<'A'<<"incorect num to 2 system";
    QTest::newRow("test_5")<<8<<'1'<<"1";
    QTest::newRow("test_6")<<8<<'4'<<"4";
    QTest::newRow("test_7")<<8<<'7'<<"7";
    QTest::newRow("test_8")<<8<<'8'<<"incorect num to 8 system";
    QTest::newRow("test_9")<<8<<'9'<<"incorect num to 8 system";
    QTest::newRow("test_10")<<8<<'A'<<"incorect num to 8 system";
    QTest::newRow("test_11")<<10<<'1'<<"1";
    QTest::newRow("test_12")<<10<<'6'<<"6";
    QTest::newRow("test_13")<<10<<'9'<<"9";
    QTest::newRow("test_14")<<10<<'0'<<"0";
    QTest::newRow("test_15")<<10<<'B'<<"incorect num to 10 system";
    QTest::newRow("test_16")<<10<<'E'<<"incorect num to 10 system";
    QTest::newRow("test_17")<<16<<'0'<<"0";
    QTest::newRow("test_18")<<16<<'4'<<"4";
    QTest::newRow("test_19")<<16<<'8'<<"8";
    QTest::newRow("test_20")<<16<<'A'<<"A";
    QTest::newRow("test_21")<<16<<'E'<<"E";
    QTest::newRow("test_22")<<16<<'z'<<"incorect num to 16 system";
}

void programmistobject::test_addNum(){
    QFETCH(int,system);
    QFETCH(char,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(system);
    try{
        object.addNum(input);
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void programmistobject::test_addMinus_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result_16");
    QTest::addColumn<QString>("result_10");
    QTest::addColumn<QString>("result_8");
    QTest::addColumn<QString>("result_2");

    QTest::newRow("test_1")<<10<<QVector<char>{'2','3','4'}<<"FF16"<<"-234"<<"177426"<<"1111111100010110";
    QTest::newRow("test_2")<<10<<QVector<char>{'4','4','3'}<<"FE45"<<"-443"<<"177105"<<"1111111001000101";
    QTest::newRow("test_3")<<10<<QVector<char>{'1'}<<"FFFF"<<"-1"<<"177777"<<"1111111111111111";
    QTest::newRow("test_4")<<16<<QVector<char>{'2','F'}<<"FFD1"<<"-47"<<"177721"<<"1111111111010001";
    QTest::newRow("test_5")<<8<<QVector<char>{'1','7'}<<"FFF1"<<"-15"<<"177761"<<"1111111111110001";
    QTest::newRow("test_6")<<2<<QVector<char>{'1','0','0'}<<"FFFC"<<"-4"<<"177774"<<"1111111111111100";
}

void programmistobject::test_addMinus(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(QString,result_16);
    QFETCH(QString,result_10);
    QFETCH(QString,result_8);
    QFETCH(QString,result_2);

    ProgrammistObject object;
    object.setCount(4);
    object.changeSystem(system);
    for(const char& x:input) object.addNum(x);
    object.addMinus();
    QCOMPARE(object.toString16(),result_16.toStdString());
    QCOMPARE(object.toString10(),result_10.toStdString());
    QCOMPARE(object.toString8(),result_8.toStdString());
    QCOMPARE(object.toString2(),result_2.toStdString());
}

void programmistobject::test_deleteLastSymbol_data(){
    QTest::addColumn<int>("input_system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<int>("delete_system");
    QTest::addColumn<QString>("result_16");
    QTest::addColumn<QString>("result_10");
    QTest::addColumn<QString>("result_8");
    QTest::addColumn<QString>("result_2");

    QTest::newRow("test_1")<<10<<QVector<char>{'2','3','4'}<<10<<"17"<<"23"<<"27"<<"10111";
    QTest::newRow("test_2")<<16<<QVector<char>{'1','2','3'}<<10<<"1D"<<"29"<<"35"<<"11101";
    QTest::newRow("test_3")<<8<<QVector<char>{'6','6'}<<2<<"1B"<<"27"<<"33"<<"11011";
    QTest::newRow("test_4")<<2<<QVector<char>{'1','1','1','1','0','0'}<<10<<"6"<<"6"<<"6"<<"110";
}

void programmistobject::test_deleteLastSymbol(){
    QFETCH(int,input_system);
    QFETCH(QVector<char>,input);
    QFETCH(int,delete_system);
    QFETCH(QString,result_16);
    QFETCH(QString,result_10);
    QFETCH(QString,result_8);
    QFETCH(QString,result_2);

    ProgrammistObject object;
    object.changeSystem(input_system);
    for(const char& x:input) object.addNum(x);
    object.changeSystem(delete_system);
    object.deleteLastSymbol();
    QCOMPARE(object.toString16(),result_16.toStdString());
    QCOMPARE(object.toString10(),result_10.toStdString());
    QCOMPARE(object.toString8(),result_8.toStdString());
    QCOMPARE(object.toString2(),result_2.toStdString());
}

void programmistobject::test_changeSystem_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<2<<"";
    QTest::newRow("test_2")<<8<<"";
    QTest::newRow("test_3")<<10<<"";
    QTest::newRow("test_4")<<16<<"";
    QTest::newRow("test_5")<<3<<"incorect system";
    QTest::newRow("test_6")<<99<<"incorect system";
}

void programmistobject::test_changeSystem(){
    QFETCH(int,system);
    QFETCH(QString,result);

    ProgrammistObject object;
    try{
        object.changeSystem(system);
        QCOMPARE(object.toString(),result.toStdString());
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.toStdString());
    }
}

void programmistobject::test_clear_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<16<<QVector<char>{'7','A'}<<"";
    QTest::newRow("test_2")<<10<<QVector<char>{'1','2','3'}<<"";
    QTest::newRow("test_3")<<8<<QVector<char>{'7','7'}<<"";
    QTest::newRow("test_4")<<2<<QVector<char>{'1','0','1','1','0'}<<"";
}

void programmistobject::test_clear(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(QString,result);

    ProgrammistObject object;
    object.changeSystem(system);
    for(const char& x:input) object.addNum(x);
    object.clear();
    QCOMPARE(object.toString16(),result.toStdString());
    QCOMPARE(object.toString10(),result.toStdString());
    QCOMPARE(object.toString8(),result.toStdString());
    QCOMPARE(object.toString2(),result.toStdString());
}

void programmistobject::test_moveLeft_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result_16");
    QTest::addColumn<QString>("result_10");
    QTest::addColumn<QString>("result_8");
    QTest::addColumn<QString>("result_2");

    QTest::newRow("test_1")<<16<<QVector<char>{'F','2'}<<"1E4"<<"484"<<"744"<<"111100100";
    QTest::newRow("test_2")<<10<<QVector<char>{'2','3','4'}<<"1D4"<<"468"<<"724"<<"111010100";
    QTest::newRow("test_3")<<8<<QVector<char>{'6','2','2','2'}<<"1924"<<"6436"<<"14444"<<"1100100100100";
    QTest::newRow("test_4")<<2<<QVector<char>{'1','0','0'}<<"8"<<"8"<<"10"<<"1000";
    QTest::newRow("test_5")<<10<<QVector<char>{}<<""<<""<<""<<"";
    QTest::newRow("test_6")<<16<<QVector<char>{'F','F','F','F'}<<"FFFF"<<"-1"<<"177777"<<"1111111111111111";
}

void programmistobject::test_moveLeft(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(QString,result_16);
    QFETCH(QString,result_10);
    QFETCH(QString,result_8);
    QFETCH(QString,result_2);

    ProgrammistObject object;
    object.changeSystem(system);
    object.setCount(4);
    for(const char& x:input) object.addNum(x);
    object.moveLeft();
    QCOMPARE(object.toString16(),result_16.toStdString());
    QCOMPARE(object.toString10(),result_10.toStdString());
    QCOMPARE(object.toString8(),result_8.toStdString());
    QCOMPARE(object.toString2(),result_2.toStdString());
}

void programmistobject::test_moveRight_data(){
    QTest::addColumn<int>("system");
    QTest::addColumn<QVector<char>>("input");
    QTest::addColumn<QString>("result_16");
    QTest::addColumn<QString>("result_10");
    QTest::addColumn<QString>("result_8");
    QTest::addColumn<QString>("result_2");

    QTest::newRow("test_1")<<16<<QVector<char>{'F','2'}<<"79"<<"121"<<"171"<<"1111001";
    QTest::newRow("test_2")<<10<<QVector<char>{'2','3','4'}<<"75"<<"117"<<"165"<<"1110101";
    QTest::newRow("test_3")<<8<<QVector<char>{'6','2','2','2'}<<"649"<<"1609"<<"3111"<<"11001001001";
    QTest::newRow("test_4")<<2<<QVector<char>{'1','0','0','0','0','1'}<<"10"<<"16"<<"20"<<"10000";
    QTest::newRow("test_5")<<10<<QVector<char>{}<<""<<""<<""<<"";
    QTest::newRow("test_6")<<16<<QVector<char>{'F','F','F','F'}<<"7FFF"<<"32767"<<"77777"<<"111111111111111";
}

void programmistobject::test_moveRight(){
    QFETCH(int,system);
    QFETCH(QVector<char>,input);
    QFETCH(QString,result_16);
    QFETCH(QString,result_10);
    QFETCH(QString,result_8);
    QFETCH(QString,result_2);

    ProgrammistObject object;
    object.changeSystem(system);
    object.setCount(4);
    for(const char& x:input) object.addNum(x);
    object.moveRight();
    QCOMPARE(object.toString16(),result_16.toStdString());
    QCOMPARE(object.toString10(),result_10.toStdString());
    QCOMPARE(object.toString8(),result_8.toStdString());
    QCOMPARE(object.toString2(),result_2.toStdString());
}

QTEST_APPLESS_MAIN(programmistobject)

#include "tst_programmistobject.moc"
