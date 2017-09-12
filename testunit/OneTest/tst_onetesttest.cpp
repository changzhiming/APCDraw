#include <QString>
#include <QtTest>

class OneTestTest : public QObject
{
    Q_OBJECT

public:
    OneTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

OneTestTest::OneTestTest()
{
}

void OneTestTest::initTestCase()
{
}

void OneTestTest::cleanupTestCase()
{
}

void OneTestTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void OneTestTest::testCase1()
{
    QFETCH(QString, data);
    QBENCHMARK {
    }
}

QTEST_MAIN(OneTestTest)

#include "tst_onetesttest.moc"
