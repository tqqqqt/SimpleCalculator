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
    void test_getSecond_time();

    void test_getMullNum_time_dot_num();
    void test_getMullNum_data_no_dot();
    void test_getMullNum_temperature();
};

valueinfo::valueinfo(){ }
valueinfo::~valueinfo(){ }

void valueinfo::test_getSecond_time(){
    ValueInfo info_object;
    QVector<QString> result={"Миллисекунды (ms)","Секунды (s)","Минуты (min)","Часы (h)","Дни (d)","Недели (wk)"}, curent_result;
    std::vector<std::string> temp;

    temp=info_object.getSecond("Время");
    std::transform(temp.begin(),temp.end(),std::back_inserter(curent_result),[](const std::string& x){ return QString::fromStdString(x); });

    QCOMPARE(curent_result,result);
}

void valueinfo::test_getMullNum_time_dot_num(){
    ValueInfo object;
    QString result="580,8", curent_result="";

    curent_result=QString::fromStdString(object.getMullNum("Время","Дни (d)","Часы (h)","24,2"));

    QCOMPARE(curent_result,result);
}

void valueinfo::test_getMullNum_data_no_dot(){
    ValueInfo object;
    QString result="2048", curent_result="";

    curent_result=QString::fromStdString(object.getMullNum("Данные","Гигабайты (GB)","Мегабайты (MB)","2"));

    QCOMPARE(curent_result,result);
}

void valueinfo::test_getMullNum_temperature(){
    ValueInfo object;
    QString result="125", curent_result="";

    curent_result=QString::fromStdString(object.getMullNum("Температура","Градус Фарингейта (F)","Градус Цельсия (C)","257"));

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(valueinfo)

#include "tst_valueinfo.moc"
