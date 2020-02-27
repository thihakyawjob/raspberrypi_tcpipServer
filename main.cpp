#include <QCoreApplication>
#include "tcpipserver.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcpipserver tcpserver;

    tcpserver.startServer();


    return a.exec();
}
