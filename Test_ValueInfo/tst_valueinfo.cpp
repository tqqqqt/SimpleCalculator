#include <QtTest>

#include "../Calculator/source/valueinfo.h"
#include <vector>
#include <string>

class valueinfo : public QObject
{
    Q_OBJECT

public:
    valueinfo();
    ~valueinfo();

private slots:
    void test_getMain();
    void test_getSecond_data();
    void test_getSecond();
    void test_getMullNum_data();
    void test_getMullNum();
};

valueinfo::valueinfo(){ }

valueinfo::~valueinfo(){ }

void valueinfo::test_getMain(){
    ValueInfo info_object;
    std::vector<std::string> temp=info_object.getMain();
    QVector<QString> result;
    result.reserve(temp.size());
    std::transform(temp.begin(),temp.end(),std::back_inserter(result),[](const std::string &x){ return QString::fromStdString(x); });
    QVector<QString> wait_result={"Площадь","Длина","Температура","Объем","Масса","Данные","Скорость","Время"};
    QCOMPARE(result,wait_result);
}

void valueinfo::test_getSecond_data(){
    QTest::addColumn<QString>("main");
    QTest::addColumn<QVector<QString>>("second");

    QTest::newRow("test_1")<<"Площадь"<<QVector<QString>{"Акры (ac)","Ары (a)","Гектары (ha)","Квадратные сантиметры (cm^2)","Квадратные футы (ft^2)","Квадратные дюймы (in^2)","Квадратные метры (m^2)"};
    QTest::newRow("test_2")<<"Длина"<<QVector<QString>{"Миллиметры (mm)","Сантиметры (cm)","Метры (m)","Километры (km)","Дюймы (in)","Футы (ft)","Ярды (yd)","Мили (mi)","Морские мили (NM)","Мили (mil)"};
    QTest::newRow("test_3")<<"Температура"<<QVector<QString>{"Градус Цельсия (C)","Градус Фарингейта (F)","Градус Кельвина (K)"};
    QTest::newRow("test_4")<<"Объем"<<QVector<QString>{"Английские галлоны (gal)","Американские галоны (gal)","Литры (l)","Миллилитры (ml)","Кубические сантиметры (cm^3)","Кубические метры (m^3)","Кубические дюймы (in^3)","Кубические футы (ft^3)"};
    QTest::newRow("test_5")<<"Масса"<<QVector<QString>{"Тонны (t)","Английский тонны (t)","Американские тонны (t)","Фунты (lb)","Унции (oz)","Килограммы (kg)","Граммы (g)"};
    QTest::newRow("test_6")<<"Данные"<<QVector<QString>{"Биты (bit)","Байты (B)","Килобайты (KB)","Мегабайты (MB)","Гигабайты (GB)","Терабайты (TB)"};
    QTest::newRow("test_7")<<"Скорость"<<QVector<QString>{"Метры в секунду (m/s)","Метры в час (m/h)","Километры в секунду (km/s)","Километры в час (km/h)","Дюймы в секунду (in/s)","Дюймы в час (in/h)","Футы в секунду (ft/s)","Футы в час (ft/h)","Мили в секунду (mi/s)","Мили в час (mi/h)","Узлы (kn)"};
    QTest::newRow("test_8")<<"Время"<<QVector<QString>{"Миллисекунды (ms)","Секунды (s)","Минуты (min)","Часы (h)","Дни (d)","Недели (wk)"};
}

void valueinfo::test_getSecond(){
    QFETCH(QString,main);
    QFETCH(QVector<QString>,second);

    ValueInfo info_object;
    std::vector<std::string> temp=info_object.getSecond(main.toStdString());
    QVector<QString> result;
    result.reserve(temp.size());
    std::transform(temp.begin(),temp.end(),std::back_inserter(result),[](const std::string &x){ return QString::fromStdString(x); });
    QCOMPARE(result,second);
}

void valueinfo::test_getMullNum_data(){
    QTest::addColumn<QString>("main");
    QTest::addColumn<QString>("left");
    QTest::addColumn<QString>("right");
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_1")<<"Площадь"<<"Ары (a)"<<"Квадратные футы (ft^2)"<<"1256"<<"1351947,14833874112192668760";
    QTest::newRow("test_2")<<"Площадь"<<"Квадратные дюймы (in^2)"<<"Квадратные сантиметры (cm^2)"<<"569"<<"3670,9604";
    QTest::newRow("test_3")<<"Длина"<<"Метры (m)"<<"Дюймы (in)"<<"8723"<<"343425,19685039370078739608";
    QTest::newRow("test_4")<<"Длина"<<"Ярды (yd)"<<"Сантиметры (cm)"<<"45236"<<"4136379,84";
    QTest::newRow("test_5")<<"Температура"<<"Градус Цельсия (C)"<<"Градус Фарингейта (F)"<<"47"<<"116,6";
    QTest::newRow("test_6")<<"Температура"<<"Градус Кельвина (K)"<<"Градус Фарингейта (F)"<<"986"<<"1315,13";
    QTest::newRow("test_7")<<"Объем"<<"Американские галоны (gal)"<<"Миллилитры (ml)"<<"457"<<"1729933,185288";
    QTest::newRow("test_8")<<"Объем"<<"Кубические метры (m^3)"<<"Английские галлоны (gal)"<<"23"<<"5059,29271087901911312790";
    QTest::newRow("test_9")<<"Масса"<<"Американские тонны (t)"<<"Унции (oz)"<<"536,236"<<"17159552,01513213462134042133368";
    QTest::newRow("test_10")<<"Масса"<<"Килограммы (kg)"<<"Тонны (t)"<<"25,1111"<<"0,0251111";
    QTest::newRow("test_11")<<"Данные"<<"Байты (B)"<<"Гигабайты (GB)"<<"65896"<<"0,00006137043237715952";
    QTest::newRow("test_12")<<"Данные"<<"Мегабайты (MB)"<<"Биты (bit)"<<"324,22"<<"2719754485,76";
    QTest::newRow("test_13")<<"Скорость"<<"Метры в час (m/h)"<<"Километры в час (km/h)"<<"452,22"<<"0,45222";
    QTest::newRow("test_14")<<"Скорость"<<"Футы в секунду (ft/s)"<<"Метры в секунду (m/s)"<<"1456"<<"443,78880000177515520000";
    QTest::newRow("test_15")<<"Время"<<"Минуты (min)"<<"Дни (d)"<<"4756"<<"3,30277777777777775664";
    QTest::newRow("test_16")<<"Время"<<"Недели (wk)"<<"Секунды (s)"<<"233"<<"140918400";
}

void valueinfo::test_getMullNum(){
    QFETCH(QString,main);
    QFETCH(QString,left);
    QFETCH(QString,right);
    QFETCH(QString,input);
    QFETCH(QString,result);

    ValueInfo info_object;
    QString mul_result=QString::fromStdString(info_object.getMullNum(main.toStdString(),left.toStdString(),right.toStdString(),input.toStdString()));
    QCOMPARE(mul_result,result);
}

QTEST_APPLESS_MAIN(valueinfo)

#include "tst_valueinfo.moc"
