#ifndef TCPIPSERVER_H
#define TCPIPSERVER_H


#include <QTcpServer>

class tcpipserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpipserver(QObject *parent = nullptr);
    void startServer();
signals:

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // TCPIPSERVER_H
