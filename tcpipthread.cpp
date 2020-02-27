#include "tcpipthread.h"




tcpipthread::tcpipthread(qintptr ID, QString fileName, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;

    //QString fileNameDT ="/home/thihakyaw/Documents/qt/"+QDateTime::currentDateTime().toString("ddMMyyyy_") + "ehmu.txt";
    QString fileNameDT ="/media/pi/FBSG1/Chem/3010/"+QDateTime::currentDateTime().toString("ddMMyyyy_") + "ehmu10.txt";

    //QString fileNameDT ="ehmu.txt";
    m_showDate = true;
    if(!fileName.isEmpty())
    {
        file = new QFile();
        file->setFileName(fileNameDT);
        file->open(QIODevice::Append | QIODevice::Text);
    }


}

void tcpipthread::run()
{
    //Thread starts here
    qDebug() << " Thread started";
    socket = new QTcpSocket();


    //set the ID

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        //something's wrong, we just email a signal
        emit error(socket->error());
        return;
    }
    //connect socket and signal
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));

    //We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    //make this thread a loop
    //thread will stay alive so that signal/slot to function properly
    //not dropped out in the middle when thread dies
    exec();
}


void tcpipthread::readyRead()
{


    QByteArray Data = socket -> readAll();

    //will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;
    this->write(Data);


    //socket -> write(Data);
}

void tcpipthread::disconnected()
{

    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);

}

void tcpipthread::write(const QString &value)
{
    QString text = value;

    QTextStream out(file);
    out.setCodec("UTF-8");
    if(file !=0)
    {
        if(m_showDate)
        {
            if((text != "\n\r") || (text != "") )
            {
                text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh.mm.ss  ") + text;
                out << text << endl;
            }
        }
        else
        {
            out << text << endl;
        }


    }


}

tcpipthread::~tcpipthread()
{
    if(file != 0)
    {
        file->close();
    }
}


void tcpipthread::setShowDateTime(bool value)
{
    m_showDate = value;
}
