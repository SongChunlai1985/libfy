#include <QCoreApplication>
#include "mw.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    mw mwt;
    return a.exec();
}
