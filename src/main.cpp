#include <QApplication>
#include "MainWindow.h"

/**
 * @brief Entry point of the application.
 * 
 * Initializes the QApplication, creates and shows the main window.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
