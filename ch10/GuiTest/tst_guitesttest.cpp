#include <QString>
#include <QtTest>
#include <QTestEventList>

#include "testableform.h"

class GuiTestTest : public QObject
{
    Q_OBJECT

public:
    GuiTestTest();

private Q_SLOTS:
    void testGui();
    void testGui_data();
};

GuiTestTest::GuiTestTest()
{
}

void GuiTestTest::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("result");

    QTestEventList mouseEvents; // three times
    mouseEvents.addMouseClick(Qt::LeftButton);
    mouseEvents.addMouseClick(Qt::LeftButton);
    mouseEvents.addMouseClick(Qt::LeftButton);
    QTest::newRow("mouse") << mouseEvents << "4";

    QTestEventList keybEvents; // four times
    keybEvents.addKeyClick(Qt::Key_Space);
    keybEvents.addDelay(250);
    keybEvents.addKeyClick(Qt::Key_Space);
    keybEvents.addDelay(250);
    keybEvents.addKeyClick(Qt::Key_Space);
    keybEvents.addDelay(250);
    keybEvents.addKeyClick(Qt::Key_Space);
    QTest::newRow("keyboard") << keybEvents << "8";
}

void GuiTestTest::testGui()
{
    TestableForm t;

    QFETCH(QTestEventList, events);
    QFETCH(QString, result);

    events.simulate(t.nextBtn);

    QCOMPARE(t.infoLabel->text(), result);
}

QTEST_MAIN(GuiTestTest)

#include "tst_guitesttest.moc"
