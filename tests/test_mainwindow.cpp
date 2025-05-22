#include <QtTest/QtTest>
#include "MainWindow.h"

class TestMainWindow : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testStartStop();
};

void TestMainWindow::testConstruction() {
    MainWindow window;
    QVERIFY(window.findChild<QWidget*>("ControlPanelWidget") != nullptr);
}

void TestMainWindow::testStartStop() {
    MainWindow window;
    window.show();
    QTest::qWait(50);
    window.onStartSimulation();
    QTest::qWait(10);
    window.onStopSimulation();
    QVERIFY(true);  // If no crash, it's fine
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
