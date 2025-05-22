#include <QtTest/QtTest>
#include "TraceViewWidget.h"
#include "Simulation.h"

class TestTraceViewWidget : public QObject {
    Q_OBJECT
private slots:
    void testSimulationAttachment();
    void testNeuronSelection();
};

void TestTraceViewWidget::testSimulationAttachment() {
    TraceViewWidget widget;
    Simulation sim(4, 4);
    widget.setSimulation(&sim);
    QVERIFY(true);  // Should not crash
}

void TestTraceViewWidget::testNeuronSelection() {
    TraceViewWidget widget;
    widget.setNeuronIndex(5);
    QCOMPARE(widget.neuronIndex(), 5);
}

QTEST_MAIN(TestTraceViewWidget)
#include "test_traceviewwidget.moc"
