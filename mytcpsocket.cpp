#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{

}

MyGpio *gpiooo;

void MyTcpSocket::doConnect(MyGpio &xb)
{
    gpiooo = &xb;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    gpiooo->info_mode = 0;

    qDebug() << "connecting...";


    socket->connectToHost("192.168.16.100", 1234);


    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
        gpiooo->info_mode = 2;
    }

     gpiooo->info_mode = 1;
}

void MyTcpSocket::mainwrite(QByteArray buf, qint64 len)
{
    //QByteArray a;

    socket->write(buf.data(),len);
}

void MyTcpSocket::connected()
{
    qDebug() << "connected...";

    //socket->write("Hello From PGITIC rasberrypi :)");
}

void MyTcpSocket::disconnected()
{
   qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written... ";
}

void MyTcpSocket::readyRead()
{
    qDebug() << "reading...";
    qDebug() << socket->readAll();
}
