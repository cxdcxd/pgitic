/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <QDateTime>
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <qendian.h>

#include "audioin.h"
#include "audioout.h"
#include "mytcpsocket.h"
#include "mygpio.h"


#define PUSH_MODE_LABEL "Enable push mode"
#define PULL_MODE_LABEL "Enable pull mode"
#define SUSPEND_LABEL   "Suspend recording"
#define RESUME_LABEL    "Resume recording"

const int BufferSize = 4096;
AudioTest *outputt;
MyTcpSocket *tcpsockett;
MyGpio *gpioo;
recorder *recorder_ref;

InputTest::InputTest()
    :
        m_device(QAudioDeviceInfo::defaultInputDevice())
    ,   m_audioInput(0)
    ,   m_input(0)
    ,   m_pullMode(false)
    ,   m_buffer(BufferSize, 0)
{

}

InputTest::~InputTest() {}

void InputTest::initializeAudio(AudioTest &x,MyTcpSocket &x2,MyGpio &x3,recorder &x4)
{
    m_format.setSampleRate(48000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(m_format))
    {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    //m_audioInfo  = new AudioInfo(m_format, this);

    outputt = &x;
    tcpsockett = &x2;
    gpioo = &x3;
    recorder_ref = &x4;

    createAudioInput();
}

bool direct = true;

void InputTest::createAudioInput()
{
    qDebug("INPUTSTART 1");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    m_audioInput = new QAudioInput(m_device, m_format, this);
    m_input = m_audioInput->start();

    //outputt->m_audioOutput->start(m_input);
    //outputt->m_output = outputt->m_audioOutput->start();

    //qDebug() << "Size " << outputt->m_audioOutput->periodSize();
    // qDebug() << "Buffer Size" << outputt->m_audioOutput->bufferSize();
    //connect(m_input, SIGNAL(readyRead()), SLOT(readMore()),Qt::DirectConnection);

    qDebug("INPUTSTART 2");
    timer->start(1);
}
int dum = 0;
void InputTest::update()
{


    //qint64 len = m_audioInput->bytesReady();
    qint64 l = m_input->read(m_buffer.data(), 1920);
    if ( l > 0 )
    {
         dum++;
         if ( dum == 1000 )
         {
            recorder_ref->stop_record();
              qDebug() << "STOP " << l;
         }
       // outputt->m_output->write(m_buffer.data(), l);
       // qDebug() << "Sended Done " << l;
       // qDebug() << gpioo->state ;
         else
         {
              qDebug() << dum << l;
         }


//        if ( gpioo->state )
//        {
//         tcpsockett->mainwrite(m_buffer, l);
//
//        }
    }

}

//void InputTest::readMore()
//{

//    //Check the number of samples in input buffer
//    qint64 len = m_audioInput->bytesReady();
//    qDebug() << "Read done " << len;

//    return;
//    //Limit sample size
//   // if(len > 4096)
//    //    len = 4096;
//    //Read sound samples from input device to buffer
//    qint64 l = m_input->read(m_buffer.data(), len);
//    if(l > 0)
//    {
//        //Assign sound samples to short array
//        short* resultingData = (short*)m_buffer.data();


//        short *outdata=resultingData;
//        outdata[ 0 ] = resultingData [ 0 ];

////        int iIndex;
////        for ( iIndex=1; iIndex < len; iIndex++ )
////        {
////            outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
////        }


//        tcpsockett->mainwrite((char*)outdata, len);

//        qDebug() << "Read done " << len;
//    }


//}

void InputTest::toggleMode()
{
    // Change bewteen pull and push modes
    //    if (m_pullMode) {
    //        m_modeButton->setText(tr(PULL_MODE_LABEL));
    //        m_pullMode = false;
    //    } else {
    //        m_modeButton->setText(tr(PUSH_MODE_LABEL));
    //        m_pullMode = true;
    //        m_audioInput->start(m_audioInfo);
    //    }
    //m_suspendResumeButton->setText(tr(SUSPEND_LABEL));
}

void InputTest::toggleSuspend()
{
    //    // toggle suspend/resume
    //    if (m_audioInput->state() == QAudio::SuspendedState) {
    //        m_audioInput->resume();
    //        m_suspendResumeButton->setText(tr(SUSPEND_LABEL));
    //    } else if (m_audioInput->state() == QAudio::ActiveState) {
    //        m_audioInput->suspend();
    //        m_suspendResumeButton->setText(tr(RESUME_LABEL));
    //    } else if (m_audioInput->state() == QAudio::StoppedState) {
    //        m_audioInput->resume();
    //        m_suspendResumeButton->setText(tr(SUSPEND_LABEL));
    //    } else if (m_audioInput->state() == QAudio::IdleState) {
    //        // no-op
    //    }
}

void InputTest::refreshDisplay()
{

}

void InputTest::deviceChanged(int index)
{
    m_audioInput->stop();
    m_audioInput->disconnect(this);
    delete m_audioInput;
    createAudioInput();
}


