#ifndef TCPIPTHREAD_H
#define TCPIPTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
class tcpipthread : public QThread
{
    Q_OBJECT
public:
    explicit tcpipthread(qintptr ID, QString fileName, QObject *parent = nullptr);
    ~tcpipthread();
    void run();
    void setShowDateTime(bool value);

signals:

    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
    void write(const QString &value);

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QFile *file;
    bool m_showDate;
};

#endif // TCPIPTHREAD_H
