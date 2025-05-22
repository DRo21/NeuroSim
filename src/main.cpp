/**
 * @file main.cpp
 * @brief Entry point for the NeuroSim Qt GUI application.
 * @author dro
 *
 * Initializes the QApplication, sets up the main window,
 * and starts the event loop.
 */

#include <QApplication>
#include "MainWindow.h"

/**
 * @brief Launches the NeuroSim simulation GUI.
 *
 * This function initializes the Qt application context and displays the main window.
 * 
 * @param argc Argument count from command line.
 * @param argv Argument vector from command line.
 * @return Exit status of the application.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
