
#include <QObject>
#include <QMediaRecorder>
#include <QAudioCaptureSource>
#include <mygpio.h>
#include <QMediaPlayer>

class recorder : public QObject
{
    Q_OBJECT
public:
    explicit recorder(QObject *parent = 0);

    void start_record();
    void stop_record();
    void play_record();

signals:


public slots:


private:

     QMediaRecorder  *_recorder;
     QMediaPlayer  *_player;

};


