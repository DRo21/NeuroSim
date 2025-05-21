#include <QApplication>
#include "MainWindow.h"

/**
 * @brief Entry point for the NeuroSim Qt GUI application.
 *
 * This initializes the application and launches the main window.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
