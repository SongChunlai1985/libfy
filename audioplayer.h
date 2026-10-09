#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include <QAudioOutput>
#include <QObject>
#include <QAudioInput>

class audioplayer: public QObject
{
    Q_OBJECT

public:
    audioplayer();
    QAudioInput* audioInput;
    QIODevice* streamIn;

    QAudioOutput* audioOutput;
    QIODevice* streamOut;
};

#endif // AUDIOPLAYER_H
