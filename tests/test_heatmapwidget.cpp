#include <QtTest/QtTest>
#include "HeatmapWidget.h"
#include "Simulation.h"

class TestHeatmapWidget : public QObject {
    Q_OBJECT
private slots:
    void testSetSimulation();
    void testDisplayModeChange();
};

void TestHeatmapWidget::testSetSimulation() {
    HeatmapWidget widget;
    Simulation sim(5, 5);
    widget.setSimulation(&sim);
    QVERIFY(true);  // Should not crash
}

void TestHeatmapWidget::testDisplayModeChange() {
    HeatmapWidget widget;
    widget.setDisplayMode(HeatmapWidget::SpikeRate);
    QCOMPARE(widget.displayMode(), HeatmapWidget::SpikeRate);
}

QTEST_MAIN(TestHeatmapWidget)
#include "test_heatmapwidget.moc"
