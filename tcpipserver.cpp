#include "tcpipserver.h"
#include "tcpipthread.h"
tcpipserver::tcpipserver(QObject *parent) : QTcpServer(parent)
{

}

void tcpipserver::startServer()
{
    int port = 3010;
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port" << port << "...";
    }
}

void tcpipserver::incomingConnection(qintptr socketDescriptor)
{
    //we have a new connection
    qDebug() << socketDescriptor << " Connecting ...";
    QString fileName = "test.txt";
    //Every new connection will be run in a newly created thread

    tcpipthread *tcpthread = new tcpipthread(socketDescriptor,fileName, this);

    connect(tcpthread, SIGNAL(finished()), tcpthread, SLOT(deleteLater()));

    tcpthread -> start();
}


