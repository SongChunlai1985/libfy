#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudio>
#include <QAudioInput>
#include <QIODevice>
#include <QDebug>
#include <QEventLoop>
#include <base/base.h>
class AudioRecorder: public QObject
{
    Q_OBJECT

signals:
    void Stop();
    void soundArrive(cv::Mat &datadftMatSm);
public:
    AudioRecorder();
    QAudioInput *m_audioInput;
    QScopedPointer<QIODevice> m_audioInfo;
    const QAudioDeviceInfo info;
    QAudioFormat format;
    QIODevice *out_io;
    qint64 lastTime;
    qint64 totalTime = 0;

    int SampleRate = 4800;
    int ChannelCount = 1;
    int SampleSize = 16;
    double frameT = 0.03;                                                                          //s

    int imageWidth = 512/*241*/;

    int total = 0;
    int runonce = 1;
    void start();
    void stop();
    void stateChanged();
    cv::Mat datadftMatSmTable;
    void notify();
    qint64 getProcessTime();
};

#endif // AUDIORECORDER_H
