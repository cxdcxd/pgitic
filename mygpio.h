#ifndef MYGPIO_H
#define MYGPIO_H

#include <QObject>
#include <QTimer>
#include "wiringPi.h"

class MyGpio : public QObject
{
    Q_OBJECT
public:
    explicit MyGpio(QObject *parent = 0);
    QTimer *mtimer;
    bool state;
    int info_mode;


signals:
    
public slots:
     void update();
    
};

#endif // MYGPIO_H
