#include <QString>
#include <QtTest>

#include "pixelcounter.h"

class HelloTestTest : public QObject
{
    Q_OBJECT

public:
    HelloTestTest();

private Q_SLOTS:
    void testPixelCount();
    void testPixelCount_data();
};

HelloTestTest::HelloTestTest()
{
}

void HelloTestTest::testPixelCount_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<int>("pixelcount");

    QTest::newRow("image") << "c:/dev/test.jpg" << 640*427;
}

void HelloTestTest::testPixelCount()
{
    PixelCounter c;
    QFETCH(QString, filename);
    QFETCH(int, pixelcount);
    QCOMPARE(c.countPixels(filename), pixelcount);

    QBENCHMARK
    {
        c.countPixels(filename);
    }
}

QTEST_APPLESS_MAIN(HelloTestTest)

#include "tst_hellotesttest.moc"
