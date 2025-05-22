#include <QtTest/QtTest>
#include "RasterPlotWidget.h"
#include "Simulation.h"

class TestRasterPlotWidget : public QObject {
    Q_OBJECT
private slots:
    void testSimulationAttachment();
};

void TestRasterPlotWidget::testSimulationAttachment() {
    RasterPlotWidget widget;
    Simulation sim(10, 10);
    widget.setSimulation(&sim);
    QVERIFY(true);  // Should attach without crash
}

QTEST_MAIN(TestRasterPlotWidget)
#include "test_rasterplotwidget.moc"
