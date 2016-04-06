//PGITIC CO
//Project Started : 1394/1/29
//TCP/IP BASED DIGITAL MICROPHONE
//EDWIN BABAIANS - edwin.babaians@gmail.com

//0.1 => project start
//0.2 => add TCP/IP library
//0.3 => add Audio/IN Audio/OUT
//0.4 => add wiringPi GPIO library

#include <QCoreApplication>
#include <QTimer>
#include <mytcpsocket.h>
#include "audioin.h"
#include "audioout.h"
#include "mygpio.h"


InputTest *input;
AudioTest *output;
MyTcpSocket *tcpsocket;
MyGpio *gpio;
recorder *recorder_center;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    gpio = new MyGpio();

    //tcpsocket = new MyTcpSocket();
    //tcpsocket->doConnect(*gpio);

    qDebug("PGITIC CORE CONTROLLER STARTED DONE - (version 95-1-15) ");

    input = new InputTest();
    output = new AudioTest();
    recorder_center = new recorder();

    output->initializeAudio();
    input->initializeAudio(*output,*tcpsocket,*gpio,*recorder_center);

    gpio->info_mode = 1;

    recorder_center->start_record();



    return a.exec();
}
