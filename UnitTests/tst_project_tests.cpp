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
    void test_polish_entry1();
    void test_polish_entry2();

};

project_tests::project_tests()
{

}

project_tests::~project_tests()
{

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
