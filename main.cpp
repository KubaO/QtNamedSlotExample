#include <QtCore/QCoreApplication>
#include "example.h"


int main (int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    Example x;

    return a.exec();

}
