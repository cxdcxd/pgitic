#include "mygpio.h"
#include <QDebug>

MyGpio::MyGpio(QObject *parent) :
    QObject(parent)
{
    info_mode = 0;
    state = false;
    mtimer = new QTimer();
    connect(mtimer, SIGNAL(timeout()), this, SLOT(update()));
    qDebug("GPIO START ");

    wiringPiSetup();
    pinMode(1,INPUT);

    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);

    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);

    mtimer->start(250);
}

bool f = false;
bool f2 = false;

void MyGpio::update()
{
    //10HZ pulling loop

    if ( info_mode == 1 )
    {

    int x = digitalRead(1);

    if ( x == 1)
    {
        //user press the push button
        digitalWrite(4,LOW);

        if ( state == false && f == false)
        {
            f = true;
            state = true;
        }
        if ( state == true && f == false)
        {
            f = true;
            state = false;
        }
    }
    else
    {
        f = false;
        digitalWrite(4,HIGH);
    }


    if ( state )
    {
         digitalWrite(5,LOW);
    }
    else
    {
         digitalWrite(5,HIGH);
    }

    }
    else
    {
        state = false;
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
    }

    if ( info_mode == 0 )
    {
        //conneting...
        if ( f2 )
        {
             digitalWrite(6,LOW);
        }
        else
        {
             digitalWrite(6,HIGH);
        }

        f2 = !f2;

    }
    else if ( info_mode == 1 )
    {
        digitalWrite(6,LOW);
    }
    else if ( info_mode == 2 )
    {
        state = false;
        digitalWrite(6,HIGH);
    }
}
