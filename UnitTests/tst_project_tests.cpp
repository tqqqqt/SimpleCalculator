#include <QtTest>

// add necessary includes here

class project_tests : public QObject
{
    Q_OBJECT

public:
    project_tests();
    ~project_tests();

private slots:
    void test_case1();

};

project_tests::project_tests()
{

}

project_tests::~project_tests()
{

}

void project_tests::test_case1()
{

}

QTEST_APPLESS_MAIN(project_tests)

#include "tst_project_tests.moc"
