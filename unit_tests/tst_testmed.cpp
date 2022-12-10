#include <QtTest>
#include "functions.h"
#include "database.h"


class testmed : public QObject
{
    Q_OBJECT

public:
    testmed();
    ~testmed();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void message_to_server_yes1();
    void message_to_server_yes2();
    void message_to_server_no();

};

testmed::testmed()
{
}

testmed::~testmed()
{
}

void testmed::initTestCase()
{
}

void testmed::cleanupTestCase()
{
}

void testmed::message_to_server_yes1()
{
    std::string log = "ivan";
    std::string pass = "Qwerty123!";
    QString result = authorize(log,pass);
    QVERIFY("authorization yes " == result);
}

void testmed::message_to_server_yes2()
{
    std::string log = "fedor";
    std::string pass = "Asdfg123!";
    QString result = authorize(log,pass);
    QVERIFY("authorization yes " == result);
}

void testmed::message_to_server_no()
{
    std::string log = "user";
    std::string pass = "12343424346";
    QString result = authorize(log,pass);
    QVERIFY("authorization error " == result);
}


QTEST_APPLESS_MAIN(testmed)

#include "tst_testmed.moc"
