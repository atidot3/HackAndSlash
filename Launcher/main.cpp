#include "QDownloader/QDownloader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath("./");
    QDownloader *down = new QDownloader();
    return a.exec();
}
