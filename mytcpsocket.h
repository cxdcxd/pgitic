#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <mygpio.h>



class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = 0);
    
    void doConnect(MyGpio &xb);
    void mainwrite(QByteArray buf,qint64 len);

signals:

    
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();


private:
    QTcpSocket *socket;
    
};

#endif // MYTCPSOCKET_H
