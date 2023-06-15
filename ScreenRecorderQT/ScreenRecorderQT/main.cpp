#include <QApplication>
#include <QProcess>
#include "mainwindow.h"


void requestScreenCapturePermission()
{
    QProcess process;
    QString command = "screencapture -l -p /dev/null";

    process.start(command);
    process.waitForFinished();

    int exitCode = process.exitCode();

    if (exitCode != 0) {
        QMessageBox::warning(nullptr, "Permission Denied",
            "Failed to request screen capture permission.");
    }
}


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QMessageBox errorDialog;
    try {
        MainWindow w;
        requestScreenCapturePermission();
        w.show();
        return a.exec();
    } catch (const std::exception& e) {
        // Call to open the error dialog
        std::string message = e.what();
        message += "\nPlease close and restart the application";
        errorDialog.critical(0, "Error", QString::fromStdString(message));
    }
}
