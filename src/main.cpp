#include "DicomMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    DicomMainWindow w;
    w.setWindowTitle("DICOM");
    w.show();
    return a.exec();
}
