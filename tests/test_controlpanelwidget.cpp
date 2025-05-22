#include <QTest>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <QSignalSpy>

#include "ControlPanelWidget.h"

class TestControlPanelWidget : public QObject {
    Q_OBJECT
private slots:
    void testDefaults();
    void testSignalEmissions();
};

void TestControlPanelWidget::testDefaults() {
    ControlPanelWidget panel;
    QCOMPARE(panel.findChild<QPushButton*>("startButton") != nullptr, true);
    QCOMPARE(panel.findChild<QSpinBox*>("gridSizeSpinBoxX") != nullptr, true);
}

void TestControlPanelWidget::testSignalEmissions() {
    ControlPanelWidget panel;
    QSignalSpy spy(&panel, SIGNAL(startSimulation()));

    auto startBtn = panel.findChild<QPushButton*>("startButton");
    QVERIFY(startBtn != nullptr);
    QTest::mouseClick(startBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(TestControlPanelWidget)
#include "test_controlpanelwidget.moc"
