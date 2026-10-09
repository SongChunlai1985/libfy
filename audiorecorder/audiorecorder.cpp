#include "audiorecorder.h"

AudioRecorder::AudioRecorder()
{

}

qint64 AudioRecorder::getProcessTime()
{
    qint64 processTime = getCurrentMSecsSinceEpoch() -  lastTime;
    lastTime = getCurrentMSecsSinceEpoch();
    return processTime;
}

void AudioRecorder::stateChanged()
{
    qDebug()<<__FUNCTION__<<"stateChanged.";
}

void AudioRecorder::notify()
{
    QByteArray buff = out_io->readAll();
    qint64 processTime = getProcessTime();
    totalTime += processTime;
    total ++;
    if(totalTime > 3000)
    {
        qDebug()<<__FUNCTION__<<"notifySize:"<<buff.size()<<"totalTime:"<<totalTime<<"totalNotify:"<<total<<(totalTime)*1.0/total<<"ms";
        //qDebug()<<buff.toHex();
        totalTime = 0;
        total = 0;
    }
    cv::Mat dataMat(SampleRate * frameT, 1, CV_16SC1, buff.data());
    //if(total == 0)qDebug()<<__FUNCTION__<<QByteArray((char*)dataMat.data, 100).toHex();
#if 1
    cv::Mat dataMat32fc1;
    dataMat.convertTo(dataMat32fc1, CV_32FC1);
    //if(total == 0)qDebug()<<__FUNCTION__<<QByteArray((char*)dataMat32fc1.data, 100).toHex();
    cv::Mat datadftMat32fc1;

    cv::dft(dataMat32fc1, datadftMat32fc1);

    cv::Mat datadftMat;
    datadftMat32fc1.convertTo(datadftMat, CV_8UC1);
#else
    cv::Mat datadftMat;
    dataMat.convertTo(datadftMat, CV_8UC1);
#endif
    //if(total == 0)qDebug()<<__FUNCTION__<<QByteArray((char*)datadftMat.data, 100).toHex();
    cv::Mat datadftMatSm;
    cv::resize(datadftMat, datadftMatSm, cv::Size(1, imageWidth));

    cv::Mat datadftMatSmFiltered;
    int dropOut = 160;
    datadftMatSmFiltered = datadftMatSm - dropOut;
    datadftMatSm = datadftMatSmFiltered * (256 / dropOut);
    cv::Mat datadftMatSmTablep(0, imageWidth, CV_8UC1);
    if(total == 0)qDebug()<<__FUNCTION__<<"data:"<<QByteArray((char*)datadftMatSm.data, 100).toHex()
                         <<"cols:"<<datadftMatSm.cols<<"rows:"<<datadftMatSm.rows
                         <<"tableCols:"<<datadftMatSmTablep.cols<<"tableRows:"<<datadftMatSmTablep.rows;
    datadftMatSmTablep.push_back(datadftMatSm.t());

    for (int i = 0; i < 29; ++i) {
        cv::Mat temp = datadftMatSmTable.row(i);
        datadftMatSmTablep.push_back(temp);
    }

    datadftMatSmTable = datadftMatSmTablep.clone();

    emit soundArrive(datadftMatSmTablep);
}

void AudioRecorder::start()
{
    format.setSampleRate(SampleRate);                                                              //设定声道数目，mono(平声道)的声道数目是1；stero(立体声)的声道数目是2
    format.setChannelCount(ChannelCount);
    format.setSampleSize(SampleSize);
    format.setCodec("audio/pcm");                                                                  //编码器
    format.setByteOrder(QAudioFormat::LittleEndian);                                               //设定高低位,LittleEndian（低位优先）,LargeEndian(高位优先)
    format.setSampleType(QAudioFormat::SignedInt);

    QAudio::Mode mode = QAudio::AudioInput;

    QList<QAudioDeviceInfo> audioDeviceInfos = QAudioDeviceInfo::availableDevices(mode);

    const QAudioDeviceInfo info = audioDeviceInfos[0];

    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    SampleRate   = format.sampleRate();
    ChannelCount = format.channelCount();
    SampleSize   = format.sampleSize();

    qDebug()<<__FUNCTION__<<"SampleRate"<<SampleRate<<"ChannelCount"<<ChannelCount<<"SampleSize"<<SampleSize;

    m_audioInput = new QAudioInput(info, format);

    m_audioInput->setNotifyInterval(30);
    m_audioInput->setBufferSize(SampleRate * frameT);                                              //必须写成0.03不可写成30/1000

    datadftMatSmTable  = cv::Mat(30, imageWidth, CV_8UC1);

    connect(m_audioInput, &QAudioInput::notify, this, &AudioRecorder::notify);
    connect(m_audioInput, &QAudioInput::stateChanged, this, &AudioRecorder::stateChanged);

    out_io = m_audioInput->start();
}

void AudioRecorder::stop()
{
    m_audioInput->stop();
}
