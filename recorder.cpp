
#include "recorder.h"

recorder::recorder(QObject *parent) :
    QObject(parent)
{

}

void recorder::start_record()
{


    QAudioCaptureSource* audioSource;

    _recorder = new QMediaRecorder(audioSource);
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setQuality(QtMultimediaKit::HighQuality);

    _recorder->setEncodingSettings(audioSettings);
    _recorder->setOutputLocation(QUrl::fromLocalFile("/home/pi/test.wav"));
    _recorder->record();

    qDebug() << "recorder started";

}

void recorder::stop_record()
{
     _recorder->stop();
}

void recorder::play_record()
{
     _player = new QMediaPlayer();
     QUrl url = QUrl::fromLocalFile("/home/pi/test.wav");

     _player->setMedia(url);
     _player->setVolume(100);
     _player->play();
}
